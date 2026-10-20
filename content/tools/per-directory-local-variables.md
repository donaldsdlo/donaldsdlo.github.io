---
title: "Emacs 目录局部变量(Per-Directory Local Variables)完全指南"
author: ["Donald Lo"]
date: 2026-10-20
lastmod: 2026-10-20T15:46:40+08:00
tags: ["Emacs", "dir-locals", "配置"]
draft: false
---

<div class="ox-hugo-toc toc">

<div class="heading">Table of Contents</div>

- [什么是 Per-Directory Local Variables](#什么是-per-directory-local-variables)
- [第一个 .dir-locals.el](#第一个-dot-dir-locals-dot-el)
- [文件格式逐层拆解](#文件格式逐层拆解)
    - [顶层 key 的三种形式](#顶层-key-的三种形式)
    - [每个条目的 (变量 . 值)](#每个条目的--变量-dot-值)
    - [特殊元素](#特殊元素)
- [作用域与优先级规则](#作用域与优先级规则)
    - [子目录内再指定主模式(递归结构)](#子目录内再指定主模式--递归结构)
    - [在子目录/模式条目里执行代码(eval)](#在子目录-模式条目里执行代码--eval)
- [.dir-locals.el 与 .dir-locals-2.el(个人覆盖共享配置)](#dot-dir-locals-dot-el-与-dot-dir-locals-2-dot-el--个人覆盖共享配置)
- [安全模型(深入)](#安全模型--深入)
    - [为什么需要安全模型](#为什么需要安全模型)
    - [safe-local-variable 与 :safe](#safe-local-variable-与-safe)
    - [enable-local-variables 的五种取值](#enable-local-variables-的五种取值)
    - [交互提示：y / n / ! / i / +](#交互提示-y-n-i-plus)
    - [safe-local-variable-values / ignored-local-variable-values](#safe-local-variable-values-ignored-local-variable-values)
    - [远程目录：enable-remote-dir-locals 与 safe-local-variable-directories](#远程目录-enable-remote-dir-locals-与-safe-local-variable-directories)
    - [enable-local-eval 与 safe-local-eval-forms](#enable-local-eval-与-safe-local-eval-forms)
    - [安全加固：在 init 文件中落地推荐配置](#安全加固-在-init-文件中落地推荐配置)
    - [实践建议](#实践建议)
- [交互式命令(不用手改文件)](#交互式命令--不用手改文件)
- [目录类(Directory Class)：无法放文件时的方案](#目录类--directory-class--无法放文件时的方案)
- [编程接口与钩子(Elisp)](#编程接口与钩子--elisp)
- [实战示例](#实战示例)
    - [统一项目缩进与编码](#统一项目缩进与编码)
    - [指定 C/C++ 风格并限制子目录](#指定-c-c-plus-plus-风格并限制子目录)
    - [给子目录单独设置](#给子目录单独设置)
    - [在项目中启用 Flycheck / Eglot / LSP 后端](#在项目中启用-flycheck-eglot-lsp-后端)
    - [Eglot + Python(pylsp / Ruff)的项目级 LSP 配置](#eglot-plus-python--pylsp-ruff--的项目级-lsp-配置)
    - [Dired 等非文件缓冲区](#dired-等非文件缓冲区)
- [与文件局部变量(File Local Variables)的关系](#与文件局部变量--file-local-variables--的关系)
- [常见问题与陷阱(FAQ)](#常见问题与陷阱--faq)
- [术语表(Glossary)](#术语表--glossary)

</div>
<!--endtoc-->



## 什么是 Per-Directory Local Variables {#什么是-per-directory-local-variables}

有时你想为某个目录(及其子目录)下的所有文件统一设置一组局部变量(local variables)，比如整个软件项目的代码风格、缩进宽度、默认编码。这种需求用 **Per-Directory Local Variables** (目录局部变量，下文简称 PDLV)最自然。

它的核心载体是一个放在目录里的文件： `.dir-locals.el` 。只要 Emacs 打开这个目录(或任意子目录)里的文件，就会读取该文件，并像设置「文件局部变量」一样把里面的变量应用到缓冲区。

几个关键性质，先建立直觉：

-   目录局部变量对「目录树」生效：Emacs 从被访问文件所在目录开始，沿目录树向上查找 `.dir-locals.el` 。
-   子目录会继承上层目录的设置；更深的文件优先生效。
-   **文件局部变量** (file-local variables，写在文件末尾的 `Local Variables:` 块里)优先级高于目录局部变量。也就是说，个别文件可以覆盖项目级默认值。
-   因为 `.dir-locals.el` 本质是 Emacs Lisp 数据(甚至能包含 `eval` )，所以 Emacs 对它有完整的安全模型(见下文「安全模型(深入)」一节)。


## 第一个 .dir-locals.el {#第一个-dot-dir-locals-dot-el}

先给一个最小可运行示例。假设你的项目根目录是 `~/projects/foo/` ，在里面新建文件 `.dir-locals.el` ：

```emacs-lisp
;; Apply to every file under this directory tree.
((nil . ((indent-tabs-mode . nil)
         (fill-column . 80))))
```

打开 `~/projects/foo/any-file.el` (或任何子目录下的文件)后：

-   `indent-tabs-mode` 被设为 `nil` (用空格而不是 Tab 缩进)
-   `fill-column` 被设为 `80`

你不需要重启 Emacs。重新访问文件(或 `M-x revert-buffer` )即可生效；也可以直接 `M-x normal-mode` 重新激活主模式，让它重新读取局部变量。


## 文件格式逐层拆解 {#文件格式逐层拆解}

`.dir-locals.el` 的内容是一个 **alist** (关联列表)。它的每一项形如：

```text
(KEY . VALUE)
```

`KEY` 可以是三种东西， `VALUE` 总是一个「变量设置 alist」。


### 顶层 key 的三种形式 {#顶层-key-的三种形式}

1.  **符号 nil** —— 对 **任何主模式** 都生效(真正全局的目录级默认)。
2.  **主模式符号** (如 `c-mode` 、 `python-mode` 、 `prog-mode` )—— 仅当缓冲区启用了该模式(或其派生模式)时生效。例如 `c-mode` 会匹配 C 文件，而 `prog-mode` 会匹配所有编程模式，因为 C 模式继承自 `prog-mode` 。
3.  **子目录字符串** (如 `"src/imported"` )—— 仅对「该子目录下的所有文件」生效，与模式无关。它的值 **本身又是一份相同结构的 alist** ，所以你可以在子目录条目里 **再** 指定 `nil` 或某个主模式(见下文「子目录内再指定主模式」)，甚至再嵌套更深的子目录(递归结构)。


### 每个条目的 (变量 . 值) {#每个条目的--变量-dot-值}

`KEY` 对应的 `VALUE` 又是一个 alist，每个元素是 `(变量名 . 值)` 。注意 .dir-locals.el 里写的是 **值** ，不是 Lisp 表达式——所以你直接写 `(fill-column . 80)` ，而不是 `(setq fill-column 80)` 。


### 特殊元素 {#特殊元素}

在设置 alist 里，有几个名字不是普通变量，而是有特殊含义的「关键字」：

-   `(mode . minor-mode)` ：开启某个次要模式。例如 `(mode . auto-fill)` 等价于启用 `auto-fill-mode` ； `(mode . outshine)` 启用 outshine 等。
-   `(eval . FORM)` ：求值一个 Lisp 表达式( **有风险** ，见安全模型)。
-   `(subdirs . nil)` ：只对「当前目录」生效， **不** 递归到子目录。常用于给某个目录单独定一套风格，而让子目录继续用上层默认。
-   `(auto-mode-alist . ((REGEXP . MODE)))` ：按文件名给该目录下的文件指定主模式，规则与普通 `auto-mode-alist` 一致。
-   `(unibyte . t)` ：把缓冲区标记为 unibyte(同文件局部变量的语义)。
-   **不能** 设置 `coding` 作为目录局部变量(编码相关设置只能写在文件局部变量里)。

一个综合示例，把三种 key 和特殊元素都用上：

```emacs-lisp
((nil . ((indent-tabs-mode . t)
         (fill-column . 80)
         (mode . auto-fill)))
 (c-mode . ((c-file-style . "BSD")
            (subdirs . nil)))
 ("src/imported"
  . ((nil . ((change-log-default-name
              . "ChangeLog.local"))))))
```

含义：

-   整棵树：用 Tab 缩进、 `fill-column` 80、开启 `auto-fill-mode` 。
-   C 文件：用 BSD 缩进风格；但 `subdirs` 设为 `nil` ，所以这套 C 风格 **只** 作用于当前目录，不传给子目录。
-   `src/imported/` 子目录下：换一个 ChangeLog 文件名。


## 作用域与优先级规则 {#作用域与优先级规则}

当多个规则命中同一个变量时，优先级从高到低是：

1.  **子目录字符串 key** (最具体，目录匹配优先于模式匹配)
2.  **更具体的主模式** (如 `c-mode` 优先于其父类 `prog-mode` )
3.  **更通用的主模式 / nil**

官方手册给了一个说明性的例子：

```emacs-lisp
((nil . ((fill-column . 40)))
 (c-mode . ((fill-column . 50)))
 (prog-mode . ((fill-column . 60)))
 ("narrow-files" . ((nil . ((fill-column . 20))))))
```

-   C 文件：命中 `c-mode` (50)，虽然它也继承自 `prog-mode` (60)，但 `c-mode` 更具体，所以用 50。
-   其他编程模式文件(非 C)：用 `prog-mode` 的 60。
-   `narrow-files/` 下的 **任何** 文件(哪怕是用 C 模式)：用 20，因为 **子目录条目优先级最高** 。

记忆口诀： `目录 > 具体模式 > 通用模式 > nil` 。


### 子目录内再指定主模式(递归结构) {#子目录内再指定主模式--递归结构}

子目录条目的值不是「扁平的变量列表」，而是和顶层一样、由 `(nil . 设置)` 与 `(mode . 设置)` 组成的 alist。也就是说，你可以在某个子目录里 **再** 按主模式细分：

```emacs-lisp
((nil . ((fill-column . 40)))
 (c-mode . ((fill-column . 50)))
 ("src/imported"
  . ((nil . ((fill-column . 20)))
     (c-mode . ((fill-column . 30))))))
```

逐条套用优先级(目录 &gt; 具体模式 &gt; 通用模式 &gt; nil)：

-   `src/imported/` 下的 **C** 文件：命中子目录里的 `c-mode` (30)。它比子目录里的 `nil` (20) 更具体，也比顶层 `c-mode` (50) 优先级高(目录条目整体优先于模式条目)，所以 `fill-column` 为 30。
-   `src/imported/` 下的 **非 C** 文件：子目录里没有匹配的模式，落到子目录的 `nil` (20)，仍为 20。
-   `src/imported/` **之外** 的 C 文件：顶层 `c-mode` (50)。
-   其它地方的非 C 文件：顶层 `nil` (40)。

同理，子目录的值里还能继续出现 `(directory . list)` 形式的「更深层子目录」，规则完全递归。要记住的只有一点：=目录= 这一维永远优先于 `模式` 这一维，而同一维内 `具体 > 通用` 。


### 在子目录/模式条目里执行代码(eval) {#在子目录-模式条目里执行代码--eval}

`eval` 是「特殊元素」之一，它的 **位置** 没有限制：顶层、子目录条目、模式条目、甚至「子目录 + 模式」的组合里都能写。也就是说，上节的嵌套结构里照样可以塞一段要执行的 Lisp：

```emacs-lisp
(("src/imported"
  . ((nil . ((fill-column . 20)
             (eval . (setq-local my-proj-tag "imported"))))
     (c-mode . ((fill-column . 30)
                (eval . (setq-local c-file-style "GNU"))))))
```

-   子目录 `src/imported/` 下 **所有** 文件：执行 `(setq-local my-proj-tag "imported")` 。
-   其中 **C** 文件：额外执行 `(setq-local c-file-style "GNU")` 。

几点要注意：

-   **eval 是危险元素** ，受 `enable-local-eval` 控制(默认 `maybe` ，会就执行与否征求确认)。要免确认，可把该表达式本身加入 `safe-local-eval-forms` ，或把所在目录加进 `safe-local-variable-directories` (提示里按 `+` )。
-   eval 在 **主模式确立之后、局部变量应用阶段** 被执行，所以用 `setq-local` 改缓冲区局部变量是安全的；别指望它在 `find-file` 更早期生效。
-   多个匹配层级都含 eval 时， **所有** 匹配到的 eval 表单都会被执行，更具体的层级在后执行，因此可覆盖较通用层级设的状态。


## .dir-locals.el 与 .dir-locals-2.el(个人覆盖共享配置) {#dot-dir-locals-dot-el-与-dot-dir-locals-2-dot-el--个人覆盖共享配置}

`.dir-locals.el` 通常会提交进版本库，作为团队共享的项目配置。但你可能想在不改动(也不提交)共享文件的前提下加一点 **个人** 偏好。Emacs 26 起支持第二个文件 `.dir-locals-2.el` ：

-   它与 `.dir-locals.el` 放在 **同一目录** 。
-   如果存在，Emacs 会 **额外** 加载它，且 `.dir-locals-2.el` 的设置 **优先于** `.dir-locals.el` 。

典型用法：把团队约定放 `.dir-locals.el` (入库)，把你的个人微调放 `.dir-locals-2.el` (加进 `.gitignore` )。两者冲突时以个人文件为准。


## 安全模型(深入) {#安全模型--深入}

`.dir-locals.el` 不是普通配置文件——它的内容会被 Emacs 求值。一个恶意或被污染的 `.dir-locals.el` 可以通过 `eval` 或篡改 `load-path` 等方式执行任意代码。因此 Emacs 对目录局部变量有完整的安全机制，理解它能让你既放心用、又不被坑。


### 为什么需要安全模型 {#为什么需要安全模型}

文件/目录局部变量里最危险的是：

-   `(eval . FORM)` —— 直接执行 Lisp。
-   某些「危险变量」，如 `load-path` 、 `eval` 、 `enable-local-variables` 本身——改了它们可能加载并执行你没打算运行的代码。

所以 Emacs 默认 **不会** 静默应用「未知是否安全」的局部变量，而是把整份局部变量列表显示出来，等你确认。


### safe-local-variable 与 :safe {#safe-local-variable-与-safe}

Emacs 判断一个变量是否「安全」，看它有没有 `safe-local-variable` 这个 **symbol property** (符号属性)。该属性的值是一个 **谓词** (predicate)：用「待设的值」去调用它，返回非 `nil` 就认为安全。

给自定义变量声明安全性的两种方式：

```emacs-lisp
;; Way 1: put property directly (works for any variable/defvar).
(put 'my-project-indent 'safe-local-variable #'integerp)

;; Way 2: use :safe keyword inside defcustom.
(defcustom my-project-indent 2
  "Project indentation width."
  :type 'integer
  :safe #'integerp)
```

Emacs 内置已经把很多「显然安全」的变量标为安全，例如 `fill-column` 、 `indent-tabs-mode` 、 `comment-column` 等都是对任意整数/布尔值安全的，所以常见配置从不会被提示。

对应的危险标记是 `risky-local-variable` (属性或 `:risky` 关键字)，一旦标记 `t` ，该变量永远走「危险」路径，绝不会无提示应用：

```emacs-lisp
(put 'load-path 'risky-local-variable t)
```


### enable-local-variables 的五种取值 {#enable-local-variables-的五种取值}

全局开关 `enable-local-variables` 决定 Emacs 如何处理(文件与目录)局部变量：

| 取值     | 行为                                      |
|--------|-----------------------------------------|
| `t` (默认) | 安全变量自动应用；不安全/危险变量 **弹窗询问** |
| `nil`    | 忽略 **所有** 局部变量                    |
| `:safe`  | 只应用已知安全的变量，其余 **忽略且不询问** |
| `:all`   | 应用 **全部** 变量，不询问(官方不建议长期开启，有安全风险) |
| 其他任意值 | 对每个含局部变量的文件都询问，不做安全预判(常见写法如设为 `:prompt` ) |

日常使用保持默认 `t` 即可：你信任的项目配置(安全变量)无感生效，遇到可疑内容才会被拦下来问你。


### 交互提示：y / n / ! / i / + {#交互提示-y-n-i-plus}

当 Emacs 遇到不安全(unsafe)的局部变量时，会显示整份列表并等待确认。可用响应：

-   `y` 或 `SPC` ：应用这份局部变量列表。
-   `n` ：忽略(不应用)。批处理模式(batch)下默认按 `n` 处理。
-   `!` ：把这份列表里 **所有** 变量/值对标记为「今后安全」，之后同文件或其它文件再遇到就不再问(仅对 **非危险** 变量有效)。
-   `i` ：把这份列表里 **所有** 变量/值对标记为「永久忽略」，今后不再应用也不再问。
-   `+` ：(**仅目录局部变量**)应用全部变量，并把该目录加入 `safe-local-variable-directories` ，以后从这个目录加载目录局部变量 **免确认** (哪怕含危险变量)。只应对你 **信任** 的目录使用。

注意：如果一份列表里 **只有** 危险(risky)变量，Emacs 不会提供、也不接受 `!` 。此时若你确实想给危险变量记安全值，请直接通过 customize 修改 `safe-local-variable-values` 。


### safe-local-variable-values / ignored-local-variable-values {#safe-local-variable-values-ignored-local-variable-values}

这两个变量持久保存你在提示里用 `!` / `i` 做的选择：

-   `safe-local-variable-values` ：alist 形如 `((var . value) ...)` ，记录「这些值组合可安全应用」。
-   `ignored-local-variable-values` ：记录「这些值组合永久忽略」。

它们通常通过 customize 界面(或提示里的 `!` /=i= )维护，不建议手改。


### 远程目录：enable-remote-dir-locals 与 safe-local-variable-directories {#远程目录-enable-remote-dir-locals-与-safe-local-variable-directories}

出于性能与安全考虑，Emacs **默认不** 对远程文件(Tramp)查找 `.dir-locals.el` 。如果你确实需要在远程项目上用目录局部变量：

```emacs-lisp
(setq enable-remote-dir-locals t)
```

开启后，远程目录 **也可以** 出现在 `safe-local-variable-directories` 中(该列表里的目录名必须是 **绝对路径** ；远程目录需先打开 `enable-remote-dir-locals` )。

`safe-local-variable-directories` 本身是个目录白名单：里面列出的目录，加载其目录局部变量时 **跳过确认** ，即使含危险变量。把公司内网仓库根目录加进去，就不用每次都被问。


### enable-local-eval 与 safe-local-eval-forms {#enable-local-eval-与-safe-local-eval-forms}

专门控制 `eval` 这个「变量」是否执行，三态与 `enable-local-variables` 类似：

-   `t` ：执行(仍可能被整体安全流程询问)
-   `nil` ：永不执行 `eval`
-   `maybe` (默认)：既不是 `t` 也不是 `nil` ，所以 Emacs **会** 就 `eval` 征求确认

    例外：若某个 `eval` 表达式本身出现在 `safe-local-eval-forms` 列表里，Emacs 直接放行，不再询问。


### 安全加固：在 init 文件中落地推荐配置 {#安全加固-在-init-文件中落地推荐配置}

上面讲的是「机制」，这里给出一份可直接写进 init 的加固基线。它同时兼顾「减少弹窗疲劳」与「降低恶意 `.dir-locals.el` / eval 带来的风险」。

1.  **只应用已知安全的变量(推荐)** 。把 `enable-local-variables` 设为 `:safe` ，Emacs 会
    自动应用已验证安全的变量，并 **静默丢弃** 其余(含危险)变量——既安全，又不再频繁弹窗：
    ```emacs-lisp
    (setq enable-local-variables :safe)
    ```
    代价：未显式标记为安全的「自定义但无害」项目变量会被忽略，除非通过 `safe-local-variable-values` 或 `safe-local-variable` 属性登记(见下)。

    注意：设为 `nil` 会 **整体关闭** 局部变量处理(但 `lexical-binding` 等少数变量仍通过 `permanently-enabled-local-variables` 保持生效，不受此开关影响)。

2.  **白名单具体变量** 。当 `:safe` 模式静默忽略了你需要的变量，可显式放行：
    ```emacs-lisp
    ;; Whitelist a specific variable/value pair:
    (add-to-list 'safe-local-variable-values '(my-custom-variable . "expected-value"))

    ;; Whitelist any value matching a predicate (e.g. any string):
    (put 'my-custom-variable 'safe-local-variable #'stringp)

    ;; Whitelist only certain values:
    (put 'my-custom-variable 'safe-local-variable
         (lambda (val)
           "Return t if VAL is \"hello\" or \"world\"."
           (member val '("hello" "world"))))
    ```

3.  **白名单具体目录** 。 `safe-local-variable-directories` 列出「受信任目录」，其目录局部变量
    **全部免确认** (即使含危险变量)。注意它 **只** 作用于目录局部变量，对文件局部变量无效：
    ```emacs-lisp
    (add-to-list 'safe-local-variable-directories "/path/to/trusted/project/")
    ```

4.  **关闭本地 eval** 。若工作流不需要动态 `eval` ，直接禁用，从根本上杜绝任意 Lisp 执行：
    ```emacs-lisp
    (setq enable-local-eval nil)
    ```

5.  **保留安全默认值** 。以下默认设置本身已是良好选择，保持即可：
    ```emacs-lisp
    (setq enable-dir-local-variables t)   ; 启用目录局部变量(.dir-locals.el)
    (setq enable-remote-dir-locals nil)   ; 不从远程(Tramp)加载，避免不可信远程配置
    ```
    `enable-remote-dir-locals` 保持 `nil` 还能顺带省去在远程文件系统上查找 `.dir-locals.el`
    的开销。需要远程目录局部变量时再按需开启，并把对应目录加进
    `safe-local-variable-directories` 。


### 实践建议 {#实践建议}

-   把项目级「无害」配置(缩进、fill-column、coding 之外的风格变量)尽量标成 `:safe` ，团队新成员打开文件不会被弹窗打断。
-   团队共享的 `.dir-locals.el` 里 **避免** 用 `eval` ；真要做复杂初始化，优先用模式钩子或目录类(见下文)。
-   个人偏好的危险设置用 `.dir-locals-2.el` 或 `safe-local-variable-directories` ，别污染共享文件。
-   永远不要把 `enable-local-variables` 长期设成 `:all` 。


## 交互式命令(不用手改文件) {#交互式命令--不用手改文件}

不想手写 s-expr，可以用内置命令，它们会直接更新 `.dir-locals.el` (若同目录还有 `.dir-locals-2.el` ，则更新后者)：

-   `M-x add-dir-local-variable` ：交互式询问「模式/子目录 → 变量 → 值」，追加一条。
-   `M-x delete-dir-local-variable` ：删除一条。
-   `M-x copy-file-locals-to-dir-locals` ：把当前文件的文件局部变量复制进目录局部变量。
-   `M-x customize-dirlocals` ：弹出一个 Easy Customization 缓冲区来编辑目录局部变量。

带 **前缀参数** (`C-u` )调用以上任一命令时，会额外询问「要改哪个文件」，你可以指定 `.dir-locals.el` 或 `.dir-locals-2.el` (文件不必已存在，但名字必须合法)。


## 目录类(Directory Class)：无法放文件时的方案 {#目录类--directory-class--无法放文件时的方案}

有些目录你 **没法** 或 **不想** 放 `.dir-locals.el` ，比如系统目录(`/usr/include/` )、只读挂载点。这时用「目录类」机制，在初始化文件里声明：

```emacs-lisp
;; Define a named class of settings.
(dir-locals-set-class-variables 'unwritable-directory
   '((nil . ((some-useful-setting . value)))))

;; Assign that class to a directory (and its subdirs).
(dir-locals-set-directory-class
   "/usr/include/" 'unwritable-directory)
```

机制要点：

-   `dir-locals-set-class-variables` 把一组设置绑定到一个 **符号类名** (如 `'unwritable-directory` )。
-   `dir-locals-set-directory-class` 把该类指派给某个目录及其子目录。之后该目录下所有文件都套用这套设置。
-   内部数据结构： `dir-locals-class-alist` (类 → 设置)、 `dir-locals-directory-cache` (目录 → 类 + 文件 mtime，用于判断缓存是否失效)。
-   通过文件加载时，Emacs 会自动调用这两个函数，并传入 `mtime` 参数；你手动指派类时传 `nil` 即可。

目录类与文件方式 **可以共存** ：Emacs 会合并两者，冲突时同样遵循「目录条目 &gt; 具体模式 &gt; 通用模式」的优先级。


## 编程接口与钩子(Elisp) {#编程接口与钩子--elisp}

当你要写自己的模式或工具、让它们「感知」目录局部变量时，会用到这些：

-   `hack-dir-local-variables` ：读取 `.dir-locals.el` ，把结果存进缓冲区的 `file-local-variables-alist` 与 `dir-local-variables-alist` ，但 **不立即应用** 。
-   `hack-dir-local-variables-non-file-buffer` ：在非文件缓冲区(如 Dired)里 **立即应用** 目录局部变量。非文件缓冲区按 `default-directory` 向上查找。
-   `dir-local-variables-alist` ：buffer-local 变量，收集到的目录局部变量 `((var . value) ...)` ，由 `hack-local-variables` 逐个应用。
-   `dir-locals-find-file` ：给定一个文件名，返回 `(.dir-locals.el 所在目录 . 设置)` 或 `nil` ，方便调试「我的设置到底从哪来」。
-   `hack-dir-local-get-variables-functions` ：特殊钩子，各函数返回 `(. cons 或 list of cons)` ，用于接入其它来源(其它编辑器的目录配置)。更深目录的结果优先；建议做好缓存以保持高效。
-   `enable-dir-local-variables` ：设为 `nil` 可让某个主模式 **忽略** 目录局部变量(但仍尊重文件局部变量)。

让 Dired 这类非文件缓冲区遵守目录局部变量的标准做法，是在其模式命令里调用 `hack-dir-local-variables-non-file-buffer` 。


## 实战示例 {#实战示例}


### 统一项目缩进与编码 {#统一项目缩进与编码}

```emacs-lisp
((nil . ((indent-tabs-mode . nil)
         (tab-width . 4)
         (fill-column . 78))))
```


### 指定 C/C++ 风格并限制子目录 {#指定-c-c-plus-plus-风格并限制子目录}

```emacs-lisp
((c-mode . ((c-file-style . "linux")
            (c-basic-offset . 8)
            (subdirs . nil)))
 (c++-mode . ((c-file-style . "stroustrup")
              (subdirs . nil))))
```


### 给子目录单独设置 {#给子目录单独设置}

```emacs-lisp
((nil . ((indent-tabs-mode . nil)))
 ("tests" . ((nil . ((fill-column . 100))))))
```

`tests/` 下的文件 `fill-column` 用 100，其余用上层默认。


### 在项目中启用 Flycheck / Eglot / LSP 后端 {#在项目中启用-flycheck-eglot-lsp-后端}

通过 `mode` 开次要模式，或用 `eval` 设置项目专属后端(`eval` 需确认，团队共享文件请谨慎)：

```emacs-lisp
((python-mode . ((eval . (setq-local flycheck-python-executable
                                "/opt/venv/project/bin/python"))
                 (mode . flycheck))))
```


### Eglot + Python(pylsp / Ruff)的项目级 LSP 配置 {#eglot-plus-python--pylsp-ruff--的项目级-lsp-配置}

下面是一份真实、完整的用法。它把 「语言服务器(pylsp)的插件开关与 Ruff 配置」写进项目根目录的 `.dir-locals.el` ，这样
每个 clone 该仓库的人打开 Python 文件时，都会自动套用同一套 LSP / 格式化 / lint 规则，
而不必在各自 init 里写死 `eglot-workspace-configuration` 。

几个要点：

-   用 `python-base-mode` 作 key，这样无论你用 `python-mode` 还是 `python-ts-mode` 都能命中(两者都派生自 `python-base-mode` )。
-   `eglot-workspace-configuration` 是 Eglot 提供的变量，其 `safe-local-variable` 安全谓词接受 plist 值，所以这份配置 **不会** 触发局部变量确认提示。
-   `fill-column` / `indent-tabs-mode` / `tab-width` 等风格变量也天然安全。

<!--listend-->

```emacs-lisp
;;; Directory Local Variables for a Python project -*- no-byte-compile: t; -*-
((nil . ((sentence-end-double-space . nil)
         (require-final-newline . t)))
 (python-base-mode
  . ((indent-tabs-mode . nil)
     (tab-width . 4)
     (fill-column . 88)
     (python-indent-offset . 4)
     (python-indent-guess-indent-offset . nil)
     (eglot-workspace-configuration
      . (:pylsp
         (;; Formatter to use for reformatting signatures in docstrings.
          :signature
          (;; Signature
           :formatter "ruff"
           :include_docstring t
           :line_length 88)
          :plugins
          (:ruff
           (;; Ruff plugin (Requires: ruff and python-lsp-ruff)
            :enabled t
            :formatEnabled t
            :lineLength 88
            ;; I: Sort imports
            :extendSelect ["I"]
            :format ["I"])

           :pylsp_mypy
           (;; Type checking (Requires: pylsp-mypy)
            :enabled t
            ;; Disabling live mode prevents type-checking updates on every edit.
            ;; Save the file to refresh mypy diagnostics.
            :live_mode :json-false)

           :pylint
           (;; Pylint
            :enabled t)

           :flake8 (:enabled :json-false)
           :mccabe (:enabled :json-false)
           :pyflakes (:enabled :json-false)
           :pycodestyle (:enabled :json-false)
           :pydocstyle (:enabled :json-false)
           :isort (:enabled :json-false)
           :autopep8 (:enabled :json-false)
           :yapf (:enabled :json-false)
           :preload (:enabled :json-false)
           :rope_autoimport (:enabled :json-false)
           :rope_completion (:enabled :json-false)

           :jedi_completion
           (;; Jedi code completion
            :enabled t))))))))
```

把这段代码放进项目根目录的 `.dir-locals.el` ，并确保 Python 环境已安装
`python-lsp-server` 、 `python-lsp-ruff` 、 `ruff` 、 `pylint` 。打开任意 `.py` 文件时，Eglot
会把这份配置作为 workspace 配置发给 pylsp：Ruff 负责格式化与 import 排序，mypy / pylint
提供类型检查与额外诊断。

如果你在用传统工具链(flake8 + isort + autopep8，而非 Ruff)，把上面的 `:plugins` 反转
即可——禁用 `:ruff` ，启用 `:flake8` / `:mccabe` / `:pyflakes` / `:pycodestyle` /
`:pylint` / `:pydocstyle` / `:isort` / `:autopep8` (注意若启用 Flake8 要同时关掉
mccabe / pyflakes / pycodestyle，避免重复检查)。

强制 Eglot 选择 pylsp ：若环境里装了多个 Python LSP，Eglot 可能连到别的服务器。在 init
文件里固定它：

```emacs-lisp
(with-eval-after-load 'eglot
  (setf (alist-get 'python-mode eglot-server-programs) '("pylsp"))
  (setf (alist-get 'python-ts-mode eglot-server-programs) '("pylsp")))
```


### Dired 等非文件缓冲区 {#dired-等非文件缓冲区}

Dired 缓冲区的 `default-directory` 也会参与查找，所以项目根目录的 `.dir-locals.el` 同样能影响 Dired(例如统一 `dired-omit-mode` 等)。这不需要你做任何额外配置，Emacs 默认就支持。


## 与文件局部变量(File Local Variables)的关系 {#与文件局部变量--file-local-variables--的关系}

-   文件局部变量写在文件末尾的 `Local Variables:` 块(或文件头 `*-*` 行)。
-   **文件局部变量优先级高于目录局部变量** ：目录层定默认值，个别文件可覆盖。
-   二者共享同一套安全模型(`enable-local-variables` 、 `safe-local-variable` 等)。
-   想「文件 → 目录」迁移设置？用 `M-x copy-file-locals-to-dir-locals` 。


## 常见问题与陷阱(FAQ) {#常见问题与陷阱--faq}

-   **改了 `.dir-locals.el` 不生效？** 重新访问文件(`revert-buffer` )或 `M-x normal-mode` ；Emacs 打开文件时只读取一次。缓存见 `dir-locals-directory-cache` 。
-   **子目录没继承设置？** 检查上层条目是否带了 `(subdirs . nil)` ；或子目录里是否有自己的 `.dir-locals.el` 覆盖了上层。
-   **总是被弹窗询问？** 说明存在非安全变量。给它加 `:safe` 属性，或在提示里按 `!` 标记为安全(非危险变量)。
-   **想对某目录永久免确认？** 把该目录加进 `safe-local-variable-directories` (提示里按 `+` ，或手动 customize)。
-   **`coding` 设不进目录局部变量？** 编码类设置只能写在文件局部变量里，目录层不支持。
-   **MS-DOS 环境？** 文件名要用 `_dir-locals.el` (8+3 限制下截断为 `_dir-loc.el` )。


## 术语表(Glossary) {#术语表--glossary}

| 术语                                | 含义                                                                 |
|-----------------------------------|--------------------------------------------------------------------|
| Per-Directory Local Variables       | 目录局部变量：对目录树所有文件生效的局部变量机制，载体是 `.dir-locals.el` |
| `.dir-locals.el`                    | 存放目录局部变量的文件，从被访问文件目录向上查找                     |
| `.dir-locals-2.el`                  | 同名次级文件(Emacs 26+)，个人覆盖用，优先级高于 `.dir-locals.el`     |
| 目录类(Directory Class)             | 用符号类名把设置绑定到目录的机制，适合无法放文件的目录               |
| safe-local-variable                 | 符号属性/关键字，声明变量在某谓词下取值安全，可无提示应用            |
| risky-local-variable                | 符号属性/关键字，标记变量永远危险，绝不在无确认下应用                |
| enable-local-variables              | 全局开关，控制是否/如何应用局部变量(`t` / `nil` / `:safe` / `:all` / 其它) |
| enable-local-eval                   | 专门控制 `eval` 是否执行的开关(`t` / `nil` / `maybe` )               |
| safe-local-variable-directories     | 受信任目录白名单，加载其目录局部变量免确认(可含危险变量)             |
| enable-remote-dir-locals            | 是否对远程(Tramp)文件查找目录局部变量，默认 `nil`                    |
| safe-local-variable-values          | 记录「值组合可安全应用」的 alist，可在提示按 `!` 或手动维护          |
| permanently-enabled-local-variables | 即使 `enable-local-variables` 为 `nil` 仍强制生效的少数变量(如 `lexical-binding` ) |
| 文件局部变量                        | 写在文件末尾的局部变量，优先级高于目录局部变量                       |
