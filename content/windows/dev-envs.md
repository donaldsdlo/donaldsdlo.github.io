---
title: "windows 开发环境配置"
author: ["Donald Lo"]
date: 2026-01-15
lastmod: 2026-01-22T10:34:05+08:00
tags: ["windows", "dev"]
draft: false
---

<div class="ox-hugo-toc toc">

<div class="heading">&#30446;&#24405;</div>

- [环境变量](#环境变量)
    - [设置重要的环境变量](#设置重要的环境变量)
- [scoop](#scoop)
    - [安装 scoop](#安装-scoop)
        - [设置环境变量](#设置环境变量)
        - [打开powershell，依次输入下面的命令](#打开powershell-依次输入下面的命令)
    - [配置国内镜像源](#配置国内镜像源)
        - [先删除默认 main 源](#先删除默认-main-源)
        - [添加南大镜像](#添加南大镜像)
        - [恢复回官方源](#恢复回官方源)
    - [配置](#配置)
    - [安装常用工具](#安装常用工具)
    - [使用aria2加速下载](#使用aria2加速下载)
    - [查找软件](#查找软件)
    - [PDF 查看工具](#pdf-查看工具)
    - [改键工具](#改键工具)
    - [截图工具](#截图工具)
    - [视频播放软件](#视频播放软件)
    - [数据库客户端](#数据库客户端)
    - [postman 的替代品 bruno](#postman-的替代品-bruno)
    - [显示当前软件是否有需要更新](#显示当前软件是否有需要更新)
    - [软件更新](#软件更新)
    - [卸载软件](#卸载软件)
    - [删除软件的旧版本](#删除软件的旧版本)
- [字体](#字体)
    - [查找字体](#查找字体)
    - [下载字体](#下载字体)
    - [安装字体](#安装字体)
    - [常用的字体](#常用的字体)
        - [落霞孤鹜中文字体](#落霞孤鹜中文字体)
        - [思源中文字体](#思源中文字体)
        - [Iosevka 英文字体](#iosevka-英文字体)
        - [Fira Code](#fira-code)
- [Windows Terminal](#windows-terminal)
- [Powershell](#powershell)
    - [查找 Powershell](#查找-powershell)
    - [安装 Powershell](#安装-powershell)
    - [设置 Windows Terminal 默认打开的是新版本的 Powershell](#设置-windows-terminal-默认打开的是新版本的-powershell)
    - [查看 Powershell 的配置文件](#查看-powershell-的配置文件)
- [Python 环境安装和配置](#python-环境安装和配置)
    - [UV](#uv)
        - [UV 介绍](#uv-介绍)
            - [什么是UV？](#什么是uv)
            - [UV的核心优势](#uv的核心优势)
            - [UV和其他工具对比](#uv和其他工具对比)
                - [UV vs. pip+virtualenv](#uv-vs-dot-pip-plus-virtualenv)
                - [UV vs. Conda](#uv-vs-dot-conda)
                - [UV vs. Poetry](#uv-vs-dot-poetry)
                - [功能对比表](#功能对比表)
        - [设置 UV 相关的环境变量](#设置-uv-相关的环境变量)
        - [使用国内镜像](#使用国内镜像)
        - [采用 UV 来管理 python 版本和项目虚拟环境，安装 UV 软件：](#采用-uv-来管理-python-版本和项目虚拟环境-安装-uv-软件)
        - [创建系统默认的 Python 环境](#创建系统默认的-python-环境)
        - [要为 uv 命令启用 Powershell 自动补全，在 Powershell 中运行以下对应命令：](#要为-uv-命令启用-powershell-自动补全-在-powershell-中运行以下对应命令)
        - [使用 uv 管理多版本 Python](#使用-uv-管理多版本-python)
            - [显示可安装以及已经安装的 Python 版本：](#显示可安装以及已经安装的-python-版本)
            - [安装指定版本的 Python](#安装指定版本的-python)
            - [已经安装的版本，在后续使用到此版本的时候，UV 不会重复下载。](#已经安装的版本-在后续使用到此版本的时候-uv-不会重复下载)
            - [查看安装的结果](#查看安装的结果)
            - [Python 安装的目录](#python-安装的目录)
            - [移除已安装的版本](#移除已安装的版本)
        - [管理项目](#管理项目)
            - [创建一个项目](#创建一个项目)
            - [添加包](#添加包)
            - [编写代码](#编写代码)
            - [执行代码](#执行代码)
            - [构建项目分发包](#构建项目分发包)
            - [查看依赖树](#查看依赖树)
        - [安装常用工具](#安装常用工具)
    - [Pycharm](#pycharm)
        - [安装 pycharm](#安装-pycharm)
        - [设置 pycharm 创建新项目的默认目录](#设置-pycharm-创建新项目的默认目录)
        - [创建新项目](#创建新项目)
- [GPG/文件加密](#gpg-文件加密)
    - [安装](#安装)
    - [生成密钥](#生成密钥)
    - [生成一个文本文件](#生成一个文本文件)
    - [加密文件](#加密文件)
    - [解密](#解密)
- [测试数学公式](#测试数学公式)

</div>
<!--endtoc-->



## 环境变量 {#环境变量}


### 设置重要的环境变量 {#设置重要的环境变量}

```shell
:: 第一步：设置 HOME
setx HOME "D:\home"

:: 第二步：设置其他基于 HOME 的变量
setx XDG_BIN_HOME "%HOME%\.local\bin"
setx XDG_CACHE_HOME "%HOME%\.cache"
setx XDG_CONFIG_HOME "%HOME%\.config"
setx XDG_DATA_HOME "%HOME%\.local\share"
setx XDG_STATE_HOME "%HOME%\.local\state"
```

在后续看到 `~` 开头的目录都是指在 `HOME` 下的子目录。


## scoop {#scoop}

Scoop 是一个面向 Windows 的命令行安装程序（包管理器），旨在简化在 Windows 系统上安装、更新和管理开源命令行工具和应用程序的过程。

主要特点包括：

-   **无需管理员权限** ：默认将软件安装到用户目录（如 `~\scoop` ），避免系统污染。
-   **使用简单** ：通过简洁的命令（如 `scoop install <app>` ）即可完成软件的安装。
-   **基于 Git 和 JSON 清单** ：软件定义以 JSON 格式存储在称为“bucket”的仓库中，便于维护和扩展。
-   **支持多 bucket** ：除了官方主仓库（main bucket），还支持额外的社区或私有 bucket（如 `extras` 、 `versions`  等）。
-   **自动处理 PATH 和依赖** ：安装后自动配置环境变量，部分软件会自动安装所需依赖（如 Visual C++ Redistributables）。


### 安装 scoop {#安装-scoop}


#### 设置环境变量 {#设置环境变量}

```shell
setx SCOOP "D:\Scoop"
setx SCOOP_GLOBAL "D:\ScoopGlobalApps"
```


#### 打开powershell，依次输入下面的命令 {#打开powershell-依次输入下面的命令}

```shell
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
```

```shell
irm get.scoop.sh | iex
```


### 配置国内镜像源 {#配置国内镜像源}


#### 先删除默认 main 源 {#先删除默认-main-源}

```shell
scoop bucket rm main
```

可以通过如下的命令查看已经安装的 bucket 清单，根据实际需要将对应的 bucket 删除，然后换成国内的源。

```shell
scoop bucket list
```

你可能可以看到如下的结果：

```shell
Name          Source                                             Updated            Manifests
----          ------                                             -------            ---------
main          https://github.com/ScoopInstaller/Main             2026/1/15 12:33:06      1418
extras        https://github.com/ScoopInstaller/Extras           2026/1/15 12:32:35      2254
versions      https://github.com/ScoopInstaller/Versions         2026/1/15 13:03:17       550
nirsoft       https://github.com/ScoopInstaller/Nirsoft          2026/1/13 13:13:19       290
php           https://github.com/ScoopInstaller/PHP              2025/12/18 0:55:41       391
nerd-fonts    https://github.com/matthewjberger/scoop-nerd-fonts 2026/1/14 18:31:41       367
nonportable   https://github.com/ScoopInstaller/Nonportable      2026/1/15 2:27:24        126
java          https://github.com/ScoopInstaller/Java             2026/1/13 16:33:01       324
games         https://github.com/Calinou/scoop-games             2026/1/15 12:32:36       379
scoop-clojure https://github.com/littleli/scoop-clojure          2026/1/14 8:43:14         28
scoop-misc    https://github.com/kiennq/scoop-misc               2026/1/14 21:09:13        22
```


#### 添加南大镜像 {#添加南大镜像}

```shell
scoop bucket add extras https://mirror.nju.edu.cn/git/scoop-extras.git/
scoop bucket add java https://mirror.nju.edu.cn/git/scoop-java.git/
scoop bucket add main https://mirror.nju.edu.cn/git/scoop-main.git/
scoop bucket add nerd-fonts https://mirror.nju.edu.cn/git/scoop-nerd-fonts.git/
scoop bucket add nirsoft https://mirror.nju.edu.cn/git/scoop-nirsoft.git/
scoop bucket add nonportable https://mirror.nju.edu.cn/git/scoop-nonportable.git/
scoop bucket add versions https://mirror.nju.edu.cn/git/scoop-versions.git/
```


#### 恢复回官方源 {#恢复回官方源}

```shell
scoop bucket rm main
scoop bucket rm extras
scoop bucket add main
scoop bucket add extras
```


### 配置 {#配置}

开启缓存，避免重复下载

```shell
scoop config cache_enabled true
```


### 安装常用工具 {#安装常用工具}

```shell
scoop install git aria2 coreutils fzf grep gzip make ripgrep rga wget which fd 7zip ag altsnap ast-grep astyle autojump curl delta direnv everything everything-cli ffmpeg geekuninstaller  hugo hugo-extended mpv pandoc scoop-search gpg
```


### 使用aria2加速下载 {#使用aria2加速下载}

```shell
scoop config aria2-enabled true
```

修改 C:\Users\donal\\.config\scoop\config.json 文件，原始文件如下：

```json
{
    "global_path":  "D:\\ScoopGlobalApps",
    "last_update":  "2025-10-29T14:27:18.4340636+08:00",
    "aria2-enabled":  true,
    "scoop_repo":  "https://github.com/ScoopInstaller/Scoop",
    "scoop_branch":  "master"
}
```

添加 "aria2-options": "--async-dns=false" 配置后：

```json
{
    "global_path":  "D:\\ScoopGlobalApps",
    "last_update":  "2025-10-29T14:27:18.4340636+08:00",
    "aria2-enabled":  true,
    "aria2-options": "--async-dns=false",
    "scoop_repo":  "https://github.com/ScoopInstaller/Scoop",
    "scoop_branch":  "master"
}
```

还有如下的配置项：

```shell
#在scoop中，开启aria2加速下载（其实，默认是开启的）
scoop config aria2-enabled $true   #直接使用true，效果也一样。

#每次下载到一台服务器的最大连接数。
scoop config aria2-max-connection-per-server 16
#用于下载的线程数（编译版好像最大到16线程，如果更大需要自己编译了）
scoop config aria2-split 16
#切片大小
scoop config aria2-min-split-size 1M

#使用Aria2c下载文件时的警告是否开启
scoop config aria2-warning-enabled $true|$false

#重试之间等待的秒数。
scoop config aria2-retry-wait 2

#其他aria2参数（再执行一次该命令，会覆盖前面的命令）
scoop config aria2-options ....
```

还可以通过如下命令查看所有的配置参数：

```shell
scoop config /?
```


### 查找软件 {#查找软件}

```shell
scoop search emacs
```

```shell
Name              Version                  Source     Binaries
----              -------                  ------     --------
emacs             30.2                     extras
emax64-pdumper    20180619                 extras     runemacs.exe | emacs.exe | emacsclientw.exe | emacs-27.0.50.exe
emacs27.2         27.2                     versions
emacs-k           31.405.20260105.e12c0610 scoop-misc
emacs-kl          31.405.20260105.e12c0610 scoop-misc
emacs-lsp-booster 0.2.1                    scoop-misc
emacs-x           30.2                     scoop-misc
emax64            20200930                 scoop-misc runemacs.exe | emacs.exe | emacsclient.exe | emacsclientw.exe | emacsclientw.exe
```

安装软件：

```shell
scoop install emacs-kl
```


### PDF 查看工具 {#pdf-查看工具}

```shell
scoop install sumatrapdf
```


### 改键工具 {#改键工具}

```shell
scoop install sharpkeys
```


### 截图工具 {#截图工具}

```shell
scoop install snipaste
```


### 视频播放软件 {#视频播放软件}

```shell
scoop install potplayer
```


### 数据库客户端 {#数据库客户端}

```shell
scoop install dbeaver
```


### postman 的替代品 bruno {#postman-的替代品-bruno}

```shell
scoop install bruno
```


### 显示当前软件是否有需要更新 {#显示当前软件是否有需要更新}

```shell
scoop status
```

```shell
Scoop is up to date.
Everything is ok!
```

如果返回的是上面的消息，则所有安装的软件都不需要更新。


### 软件更新 {#软件更新}

更新指定的软件

```shell
scoop update deno
```

更新所有软件：

```shell
scoop update -a
```


### 卸载软件 {#卸载软件}

```shell
scoop uninstall peazip
```

```shell
Uninstalling 'peazip' (10.8.0).
Removing shim 'peazip.shim'.
Removing shim 'peazip.exe'.
Removing shortcut ~\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Scoop Apps\PeaZip.lnk
Unlinking D:\Scoop\apps\peazip\current
'peazip' was uninstalled.
```


### 删除软件的旧版本 {#删除软件的旧版本}

```shell
scoop cleanup *
```

会显示删除的所有的版本信息：

```shell
Removing codex: 0.80.0 0.81.0
Removing deno: 2.6.4
Removing erlang: 28.3
Removing golang: 1.25.5
Removing innounp: 2.67.0
Removing jdtls: 1.56.0-202601140747
Removing luau-lsp: 1.60.0
Removing opencode: 1.1.18 1.1.20
Removing zed: 0.218.7
Removing zotero: 7.0.31
Everything is shiny now!
```


## 字体 {#字体}


### 查找字体 {#查找字体}

```shell
scoop search maple
```

```shell
Results from local buckets...

Name                Version Source     Binaries
----                ------- ------     --------
maple               0.9.1.0 extras
Maple-Mono-autohint 7.9     nerd-fonts
Maple-Mono-NF-CN    7.9     nerd-fonts
Maple-Mono-NF       7.9     nerd-fonts
Maple-Mono-otf      7.9     nerd-fonts
Maple-Mono          7.9     nerd-fonts
```


### 下载字体 {#下载字体}

```shell
scoop download Maple-Mono-NF-CN
```

```shell
INFO  Downloading 'Maple-Mono-NF-CN' [64bit] from nerd-fonts bucket
Starting download with aria2 ...
Download: [#694632 55MiB/152MiB(36%) CN:5 DL:332KiB ETA:4m57s]
```

当出现如下最后一行的信息时，表示已经下载完成。

```shell
PS D:\> scoop download Maple-Mono-NF-CN
INFO  Downloading 'Maple-Mono-NF-CN' [64bit] from nerd-fonts bucket
Starting download with aria2 ...
Download: Download Results:
Download: gid   |stat|avg speed  |path/URI
Download: ======+====+===========+=======================================================
Download: 694632|OK  |   314KiB/s|D:/Scoop/cache/Maple-Mono-NF-CN#7.9#2184a5b.zip
Download: Status Legend:
Download: (OK):download completed.
Checking hash of MapleMono-NF-CN.zip ... ok.
'Maple-Mono-NF-CN' (7.9) was downloaded successfully!
```


### 安装字体 {#安装字体}

下载的文件保存在之前设置的环境变量 `SCOOP` 下的 `cache` 目录下，且是一个压缩包：

{{< figure src="/images/dev-envs.org/2026-01-16_14-43-09_screenshot.png" >}}

需要手工解压缩：

{{< figure src="/images/dev-envs.org/2026-01-16_14-43-55_screenshot.png" >}}

选中所有的字体文件（以 ttf 结尾的文件），然后鼠标右键菜单中选择 **为所有用户安装** :

{{< figure src="/images/dev-envs.org/2026-01-16_14-49-30_screenshot.png" >}}


### 常用的字体 {#常用的字体}


#### 落霞孤鹜中文字体 {#落霞孤鹜中文字体}

```shell
scoop search lxgw
```

```shell
Results from local buckets...

Name              Version Source     Binaries
----              ------- ------     --------
LXGW-Bright-GB    5.321   nerd-fonts
LXGW-Bright-TC    5.321   nerd-fonts
LXGW-Bright       5.321   nerd-fonts
LXGWNeoXiHei      1.239   nerd-fonts
LXGWNeoZhiSong    1.058   nerd-fonts
LXGWWenKai        1.521   nerd-fonts
LXGWWenKaiGB      1.521   nerd-fonts
LXGWWenKaiMono    1.521   nerd-fonts
LXGWWenKaiMonoGB  1.521   nerd-fonts
LXGWWenKaiMonoTC  1.521   nerd-fonts
LXGWWenKaiScreen  1.521   nerd-fonts
LXGWWenKaiScreenR 1.315   nerd-fonts
LXGWWenKaiTC      1.521   nerd-fonts
```

可以选用其中的 LXGWWenKaiMonoGB 字体


#### 思源中文字体 {#思源中文字体}

```shell
scoop search source
```

```shell
Results from local buckets...

Name                          Version      Source     Binaries
----                          -------      ------     --------
ossgadget                     0.1.422      main       oss-find-source.exe
pulumi                        3.215.0      main       pulumi-resource-pulumi-nodejs.cmd | pulumi-resource-pulumi-pytho…
sourcegraph-cli               6.12.0       main
resource-hacker               5.2.8        extras
resource-tuner-console        2.30         extras
resource-tuner                2.30         extras
sourcegit                     2026.01      extras
sourcetrail                   2021.4.19    extras
sourcetree                    3.4.27       extras
upsource                      2020.1.1992  extras
appresourcesusageview         1.06         nirsoft
dotnetresourcesextract        1.01         nirsoft
eventlogsourcesview           1.00         nirsoft
resourcesextract              1.18         nirsoft
Source-Han-Mega-OTC           20190603     nerd-fonts
Source-Han-Mono-HC            1.002        nerd-fonts
Source-Han-Mono-J             1.002        nerd-fonts
Source-Han-Mono-K             1.002        nerd-fonts
Source-Han-Mono-SC            1.002        nerd-fonts
Source-Han-Mono-TC            1.002        nerd-fonts
Source-Han-Noto-CJK-Ultra-OTC 20190603     nerd-fonts
Source-Han-Sans-HC            2.004        nerd-fonts
Source-Han-Sans-J             2.004        nerd-fonts
Source-Han-Sans-K             2.004        nerd-fonts
Source-Han-Sans-SC            2.004        nerd-fonts
Source-Han-Sans-TC            2.004        nerd-fonts
Source-Han-Serif-HC           2.003        nerd-fonts
Source-Han-Serif-J            2.003        nerd-fonts
Source-Han-Serif-K            2.003        nerd-fonts
Source-Han-Serif-SC           2.003        nerd-fonts
Source-Han-Serif-TC           2.003        nerd-fonts
SourceCodePro-NF-Mono         3.4.0        nerd-fonts
SourceCodePro-NF-Propo        3.4.0        nerd-fonts
SourceCodePro-NF              3.4.0        nerd-fonts
sourcedepot                   4.9.29711.24 scoop-misc
```

source 为 nerd-fonts 的都是字体，我们可以安装 SC 结尾的简体中文字体。


#### Iosevka 英文字体 {#iosevka-英文字体}

```shell
scoop search iosevka
```

```shell
Results from local buckets...

Name                     Version Source     Binaries
----                     ------- ------     --------
Iosevka-NF-Mono          3.4.0   nerd-fonts
Iosevka-NF-Propo         3.4.0   nerd-fonts
Iosevka-NF               3.4.0   nerd-fonts
IosevkaTerm-NF-Mono      3.4.0   nerd-fonts
IosevkaTerm-NF-Propo     3.4.0   nerd-fonts
IosevkaTerm-NF           3.4.0   nerd-fonts
IosevkaTermSlab-NF-Mono  3.4.0   nerd-fonts
IosevkaTermSlab-NF-Propo 3.4.0   nerd-fonts
IosevkaTermSlab-NF       3.4.0   nerd-fonts
```


#### Fira Code {#fira-code}

```shell
scoop search firacode
```

```shell
Results from local buckets...

Name              Version Source     Binaries
----              ------- ------     --------
FiraCode-NF-Mono  3.4.0   nerd-fonts
FiraCode-NF-Propo 3.4.0   nerd-fonts
FiraCode-NF       3.4.0   nerd-fonts
FiraCode-Script   0.0.28  nerd-fonts
FiraCode          6.2     nerd-fonts
```

```shell
scoop download FiraCode
```


## Windows Terminal {#windows-terminal}

```shell
scoop install windows-terminal
```


## Powershell {#powershell}


### 查找 Powershell {#查找-powershell}

```shell
winget search --id Microsoft.PowerShell
```

```shell
名称               ID                           版本    源
---------------------------------------------------------------
PowerShell         Microsoft.PowerShell         7.5.4.0 winget
PowerShell Preview Microsoft.PowerShell.Preview 7.6.0.6 winget
```


### 安装 Powershell {#安装-powershell}

```shell
winget install --id Microsoft.PowerShell --source winget
```


### 设置 Windows Terminal 默认打开的是新版本的 Powershell {#设置-windows-terminal-默认打开的是新版本的-powershell}

打开 Windows Termial

{{< figure src="/images/dev-envs.org/2026-01-20_09-02-04_screenshot.png" >}}

通过 Ctrl+, 快捷键打开设置界面

{{< figure src="/images/dev-envs.org/2026-01-20_09-02-58_screenshot.png" >}}


### 查看 Powershell 的配置文件 {#查看-powershell-的配置文件}

```shell
echo $PROFILE
```

```shell
D:\Documents\PowerShell\Microsoft.PowerShell_profile.ps1
```

需要添加的配置和一些函数都可以写在这个文件中。


## Python 环境安装和配置 {#python-环境安装和配置}


### UV {#uv}


#### UV 介绍 {#uv-介绍}

UV 是一个由 Astral 公司用 Rust 开发的高性能 Python 包管理工具，旨在提供比传统 pip 更快的包安装和依赖管理体验。

> An extremely fast Python package and project manager, written in Rust.

Python 生态系统中的包管理一直是开发者关注的焦点。从最初的 pip 到后来的 Poetry、PDM 等工具，每一次演进都试图解决前代工具的痛点。而今天我们要介绍的 UV，作为由 Ruff 团队（Astral）开发的下一代 Python 包管理工具，正以其惊人的速度和创新的设计理念，重新定义 Python 包管理的标准。


##### 什么是UV？ {#什么是uv}

UV 是一个极速的 Python 包管理器和解析器，由 Rust 编写，专注于提供卓越的性能和用户体验。其名称 "UV" 源自 "μv"（微伏），暗示着其轻量级和高效的特性。作为 pip 的直接替代品，UV 提供了兼容的命令行接口，同时在速度上实现了数量级的提升。


##### UV的核心优势 {#uv的核心优势}

与传统的 Python 包管理工具相比，UV 具有以下显著优势：

-   **🚀 一体化工具** ：一个工具替代 pip、pip-tools、pipx、poetry、pyenv、twine、virtualenv 等多种工具
-   **⚡️ 极致速度** ：比 pip 快 10-100 倍
-   **🗂️ 全面项目管理** ：提供通用锁文件的综合项目管理功能
-   **❇️ 脚本运行** ：支持带有内联依赖元数据的脚本运行
-   **🐍 Python版本管理** ：安装和管理不同的 Python 版本
-   **🛠️ 工具安装** ：运行和安装以 Python 包形式发布的工具
-   **🔩 兼容pip接口** ：提供熟悉的命令行界面，同时大幅提升性能
-   **🏢 工作区支持** ：支持 Cargo 风格的工作区，适用于大规模项目
-   **💾 高效磁盘空间利用** ：通过全局缓存实现依赖去重
-   **⏬ 简易安装** ：无需 Rust 或 Python 环境，可通过 curl 或 pip 直接安装
-   **🖥️ 多平台支持** ：支持 macOS、Linux 和 Windows 系统

随着Python项目规模和复杂度的增长，传统工具在性能和用户体验方面的局限性日益凸显。UV 的出现，为开发者提供了一个更快、更可靠的选择，特别适合大型项目和CI/CD环境中的应用。


##### UV和其他工具对比 {#uv和其他工具对比}

在Python生态系统中，包管理和环境管理工具众多，主要包括pip+virtualenv、Poetry、Conda等。在决定是否采用UV之前，了解它与现有工具的区别和优势非常重要。


###### UV vs. pip+virtualenv {#uv-vs-dot-pip-plus-virtualenv}

pip和virtualenv是Python包管理和虚拟环境创建的传统工具组合。UV相比它们具有以下优势：

-   **速度** ：UV的Rust实现使其比pip快10-100倍，特别是在大型项目中
-   **集成环境管理** ：UV将包管理和环境管理集成在一个工具中，简化了工作流程
-   **内存使用** ：UV在包安装和依赖解析过程中使用的内存显著减少
-   **错误处理** ：UV提供更清晰的错误信息和更好的依赖冲突解决方案
-   **可复现性** ：UV的锁文件方法确保了跨系统环境的一致性，这是基本requirements.txt文件无法保证的


###### UV vs. Conda {#uv-vs-dot-conda}

Conda是一个完整的包管理解决方案，特别适合科学计算环境。UV与Conda相比：

-   **速度** ：UV的包安装和依赖解析速度远快于Conda的有时缓慢的性能
-   **资源占用** ：UV具有更小的资源占用，意味着更少的内存使用和更快的启动时间
-   **集成性** ：UV与现有Python打包标准和工具无缝集成，更容易与更广泛的Python生态系统协作
-   **非Python包** ：Conda可以管理非Python包和系统级依赖，而UV专注于Python包


###### UV vs. Poetry {#uv-vs-dot-poetry}

Poetry是另一个现代Python项目管理工具，与UV有许多相似之处：

-   **依赖管理** ：两者都有效处理包依赖和虚拟环境
-   **项目结构** ：两者都提供初始化和构建Python项目的工具
-   **锁文件** ：两者都生成锁文件以确保环境可复现

然而，UV的Rust实现使其在速度和资源使用方面具有显著优势。此外，UV与现有Python包管理工具的兼容性意味着它可以与其他工具（如pip）一起工作，提供了Poetry更固执己见的方法有时缺乏的灵活性。


###### 功能对比表 {#功能对比表}

| 功能特性   | UV           | pip+virtualenv        | Conda  | Poetry   |
|--------|--------------|-----------------------|--------|----------|
| 实现语言   | Rust         | Python                | Python | Python   |
| 速度       | 比pip快10-100倍 | 基准线                | 慢于pip | 快于pip  |
| 内存使用   | 非常高效     | 较高                  | 高     | 中等     |
| 环境管理   | 内置         | 需要单独工具          | 内置   | 内置     |
| 依赖解析   | 快速、现代解析器 | 基础                  | 全面   | 现代解析器 |
| 非Python包支持 | 否           | 否                    | 是     | 否       |
| 锁文件     | 是           | 否(基本requirements.txt) | 是     | 是       |
| 项目结构化 | 是           | 否                    | 否     | 是       |
| 包发布     | 是           | 是(需要twine)         | 是     | 是       |
| 兼容性     | 与现有pip生态系统兼容 | 标准Python工具        | 自有生态系统 | 更固执己见的方法 |
| 错误处理   | 清晰的错误信息 | 基本                  | 良好   | 良好     |
| 资源占用   | 最小         | 中等                  | 重     | 中等     |
| 科学计算焦点 | 否           | 否                    | 是     | 否       |
| 跨平台一致性 | 是           | 有限                  | 优秀   | 良好     |

总的来说，UV结合了现有工具的最佳特性，同时通过其Rust实现提供了显著的性能优势。对于寻求更快、更可靠的Python包管理解决方案的开发者来说，UV是一个极具吸引力的选择，特别是对于大型项目或CI/CD环境。


#### 设置 UV 相关的环境变量 {#设置-uv-相关的环境变量}

```shell
setx UV_PYTHON_INSTALL_DIR D:\uv\python
setx UV_TOOL_DIR D:\uv\tools
```


#### 使用国内镜像 {#使用国内镜像}

在文件 ~/.config/uv/uv.toml 中添加如下内容：

```toml
[[index]]
url = "https://mirrors.tuna.tsinghua.edu.cn/pypi/web/simple/"
default = true
```


#### 采用 UV 来管理 python 版本和项目虚拟环境，安装 UV 软件： {#采用-uv-来管理-python-版本和项目虚拟环境-安装-uv-软件}

```shell
scoop install uv
```

安装完成后，可以通过以下命令验证安装是否成功：

```shell
uv --version
```

安装正确会得到版本号：

```shell
uv 0.9.26 (ee4f00362 2026-01-15)
```


#### 创建系统默认的 Python 环境 {#创建系统默认的-python-环境}

在 D:\python-envs 目录中：

```shell
uv init default-python --python 3.14
```

```shell
cd default-python
```

安装包：

```shell
uv add requests
```

指定版本约束

```shell
uv add 'requests==2.31.0'
```

添加 Git 依赖:

```shell
uv add git+https://github.com/psf/requests
```

将指定包更新到最新的兼容版本，同时保持锁文件中其他依赖不变:

```shell
uv lock --upgrade-package requests
```

从 requirements.txt 文件添加所有依赖:

```shell
uv add -r requirements.txt -c constraints.txt
```

删除包：

```shell
uv remove requests
```

将 default-python\\.venv\Scripts 的完整目录添加到 PATH 环境变量的最前面，这样就可以使用这个环境下的 python 作为系统的默认 python 了。


#### 要为 uv 命令启用 Powershell 自动补全，在 Powershell 中运行以下对应命令： {#要为-uv-命令启用-powershell-自动补全-在-powershell-中运行以下对应命令}

```shell
if (!(Test-Path -Path $PROFILE)) {
  New-Item -ItemType File -Path $PROFILE -Force
}
Add-Content -Path $PROFILE -Value '(& uv generate-shell-completion powershell) | Out-String | Invoke-Expression'
```


#### 使用 uv 管理多版本 Python {#使用-uv-管理多版本-python}


##### 显示可安装以及已经安装的 Python 版本： {#显示可安装以及已经安装的-python-版本}

```shell
uv python list
```

```shell
cpython-3.15.0a5-windows-x86_64-none                 <download available>
cpython-3.15.0a5+freethreaded-windows-x86_64-none    <download available>
cpython-3.15.0a1-windows-x86_64-none                 D:\uv\python\cpython-3.15.0a1-windows-x86_64-none\python.exe
cpython-3.15.0a1-windows-x86_64-none                 C:\Users\donal\.local\bin\python3.15.exe
cpython-3.14.2-windows-x86_64-none                   <download available>
cpython-3.14.2+freethreaded-windows-x86_64-none      <download available>
cpython-3.14.0-windows-x86_64-none                   D:\uv\python\cpython-3.14.0-windows-x86_64-none\python.exe
cpython-3.14.0-windows-x86_64-none                   C:\Users\donal\.local\bin\python3.14.exe
cpython-3.14.0+freethreaded-windows-x86_64-none      C:\Users\donal\.local\bin\python3.14t.exe
cpython-3.14.0+freethreaded-windows-x86_64-none      D:\uv\python\cpython-3.14.0+freethreaded-windows-x86_64-none\python.exe
cpython-3.13.11-windows-x86_64-none                  D:\uv\python\cpython-3.13.11-windows-x86_64-none\python.exe
cpython-3.13.11+freethreaded-windows-x86_64-none     <download available>
cpython-3.12.12-windows-x86_64-none                  D:\uv\python\cpython-3.12.12-windows-x86_64-none\python.exe
cpython-3.11.14-windows-x86_64-none                  D:\uv\python\cpython-3.11.14-windows-x86_64-none\python.exe
cpython-3.10.19-windows-x86_64-none                  <download available>
cpython-3.9.25-windows-x86_64-none                   <download available>
cpython-3.8.20-windows-x86_64-none                   <download available>
pypy-3.11.13-windows-x86_64-none                     <download available>
pypy-3.10.16-windows-x86_64-none                     <download available>
pypy-3.9.19-windows-x86_64-none                      <download available>
pypy-3.8.16-windows-x86_64-none                      <download available>
graalpy-3.12.0-windows-x86_64-none                   <download available>
graalpy-3.11.0-windows-x86_64-none                   <download available>
graalpy-3.10.0-windows-x86_64-none                   <download available>
```


##### 安装指定版本的 Python {#安装指定版本的-python}

```shell
uv python install 3.9
```

```shell
cpython-3.9.25-windows-x86_64-none (download) ------------------------------ 1.73 MiB/21.67 MiB
```

出现如下的消息时表示已经安装完成：

```shell
Installed Python 3.9.25 in 2m 31s
 + cpython-3.9.25-windows-x86_64-none (python3.9.exe)
```

也可以使用完整的名称来安装 Python:

```shell
uv python install pypy-3.8.16-windows-x86_64-none
```

```shell
pypy-3.8.16-windows-x86_64-none (download) ------------------------------ 1.58 MiB/29.98 MiB
```

出现如下的消息时表示已经安装完成：

```shell
Installed Python 3.8.16 in 13m 42s
 + pypy-3.8.16-windows-x86_64-none (python3.8.exe)
```


##### 已经安装的版本，在后续使用到此版本的时候，UV 不会重复下载。 {#已经安装的版本-在后续使用到此版本的时候-uv-不会重复下载}


##### 查看安装的结果 {#查看安装的结果}

```shell
uv python list
```

```shell
cpython-3.15.0a5-windows-x86_64-none                 <download available>
cpython-3.15.0a5+freethreaded-windows-x86_64-none    <download available>
cpython-3.15.0a1-windows-x86_64-none                 D:\uv\python\cpython-3.15.0a1-windows-x86_64-none\python.exe
cpython-3.15.0a1-windows-x86_64-none                 C:\Users\donal\.local\bin\python3.15.exe
cpython-3.14.2-windows-x86_64-none                   <download available>
cpython-3.14.2+freethreaded-windows-x86_64-none      <download available>
cpython-3.14.0-windows-x86_64-none                   D:\uv\python\cpython-3.14.0-windows-x86_64-none\python.exe
cpython-3.14.0-windows-x86_64-none                   C:\Users\donal\.local\bin\python3.14.exe
cpython-3.14.0+freethreaded-windows-x86_64-none      C:\Users\donal\.local\bin\python3.14t.exe
cpython-3.14.0+freethreaded-windows-x86_64-none      D:\uv\python\cpython-3.14.0+freethreaded-windows-x86_64-none\python.exe
cpython-3.13.11-windows-x86_64-none                  D:\uv\python\cpython-3.13.11-windows-x86_64-none\python.exe
cpython-3.13.11+freethreaded-windows-x86_64-none     <download available>
cpython-3.12.12-windows-x86_64-none                  D:\uv\python\cpython-3.12.12-windows-x86_64-none\python.exe
cpython-3.11.14-windows-x86_64-none                  D:\uv\python\cpython-3.11.14-windows-x86_64-none\python.exe
cpython-3.10.19-windows-x86_64-none                  <download available>
cpython-3.9.25-windows-x86_64-none                   D:\uv\python\cpython-3.9.25-windows-x86_64-none\python.exe
cpython-3.9.25-windows-x86_64-none                   <download available>
cpython-3.8.20-windows-x86_64-none                   <download available>
pypy-3.11.13-windows-x86_64-none                     <download available>
pypy-3.10.16-windows-x86_64-none                     <download available>
pypy-3.9.19-windows-x86_64-none                      <download available>
pypy-3.8.16-windows-x86_64-none                      D:\uv\python\pypy-3.8.16-windows-x86_64-none\pypy3.8.exe
pypy-3.8.16-windows-x86_64-none                      D:\home\.local\bin\python3.8.exe
pypy-3.8.16-windows-x86_64-none                      <download available>
graalpy-3.12.0-windows-x86_64-none                   <download available>
graalpy-3.11.0-windows-x86_64-none                   <download available>
graalpy-3.10.0-windows-x86_64-none                   <download available>
```


##### Python 安装的目录 {#python-安装的目录}

```shell
uv python dir
```

```shell
D:\uv\python
```


##### 移除已安装的版本 {#移除已安装的版本}

```shell
uv python uninstall 3.9
```

```shell
Searching for Python versions matching: Python 3.9
Uninstalled Python 3.9.25 in 483ms
 - cpython-3.9.25-windows-x86_64-none (python3.9.exe)
```

也可以通过完整的 Python 版本名称来移除：

```shell
uv python uninstall pypy-3.8.16-windows-x86_64-none
```

```shell
Searching for Python versions matching: pypy-3.8.16-windows-x86_64-none
Uninstalled Python 3.8.16 in 431ms
 - pypy-3.8.16-windows-x86_64-none (python3.8.exe)
```


#### 管理项目 {#管理项目}


##### 创建一个项目 {#创建一个项目}

```shell
PS E:\tmp> uv init test04 --python 3.14
```

```shell
Initialized project `test04` at `E:\tmp\test04`
```

执行完这个命令后，会创建 `test04` 目录并在其中创建如下的文件：

```shell
PS E:\tmp\test04> ls
```

```shell
    Directory: E:\tmp\test04

Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
-a---           2026/1/20    15:46            109 .gitignore
-a---           2026/1/20    15:46              5 .python-version
-a---           2026/1/20    15:46             84 main.py
-a---           2026/1/20    15:46            152 pyproject.toml
-a---           2026/1/20    15:46              0 README.md
```

其中的文件：

-   gitignore：uv 会帮你把项目建立成 git 储存库，并且帮你写好了 .gitignore 文件，避免 Python 执行过程产生的暂存文件等也提交到储存库内
    ```shell
            # Python-generated files
            __pycache__/
            *.py[oc]
            build/
            dist/
            wheels/
            *.egg-info

            # Virtual environments
            .venv
    ```
-   .python-version：记录这个项目使用的 Python 版本
-   main.py
-   pyproject.toml：此项目的诠释数据，其实就是前面单一程序文件形式的项目在源代码开头注释的内容
    ```toml
            [project]
            name = "test04"
            version = "0.1.0"
            description = "Add your description here"
            readme = "README.md"
            requires-python = ">=3.14"
            dependencies = [
            "openpyxl>=3.1.5",
            ]
    ```
-   README. ME：空的 markdown 文件，预留让你撰写项目说明用。


##### 添加包 {#添加包}

可以在其中安装相关的包:

```shell
PS E:\tmp\test04> uv add openpyxl
```

```shell
Using CPython 3.14.0
Creating virtual environment at: .venv
Resolved 3 packages in 426ms
Installed 2 packages in 498ms
 + et-xmlfile==2.0.0
 + openpyxl==3.1.5
```

添加只在开发时使用的包

```shell
uv add --dev pytest black
```


##### 编写代码 {#编写代码}

修改 main.py 中的代码如下：

```python

from openpyxl import load_workbook

def read_excel_columns():
    file_path = r"D:\data\Desktop\EXPOR615.XLSX"

    try:
        # 加载工作簿
        workbook = load_workbook(filename=file_path)

        # 获取第一个工作表（也可以指定表名：workbook['Sheet1']）
        worksheet = workbook.active

        print("读取的A、B列数据（最多10行）：")
        print("-" * 30)

        # 读取前10行的A、B列数据
        for row in range(1, 11):  # 行号从1到10
            cell_a = worksheet.cell(row=row, column=1).value
            cell_b = worksheet.cell(row=row, column=2).value

            # 如果两列都为空，可以考虑提前退出（可选）
            # if cell_a is None and cell_b is None:
            #     break

            print(f"第{row:2d}行: A={cell_a}, B={cell_b}")

    except FileNotFoundError:
        print(f"错误：文件 {file_path} 未找到！")
    except Exception as e:
        print(f"读取文件时发生错误：{e}")
    finally:
        # openpyxl 会自动处理文件关闭，无需手动关闭
        pass

if __name__ == "__main__":
    read_excel_columns()
```


##### 执行代码 {#执行代码}

你需要修改实际的 Excel 文件名称，并在对应的文件中输入一些数据才能执行程序。

```shell
PS E:\tmp\test04> uv run .\main.py
```

程序的输出如下（输出的内容根据你的文件中的内容会不太一样）：

```shell
读取的A、B列数据（最多10行）：
------------------------------
第 1行: A=MANDT, B=BANFN
第 2行: A=200, B=8900000002
第 3行: A=200, B=8900000048
第 4行: A=200, B=8900000048
第 5行: A=200, B=8900000049
第 6行: A=200, B=8900000668
第 7行: A=200, B=8900000669
第 8行: A=200, B=8900000672
第 9行: A=200, B=8900000681
第10行: A=200, B=8900000682
```


##### 构建项目分发包 {#构建项目分发包}

```shell
PS E:\tmp\test04> uv build
```

```shell
Building source distribution...
running egg_info
creating test04.egg-info
writing test04.egg-info\PKG-INFO
writing dependency_links to test04.egg-info\dependency_links.txt
writing requirements to test04.egg-info\requires.txt
writing top-level names to test04.egg-info\top_level.txt
writing manifest file 'test04.egg-info\SOURCES.txt'
reading manifest file 'test04.egg-info\SOURCES.txt'
writing manifest file 'test04.egg-info\SOURCES.txt'
running sdist
running egg_info
writing test04.egg-info\PKG-INFO
writing dependency_links to test04.egg-info\dependency_links.txt
writing requirements to test04.egg-info\requires.txt
writing top-level names to test04.egg-info\top_level.txt
reading manifest file 'test04.egg-info\SOURCES.txt'
writing manifest file 'test04.egg-info\SOURCES.txt'
running check
creating test04-0.1.0
creating test04-0.1.0\test04.egg-info
copying files to test04-0.1.0...
copying README.md -> test04-0.1.0
copying main.py -> test04-0.1.0
copying pyproject.toml -> test04-0.1.0
copying test04.egg-info\PKG-INFO -> test04-0.1.0\test04.egg-info
copying test04.egg-info\SOURCES.txt -> test04-0.1.0\test04.egg-info
copying test04.egg-info\dependency_links.txt -> test04-0.1.0\test04.egg-info
copying test04.egg-info\requires.txt -> test04-0.1.0\test04.egg-info
copying test04.egg-info\top_level.txt -> test04-0.1.0\test04.egg-info
copying test04.egg-info\SOURCES.txt -> test04-0.1.0\test04.egg-info
Writing test04-0.1.0\setup.cfg
Creating tar archive
removing 'test04-0.1.0' (and everything under it)
Building wheel from source distribution...
running egg_info
writing test04.egg-info\PKG-INFO
writing dependency_links to test04.egg-info\dependency_links.txt
writing requirements to test04.egg-info\requires.txt
writing top-level names to test04.egg-info\top_level.txt
reading manifest file 'test04.egg-info\SOURCES.txt'
writing manifest file 'test04.egg-info\SOURCES.txt'
running bdist_wheel
running build
running build_py
creating build\lib
copying main.py -> build\lib
running egg_info
writing test04.egg-info\PKG-INFO
writing dependency_links to test04.egg-info\dependency_links.txt
writing requirements to test04.egg-info\requires.txt
writing top-level names to test04.egg-info\top_level.txt
reading manifest file 'test04.egg-info\SOURCES.txt'
writing manifest file 'test04.egg-info\SOURCES.txt'
installing to build\bdist.win-amd64\wheel
running install
running install_lib
creating build\bdist.win-amd64\wheel
copying build\lib\main.py -> build\bdist.win-amd64\wheel\.
running install_egg_info
Copying test04.egg-info to build\bdist.win-amd64\wheel\.\test04-0.1.0-py3.14.egg-info
running install_scripts
creating build\bdist.win-amd64\wheel\test04-0.1.0.dist-info\WHEEL
creating 'E:\tmp\test04\dist\.tmp-oxq28ff2\test04-0.1.0-py3-none-any.whl' and adding 'build\bdist.win-amd64\wheel' to it
adding 'main.py'
adding 'test04-0.1.0.dist-info/METADATA'
adding 'test04-0.1.0.dist-info/WHEEL'
adding 'test04-0.1.0.dist-info/top_level.txt'
adding 'test04-0.1.0.dist-info/RECORD'
removing build\bdist.win-amd64\wheel
Successfully built dist\test04-0.1.0.tar.gz
Successfully built dist\test04-0.1.0-py3-none-any.whl
```


##### 查看依赖树 {#查看依赖树}

```shell
PS E:\tmp\test04> uv tree
```

```shell
Resolved 15 packages in 1ms
test04 v0.1.0
├── openpyxl v3.1.5
│   └── et-xmlfile v2.0.0
├── black v26.1.0 (group: dev)
│   ├── click v8.3.1
│   │   └── colorama v0.4.6
│   ├── mypy-extensions v1.1.0
│   ├── packaging v25.0
│   ├── pathspec v1.0.3
│   ├── platformdirs v4.5.1
│   └── pytokens v0.4.0
└── pytest v9.0.2 (group: dev)
    ├── colorama v0.4.6
    ├── iniconfig v2.3.0
    ├── packaging v25.0
    ├── pluggy v1.6.0
    └── pygments v2.19.2
```


#### 安装常用工具 {#安装常用工具}

安装工具：

```shell
uv tool install aider-chat ruff ty basedpyright black
```

安装工具的时候指定 Python 版本：

```shell
uv tool install aider-chat --python 3.11
```

查看已经安装的工具：

```shell
uv tool list
```

```shell
aider-chat v0.86.1
- aider
ansible-lint v26.1.1
- ansible-lint
autopep8 v2.3.2
- autopep8
basedpyright v1.37.1
- basedpyright
- basedpyright-langserver
black v26.1.0
- black
- blackd
warning: Ignoring malformed tool `blink-search` (run `uv tool uninstall blink-search` to remove)
citation-langserver v0.2.2
- citation-langserver
cmake-language-server v0.1.11
- cmake-language-server
cmakelang v0.6.13
- cmake-annotate
- cmake-format
- cmake-genparsers
- cmake-lint
- ctest-to
codex v1.9.2
- codex
cpp-linter v1.11.4
- cpp-linter
cpplint v2.0.2
- cpplint
debugpy v1.8.19
- debugpy
- debugpy-adapter
warning: Ignoring malformed tool `default-python` (run `uv tool uninstall default-python` to remove)
flake8 v7.3.0
- flake8
fortls v3.2.2
- fortls
warning: Ignoring malformed tool `holo-layer` (run `uv tool uninstall holo-layer` to remove)
warning: Ignoring malformed tool `leetcode` (run `uv tool uninstall leetcode` to remove)
warning: Ignoring malformed tool `lsp-bridge` (run `uv tool uninstall lsp-bridge` to remove)
pathaction v0.9.6
- pathaction
pep8 v1.7.1
- pep8
pre-commit v4.5.1
- pre-commit
proselint v0.16.0
- proselint
pyflakes v3.4.0
- pyflakes
pylint v4.0.4
- pylint
- pylint-config
- pyreverse
- symilar
pyrefly v0.48.2
- pyrefly
warning: Ignoring malformed tool `quickrun` (run `uv tool uninstall quickrun` to remove)
robotframework v7.4.1
- libdoc
- rebot
- robot
ruff v0.14.13
- ruff
sqlparse v0.5.5
- sqlformat
tomllint v0.3.2
- tomllint
ty v0.0.12
- ty
yamllint v1.38.0
- yamllint
```

升级特定工具

```shell
uv tool upgrade ruff
```

升级所有工具

```shell
uv tool upgrade --all
```


### Pycharm {#pycharm}


#### 安装 pycharm {#安装-pycharm}

查找有哪些版本的 pycharm:

```shell
scoop search pycharm
```

```shell
'extras' bucket:
    pycharm (2025.3.1.1-253.29346.308)
    pycharm-professional (2025.3.1.1-253.29346.308)

'versions' bucket:
    pycharm-eap (2025.2-252.23892.194)
    pycharm-latest (2025.3-253.30387.25)
    pycharm-professional-eap (2025.3-253.28294.166)
    pycharm-professional-rc (2025.3.2-253.30387.25)
    pycharm-rc (2025.2.3-252.26830.27)
```

安装社区版本的 pycharm:

```shell
scoop install pycharm
```


#### 设置 pycharm 创建新项目的默认目录 {#设置-pycharm-创建新项目的默认目录}

打开配置界面：

{{< figure src="/images/dev-envs.org/2026-01-22_10-08-54_screenshot.png" >}}

找到 **默认项目目录** 然后选择需要保存新的项目目录，然后点确定并重启 IDE 就可以了。

{{< figure src="/images/dev-envs.org/2026-01-22_10-09-42_screenshot.png" >}}


#### 创建新项目 {#创建新项目}

{{< figure src="/images/dev-envs.org/2026-01-22_10-11-22_screenshot.png" >}}

{{< figure src="/images/dev-envs.org/2026-01-22_10-12-45_screenshot.png" >}}

{{< figure src="/images/dev-envs.org/2026-01-22_10-13-37_screenshot.png" >}}

```shell
PS E:\codes\python\test04> ls
```

```shell
    Directory: E:\codes\python\test04

Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
d----           2026/1/22    10:13                .idea
d----           2026/1/22    10:12                .venv
-a---           2026/1/22    10:13            502 main.py
-a---           2026/1/22    10:12            131 pyproject.toml
```

也可以在 pycharm 中通过 Alt+F12 打开终端：

{{< figure src="/images/dev-envs.org/2026-01-22_10-15-52_screenshot.png" >}}

然后就可以执行命令了：

比如安装 openxyxl 包：

{{< figure src="/images/dev-envs.org/2026-01-22_10-16-31_screenshot.png" >}}


## GPG/文件加密 {#gpg-文件加密}


### 安装 {#安装}

```shell
scoop install gpg
```

验证是否安装成功：

```shell
gpg --version
```

```shell
gpg (GnuPG) 2.5.16
libgcrypt 1.11.2
Copyright (C) 2025 g10 Code GmbH
License GNU GPL-3.0-or-later <https://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

Home: D:\Scoop\apps\gpg\current\home
Supported algorithms:
Pubkey: RSA, Kyber, ELG, DSA, ECDH, ECDSA, EDDSA
Cipher: IDEA, 3DES, CAST5, BLOWFISH, AES, AES192, AES256, TWOFISH,
        CAMELLIA128, CAMELLIA192, CAMELLIA256
Hash: SHA1, RIPEMD160, SHA256, SHA384, SHA512, SHA224
Compression: Uncompressed, ZIP, ZLIB, BZIP2
```


### 生成密钥 {#生成密钥}

```shell
gpg --gen-key
```

输入回车，系统会给出提示：

```shell
gpg (GnuPG) 2.5.16; Copyright (C) 2025 g10 Code GmbH
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

gpg: keybox 'D:\\Scoop\\apps\\gpg\\current\\home\\pubring.kbx' created
Note: Use "gpg --full-generate-key" for a full featured key generation dialog.

GnuPG needs to construct a user ID to identify your key.

Real name:
```

一次输入名字以及邮箱：

```shell
Real name: Donald Lo
Email address: donald.sd.lo@gmail.com
You selected this USER-ID:
    "Donald Lo <donald.sd.lo@gmail.com>"

Change (N)ame, (E)mail, or (O)kay/(Q)uit?
```

确认名字和邮箱后输入 o 后回车，会弹出一个输入密码保护 key 的对话框：

{{< figure src="/images/dev-envs.org/2026-01-21_15-37-56_screenshot.png" >}}

输入密码后回车，由于我输入的密码过于简单，弹出如下的对话框：

{{< figure src="/images/dev-envs.org/2026-01-21_15-38-17_screenshot.png" >}}

点击 Take this one anyway 按钮，会让你确认密码：

{{< figure src="/images/dev-envs.org/2026-01-21_15-38-37_screenshot.png" >}}

再此输入密码后点击 OK 就会生成 key。

{{< figure src="/images/dev-envs.org/2026-01-21_15-41-04_screenshot.png" >}}

如果要更多选项，可以使用如下命令生成 key：

```shell
gpg --full-generate-key
```


### 生成一个文本文件 {#生成一个文本文件}

```shell
PS E:\tmp\test04> cat .\test01.txt
```

其中的内容如下：

```shell
01
02
03
04
```


### 加密文件 {#加密文件}

```shell
PS E:\tmp\test04> gpg --recipient "Donald Lo <donald.sd.lo@gmail.com>" --output test01.txt.gpg --encrypt .\test01.txt
```

```shell
gpg: checking the trustdb
gpg: marginals needed: 3  completes needed: 1  trust model: pgp
gpg: depth: 0  valid:   1  signed:   0  trust: 0-, 0q, 0n, 0m, 0f, 1u
gpg: next trustdb check due at 2029-01-20
```

查看加密后的文件内容

```shell
PS E:\tmp\test04> cat test01.txt.gpg
```

内容完全混乱了，无法识别：

```shell
�^+7I␦^�+�@�lQr���&�4   �{�JQ�,%_��h9��
0�b�� �D������_o��-�a�s�b��мu�O1�h����u�p��[    �ZM�S�upn����j}ۑ�ŀ����G�����Ŷ��m�*V;U{gXFU%�R����[�*��s�0�{X�㏌�0FZ"T
```


### 解密 {#解密}

```shell
PS E:\tmp\test04> gpg --output test.de.txt --decrypt test01.txt.gpg
```

回车，如果提示要输入密码就输入之前输入的密码，之后会显示如下的消息：

```shell
gpg: encrypted with cv25519 key, ID 2B37491A5EF82BAB, created 2026-01-21
      "Donald Lo <donald.sd.lo@gmail.com>"
```

查看解密之后的文件：

```shell
PS E:\tmp\test04> cat test.de.txt
```

```shell
01
02
03
04
```


## 测试数学公式 {#测试数学公式}

这是一个行内的数学公式： \\(n^2 = 10\\)

\\[ n + 1 = x + y \\]

这是末尾的字符。
