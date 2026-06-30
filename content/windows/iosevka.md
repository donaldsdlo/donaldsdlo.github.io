---
title: "Iosevka — 为编程而生的可变字体"
author: ["Donald Lo"]
date: 2026-06-29
lastmod: 2026-06-29T21:17:00+08:00
tags: ["Iosevka", "字体", "编程字体"]
draft: false
---

<div class="ox-hugo-toc toc">

<div class="heading">&#30446;&#24405;</div>

- [为什么选择 Iosevka](#为什么选择-iosevka)
    - [Iosevka 是什么](#iosevka-是什么)
    - [设计哲学](#设计哲学)
    - [与其他编程字体对比](#与其他编程字体对比)
- [Iosevka 的八个子系列](#iosevka-的八个子系列)
    - [Iosevka（默认等宽）](#iosevka-默认等宽)
    - [Iosevka Term](#iosevka-term)
    - [Iosevka Fixed](#iosevka-fixed)
    - [Iosevka Slab / Term Slab / Fixed Slab](#iosevka-slab-term-slab-fixed-slab)
    - [Iosevka Aile](#iosevka-aile)
    - [Iosevka Etoile](#iosevka-etoile)
    - [子系列选择指南](#子系列选择指南)
- [字体特性](#字体特性)
    - [字重](#字重)
    - [宽度](#宽度)
    - [倾斜](#倾斜)
    - [语言覆盖](#语言覆盖)
- [连字（Ligatures）](#连字-ligatures)
    - [默认连字](#默认连字)
    - [语言特定连字](#语言特定连字)
    - [在编辑器中控制连字](#在编辑器中控制连字)
- [Stylistic Sets（风格集）](#stylistic-sets-风格集)
    - [如何启用风格集](#如何启用风格集)
- [Character Variants（字符变体）](#character-variants-字符变体)
    - [常用字符变体](#常用字符变体)
        - [数字 0（cv10）— 区分 0 和 O](#数字-0-cv10-区分-0-和-o)
        - [数字 1（cv01）— 区分 1 和 l](#数字-1-cv01-区分-1-和-l)
        - [字母 a（cv26）— 单层 vs 双层](#字母-a-cv26-单层-vs-双层)
        - [字母 g（cv36）](#字母-g-cv36)
        - [星号 \*（cv49）](#星号-cv49)
        - [其他值得关注的字符变体](#其他值得关注的字符变体)
    - [Cherry-Picking 自定义](#cherry-picking-自定义)
- [安装 Iosevka](#安装-iosevka)
    - [Windows 安装](#windows-安装)
        - [从 GitHub Releases 下载](#从-github-releases-下载)
        - [通过 Scoop 安装](#通过-scoop-安装)
        - [通过 Chocolatey 安装](#通过-chocolatey-安装)
    - [macOS 安装](#macos-安装)
        - [通过 Homebrew 安装](#通过-homebrew-安装)
        - [手动安装](#手动安装)
    - [Linux / Arch Linux 安装](#linux-arch-linux-安装)
        - [Arch Linux（pacman）](#arch-linux-pacman)
        - [手动安装（所有 Linux 发行版）](#手动安装-所有-linux-发行版)
        - [一键下载所有 TTC 包](#一键下载所有-ttc-包)
        - [Void Linux](#void-linux)
        - [Fedora](#fedora)
    - [国内镜像下载](#国内镜像下载)
- [在编辑器和终端中配置](#在编辑器和终端中配置)
    - [VS Code / Cursor](#vs-code-cursor)
    - [Vim / Neovim](#vim-neovim)
    - [Emacs](#emacs)
    - [Windows Terminal](#windows-terminal)
    - [Alacritty](#alacritty)
    - [Kitty](#kitty)
    - [其他终端模拟器](#其他终端模拟器)
- [自定义构建](#自定义构建)
    - [准备环境](#准备环境)
    - [private-build-plans.toml 配置](#private-build-plans-dot-toml-配置)
    - [构建命令](#构建命令)
    - [配置示例 — 精简的终端字体](#配置示例-精简的终端字体)
    - [使用 Docker 构建](#使用-docker-构建)
    - [使用在线 Customizer](#使用在线-customizer)
- [Sarasa Gothic — CJK 用户的选择](#sarasa-gothic-cjk-用户的选择)
    - [Iosevka + CJK 字体回退方案](#iosevka-plus-cjk-字体回退方案)
- [常见问题](#常见问题)
        - [Iosevka 和 Iosevka Term 有什么区别？](#iosevka-和-iosevka-term-有什么区别)
        - [Iosevka Fixed 是什么？什么时候用？](#iosevka-fixed-是什么-什么时候用)
        - [如何选择字重？](#如何选择字重)
        - [连字在终端中不显示？](#连字在终端中不显示)
        - [如何区分 0 和 O？](#如何区分-0-和-o)
        - [为什么自定义构建这么慢？](#为什么自定义构建这么慢)
        - [Iosevka 在 Java 应用中显示异常？](#iosevka-在-java-应用中显示异常)
        - [如何在浏览器中使用 Iosevka？](#如何在浏览器中使用-iosevka)
- [参考链接](#参考链接)

</div>
<!--endtoc-->



## 为什么选择 Iosevka {#为什么选择-iosevka}


### Iosevka 是什么 {#iosevka-是什么}

[Iosevka](https://github.com/be5invis/Iosevka)（发音 [ˌjɔˈseβ.kʰa]）是由 [Belleve Invis](https://github.com/be5invis)（aka be5invis）设计和开发的一款开源字体家族。它是一个 `无衬线 + 衬线` 、 `等宽 + 准比例` 的混合型字体家族，专门为 `编写代码` 、 `终端使用` 和 `技术文档排版` 而设计。

Iosevka 最大的特点是 `高度可定制` ——它提供了 144 个可配置的字符变体和 19 个预定义风格集（Stylistic Sets），让你可以精确地打造一个符合个人审美和编程习惯的字体。无论你偏好 Consolas 的圆润、JetBrains Mono 的现代感，还是 Pragmata Pro 的紧凑，Iosevka 都能通过配置还原出类似的风格，同时保持自身的设计一致性。

Iosevka 使用 [SIL Open Font License 1.1](https://github.com/be5invis/Iosevka/blob/main/LICENSE.md) 开源许可，可以自由使用、修改和分发。


### 设计哲学 {#设计哲学}

Iosevka 的设计有以下几个核心理念：

-   `空间高效` — Iosevka 等宽字体的默认字形宽度仅为 `1/2em` ，比 Fira Code、IBM Plex Mono 等常见编程字体更窄。在相同屏幕宽度下，你可以显示更多的代码列。对于分屏编辑或小屏幕开发来说，这是一个显著的优势。
-   `窄体优先` — 字形设计紧凑但不拥挤。字符间的间距经过精心调整，使得在密集代码中依然保持良好的可读性。
-   `变体丰富` — 几乎每个容易混淆的字符（如 `0` 和 `O` 、 `1` 和 `l` 、 `{` 和 `(` ）都有多种形态可选，你可以选择最不容易认错的组合。
-   `连字支持` — 支持 <kbd>&gt;=</kbd> <kbd>===</kbd> <kbd>-&gt;</kbd> <kbd>=&gt;</kbd> 等编程常见符号的连字（Ligatures），并且提供 `21 种语言特定连字集` ，覆盖 JavaScript、Haskell、Julia、F#、Coq 等语言。
-   `准比例字体` — 除了等宽版本，Iosevka 还提供准比例（Quasi-Proportional）版本 Aile 和 Etoile，适合撰写技术文档和日常文本。在准比例模式下，窄字母（如 `i` 、 `l` ）会更窄，宽字母（如 `m` 、 `w` ）会更宽，阅读体验更接近自然排版。


### 与其他编程字体对比 {#与其他编程字体对比}

| 特性    | Iosevka        | Fira Code | JetBrains Mono | Cascadia Code | Source Code Pro |
|-------|----------------|-----------|----------------|---------------|-----------------|
| 字形宽度 | 1/2em（最窄）  | 标准      | 标准           | 标准          | 标准            |
| 可配置字符变体 | 144 个         | 无        | 无             | 无            | 无              |
| 预定义风格集 | 19 个          | 无        | 无             | 无            | 无              |
| 连字    | 默认 + 21 种语言集 | 默认      | 默认           | 默认          | 无              |
| 衬线变体 | 有（Slab/Etoile） | 无        | 无             | 无            | 无              |
| 准比例变体 | 有（Aile/Etoile） | 无        | 无             | 无            | 无              |
| 自定义构建 | 支持           | 不支持    | 不支持         | 不支持        | 不支持          |
| 开源许可 | OFL 1.1        | OFL 1.1   | OFL 1.1        | OFL 1.1       | OFL 1.1         |
| CJK 支持 | 无（用 Sarasa） | 无        | 无             | 无            | 无              |

Iosevka 的核心竞争力在于 `可定制性` 和 `空间效率` 。如果你对字体的细节有偏好（比如数字 0 是否带斜杠、字母 a 是单层还是双层），Iosevka 是目前唯一能让你精确控制这些细节的开源编程字体。


## Iosevka 的八个子系列 {#iosevka-的八个子系列}

Iosevka 家族包含 8 个子系列，它们共享相同的字符集和基本设计，但在间距策略、衬线风格和等宽/比例模式上有所不同。


### Iosevka（默认等宽） {#iosevka-默认等宽}

标准等宽版本，字形宽度 1/2em，支持连字。这是最常用的版本，适合作为代码编辑器字体。符号（如箭头、几何图形）保持标准宽度，可能比终端列宽更宽。


### Iosevka Term {#iosevka-term}

为终端模拟器优化的等宽版本。与标准版相比，Term 版本的箭头和几何符号会变窄，以适应终端对列数的严格要求。如果你在终端中发现符号对齐有问题，换用 Term 版本通常可以解决。


### Iosevka Fixed {#iosevka-fixed}

最严格的等宽版本，在 Term 的基础上进一步 `禁用了所有连字` 。适用于不支持连字的环境（如某些老旧终端、日志查看工具、 `less` 命令等），或当你不希望连字干扰代码阅读时。


### Iosevka Slab / Term Slab / Fixed Slab {#iosevka-slab-term-slab-fixed-slab}

Slab 衬线版本，与对应的 Sans 版本（Iosevka / Term / Fixed）结构相同，但在笔画末端加入了方头衬线（Slab Serif）。Slab 版本的视觉风格更接近 Courier 或 Roboto Slab，给人一种经典打字机的感觉。三个变体（Slab / Term Slab / Fixed Slab）的区别与 Sans 版本完全对应。


### Iosevka Aile {#iosevka-aile}

准比例（Quasi-Proportional）无衬线版本，适合撰写技术文档和日常文本。在 Aile 中，不同字符有不同的宽度：窄字母 `i` 、 `l` 更窄，宽字母 `m` 、 `w` 更宽。这种设计使得文本排版更自然，阅读更舒适，同时仍然保持编程字体的清晰度。Aile 只有一种宽度（Normal），没有 Extended 变体。


### Iosevka Etoile {#iosevka-etoile}

准比例衬线版本，与 Aile 结构相同但带有 Slab 衬线。适合在技术文档中需要衬线风格的场合。


### 子系列选择指南 {#子系列选择指南}

| 使用场景 | 推荐子系列               | 理由                |
|------|---------------------|-------------------|
| 代码编辑器 | Iosevka 或 Iosevka Term  | Term 版符号更窄，标准版符号更美观 |
| 终端模拟器 | Iosevka Term             | 符号宽度适配终端列要求 |
| 不需要连字 | Iosevka Fixed            | 无连字，最大兼容性  |
| 偏好衬线风格 | Iosevka Slab / Term Slab | 经典打字机感        |
| 技术文档 | Iosevka Aile             | 准比例，阅读更舒适  |
| 技术文档（衬线） | Iosevka Etoile           | 准比例 + 衬线       |
| 日志/管道输出 | Iosevka Fixed            | 无连字，不会干扰日志阅读 |


## 字体特性 {#字体特性}


### 字重 {#字重}

Iosevka 提供 9 种字重（Weight），从细到粗：

| 字重名称   | 字重值 | 典型用途       |
|--------|-----|------------|
| Thin       | 100 | 大标题、装饰性文本 |
| ExtraLight | 200 | 注释、辅助文本 |
| Light      | 300 | 长时间阅读、低对比度环境 |
| Regular    | 400 | 正文、代码（默认） |
| Medium     | 500 | 代码（稍微加粗，可读性更好） |
| SemiBold   | 600 | 标题、强调     |
| Bold       | 700 | 粗体强调、标题 |
| ExtraBold  | 800 | 大标题         |
| Heavy      | 900 | 特大标题、高对比度 |

许多开发者偏好 `Medium` （500）或 `SemiBold` （600）字重作为代码字体，因为比 Regular 稍粗的笔画在屏幕上更容易辨识。


### 宽度 {#宽度}

等宽子系列提供两种宽度：

-   `Normal` — 标准 1/2em 宽度，紧凑高效
-   `Extended` — 更宽的字形，字符间留有更多呼吸空间

如果你觉得 Normal 太紧凑，或者使用大屏幕不需要节省空间，Extended 版本会带来更舒适的阅读体验。

准比例子系列（Aile、Etoile）只有 Normal 宽度。


### 倾斜 {#倾斜}

三种倾斜样式：

-   `Upright` — 正体（罗马体），默认
-   `Italic` — 斜体，字形经过专门重新设计（不仅仅是倾斜），如 `a` 变为手写风格
-   `Oblique` — 倾斜体，直接将正体倾斜，不重新设计字形

Italic 和 Oblique 的区别在于：Italic 的某些字母（如 `a` 、 `f` 、 `g` ）会有独立的斜体设计，而 Oblique 只是机械地将正体倾斜。如果你偏好统一的视觉风格，选择 Oblique；如果你想要更传统的斜体效果，选择 Italic。


### 语言覆盖 {#语言覆盖}

Iosevka 支持以下字符范围：

-   `拉丁字母` — 完整覆盖，包括所有变音符号组合
-   `希腊字母` — 包括多调希腊语（Polytonic Greek）
-   `部分西里尔字母` — 覆盖俄语、乌克兰语、白俄罗斯语、保加利亚语等主要斯拉夫语言
-   `IPA 音标` — 国际音标符号
-   `常用标点和符号` — 包括 Box Drawing、Block Elements 等终端绘图字符
-   `Powerline 符号` — 用于终端提示符的箭头和分隔符

官方宣称支持 `248 种语言` ，覆盖了几乎所有使用拉丁字母、希腊字母和西里尔字母的语言。


## 连字（Ligatures） {#连字-ligatures}

连字是 Iosevka 最具视觉吸引力的特性之一。当你在代码中输入 `>=` 时，这些字符会自动组合成一个美观的箭头符号 `→=；`!= 和 `=` 组合成 `≢` 等。


### 默认连字 {#默认连字}

Iosevka 的默认连字集通过 OpenType `calt` （Contextual Alternates）特性启用，覆盖了编程中最常见的符号组合：

-   箭头类：=-&gt; `> <-- <=` &lt;--&gt; &lt;-&gt; &lt;==&gt; =
-   比较类：=== !== &lt;= &gt;= `= !` &lt;&gt;
-   运算类：=/= `/` ~=
-   括号类：=[| |] {| |} (\* \*)
-   标记类：=:: ::: ... ~~+ ++~~ || |||=
-   特殊类：=&lt;!-- &lt;/&gt; &lt;/ /&gt;=

此外，Iosevka 还支持 `长连字` （Long Ligatures），例如用等号构成的长箭头 =---&gt; ===&gt; 或水平线。


### 语言特定连字 {#语言特定连字}

Iosevka 为不同编程语言提供了专门的连字集，每种语言的连字规则略有不同。例如，Haskell 使用反斜杠和斜杠表示逻辑运算，Julia 有自己特殊的箭头语法。

要启用语言特定连字，需要 `关闭默认 calt 连字` 并启用对应的 OpenType 特性标签：

| 特性标签 | 语言       | 说明                          |
|------|----------|-----------------------------|
| `CLIK` | C-Like     | C/C++/Java/Rust 等类 C 语言   |
| `JSPT` | JavaScript | JavaScript/TypeScript         |
| `PHPX` | PHP        | PHP                           |
| `JLIA` | Julia      | Julia                         |
| `RAKU` | Raku       | Raku（原 Perl 6）             |
| `MLXX` | ML         | OCaml/Standard ML             |
| `FSHP` | F#         | F#                            |
| `FSTA` | F\*        | F\*                           |
| `HSKL` | Haskell    | Haskell                       |
| `IDRS` | Idris      | Idris                         |
| `ELMX` | Elm        | Elm                           |
| `PURS` | PureScript | PureScript                    |
| `SWFT` | Swift      | Swift                         |
| `DFNY` | Dafny      | Dafny                         |
| `COQX` | Coq        | Coq                           |
| `MTLB` | MATLAB     | MATLAB                        |
| `VRLG` | Verilog    | Verilog/VHDL                  |
| `WFLM` | Wolfram    | Wolfram Language（Mathematica） |
| `ERLA` | Erlang     | Erlang/Elixir                 |


### 在编辑器中控制连字 {#在编辑器中控制连字}

大多数现代编辑器和终端默认启用 `calt` 连字。如果你需要关闭连字或切换到语言特定连字，需要在编辑器设置中配置 OpenType 特性。

关闭连字（通用方法）——在编辑器中将 `font-ligatures` 设置为 `false` ，或在 CSS 中使用：

```css
font-feature-settings: "calt" 0;
```

启用语言特定连字（以 Haskell 为例）：

```css
font-feature-settings: "calt" 0, "HSKL" 1;
```


## Stylistic Sets（风格集） {#stylistic-sets-风格集}

Iosevka 提供了 19 个预定义风格集（Stylistic Sets，ss01-ss20，无 ss19），每个风格集模拟一种经典编程字体的字符风格。启用风格集会一次性改变多个字符的形态。

| 风格集 | 模拟字体        | 说明                            |
|-----|-------------|-------------------------------|
| `ss01` | Andale Mono     | 早期等宽字体，简洁实用          |
| `ss02` | Anonymous Pro   | 清晰圆润，适合长文本            |
| `ss03` | Consolas        | Windows 经典编程字体，非常流行  |
| `ss04` | Menlo           | macOS 默认编程字体（基于 Vera Sans Mono） |
| `ss05` | Fira Mono       | 现代设计，笔画几何化            |
| `ss06` | Liberation Mono | 开源兼容 Courier New            |
| `ss07` | Monaco          | Mac 经典编程字体，高可读性      |
| `ss08` | Pragmata Pro    | 紧凑型商业编程字体              |
| `ss09` | Source Code Pro | Adobe 出品，标准设计            |
| `ss10` | Envy Code R     | 紧凑圆润，视觉独特              |
| `ss11` | X Window        | 经典 X11 终端字体风格           |
| `ss12` | Ubuntu Mono     | Ubuntu 系统字体等宽版           |
| `ss13` | Lucida          | Lucida Console/Sans Typewriter  |
| `ss14` | JetBrains Mono  | JetBrains 出品，现代流行        |
| `ss15` | IBM Plex Mono   | IBM 设计系统字体                |
| `ss16` | PT Mono         | ParaType 出品，斯拉夫支持好     |
| `ss17` | Recursive Mono  | 可变编程字体，多风格            |
| `ss18` | Input Mono      | David Jonathan Ross 设计        |
| `ss20` | Curly           | 花体风格，字母弯曲更明显        |


### 如何启用风格集 {#如何启用风格集}

在编辑器配置中通过 OpenType 特性标签启用。例如，在 VS Code 的 `settings.json` 中：

```json
{
  "editor.fontLigatures": ["ss03"]
}
```

启用多个风格集：

```json
{
  "editor.fontLigatures": ["ss03", "ss14"]
}
```

在 CSS 中：

```css
font-feature-settings: "ss03" 1;
```

**注意** ：某些软件可能限制 OpenType 特性的数量，如果启用的特性过多，部分特性可能被丢弃。请验证你的配置是否在使用的软件中生效。


## Character Variants（字符变体） {#character-variants-字符变体}

如果风格集的预设风格不完全符合你的需求，你可以使用字符变体（Character Variants） `逐个字符` 地选择形态。Iosevka 提供了 144 个可配置字符，每个字符有多个变体可选。


### 常用字符变体 {#常用字符变体}

以下列出最常用和最容易混淆的字符变体：


#### 数字 0（cv10）— 区分 0 和 O {#数字-0-cv10-区分-0-和-o}

这是编程字体中最关键的区分之一。Iosevka 的数字 0 提供了多达 54 种变体，最常用的几种：

| 变体值      | 设置                       | 效果             |
|----------|--------------------------|----------------|
| `cv10 = 1`  | `zero = 'unslashed'`       | 无斜杠的 0（与 O 容易混淆） |
| `cv10 = 2`  | `zero = 'slashed'`         | 带斜杠的 0（默认，推荐） |
| `cv10 = 3`  | `zero = 'reverse-slashed'` | 带反斜杠的 0     |
| `cv10 = 6`  | `zero = 'dotted'`          | 中心带点的 0     |
| `cv10 = 19` | `zero = 'oval-unslashed'`  | 椭圆形无斜杠     |
| `cv10 = 20` | `zero = 'oval-slashed'`    | 椭圆形带斜杠     |


#### 数字 1（cv01）— 区分 1 和 l {#数字-1-cv01-区分-1-和-l}

| 变体值     | 设置              | 效果           |
|---------|-----------------|--------------|
| `cv01 = 1` | `one = 'line'`    | 仅一条竖线     |
| `cv01 = 2` | `one = 'no-base'` | 无底部衬线（Sans 默认） |
| `cv01 = 3` | `one = 'base'`    | 有底部衬线（Slab 默认） |


#### 字母 a（cv26）— 单层 vs 双层 {#字母-a-cv26-单层-vs-双层}

| 变体值     | 设置                 | 效果            |
|---------|--------------------|---------------|
| `cv26 = 1` | `a = 'double-story'` | 双层 a（默认，编程字体传统） |
| `cv26 = 2` | `a = 'single-story'` | 单层 a（更像手写） |


#### 字母 g（cv36） {#字母-g-cv36}

| 变体值     | 设置                    | 效果        |
|---------|-----------------------|-----------|
| `cv36 = 1` | `g = 'double-story'`    | 双层 g（默认） |
| `cv36 = 2` | `g = 'single-story'`    | 单层 g（开放式尾环） |
| `cv36 = 3` | `g = 'earless-corner'`  | 无耳角型    |
| `cv36 = 4` | `g = 'earless-rounded'` | 无耳圆型    |


#### 星号 \*（cv49） {#星号-cv49}

| 变体值     | 设置                | 效果     |
|---------|-------------------|--------|
| `cv49 = 1` | `asterisk = 'high'` | 高位星号（默认） |
| `cv49 = 2` | `asterisk = 'low'`  | 低位星号 |


#### 其他值得关注的字符变体 {#其他值得关注的字符变体}

-   `cv25` （ `i` ）：带衬线 vs 无衬线的 i
-   `cv30` （ `l` ）：各种 l 的形态，区分 l/1/I
-   `cv31` （ `m` ）：短腿 vs 长腿
-   `cv38` （ `q` ）：直尾 vs 弯尾
-   `cv44` （ `f` ）：无延伸 vs 顶部延伸 vs 底部延伸 vs 双延伸
-   `cv71` （ `=` ）：各种等号形态
-   `cv73` （ `<` ）：各种小于号形态
-   `cv74` （ `>=` ）：各种大于号形态
-   `cv78` （ `$` ）：各种美元符号形态
-   `cv80` （ `%` ）：各种百分号形态


### Cherry-Picking 自定义 {#cherry-picking-自定义}

你不需要选择一个完整的风格集——可以逐个字符地挑选你最喜欢的变体，这叫做 Cherry-Picking。通过 OpenType `cv##` 特性标签或自定义构建配置来设置。

在编辑器中启用特定字符变体（以数字 0 带点、单层 a 为例）：

```json
{
  "editor.fontLigatures": ["cv10=6", "cv26=2"]
}
```

在 CSS 中：

```css
font-feature-settings: "cv10" 6, "cv26" 2;
```


## 安装 Iosevka {#安装-iosevka}


### Windows 安装 {#windows-安装}


#### 从 GitHub Releases 下载 {#从-github-releases-下载}

1.  访问 [Iosevka Releases 页面](https://github.com/be5invis/Iosevka/releases)
2.  找到最新版本（当前为 v34.7.0）
3.  下载你需要的字体包，文件名格式为 `PkgTTC-Iosevka-<子系列>.zip`
4.  解压 ZIP 文件
5.  选中字体文件（.ttc 或 .ttf），右键 → "为所有用户安装"（推荐）

**注意** ：Windows 10 1809 及以上版本默认按用户安装字体，这可能导致某些 Java 应用兼容性问题。建议右键选择"为所有用户安装"（Install for all users）。


#### 通过 Scoop 安装 {#通过-scoop-安装}

```powershell
scoop bucket add nerd-fonts
scoop install Iosevka-Term
```


#### 通过 Chocolatey 安装 {#通过-chocolatey-安装}

```powershell
choco install iosevka
```


### macOS 安装 {#macos-安装}


#### 通过 Homebrew 安装 {#通过-homebrew-安装}

```bash
brew install --cask font-iosevka

# 安装其他变体
brew search font-iosevka
brew install --cask font-iosevka-term
brew install --cask font-iosevka-slab
```


#### 手动安装 {#手动安装}

1.  从 [Releases](https://github.com/be5invis/Iosevka/releases) 下载字体包
2.  解压后双击字体文件，在字体册（Font Book）中点击"安装字体"
3.  或将字体文件复制到 `~/Library/Fonts/`


### Linux / Arch Linux 安装 {#linux-arch-linux-安装}


#### Arch Linux（pacman） {#arch-linux-pacman}

Arch 官方仓库提供了 Iosevka 的 TTC 包：

```bash
# 搜索可用的 Iosevka 包
pacman -Ss iosevka

# 安装标准版
sudo pacman -S ttc-iosevka

# 安装 Term 版
sudo pacman -S ttc-iosevka-term

# 安装 Slab 版
sudo pacman -S ttc-iosevka-slab
```


#### 手动安装（所有 Linux 发行版） {#手动安装-所有-linux-发行版}

```bash
# 创建用户字体目录
mkdir -p ~/.local/share/fonts

# 下载最新版 Iosevka（以 Term 版为例）
cd /tmp
curl -sL https://github.com/be5invis/Iosevka/releases/latest/download/PkgTTC-IosevkaTerm.zip -o IosevkaTerm.zip
unzip IosevkaTerm.zip -d IosevkaTerm

# 复制到用户字体目录
cp IosevkaTerm/*.ttc ~/.local/share/fonts/

# 刷新字体缓存
fc-cache -fv

# 验证安装
fc-list | grep Iosevka
```


#### 一键下载所有 TTC 包 {#一键下载所有-ttc-包}

```bash
cd ~/.local/share/fonts
curl -s 'https://api.github.com/repos/be5invis/Iosevka/releases/latest' \
  | jq -r '.assets[] | .browser_download_url' \
  | grep PkgTTC-Iosevka \
  | xargs -n 1 curl -L -O --fail --silent --show-error
fc-cache -fv
```


#### Void Linux {#void-linux}

```bash
xbps-install font-iosevka
```


#### Fedora {#fedora}

```bash
# 从 COPR 安装
dnf copr enable peterwu/iosevka
dnf search iosevka
sudo dnf install <选中的包>
```


### 国内镜像下载 {#国内镜像下载}

由于 GitHub Releases 在国内访问速度不稳定，可以使用以下镜像：

-   [清华大学 TUNA 镜像](https://mirrors.tuna.tsinghua.edu.cn/github-release/be5invis/Iosevka) — `https://mirrors.tuna.tsinghua.edu.cn/github-release/be5invis/Iosevka`
-   [南京大学 NJU 镜像](https://mirrors.nju.edu.cn/github-release/be5invis/Iosevka) — `https://mirrors.nju.edu.cn/github-release/be5invis/Iosevka`

镜像可能比 GitHub 最新版本有数小时到数天的延迟，但对于大多数用户来说已经足够。


## 在编辑器和终端中配置 {#在编辑器和终端中配置}


### VS Code / Cursor {#vs-code-cursor}

在 `settings.json` 中添加：

```json
{
  "editor.fontFamily": "'Iosevka Term', 'Iosevka', monospace",
  "editor.fontSize": 15,
  "editor.fontLigatures": true,
  "editor.fontWeight": "500"
}
```

启用特定风格集和字符变体：

```json
{
  "editor.fontFamily": "'Iosevka Term', monospace",
  "editor.fontSize": 15,
  "editor.fontLigatures": ["ss03", "cv10=6", "cv26=2"],
  "editor.fontWeight": "500"
}
```

`fontLigatures` 数组中可以混合使用风格集标签（ `ss03` ）和字符变体标签（ `cv10=6` ）。


### Vim / Neovim {#vim-neovim}

Vim 和 Neovim 本身不直接控制 OpenType 特性，但你可以通过终端模拟器的设置来配置。

如果你使用 Neovim 的 GUI 前端（如 Neovide、VimR），在 `init.lua` 或 `ginit.vim` 中设置：

```lua
-- Neovide
vim.g.neovide_font = "Iosevka Term"
vim.opt.guifont = "Iosevka Term:h14"
```


### Emacs {#emacs}

在 Emacs 中配置 Iosevka 并启用字符变体：

```elisp
(set-face-attribute 'default nil
                    :family "Iosevka Term"
                    :height 150
                    :weight 'medium)

;; 启用连字和字符变体
(let ((alist '((33 . ("ss03" "cv10=6")))))
  (dolist (item alist)
    (set-char-table-range composition-function-table (car item)
                          `([,(cdr item) 0 font-shape-gstring]))))
```

更简单的方式——使用 [ligature.el](https://github.com/mickeynp/ligature.el) 插件：

```elisp
(use-package ligature
  :config
  (ligature-set-ligatures 'prog-mode '("=>" "->" "<=" ">=" "==" "!=" "===" "!==" "=!="
                                        "<>" "::<" "::" "++" "--" "**" "||" "&&"
                                        "<<" ">>" "|>" "<|" ":>" "<:" "->>" "<<-"
                                        "<!--" "<!---" "|->")))
(global-ligature-mode t)
```


### Windows Terminal {#windows-terminal}

在 Windows Terminal 的 `settings.json` （可通过 Ctrl+Shift+, 打开）中配置：

```json
{
  "profiles": {
    "defaults": {
      "font": {
        "face": "Iosevka Term",
        "size": 13,
        "weight": "semi-bold"
      }
    }
  }
}
```


### Alacritty {#alacritty}

在 `~/.config/alacritty/alacritty.toml` 中：

```toml
[font]
normal = { family = "Iosevka Term", style = "Medium" }
bold = { family = "Iosevka Term", style = "Bold" }
italic = { family = "Iosevka Term", style = "Medium Italic" }
size = 14.0
```


### Kitty {#kitty}

Kitty 对 Iosevka 有特殊支持——需要启用 `exportGlyphNames` 才能正确显示连字。建议使用自定义构建（见下文）并设置 `exportGlyphNames = true` 。

在 `~/.config/kitty/kitty.conf` 中：

```fundamental
font_family      Iosevka Term Medium
bold_font        Iosevka Term Bold
italic_font      Iosevka Term Medium Italic
bold_italic_font Iosevka Term Bold Italic
font_size 14.0
```


### 其他终端模拟器 {#其他终端模拟器}

大多数现代终端模拟器都支持连字字体，配置方法类似：

-   `WezTerm` — 在 `wezterm.lua` 中设置 `font = wezterm.font("Iosevka Term")`
-   `Konsole` — 在配置文件中设置字体为 Iosevka Term
-   `GNOME Terminal` — 在首选项 → 配置文件 → 文本 中选择 Iosevka Term
-   `Foot` — 在 `foot.ini` 中设置 `font=Iosevka Term:size=14`


## 自定义构建 {#自定义构建}

Iosevka 最强大的功能是支持自定义构建——你可以精确控制每一个字符的形态、连字规则、字重范围等，构建出独一无二的个人字体。


### 准备环境 {#准备环境}

自定义构建需要从源码编译 Iosevka，需要以下工具：

```bash
# 安装 Node.js（>= 18.0.0）
# 在 Arch Linux 上：
sudo pacman -S nodejs npm

# 安装 ttfautohint（字体微调工具）
sudo pacman -S ttfautohint

# 克隆 Iosevka 仓库
git clone --depth 1 https://github.com/be5invis/Iosevka.git
cd Iosevka

# 安装依赖
npm install
```

**注意** ：构建过程会占用大量 CPU 和内存。每个并发任务峰值消耗超过 1GB 内存。如果内存有限，可以在构建命令中添加 `--jCmd=2` 来限制并发数。


### private-build-plans.toml 配置 {#private-build-plans-dot-toml-配置}

在 Iosevka 仓库根目录创建 `private-build-plans.toml` 文件，与 `build-plans.toml` 并列。

基本配置结构：

```toml
[buildPlans.MyCustomFont]
family = "My Iosevka"
spacing = "term"
serifs = "slab"
noCvSs = false
noLigation = false
exportGlyphNames = true

  [buildPlans.MyCustomFont.variants]
  inherits = "ss03"

    [buildPlans.MyCustomFont.variants.design]
    zero = "dotted"
    one = "no-base"
    a = "single-story"
    g = "single-story"
    asterisk = "low"

    [buildPlans.MyCustomFont.variants.italic]
    a = "double-story"

  [buildPlans.MyCustomFont.ligations]
  inherits = "default-calt"
  enables = ["arrow-r", "eqeq", "exeq"]
  disables = ["llgg"]

  [buildPlans.MyCustomFont.weights]
  Regular = [400, "Normal"]
  Medium = [500, "Normal"]
  Bold = [700, "Normal"]

  [buildPlans.MyCustomFont.widths]
  Normal = [1, "Normal"]

  [buildPlans.MyCustomFont.slopes]
  Upright = ["upright", "Default"]
  Italic = ["italic", "Default"]
```

各配置项说明：

-   `family` — 自定义字体的家族名，安装后会以此名称出现在字体列表中
-   `spacing` — 间距策略，可选值： `normal`  、 `term` 、 `fontconfig-mono` 、 `fixed` 、 `quasi-proportional` 、 `quasi-proportional-extension-only` 、 `wide-mosaic`
-   `serifs` — 衬线风格， `slab` 为衬线，不设置则为无衬线
-   `noCvSs` — 设为 `true` 则禁用所有 `cv##` 和 `ss##` OpenType 特性
-   `noLigation` — 设为 `true` 则禁用连字
-   `exportGlyphNames` — 设为 `true` 则导出字形名称， `Kitty 终端需要此选项` 才能正确显示连字
-   `variants.inherits` — 继承一个预定义风格集作为基础
-   `variants.design` — 对所有倾斜样式生效的字符变体覆盖
-   `variants.upright/italic/oblique` — 仅对特定倾斜样式生效的字符变体覆盖
-   `ligations.inherits` — 继承一个预定义连字集
-   `ligations.enables/disables` — 精确启用或禁用特定连字组
-   `weights/widths/slopes` — 控制构建哪些字重/宽度/倾斜变体，减少不需要的变体可以大幅缩短构建时间


### 构建命令 {#构建命令}

```bash
# 构建所有格式（TTF + Webfont，hinted + unhinted）
npm run build -- contents::MyCustomFont

# 只构建 TTF
npm run build -- ttf::MyCustomFont

# 只构建未 hint 的 TTF（更快）
npm run build -- ttf-unhinted::MyCustomFont

# 只构建 Web 字体（CSS + WOFF2）
npm run build -- webfont::MyCustomFont

# 限制并发数（内存不足时使用）
npm run build -- ttf::MyCustomFont --jCmd=2
```

构建产物在 `dist/` 目录中。


### 配置示例 — 精简的终端字体 {#配置示例-精简的终端字体}

以下配置构建一个专门为终端使用的精简字体，只包含 Regular、Bold、Italic 三种变体，继承 Consolas 风格，带点状零，无连字：

```toml
[buildPlans.IosevkaTermConsolas]
family = "Iosevka Term Consolas"
spacing = "term"
noLigation = true
exportGlyphNames = true

  [buildPlans.IosevkaTermConsolas.variants]
  inherits = "ss03"

    [buildPlans.IosevkaTermConsolas.variants.design]
    zero = "dotted"

  [buildPlans.IosevkaTermConsolas.weights]
  Regular = [400, "Normal"]
  Bold = [700, "Normal"]

  [buildPlans.IosevkaTermConsolas.slopes]
  Upright = ["upright", "Default"]
  Italic = ["italic", "Default"]
```


### 使用 Docker 构建 {#使用-docker-构建}

如果不想在本地安装 Node.js 和 ttfautohint，可以使用 Docker：

```bash
# 构建 Docker 镜像
cd Iosevka/docker
docker build -t iosevka-builder .

# 运行构建
docker run -it -v $(pwd)/../private-build-plans.toml:/opt/iosevka/private-build-plans.toml -v $(pwd)/../dist:/opt/iosevka/dist iosevka-builder npm run build -- ttf::MyCustomFont
```


### 使用在线 Customizer {#使用在线-customizer}

如果你不想从源码构建，Iosevka 提供了在线定制工具 [Iosevka Customizer](https://be5invis.github.io/Iosevka/customizer)，可以在浏览器中：

1.  选择子系列（Spacing）
2.  选择衬线风格（Style）
3.  调整字重（Weight）
4.  选择倾斜样式（Slope）
5.  逐个挑选字符变体
6.  配置连字集
7.  生成 `private-build-plans.toml` 配置文件

生成的配置文件可以用于本地构建。


## Sarasa Gothic — CJK 用户的选择 {#sarasa-gothic-cjk-用户的选择}

Iosevka 本身 `不包含` 中文、日文、韩文（CJK）字符。如果你需要 CJK 支持，同一个作者开发了 [Sarasa Gothic](https://github.com/be5invis/Sarasa-Gothic)——将 Iosevka 与 Source Han Sans（思源黑体）合并的字体家族。

Sarasa Gothic 保留了 Iosevka 的编程连字和等宽特性，同时完整支持 CJK 字符集。它同样提供多种变体（Sarasa Gothic、Sarasa Term、Sarasa Fixed、Sarasa Slab 等），选择逻辑与 Iosevka 一致。

```bash
# Arch Linux 安装 Sarasa Gothic
sudo pacman -S ttc-sarasa-gothic

# 或安装特定变体
yay -S otf-sarasa-gothic
```


### Iosevka + CJK 字体回退方案 {#iosevka-plus-cjk-字体回退方案}

如果你不想使用 Sarasa Gothic，也可以在编辑器中设置字体回退（Font Fallback），将 Iosevka 设为主字体，Noto Sans CJK SC 或 Source Han Sans SC 设为 CJK 回退字体：

```json
{
  "editor.fontFamily": "'Iosevka Term', 'Noto Sans CJK SC', 'Source Han Sans SC', monospace"
}
```

这种方案的优点是英文和中文各自使用最佳字体，但中英文混排时对齐可能不如 Sarasa Gothic 完美。


## 常见问题 {#常见问题}


#### Iosevka 和 Iosevka Term 有什么区别？ {#iosevka-和-iosevka-term-有什么区别}

Term 版本将箭头和几何符号变窄，以适应终端的列宽要求。标准 Iosevka 的某些符号（如 →、⟵）宽度超过一个字符格，在终端中可能导致对齐问题。如果你只在代码编辑器中使用，选择标准 Iosevka；如果在终端中使用，选择 Iosevka Term。


#### Iosevka Fixed 是什么？什么时候用？ {#iosevka-fixed-是什么-什么时候用}

Fixed 版本在 Term 的基础上禁用了所有连字。适用于：不支持连字的终端、查看日志时不想连字干扰、使用 `less` 或 `grep` 等工具时。大多数日常编码不需要 Fixed 版本。


#### 如何选择字重？ {#如何选择字重}

推荐从 `Medium` （500）开始尝试。Regular（400）在高分辨率屏幕上可能显得偏细，Medium 在大多数显示器上可读性更好。SemiBold（600）适合在深色主题下使用。


#### 连字在终端中不显示？ {#连字在终端中不显示}

确认你使用的是 Iosevka 或 Iosevka Term（不是 Fixed 版本），并且终端模拟器支持连字。大多数现代终端（Kitty、Alacritty、WezTerm、Windows Terminal、iTerm2）都支持连字。


#### 如何区分 0 和 O？ {#如何区分-0-和-o}

Iosevka 默认的数字 0 带斜杠（ `zero = 'slashed'` ），这已经能很好地区分。如果你想要更强的区分，可以尝试带点的零（ `zero = 'dotted'` ）。


#### 为什么自定义构建这么慢？ {#为什么自定义构建这么慢}

Iosevka 的构建涉及大量字形生成和字体微调。完整构建一个子系列可能需要 30 分钟以上。可以通过以下方式加速：

1.  减少构建的字重/宽度/倾斜变体数量
2.  使用 `--jCmd` 参数增加并发（如果内存充足）
3.  只构建需要的格式（如 `ttf-unhinted` 比 `contents` 快很多）


#### Iosevka 在 Java 应用中显示异常？ {#iosevka-在-java-应用中显示异常}

在 Windows 上，如果你使用了"按用户安装"而不是"为所有用户安装"，某些 Java 应用可能找不到字体。解决方法：右键字体文件 → "为所有用户安装"。


#### 如何在浏览器中使用 Iosevka？ {#如何在浏览器中使用-iosevka}

Iosevka 提供 WOFF2 格式的 Web 字体。可以通过 CSS 的 `@font-face` 引入：

```css
@font-face {
  font-family: 'Iosevka';
  src: url('iosevka-term.woff2') format('woff2');
  font-weight: 400;
  font-style: normal;
}

code, pre {
  font-family: 'Iosevka', monospace;
  font-feature-settings: "calt" 1, "ss03" 1;
}
```


## 参考链接 {#参考链接}

-   [Iosevka 官网](https://typeof.net/Iosevka/) — 在线预览和 Customizer
-   [Iosevka GitHub 仓库](https://github.com/be5invis/Iosevka) — 源码、Issue、Releases
-   [自定义构建文档](https://github.com/be5invis/Iosevka/blob/main/doc/custom-build.md) — 完整的 private-build-plans.toml 配置参考
-   [Stylistic Sets 列表](https://github.com/be5invis/Iosevka/blob/main/doc/stylistic-sets.md) — 所有预定义风格集
-   [Character Variants 列表](https://github.com/be5invis/Iosevka/blob/main/doc/character-variants.md) — 所有字符变体
-   [语言特定连字集](https://github.com/be5invis/Iosevka/blob/main/doc/language-specific-ligation-sets.md) — 所有语言连字标签
-   [Iosevka Customizer](https://be5invis.github.io/Iosevka/customizer) — 在线配置工具
-   [Iosevka Specimen](https://be5invis.github.io/Iosevka/specimen) — 字体样本展示
-   [Sarasa Gothic](https://github.com/be5invis/Sarasa-Gothic) — CJK 版本（Iosevka + 思源黑体）
-   [清华大学 TUNA 镜像](https://mirrors.tuna.tsinghua.edu.cn/github-release/be5invis/Iosevka) — 国内下载加速
