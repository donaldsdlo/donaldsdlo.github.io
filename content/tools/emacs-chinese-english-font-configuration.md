---
title: "Emacs 中英文字体配置指南"
author: ["Donald Lo"]
date: 2026-07-14
lastmod: 2026-08-29T11:24:00+08:00
tags: ["Emacs", "字体", "中英文", "org-mode"]
draft: false
---

<div class="ox-hugo-toc toc">

<div class="heading">&#30446;&#24405;</div>

- [字体问题的历史](#字体问题的历史)
    - [Windows 系统特有的字体卡顿问题](#windows-系统特有的字体卡顿问题)
- [核心概念](#核心概念)
    - [Face](#face)
    - [Fontset](#fontset)
    - [Script 与 Charset](#script-与-charset)
    - [字体名称的组成](#字体名称的组成)
- [查看系统字体](#查看系统字体)
    - [Linux](#linux)
    - [Windows](#windows)
    - [macOS](#macos)
    - [在 Emacs 中查看](#在-emacs-中查看)
- [方案一：使用中英文等宽的统一字体](#方案一-使用中英文等宽的统一字体)
    - [可选字体](#可选字体)
        - [Sarasa Gothic / Sarasa Mono SC Nerd](#sarasa-gothic-sarasa-mono-sc-nerd)
        - [Maple Mono CN](#maple-mono-cn)
    - [配置方法](#配置方法)
    - [优缺点](#优缺点)
- [方案二：中英文字体分别设置 + face-font-rescale-alist](#方案二-中英文字体分别设置-plus-face-font-rescale-alist)
    - [face-font-rescale-alist](#face-font-rescale-alist)
    - [如何确定缩放比例](#如何确定缩放比例)
    - [配置 default / fixed-pitch / variable-pitch](#配置-default-fixed-pitch-variable-pitch)
    - [Org Mode 中 fixed-pitch 的使用](#org-mode-中-fixed-pitch-的使用)
    - [优缺点](#优缺点)
- [方案三：使用 fontset 为特定 Face 单独设置字体](#方案三-使用-fontset-为特定-face-单独设置字体)
    - [核心函数](#核心函数)
    - [工作原理](#工作原理)
    - [配置示例](#配置示例)
    - [需要对齐的 Face 列表](#需要对齐的-face-列表)
    - [优缺点](#优缺点)
- [常用的开源免费等宽英文字体](#常用的开源免费等宽英文字体)
- [常用的开源免费中文字体](#常用的开源免费中文字体)
- [方案选择指南](#方案选择指南)
- [完整配置示例](#完整配置示例)
- [常见问题](#常见问题)
    - [为什么修改 face-font-rescale-alist 后不生效？](#为什么修改-face-font-rescale-alist-后不生效)
    - [为什么中文字体缩放时不跟随英文？](#为什么中文字体缩放时不跟随英文)
    - [如何查看当前字符使用的字体？](#如何查看当前字符使用的字体)
    - [set-frame-font 和 set-face-attribute 有什么区别？](#set-frame-font-和-set-face-attribute-有什么区别)
    - [如何在终端模式中配置字体？](#如何在终端模式中配置字体)
- [参考链接](#参考链接)

</div>
<!--endtoc-->



## 字体问题的历史 {#字体问题的历史}

1980 年，国家标准 GB2312 发布，收录 6763 个汉字和 682 个非汉字图形字符。这是汉字进入计算机世界的第一步，但"收录"和"能显示"之间隔着天堑。彼时微机内存不过 640KB，一块 16×16 点阵的汉字字模就要占 32 字节，六千多个汉字的字库直逼 200KB——光装字库就吃掉三分之一的常规内存。CCDOS 最早的解决方案是把字库驻留硬盘，按需调入，每次显示汉字都要读盘，速度慢到让人怀疑机器是不是死了。后来有了汉卡，把字库烧进 ROM 插在扩展槽上，才算把显示速度拉到了可用的水平。

那段日子里，汉字是计算机里的二等公民。操作系统不认，软件不支持，连打印出来都是歪歪扭扭的点阵。严援朝写 CCDOS、倪光南做联想汉卡、王永民发明五笔字型——每一项都像是硬生生在英文计算机的骨架上凿出一个洞来，把汉字塞进去。到了 90 年代，Windows 3.1 中文版和中文之星让局面有了实质好转，TrueType 字体技术把矢量汉字带进了图形界面。再到后来 Unicode 统一编码、系统级 CJK 支持成为标配，汉字的问题才真正算是妥善解决，以致今日你我输入汉字，几乎像呼吸与喝水一样自然。

但 Emacs 是个例外。Emacs 的图形界面起源于 X Window System，而 X11 的字体机制是一套诞生于 80 年代末的设计—— `XLFD` （X Logical Font Description）。这套机制把字体的每一个属性都编码进名字里：

```text
-DAMA-Ubuntu Mono-regular-normal-normal-*-12-*-*-*-m-0-iso10646-1
```

现代 Emacs 已经用 `font-spec` 封装了这些噩梦，你只需要写：

```emacs-lisp
(font-spec :family "Ubuntu Mono" :size 12)
```

但问题的核心从未变过： `中英文混排时的对齐`  。西文等宽字体中每个字符宽度相同，适合代码排版；汉字天然等宽，但一个等宽西文字符是中文字符的 `0.6` 倍的宽度，当然也有其他的倍数，少数英文字体是中文字体的 `0.5` 倍宽度。当两者混排——尤其是在 Org Mode 的表格中——若比例不对，表格就会错位变形。


### Windows 系统特有的字体卡顿问题 {#windows-系统特有的字体卡顿问题}

在 Windows 平台上，Emacs 处理中文字体时常会遇到一个 Linux/macOS 用户极少遭遇的痛点： `字体切换时的明显卡顿` 。这个问题的根源深埋在 Windows 字体子系统的设计哲学中，要理解它，必须先了解 DirectWrite 与 GDI 这两套并存的字体渲染架构。

Windows Vista 引入 DirectWrite 作为新一代文本渲染 API，相比古老的 GDI（Graphics Device Interface）有了质的飞跃：支持亚像素抗锯齿、硬件加速、UTF-16 编码、清晰的文本渲染（ClearType）。然而出于兼容性考虑，Windows 仍然保留 GDI 作为后备。当一个应用程序（如 Emacs）调用 `CreateFont` 系列 API 时，系统会根据字体名称在 GDI 字体表中查找；遇到 CJK 字符时，又可能回落到 DirectWrite 的字体回退链。这一跨架构调用本身就是性能损耗的一个源头。

在 Emacs 30 之前的版本中，Windows 图形后端使用的是 `GDI` 路径（即 HarfBuzz 之前的旧渲染管线）。每个 CJK 字符的渲染都需要经过以下步骤：

1.  根据字符的 Unicode 码位，遍历 Fontset 中定义的脚本映射
2.  调用 Windows API 在系统字体注册表中查找匹配的字体
3.  `逐字符` 通过 GDI `GetGlyphOutline` 获取字形轮廓（glyph outline）
4.  将轮廓光栅化为位图，最后绘制到屏幕

这套流程在渲染拉丁字符时几乎无感——一个英文字母的 glyph 轮廓通常只有几十到几百字节，缓存命中率极高。但 CJK 字符完全是另一个故事：常用汉字就有六七千个，每个字形轮廓动辄数百字节到数千字节不等（取决于字体复杂度），更别提 Windows 系统中常常预装了十几种以上的中文字体（微软雅黑、宋体、黑体、楷体、SimSun-ExtB、Microsoft YaHei UI 等），每个脚本（ `han` , `cjk-misc` , `kana` , `bopomofo` ）都要逐个查询。

实际表现是灾难性的：在一个包含大量中文的长 Org Mode 文件中，滚动或重绘时鼠标会频繁出现 `小转圈` ； `M-x redisplay` 反复触发； `C-x C-+` 改变字号后整个 frame 冻结数秒；甚至输入中文时每一个汉字的插入都要等待几十毫秒，让打字体验如同在泥沼中跋涉。Elisp 调试时若开启 `M-x toggle-debug-on-quit` ，会发现 `font-get-glyph` 或 `gdi-get-glyph` 频繁出现在堆栈顶端。

情况在 Emacs 30 及以后有了实质性改善。新版默认改用 `HarfBuzz + DirectWrite` 渲染管线：

```emacs-lisp
;; Emacs 30+ 默认启用 HarfBuzz（无需显式开启）
;; 若需强制启用，可设置：
(setq w32-use-harfbuzz-for-fonts t)
(setq harfbuzz-fonts-default-resolution 96)
(setq harfbuzz-fonts-default-rendering-batch-size 256)
```

HarfBuzz 引入的关键变革是 `OpenType 字体表预加载` 与 `批量字形查询` ：它会在启动时一次性将 Fontset 中所有相关字体的 cmap（字符映射表）和 glyph cache 加载到内存，之后渲染单个字符时只需哈希表查找，性能从此质的飞跃。在开启 HarfBuzz 后，许多 Windows 用户反映长 Org 文档的滚动卡顿基本消失，字号切换也丝滑顺畅。

然而 HarfBuzz 并非万能灵药。如果系统中安装了过多的中文字体（特别是一些 OTF/TTC 子集字体、Adobe 字体、来自不同 CJK 区域的字体），HarfBuzz 的字体发现（font discovery）阶段仍可能消耗数秒甚至十几秒。这主要是因为 `fc-cache` （Windows 下通过 `fontconfig-bin` 或 Emacs 内置的字体枚举）要遍历注册表中每一个字体条目，提取元数据中的 `family` , `style` , `script` , `language` 等标签。对于 Nerd Font 类包含数千图标字模的字体，这个开销尤为明显。

缓解策略主要有：

1.  `精简系统字体` —— 只保留常用字体，移除不用的 CJK 变体。Windows 自带的 **可选功能** 中可以卸载东亚字体扩展包，只保留基础中文字体。
2.  `使用 Nerd Font 替代方案` —— 比如直接安装 Sarasa Mono SC（更纱黑体），一个字体文件同时覆盖等宽英文和中文 2:1 字宽，省去 fontset 配置中切换多套字体的开销。
3.  `预热字体缓存` —— 启动后第一次切换 buffer（或打开文件）时主动触发一次重绘，让 HarfBuzz 完成 glyph cache 填充：

<!--listend-->

```emacs-lisp
;; 启动后预热字体缓存（减少首次打开中文文件时的卡顿）
(add-hook 'emacs-startup-hook
  (lambda ()
    (redisplay)
    (sit-for 0.5)))
```

1.  `关闭多余插件的字体切换逻辑` —— 许多 major mode（如 `lsp-mode` , `company` , `tree-sitter` ）会在不同上下文下切换字体，触发额外的 fontset 查询。可以通过 `(setq inhibit-compacting-font-caches t)` 减少缓存抖动。

为 Emacs 配置字体，在 Windows 上不仅是一个美学问题，更是一个性能工程问题。它既要考虑字形对齐、美观可读，也要考虑渲染管线的选择、字体集大小、glyph cache 命中率。本文将从最简单的方案到最精细的方案，逐一介绍如何在 Windows 平台上实现既美观又流畅的中英文混排。


## 核心概念 {#核心概念}


### Face {#face}

Face 是 Emacs 中控制文字外观的基本单元——可以理解为 CSS 的样式规则。每个 Face 包含 `:family` 、 `:height` 、 `:weight` 、 `:slant` 等属性。Emacs 内置的 Face 包括：

-   `default` — 全局默认字体
-   `fixed-pitch` — 等宽字体（用于代码、表格等需要对齐的内容）
-   `variable-pitch` — 比例字体（用于正文阅读）
-   `bold` , `italic` , `bold-italic` — 粗体、斜体等

Org Mode 定义了大量 Face： `org-level-1` 到 `org-level-8` 是各级标题， `org-table` 是表格， `org-code` 是行内代码， `org-block` 是代码块， `org-verbatim` 是等宽文本等。

用 `M-x describe-face` 可以查看任意 Face 的属性。用 `M-x describe-char` 可以查看光标下字符使用的 Face。


### Fontset {#fontset}

Fontset 是 Emacs 用来显示所有脚本（Script）的字体集合。一个 Fontset 将不同的 Unicode 脚本映射到不同的物理字体。Emacs 定义了三个内置 Fontset：

-   `standard fontset` — 标准字体集
-   `startup fontset` — 启动时使用的字体集
-   `default fontset` — 其他两个的默认回退

当你设置 `default` Face 的字体时，Emacs 会修改默认 Fontset，从而影响所有 Frame。中文字体的问题，本质上是 Fontset 中汉字脚本（ `han` ）的字体与拉丁字体之间的宽度比例问题。


### Script 与 Charset {#script-与-charset}

Unicode 为世界上几乎所有的文字赋予了编码。在这个空间里，汉字集合被划分为多个子集，每个子集通过脚本（Script）或字符集（Charset）选取：

| 名称          | 类型    | 覆盖范围        |
|-------------|-------|-------------|
| `han`         | Script  | 常用汉字（中日韩统一表意文字） |
| `cjk-misc`    | Script  | CJK 标点符号    |
| `kana`        | Script  | 日文假名        |
| `bopomofo`    | Script  | 注音符号        |
| `chinese-gbk` | Charset | GBK 编码汉字    |
| `big5`        | Charset | Big5 编码繁体汉字 |

用 `C-h h` （ `view-hello-file` ）可以查看 Emacs 支持的所有语言的示例文本。用 `M-x list-character-sets` 可以列出所有字符集。变量 `script-representative-chars` 列出了所有脚本及其代表性字符。


### 字体名称的组成 {#字体名称的组成}

在现代操作系统中，一个字体文件（ `.ttf` 或 `.otf` ）包含的信息远不止一个名字。以 `Sarasa Mono SC Nerd` 为例，其完整标识包括：

| 组成部分    | 说明                                 | 示例                  |
|---------|------------------------------------|---------------------|
| Family Name | 字族名，字体选择器中显示的名称       | `Sarasa Mono SC Nerd` |
| Style       | 字体样式：Regular/Bold/Italic/Bold Italic | `Regular`             |
| Weight      | 字重：Thin(100) 到 Black(900)        | `Medium (500)`        |
| Width       | 宽度：Condensed/Normal/Extended      | `Normal`              |
| Slant       | 倾斜：Upright/Italic/Oblique         | `Upright`             |
| Size        | 点大小（point size），1pt ≈ 1/72 英寸 | `14`                  |
| Spacing     | 间距类型：Mono/Proportional          | `Mono`                |

在 Emacs 中， `:height` 属性的单位是 `1/10 pt` ，所以 `:height 140` 表示 14pt。


## 查看系统字体 {#查看系统字体}


### Linux {#linux}

使用 `fc-list` 命令：

```bash
fc-list | grep "Noto Sans CJK"
fc-list :family | sort -u
fc-list :family style spacing
```

查看字体的详细信息：

```bash
fc-match "Sarasa Mono SC"
fc-scan --format "%{family}\n" /path/to/font.ttf
```


### Windows {#windows}

在 PowerShell 中：

```powershell
Add-Type -AssemblyName System.Drawing
(New-Object System.Drawing.Text.InstalledFontCollection).Families | ForEach-Object { $_.Name }
```


### macOS {#macos}

```bash
fc-list :family | sort -u
```


### 在 Emacs 中查看 {#在-emacs-中查看}

```emacs-lisp
(font-family-list)
(member "Sarasa Mono SC Nerd" (font-family-list))
```

`M-x describe-font` 查看当前使用的字体详情， `M-x describe-fontset` 查看当前 Fontset 的映射。


## 方案一：使用中英文等宽的统一字体 {#方案一-使用中英文等宽的统一字体}

最简单的方案：选择一款内置中英文且严格 2:1 等宽的字体，所有 Face 都使用这一种字体。


### 可选字体 {#可选字体}


#### Sarasa Gothic / Sarasa Mono SC Nerd {#sarasa-gothic-sarasa-mono-sc-nerd}

[Sarasa Gothic](https://github.com/be5invis/Sarasa-Gothic) 由 Iosevka 的作者 Belleve Invis 开发，将 Iosevka 与思源黑体（Source Han Sans）合并。它保留了 Iosevka 的编程连字和等宽特性，同时完整支持 CJK 字符集。Sarasa Mono SC 是等宽无衬线版本， `Nerd Font` 变体额外包含 Powerline 符号和文件类型图标。

| 子系列        | 特点               |
|------------|------------------|
| Sarasa Gothic | 标准等宽，符号宽度可能超过一个字符格 |
| Sarasa Term   | 终端优化，箭头和几何符号变窄 |
| Sarasa Fixed  | 最严格等宽，禁用所有连字 |
| Sarasa Slab   | 衬线版本           |

Sarasa 的中英文宽度严格 2:1，在 Org Mode 表格中完美对齐。


#### Maple Mono CN {#maple-mono-cn}

[Maple Mono](https://font.subf.dev/zh-cn/) 是一款专为编程设计的字体，其 CN 变体内置中文支持，同样保证中英文 2:1 等宽。还提供 Nerd Font 变体（ `Maple Mono NF CN` ），包含 Powerline 符号。


### 配置方法 {#配置方法}

```emacs-lisp
(when (display-graphic-p)
  (set-face-attribute 'default nil
		      :family "Sarasa Mono SC Nerd"
		      :height 140)
  (set-face-attribute 'fixed-pitch nil
		      :family "Sarasa Mono SC Nerd"
		      :height 1.0)
  (set-face-attribute 'variable-pitch nil
		      :family "Sarasa Mono SC Nerd"
		      :height 1.0))
```

或者使用 Maple Mono CN：

```emacs-lisp
(when (display-graphic-p)
  (set-face-attribute 'default nil
		      :family "Maple Mono NF CN"
		      :height 140))
```


### 优缺点 {#优缺点}

`优点` ：

-   配置极简，一个字体搞定一切
-   中英文完美 2:1 对齐，表格不会错位
-   不需要调整 `face-font-rescale-alist`
-   缩放（ `C-x C-+` / `C-x C--` ）对中英文同时生效

`缺点` ：

-   中文和英文无法分别选择最满意的字体——中文字形质量取决于字体作者的 CJK 部分，而英文设计也受 CJK 宽度约束
-   Sarasa 的中文字形基于思源黑体，虽然质量不错，但不如专门的中文楷体或宋体有个性
-   字体文件较大（Sarasa 完整安装约 300MB+）


## 方案二：中英文字体分别设置 + face-font-rescale-alist {#方案二-中英文字体分别设置-plus-face-font-rescale-alist}

如果你对中英文字体各有偏好——比如英文用 JetBrains Mono，中文用 LXGW WenKai——就需要分别设置，然后通过 `face-font-rescale-alist` 调整宽度比例来保证等宽。


### face-font-rescale-alist {#face-font-rescale-alist}

`face-font-rescale-alist` 是 Emacs 的一个变量，用于指定字体的缩放比例。其格式为 `(font-name . scale-factor)` 的列表。当 Emacs 渲染某个字体时，会查找该字体名是否匹配列表中的条目，若匹配则将字体的像素宽度乘以缩放因子。

关键点： `这个缩放对中文和英文同时生效` ，包括 `C-x C-+` 的缩放操作。所以如果你之前给中文字体单独设了 `:size` ，会导致缩放时中文不跟随英文变化——改用 `face-font-rescale-alist` 就不会。

```emacs-lisp
(setq face-font-rescale-alist
      '(("LXGW WenKai" . 1.2)
	("Microsoft YaHei" . 1.2)
	("WenQuanYi Zen Hei" . 1.2)))
```

`注意` ：修改 `face-font-rescale-alist` 后 `必须重启 Emacs` 才能生效（这是一个 [已知的 bug](https://debbugs.gnu.org/db/17/1785.html) ）。


### 如何确定缩放比例 {#如何确定缩放比例}

确定 `face-font-rescale-alist` 缩放比例的核心思路：让 `2 个英文字符宽度 = 1 个中文字符宽度` 。

以下是常用英文等宽字体与中文字体搭配时的 `参考缩放比例` （基于 14pt、Windows 系统）。 `实际值因系统 DPI、字号和字体版本而异` ，请以实际测量为准。

| 英文字体         | 中文字体          | 缩放比例 | 说明                   |
|--------------|---------------|------|----------------------|
| JetBrains Mono   | LXGW WenKai Mono  | 1.20 | 最常见搭配，LXGW 偏宽  |
| JetBrains Mono   | Microsoft YaHei   | 1.20 | YaHei 宽度接近 LXGW    |
| JetBrains Mono   | Sarasa Mono SC    | 1.00 | Sarasa 本身就是 2:1 设计 |
| JetBrains Mono   | WenQuanYi Zen Hei | 1.20 | 文泉驿偏宽             |
| Source Code Pro  | LXGW WenKai Mono  | 1.18 | Source Code Pro 略宽于 JB |
| Source Code Pro  | Microsoft YaHei   | 1.18 |                        |
| Consolas         | Microsoft YaHei   | 1.22 | Consolas 偏窄          |
| Consolas         | LXGW WenKai Mono  | 1.22 |                        |
| Fira Code        | LXGW WenKai Mono  | 1.17 | Fira Code 中等宽度     |
| Fira Code        | Microsoft YaHei   | 1.17 |                        |
| Iosevka Fixed    | LXGW WenKai Mono  | 1.23 | Iosevka 较窄           |
| Iosevka Fixed    | Sarasa Mono SC    | 1.00 | Sarasa 2:1             |
| Ubuntu Mono      | LXGW WenKai Mono  | 1.17 |                        |
| DejaVu Sans Mono | LXGW WenKai Mono  | 1.17 |                        |
| Cascadia Code    | LXGW WenKai Mono  | 1.18 |                        |
| Cascadia Code    | Microsoft YaHei   | 1.18 |                        |
| Menlo            | LXGW WenKai Mono  | 1.22 | macOS 默认，偏窄       |
| SF Mono          | PingFang SC       | 1.22 | macOS 搭配             |

`经验法则` ：

-   英文字体越窄，中文字体的缩放比例越大
-   Sarasa Mono SC / Sarasa Gothic SC 本身遵循 2:1 宽度设计，搭配任何英文字体都不需要额外缩放（比例 1.0）
-   LXGW WenKai 系列、Microsoft YaHei、WenQuanYi Zen Hei 的中文宽度相近，缩放比例通常在 1.17–1.23 之间
-   不同字号下比例可能微调——14pt 时的 1.20 到 18pt 可能变成 1.18


### 配置 default / fixed-pitch / variable-pitch {#配置-default-fixed-pitch-variable-pitch}

在方案二中，我们需要分别设置三个核心 Face：

-   `default` — 全局默认字体（通常是等宽英文字体）
-   `fixed-pitch` — 等宽字体，用于代码、表格等需要对齐的内容
-   `variable-pitch` — 比例字体，用于正文阅读

<!--listend-->

```emacs-lisp
(when (display-graphic-p)
  (set-face-attribute 'default nil
		      :family "JetBrains Mono"
		      :height 140
		      :weight 'medium)
  (set-face-attribute 'fixed-pitch nil
		      :family "JetBrains Mono"
		      :height 1.0)
  (set-face-attribute 'variable-pitch nil
		      :family "Source Sans Pro"
		      :height 1.0)

  (dolist (script '(han cjk-misc bopomofo kana))
    (set-fontset-font t script (font-spec :family "LXGW WenKai Mono")))

  (setq face-font-rescale-alist
	'(("LXGW WenKai" . 1.2)
	  ("LXGW WenKai Mono" . 1.2))))
```

`:height` 的规则： `default` Face 必须使用绝对值（pt × 10），其他 Face 使用相对值（浮点数，1.0 表示与 default 相同）。这确保 `text-scale-adjust` （ `C-x C-+` ）能正确缩放所有字体。


### Org Mode 中 fixed-pitch 的使用 {#org-mode-中-fixed-pitch-的使用}

在 Org Mode 中启用 `variable-pitch-mode` 后，正文使用比例字体，但表格、代码块等需要对齐的元素必须使用等宽字体。方法是让这些 Face 继承 `fixed-pitch` ：

```emacs-lisp
(custom-theme-set-faces
 'user
 '(org-block ((t (:inherit fixed-pitch))))
 '(org-code ((t (:inherit (shadow fixed-pitch)))))
 '(org-table ((t (:inherit fixed-pitch))))
 '(org-verbatim ((t (:inherit (shadow fixed-pitch)))))
 '(org-meta-line ((t (:inherit (font-lock-comment-face fixed-pitch)))))
 '(org-special-keyword ((t (:inherit (font-lock-comment-face fixed-pitch)))))
 '(org-property-value ((t (:inherit fixed-pitch))) t)
 '(org-indent ((t (:inherit (org-hide fixed-pitch)))))
 '(org-document-info-keyword ((t (:inherit (shadow fixed-pitch)))))
 '(org-tag ((t (:inherit (shadow fixed-pitch) :weight bold :height 0.8)))))
```

然后在 Org Mode 中自动启用 `variable-pitch-mode` ：

```emacs-lisp
(add-hook 'org-mode-hook 'variable-pitch-mode)
(add-hook 'org-mode-hook 'visual-line-mode)
```

`visual-line-mode` 配合比例字体使用，长行自动折行而非硬换行。


### 优缺点 {#优缺点}

`优点` ：

-   中英文字体各取所长
-   可以在正文使用比例字体（如 Source Sans Pro），在代码和表格使用等宽字体
-   灵活度高

`缺点` ：

-   `face-font-rescale-alist` 的缩放值在不同字号下可能不同——14pt 时的比例到了 18pt 可能就不准了。有些用户甚至为不同字号维护不同的缩放值
-   缩放值在不同操作系统上可能不同（macOS 和 Linux 的字体渲染引擎不同）
-   修改 `face-font-rescale-alist` 后必须重启 Emacs
-   Org Mode 表格的对齐是"软对齐"——依赖于字符的物理宽度比例，如果比例稍有偏差，长表格就会逐渐错位


## 方案三：使用 fontset 为特定 Face 单独设置字体 {#方案三-使用-fontset-为特定-face-单独设置字体}

方案一和方案二都是在全局 Fontset 层面设置中英文字体映射，所有 Face 共享同一套中英字体组合。但有时你需要更精细的控制——比如 Org Mode 标题使用楷体，表格使用等宽黑体，代码块使用 Nerd Font。

这时需要为特定的 Face 创建独立的 Fontset，每个 Fontset 可以有不同的英文字体和中文字体映射。


### 核心函数 {#核心函数}

```emacs-lisp
(defun +convert-face-name (face-symbol)
  "Convert a hyphenated face symbol (e.g., 'org-level-1) to a plain string without hyphens (e.g., \"orglevel1\")."
  (replace-regexp-in-string "-" "" (symbol-name face-symbol)))

(defun +setup-fontset (face en-font cn-font)
  "Set up a fontset for a given face with separate English and Chinese fonts.
FACE is the face symbol (e.g., 'org-level-1).
EN-FONT is the English font family name (string).
CN-FONT is the Chinese font family name (string)."
  (let ((+fontset-name (concat "fontset-" (+convert-face-name face))))
    (create-fontset-from-fontset-spec
     (font-xlfd-name
      (font-spec :family en-font
		 :registry +fontset-name)))
    (set-fontset-font +fontset-name 'han (font-spec :family cn-font))
    (set-face-attribute face nil :fontset +fontset-name)))
```


### 工作原理 {#工作原理}

`+setup-fontset` 做了三件事：

1.  `创建 Fontset` — 基于 `en-font` 创建一个名为 `fontset-<facename>` 的新 Fontset。 `create-fontset-from-fontset-spec` 需要一个 XLFD 格式的字体名， `font-xlfd-name` 函数将 `font-spec` 对象转换为 XLFD 格式，同时指定新 Fontset 的注册名（ `registry` ）。
2.  `设置中文回退` — 用 `set-fontset-font` 将 `han` 脚本映射到 `cn-font` 。这个 Fontset 中，英文用 `en-font` ，汉字用 `cn-font` 。
3.  `应用到 Face` — 用 `set-face-attribute` 的 `:fontset` 属性将该 Fontset 绑定到指定的 Face。


### 配置示例 {#配置示例}

```emacs-lisp
(when (display-graphic-p)
  (set-face-attribute 'default nil
		      :family "JetBrains Mono"
		      :height 140
		      :weight 'medium)
  (dolist (script '(han cjk-misc bopomofo kana))
    (set-fontset-font t script (font-spec :family "Sarasa Mono SC Nerd")))

  (+setup-fontset 'org-level-1 "Iosevka Term" "LXGW WenKai")
  (+setup-fontset 'org-level-2 "Iosevka Term" "LXGW WenKai")
  (+setup-fontset 'org-level-3 "Iosevka Term" "LXGW WenKai")
  (+setup-fontset 'org-level-4 "Iosevka Term" "LXGW WenKai")
  (+setup-fontset 'org-level-5 "Iosevka Term" "LXGW WenKai")
  (+setup-fontset 'org-level-6 "Iosevka Term" "LXGW WenKai")
  (+setup-fontset 'org-level-7 "Iosevka Term" "LXGW WenKai")
  (+setup-fontset 'org-level-8 "Iosevka Term" "LXGW WenKai")
  (+setup-fontset 'org-table "JetBrains Mono" "Sarasa Mono SC Nerd")
  (+setup-fontset 'org-block "JetBrains Mono" "Sarasa Mono SC Nerd")
  (+setup-fontset 'org-code "JetBrains Mono" "Sarasa Mono SC Nerd")

  (setq face-font-rescale-alist
	'(("Sarasa Mono SC" . 1.0)
	  ("LXGW WenKai" . 1.2))))
```

这个配置的效果是：

-   全局默认：JetBrains Mono + Sarasa Mono SC Nerd
-   Org 标题（ `org-level-1` 到 `org-level-8` ）：Iosevka Term + LXGW WenKai（楷体，更具文学气质）
-   Org 表格和代码块：JetBrains Mono + Sarasa Mono SC Nerd（严格 2:1 等宽，保证对齐）


### 需要对齐的 Face 列表 {#需要对齐的-face-列表}

在 Org Mode 中，以下 Face 需要使用中英文等宽字体才能正确对齐：

| Face                   | 用途                          | 需要等宽的原因 |
|------------------------|-----------------------------|---------|
| `org-table`            | 表格                          | 表格列对齐 |
| `org-block`            | 代码块                        | 代码缩进和对齐 |
| `org-block-begin-line` | 代码块开始行                  | 与代码块字体一致 |
| `org-block-end-line`   | 代码块结束行                  | 与代码块字体一致 |
| `org-code`             | 行内代码（ `~code~` ）        | 与代码块字体一致 |
| `org-verbatim`         | 等宽文本（ <kbd>=verbatim=</kbd> ） | 保持等宽显示 |
| `org-checkbox`         | 复选框                        | 与列表项对齐 |
| `org-indent`           | 缩进区域                      | 缩进对齐 |
| `org-meta-line`        | 元数据行（ `#+KEYWORD` ）     | 代码行对齐 |
| `org-special-keyword`  | 特殊关键词                    | 代码行对齐 |
| `org-property-value`   | 属性值                        | 与属性名对齐 |


### 优缺点 {#优缺点}

`优点` ：

-   最精细的控制粒度——每个 Face 可以有独立的中英字体组合
-   标题可以用有气质的楷体，表格用严格等宽的黑体，各得其所
-   不受全局 `face-font-rescale-alist` 的单一缩放值限制

`缺点` ：

-   配置最复杂，需要理解 Fontset 的创建和绑定机制
-   每增加一个需要特殊字体的 Face，就需要调用一次 `+setup-fontset`
-   缩放时，自定义 Fontset 中的中文字体是否跟随缩放取决于具体配置


## 常用的开源免费等宽英文字体 {#常用的开源免费等宽英文字体}

以下是适合编程使用的开源等宽英文字体，按字母序排列：

| 字体                   | 许可                | 字形宽度 | 特点                     | 与中文字体的宽度比 |
|----------------------|-------------------|------|------------------------|-----------|
| Cascadia Code          | OFL 1.1             | 标准  | Windows Terminal 默认字体，连字 | 需 1.15-1.20 |
| Fira Code              | OFL 1.1             | 标准  | 连字丰富，社区活跃       | 需 1.15-1.20 |
| Hack                   | OFL 1.1 + MIT       | 标准  | 清晰简洁，适合终端       | 需 1.15-1.20 |
| IBM Plex Mono          | OFL 1.1             | 标准  | IBM 设计系统             | 需 1.15-1.20 |
| Iosevka / Iosevka Term | OFL 1.1             | 1/2em | 极窄字形，高度可定制     | 需 1.20-1.30 |
| JetBrains Mono         | OFL 1.1             | 标准  | 行距大，可读性好         | 需 1.15-1.20 |
| Maple Mono             | OFL 1.1             | 标准  | 内置 CN 变体，中英等宽   | CN 变体为 1.0 |
| Monaspace Neon         | OFL 1.1             | 标准  | GitHub Monaspace 系列    | 需 1.15-1.20 |
| Source Code Pro        | OFL 1.1             | 标准  | Adobe 出品，设计规范     | 需 1.15-1.20 |
| Ubuntu Mono            | UBUNTU FONT LICENCE | 标准  | Ubuntu 系统字体          | 需 1.15-1.20 |

`宽度比说明` ："需 1.15-1.20"表示若使用该英文字体搭配标准中文字体（如思源黑体），中文字体需要约 1.15 到 1.20 的缩放因子才能达到 2:1 等宽。实际值取决于具体字体和字号，需实测调整。

Iosevka 的字形宽度为 1/2em（比其他字体更窄），所以需要更大的中文缩放值。


## 常用的开源免费中文字体 {#常用的开源免费中文字体}

| 字体                         | 许可    | 类型 | 特点                         |
|----------------------------|-------|----|----------------------------|
| LXGW WenKai / 落霞孤鹜文楷   | OFL 1.1 | 楷体 | 手写风格，适合正文和标题     |
| LXGW WenKai Mono / 文楷等宽  | OFL 1.1 | 楷体等宽 | 文楷的等宽版本，中英 2:1     |
| Noto Sans CJK SC / 思源黑体  | OFL 1.1 | 黑体 | Google + Adobe 联合开发，覆盖全 |
| Noto Serif CJK SC / 思源宋体 | OFL 1.1 | 宋体 | 思源的衬线版本，适合长文阅读 |
| Source Han Sans SC / 思源黑体 | OFL 1.1 | 黑体 | 同 Noto Sans CJK SC（Adobe 命名） |
| Source Han Serif SC / 思源宋体 | OFL 1.1 | 宋体 | 同 Noto Serif CJK SC         |
| Sarasa Gothic / 更纱黑体     | OFL 1.1 | 黑体等宽 | Iosevka + 思源黑体，中英 2:1 |
| Maple Mono CN                | OFL 1.1 | 黑体等宽 | Maple Mono 的中文变体，中英 2:1 |
| WenQuanYi Micro Hei / 文泉驿微米黑 | GPL-2.0 | 黑体 | 老牌开源中文字体             |
| WenQuanYi Zen Hei / 文泉驿正黑 | GPL-2.0 | 黑体 | 文泉驿系列                   |


## 方案选择指南 {#方案选择指南}

| 需求                     | 推荐方案 | 推荐字体组合                                      |
|------------------------|------|---------------------------------------------|
| 不想折腾，只要能对齐     | 方案一 | Sarasa Mono SC Nerd 或 Maple Mono NF CN           |
| 英文有偏好，中文用等宽回退 | 方案二 | JetBrains Mono + Sarasa Mono SC Nerd              |
| 正文用比例字体，代码用等宽 | 方案二 | Source Sans Pro + JetBrains Mono + Sarasa Mono SC |
| 标题用楷体，表格用黑体，每个 Face 精细控制 | 方案三 | Iosevka + LXGW WenKai + Sarasa Mono SC Nerd       |


## 完整配置示例 {#完整配置示例}

以下是一个综合了方案二和方案三的完整配置，适用于 Windows 系统：

```emacs-lisp
(defun +convert-face-name (face-symbol)
  "Convert a hyphenated face symbol (e.g., 'org-level-1) to a plain string without hyphens (e.g., \"orglevel1\")."
  (replace-regexp-in-string "-" "" (symbol-name face-symbol)))

(defun +setup-fontset (face en-font cn-font)
  "Set up a fontset for a given face with separate English and Chinese fonts.
FACE is the face symbol (e.g., 'org-level-1).
EN-FONT is the English font family name (string).
CN-FONT is the Chinese font family name (string)."
  (let ((+fontset-name (concat "fontset-" (+convert-face-name face))))
    (create-fontset-from-fontset-spec
     (font-xlfd-name
      (font-spec :family en-font
		 :registry +fontset-name)))
    (set-fontset-font +fontset-name 'han (font-spec :family cn-font))
    (set-face-attribute face nil :fontset +fontset-name)))

(when (display-graphic-p)
  (let ((en-font "JetBrains Mono")
	(cn-font "Sarasa Mono SC Nerd")
	(cn-serif-font "LXGW WenKai"))
    (set-face-attribute 'default nil
			:family en-font
			:height 140
			:weight 'medium)
    (set-face-attribute 'fixed-pitch nil
			:family en-font
			:height 1.0)
    (set-face-attribute 'variable-pitch nil
			:family "Source Sans Pro"
			:height 1.0)

    (dolist (script '(han cjk-misc bopomofo kana))
      (set-fontset-font t script (font-spec :family cn-font)))

    (setq face-font-rescale-alist
	  `((,cn-font . 1.0)
	    (,cn-serif-font . 1.2)))

    (dolist (face '(org-level-1 org-level-2 org-level-3 org-level-4
		    org-level-5 org-level-6 org-level-7 org-level-8
		    org-document-title))
      (+setup-fontset face "Iosevka Term" cn-serif-font))

    (custom-theme-set-faces
     'user
     '(org-block ((t (:inherit fixed-pitch))))
     '(org-code ((t (:inherit (shadow fixed-pitch)))))
     '(org-table ((t (:inherit fixed-pitch))))
     '(org-verbatim ((t (:inherit (shadow fixed-pitch)))))
     '(org-meta-line ((t (:inherit (font-lock-comment-face fixed-pitch)))))
     '(org-special-keyword ((t (:inherit (font-lock-comment-face fixed-pitch)))))
     '(org-property-value ((t (:inherit fixed-pitch))) t)
     '(org-indent ((t (:inherit (org-hide fixed-pitch)))))
     '(org-document-info-keyword ((t (:inherit (shadow fixed-pitch)))))
     '(org-tag ((t (:inherit (shadow fixed-pitch) :weight bold :height 0.8)))))))
```


## 常见问题 {#常见问题}


### 为什么修改 face-font-rescale-alist 后不生效？ {#为什么修改-face-font-rescale-alist-后不生效}

`face-font-rescale-alist` 修改后 `必须重启 Emacs` 。这是一个 [已知的 bug](https://debbugs.gnu.org/db/17/1785.html) （#1785），从 2010 年报告至今。不要试图用 `eval-buffer` 或重新求值来让它生效，直接重启。


### 为什么中文字体缩放时不跟随英文？ {#为什么中文字体缩放时不跟随英文}

如果你在 `set-fontset-font` 时给中文字体指定了 `:size` 参数，中文的大小就是固定的，不会跟随 `C-x C-+` 缩放。解决方法： 不设 `:size` ，改用 `face-font-rescale-alist` 。


### 如何查看当前字符使用的字体？ {#如何查看当前字符使用的字体}

用 `M-x describe-char` 查看光标下字符的详细信息，包括 Face、Fontset、字体名、编码等。


### set-frame-font 和 set-face-attribute 有什么区别？ {#set-frame-font-和-set-face-attribute-有什么区别}

`set-frame-font` 只修改当前 Frame（或指定 Frame）的字体，且默认 `不应用于子 Frame` （child frame），这会导致 Corfu 等使用子 Frame 的补全菜单字体不一致。解决方法：

```emacs-lisp
(set-frame-font "JetBrains Mono 14" nil t)
```

第三个参数 `t` 表示应用到所有已有的图形化 Frame。

`set-face-attribute 'default nil ...` 修改 `default` Face 的属性，对所有 Frame 生效（包括子 Frame），因此更推荐使用。


### 如何在终端模式中配置字体？ {#如何在终端模式中配置字体}

Emacs 终端模式（ `emacs -nw` ）中字体由终端模拟器控制，Emacs 的字体配置不生效。在终端模拟器的设置中配置字体即可。


## 参考链接 {#参考链接}

-   [Emacs Manual - Fonts](https://www.gnu.org/software/emacs/manual/html_node/emacs/Fonts.html)
-   [Modus Themes - Font configurations for Org](https://www.gnu.org/software/emacs/manual/html_node/modus-themes/DIY-Font-configurations-for-Org-and-others.html)
-   [Emacs, fonts and fontsets - Alan Third](https://idiocy.org/emacs-fonts-and-fontsets.html)
-   [Sarasa Gothic - Iosevka + 思源黑体](https://github.com/be5invis/Sarasa-Gothic)
-   [Iosevka - 可变编程字体](https://github.com/be5invis/Iosevka)
-   [Maple Mono - 编程字体](https://font.subf.dev/zh-cn/)
-   [LXGW WenKai - 落霞孤鹜文楷](https://github.com/lxgw/LxgwWenKai)
-   [Beautifying Org Mode in Emacs](https://zzamboni.org/post/beautifying-org-mode-in-emacs/)
-   [Setting the Default Font for Emacs](https://emacsredux.com/blog/2023/03/16/setting-the-default-font-for-emacs/)
-   [Font configuration in Emacs - Jihuan Tian](https://jihuan-tian.github.io/computer/2026/04/29/font-configuration-in-emacs.html)
