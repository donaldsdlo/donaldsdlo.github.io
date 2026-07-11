---
title: "Windows 系统 Emacs 中的中文输入法切换"
author: ["Donald Lo"]
date: 2026-07-11
lastmod: 2026-07-11T11:17:00+08:00
tags: ["windows", "Emacs", "输入法"]
draft: false
---

<div class="ox-hugo-toc toc">

<div class="heading">&#30446;&#24405;</div>

- [问题在哪](#问题在哪)
- [解决方案](#解决方案)
    - [PowerToy 键位映射](#powertoy-键位映射)
    - [rimel + Rime，让 Emacs 拿回控制权](#rimel-plus-rime-让-emacs-拿回控制权)

</div>
<!--endtoc-->



## 问题在哪 {#问题在哪}

在 Windows 上用 Emacs + Evil 切中文输入法，体验烂。系统快捷键 `Win+Space` 切换中英文，多数时候管用，但一进 Emacs 就卡——从 Insert 模式按 `ESC` 回 Normal，想敲 `jj` 翻行，输入法还挂在中文上，打出来的是"健健"。

多数人以为这是快捷键冲突。改个键位就好了。

不是。烂在控制权不在你手里。

"快捷键冲突"这个诊断有个前提：输入法归系统管，Emacs 只是调用者。系统说切就切，Emacs 没有发言权。这个前提在浏览器里不成立——你切到中文，光标进地址栏自动变英文，回页面又切回来。浏览器劫了控制权，按场景调度，所以你不觉得卡。

Emacs 没劫。它老老实实问系统："现在什么状态？"系统说中文，Emacs 就信。

这不是键位冲突。这是两个调度器在抢总线，Emacs 每次都让步。

**为什么让步？** Emacs 的输入法模型是 1990 年代设计的。那个年代，输入法是"选一个，挂着，用完关掉"，一种状态全局生效。但 2026 年的 Windows 不是这样——系统的输入法是 per-window 的，每个应用有自己的语言状态。Emacs 内部有二十个 buffer，代码要英文，笔记要中文，org 的 src block 要英文、外面要中文——它比系统更清楚自己该用什么语言，但它没告诉系统。

一个更懂调度的人，沉默地让一个更不懂的人做决策。结果就是你每次切模式，都得手动同步状态。

输入法状态应该跟什么绑定？系统绑了窗口，太粗。Emacs 绑了 `toggle-input-method` 命令，太手动。正确的绑定对象是  **编辑上下文** ：代码区 → 英文，注释区 → 中文，minibuffer → 英文，org src block → 英文、block 外 → 跟上次一致，Normal 模式 → 英文，Insert 模式 → 跟上次一致。

这不是"自动切换"，是"状态随上下文迁移"——跟 CPU 上下文切换一样，从用户态切到内核态，寄存器自动保存恢复，不需要你手动 push。


## 解决方案 {#解决方案}

-   使用 PowerToy 来统一快捷键来切换输入法
-   在 Emacs 中使用 Rimel package 来使用自然码输入法（带辅助码）


### PowerToy 键位映射 {#powertoy-键位映射}

用 PowerToy 的 Keyboard Manager，在 Emacs 窗口中将 `Win+Space` 重映射为 `Ctrl+\` （Emacs 默认的 `toggle-input-method` 快捷键），其他应用保持系统行为不变。

{{< figure src="/content-org/windows/chinese-input-method-switching-in-emacs-on-windows.org/2026-07-11_09-21-08_screenshot.png" width="90%" >}}

{{< figure src="/content-org/windows/chinese-input-method-switching-in-emacs-on-windows.org/2026-07-11_09-21-30_screenshot.png" width="90%" >}}

{{< figure src="/content-org/windows/chinese-input-method-switching-in-emacs-on-windows.org/2026-07-11_09-21-56_screenshot.png" width="90%" >}}

{{< figure src="/content-org/windows/chinese-input-method-switching-in-emacs-on-windows.org/2026-07-11_09-22-39_screenshot.png" width="90%" >}}

这条路解决的是"键位层面"，调度逻辑没变——你还是在手动切换，只是换了个手指组合。适合不想动 Emacs 配置的场景。


### rimel + Rime，让 Emacs 拿回控制权 {#rimel-plus-rime-让-emacs-拿回控制权}

rimel 包在 Emacs 内部运行 Rime 输入法，绕开系统的输入法调度。关键在于 `rimel-disable-predicates` ——这就是一张上下文→输入法状态的映射表。 `rimel-predicate-prog-in-code-p` 说：在代码里，别激活； `rimel-predicate-current-uppercase-letter-p` 说：大写字母后面，别激活。状态随上下文自动迁移，不需要你手动切。

```emacs-lisp
(use-package rimel
    :init
    (setq liberime-module-file (expand-file-name (concat "bin/liberime-core" (pcase system-type ('windows-nt ".dll") ('darwin ".dylib") (_ ".so"))) user-emacs-directory))
    (setq default-input-method "rimel")
    :custom
    (liberime-shared-data-dir +rime-shared-data-dir)
    (liberime-user-data-dir +rime-user-data-dir)
    ;; (liberime-user-data-dir "~/rime")

    ;; Recommended config: code area + after letter + uppercase letter
    (rimel-disable-predicates
        '(rimel-predicate-prog-in-code-p
             ;; rimel-predicate-after-alphabet-char-p
             rimel-predicate-current-uppercase-letter-p)
        ;; Optional: display candidates via posframe (defaults to posframe if installed)
        (rimel-show-candidate 'posframe))
    :config
    (defun rimel-activate (_name)
        "Activate rimel input method.
Called by Emacs when user selects the \"rimel\" input method.
_NAME is the input method name (unused)."
        (unless (liberime-workable-p)
            (liberime-load))
        (when (and rimel-schema
                  (liberime-workable-p)
                  (not (string= rimel-schema liberime-current-schema)))
            (liberime-try-select-schema rimel-schema))
        (setq-local input-method-function #'rimel-input-method)
        (setq-local deactivate-current-input-method-function #'rimel-deactivate))
    (defun my/rimel-predicate-org-in-src-block-p ()
        "Return non-nil when point is inside an Org source block."
        (and (derived-mode-p 'org-mode)
            (fboundp 'org-in-src-block-p)
            (save-match-data (setq element (org-element-at-point)))
            (when (org-element-type-p element 'src-block)
                (not (or (<= (line-beginning-position)
                                 (org-element-post-affiliated element))
                             (>= (line-end-position)
                             (org-with-point-at (org-element-end element)
                                 (point)))))))))
```

动态库从 <https://github.com/emacs-rime/liberime/releases> 下载最新版本，例如 `liberime-v0.0.10.1-windows-ucrt-x86_64-with-deps.zip` ，将下载的压缩包中的 `bin` 目录下的文件复制到 `~/.emacs.d/bin` 。

{{< figure src="/content-org/windows/chinese-input-method-switching-in-emacs-on-windows.org/2026-07-11_09-44-58_screenshot.png" width="90%" >}}

使用的 emacs 版本为 scoop 中的 emacs-k（如果版本不匹配，可能会碰到动态库加载的问题）。

错误信息如下：

```bash
apply: Module could not be opened: "d:/home/.emacs.d/bin/liberime-core.dll", "                  "
```

{{< figure src="/content-org/windows/chinese-input-method-switching-in-emacs-on-windows.org/2026-07-11_11-17-23_screenshot.png" width="90%" >}}
