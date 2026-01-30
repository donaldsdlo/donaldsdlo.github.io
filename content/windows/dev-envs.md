---
title: "windows 开发环境配置"
author: ["Donald Lo"]
date: 2026-01-15
lastmod: 2026-01-30T12:59:20+08:00
tags: ["windows", "dev"]
draft: false
---

<div class="ox-hugo-toc toc">

<div class="heading">&#30446;&#24405;</div>

- [环境变量](#环境变量)
    - [什么是 Windows 环境变量？](#什么是-windows-环境变量)
    - [环境变量的类型](#环境变量的类型)
        - [系统环境变量](#系统环境变量)
        - [用户环境变量](#用户环境变量)
    - [设置重要的环境变量](#设置重要的环境变量)
    - [查看环境变量](#查看环境变量)
    - [内置环境变量](#内置环境变量)
    - [默认环境变量(Windows 10/11)](#默认环境变量--windows-10-11)
- [scoop 方便的软件安装工具](#scoop-方便的软件安装工具)
    - [为什么不用 `winget`](#为什么不用-winget)
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
    - [Listary 应用启动器和文件快速搜索](#listary-应用启动器和文件快速搜索)
    - [PDF 查看工具](#pdf-查看工具)
    - [改键工具](#改键工具)
    - [Busybox-常用的命令行工具](#busybox-常用的命令行工具)
    - [安装浏览器](#安装浏览器)
    - [Obsidian-笔记软件](#obsidian-笔记软件)
    - [轻巧的文本编辑软件-Sublime](#轻巧的文本编辑软件-sublime)
    - [Pandoc-文件格式转换工具](#pandoc-文件格式转换工具)
    - [Octave-开源数据软件](#octave-开源数据软件)
    - [Everything](#everything)
    - [Draw.io](#draw-dot-io)
    - [截图工具](#截图工具)
    - [视频播放软件](#视频播放软件)
    - [数据库客户端](#数据库客户端)
    - [postman 的替代品 bruno](#postman-的替代品-bruno)
    - [yt-dlp 下载网站视频](#yt-dlp-下载网站视频)
        - [软件安装](#软件安装)
        - [在 firefox 中登录哔哩](#在-firefox-中登录哔哩)
        - [你可以使用如下的命令来下载视频](#你可以使用如下的命令来下载视频)
        - [有一些值得追的系列，自动下载](#有一些值得追的系列-自动下载)
        - [只下载音频](#只下载音频)
        - [当然你也可以将这些长的命令写进 powershell 中，变成一个段的函数](#当然你也可以将这些长的命令写进-powershell-中-变成一个段的函数)
    - [Motrix 下载工具](#motrix-下载工具)
    - [SharpKey  键位重映射工具](#sharpkey-键位重映射工具)
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
        - [Iosevka 英文字体-是中文字体宽度的一半](#iosevka-英文字体-是中文字体宽度的一半)
        - [Fira Code-是中文字体宽度的 0.6](#fira-code-是中文字体宽度的-0-dot-6)
- [Rime 中文输入法-可以配置各种输入法](#rime-中文输入法-可以配置各种输入法)
    - [为什么用 Rime？](#为什么用-rime)
    - [我使用 Rime 的理由](#我使用-rime-的理由)
    - [安装 Rime 输入法](#安装-rime-输入法)
    - [使用其他的输入法方案](#使用其他的输入法方案)
    - [自然码双拼输入法辅助码键位图](#自然码双拼输入法辅助码键位图)
- [Windows Terminal](#windows-terminal)
- [Powershell](#powershell)
    - [查找 Powershell](#查找-powershell)
    - [安装 Powershell](#安装-powershell)
    - [设置 Windows Terminal 默认打开的是新版本的 Powershell](#设置-windows-terminal-默认打开的是新版本的-powershell)
    - [查看 Powershell 的配置文件](#查看-powershell-的配置文件)
- [MSYS2](#msys2)
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
        - [安装 Pycharm](#安装-pycharm)
        - [设置 Pycharm 创建新项目的默认目录](#设置-pycharm-创建新项目的默认目录)
        - [创建新项目](#创建新项目)
- [Node](#node)
- [Rust](#rust)
- [Java](#java)
    - [软件安装](#软件安装)
        - [JDK](#jdk)
        - [IDE](#ide)
        - [Maven](#maven)
- [C/C++](#c-c-plus-plus)
- [TexLive](#texlive)
    - [安装方法](#安装方法)
    - [切换镜像](#切换镜像)
    - [下载自定义的 template](#下载自定义的-template)
- [WSL2](#wsl2)
    - [先决条件](#先决条件)
    - [安装 WSL 命令](#安装-wsl-命令)
    - [如果不能按上面的方式安装，则使用如下方式安装](#如果不能按上面的方式安装-则使用如下方式安装)
    - [安装新的 Linux 分发版时将默认版本设置为 WSL 2](#安装新的-linux-分发版时将默认版本设置为-wsl-2)
    - [列出可用的 Linux 分发版](#列出可用的-linux-分发版)
    - [Update WSL](#update-wsl)
    - [在 WSL 上安装 Arch Linux](#在-wsl-上安装-arch-linux)
    - [如果上面的方式安装缓慢，可以从镜像站下载文件后从文件安装](#如果上面的方式安装缓慢-可以从镜像站下载文件后从文件安装)
        - [查找镜像下载 URL](#查找镜像下载-url)
        - [从文件安装 Arch Linux WSL](#从文件安装-arch-linux-wsl)
    - [添加国内镜像](#添加国内镜像)
    - [确认是否已经启用了 `systemd` 服务](#确认是否已经启用了-systemd-服务)
    - [更新系统](#更新系统)
    - [安装熟悉的 NeoVIM](#安装熟悉的-neovim)
    - [修改镜像源](#修改镜像源)
    - [安装一些常用软件](#安装一些常用软件)
    - [安装和配置 Docker](#安装和配置-docker)
        - [安装 Docker](#安装-docker)
        - [启动 Docker 守护进程](#启动-docker-守护进程)
        - [查看 Docker 服务状态](#查看-docker-服务状态)
        - [将用户添加到 Docker 组](#将用户添加到-docker-组)
        - [换源](#换源)
            - [创建目录](#创建目录)
            - [向配置文件写入镜像源](#向配置文件写入镜像源)
            - [重启 Docker 服务](#重启-docker-服务)
            - [验证](#验证)
    - [安装 python 管理工具](#安装-python-管理工具)
    - [备份 Arch](#备份-arch)
    - [问题处理](#问题处理)
        - [Locales](#locales)
    - [字体安装](#字体安装)
    - [输入法](#输入法)
    - [删除 Arch Linux](#删除-arch-linux)
- [虚拟机管理](#虚拟机管理)
    - [设置默认的目录，节省 C 盘空间](#设置默认的目录-节省-c-盘空间)
    - [相关软件安装](#相关软件安装)
    - [虚拟机默认位置](#虚拟机默认位置)
    - [查找 vagrant box](#查找-vagrant-box)
    - [创建虚拟机](#创建虚拟机)
        - [Virtualbox 这是个失败的例子，但是应该是可以成功的，不知道跟什么冲突了](#virtualbox-这是个失败的例子-但是应该是可以成功的-不知道跟什么冲突了)
        - [VMWare](#vmware)
            - [安装 VMWare Workstation](#安装-vmware-workstation)
            - [从网站 https://developer.hashicorp.com/vagrant/install/vmware 上下载 Vagrant VMware Utility 并安装](#从网站-https-developer-dot-hashicorp-dot-com-vagrant-install-vmware-上下载-vagrant-vmware-utility-并安装)
            - [安装 vmware-desktop 插件](#安装-vmware-desktop-插件)
            - [重新下载支持 vmware_desktop 的 Box](#重新下载支持-vmware-desktop-的-box)
            - [初始化虚拟机](#初始化虚拟机)
            - [启动虚拟机](#启动虚拟机)
            - [登录到这个虚拟机](#登录到这个虚拟机)
            - [停止虚拟机](#停止虚拟机)
            - [销毁虚拟机](#销毁虚拟机)
            - [批量创建虚拟机](#批量创建虚拟机)
- [NeoVIM](#neovim)
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


### 什么是 Windows 环境变量？ {#什么是-windows-环境变量}

`Windows` 环境变量是操作系统用于存储与系统运行相关的值或配置信息的 `名称-值` 对。它们用于控制应用程序和操作系统行为，类似于一组全局的设置或配置。环境变量可以影响系统的许多方面，例如文件搜索路径、临时文件存储位置、用户和系统设置等。


### 环境变量的类型 {#环境变量的类型}

环境变量可分为用户变量与系统变量两类。


#### 系统环境变量 {#系统环境变量}

这些变量在整个操作系统范围内可用，影响所有用户和系统中的所有进程。它们通常由系统管理员设置。

常见的系统环境变量包括：

-   `%PATH%` ：定义可执行文件的搜索路径。当你在 命令提示符 中输入一个命令时，系统会在这些路径中搜索对应的可执行文件。
-   `%TEMP%` 或 `%TMP%` ：定义临时文件的存放目录。
-   `%SystemRoot%` ：指向 `Windows` 操作系统的安装目录，通常是 `C:\Windows` 。


#### 用户环境变量 {#用户环境变量}

这些变量仅对特定用户有效，不影响其他用户。用户可以根据自己的需要自定义这些变量。 例如，每个用户都有自己的 `%PATH%` 变量，用于添加特定于该用户的可执行文件路径。


### 设置重要的环境变量 {#设置重要的环境变量}

在 `命令提示符` 中执行如下的命令：

```bash
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


### 查看环境变量 {#查看环境变量}

打开命令提示符（ `cmd` ），然后输入 `env` 命令，按回车。你将看到当前所有的环境变量及其值。

{{< figure src="/images/dev-envs.org/2026-01-25_09-56-26_screenshot.png" width="90%" >}}

输入 `echo %VARIABLE_NAME%` 可以查看特定环境变量的值，例如 `echo %HOME%` 。

{{< figure src="/images/dev-envs.org/2026-01-25_09-57-51_screenshot.png" width="90%" >}}

或者可以通过 **系统设置** :

{{< figure src="/images/dev-envs.org/2026-01-25_10-02-52_screenshot.png" width="90%" >}}

在位置 1 按鼠标右键，然后在位置 2 点击鼠标左键：

{{< figure src="/images/dev-envs.org/2026-01-25_10-09-36_screenshot.png" width="90%" >}}

点击图中的 **高级系统设置**:

{{< figure src="/images/dev-envs.org/2026-01-25_10-05-38_screenshot.png" width="90%" >}}

点击位置 1 的 **环境变量** 按钮：

{{< figure src="/images/dev-envs.org/2026-01-25_10-06-38_screenshot.png" width="90%" >}}

在此界面，除了可以查看环境变量的值，也可以进行维护。


### 内置环境变量 {#内置环境变量}

Windows系统中有一些常见的内置环境变量，它们提供了有关操作系统、用户、文件路径等信息。有一些内置环境变量在“环境变量”设置窗口是不显示的。

以下是一些常见的系统内置环境变量：

-   `%SystemRoot%` ： `Windows` 操作系统的根目录，通常是 `C:\Windows` 。
-   `%PATH%` ：存储可执行文件的搜索路径。当你在命令行中输入命令时，系统会按顺序在这些路径中查找对应的可执行文件。
-   `%TEMP%` / `%TMP%` ：用于存放临时文件的目录。 `Windows` 和应用程序通常在这个目录中创建临时文件。
-   `%ProgramFiles%=：指向默认的程序文件目录，通常是系统中安装的大部分应用程序的存放位置。默认是: =C:\Program Files` 。
-   `%ProgramFiles(x86)%` ：在64位 `Windows=上，指向32位应用程序的默认安装目录。通常是: =C:\Program Files (x86)`  。
-   `%HOMEDRIVE%` ：当前用户的主目录所在的驱动器号。通常是： `C:` 。
-   `%HOMEPATH%` ：当前用户的主目录路径，不包含驱动器号，默认值： `\Users\<用户名>。`
-   `%USERPROFILE%=：当前用户的主目录的完整路径，包括驱动器号。通常是： =C:\Users\<用户名>。`
-   `%APPDATA%` ：指向当前用户的应用程序数据目录，通常用于存放用户配置文件和应用程序数据。通常是： `C:\Users\<用户名>\AppData\Roaming。`
-   `%LOCALAPPDATA%` ：指向当前用户的本地应用程序数据目录，与 `%APPDATA%` 类似，但数据不会在网络中漫游。通常是： `C:\Users\<用户名>\AppData\Local。`
-   `%COMSPEC%` ：指向命令解释器（通常是 `cmd.exe` ）的路径。通常是： `C:\Windows\System32\cmd.exe` 。
-   `%WINDIR%` ：另一个指向 `Windows` 目录的变量，通常与 `%SystemRoot%` 相同。通常是： `C:\Windows` 。
-   `%NUMBER_OF_PROCESSORS%=：指示当前系统中可用的处理器核心数量。示例: =2` （具体取决于具体硬件配置）。
-   `%PROCESSOR_ARCHITECTURE%=：指示处理器架构类型（例如x86、AMD64）。示例: =AMD64` （表示64位架构）。
-   `%PROCESSOR_IDENTIFIER%=： 提供关于处理器的信息，包括型号和制造商。如: =Intel64 Family 6 Model 158 Stepping 10, GenuineIntel` 。
-   `%ALLUSERSPROFILE%` ：指向所有用户的公共配置文件目录，通常用于共享应用程序数。通常是： `C:\ProgramData` 。
-   `%USERPROFILE%` ：当前用户的配置文件的位置，通常是： `C:\Users\<用户名>`


### 默认环境变量(Windows 10/11) {#默认环境变量--windows-10-11}

如果不小心误删除了环境变量，可以使用默认的环境变量进行恢复。(在误删除后，没有重启的情况下，也可以尝试通过注册表记录的值进行恢复，因为修改环境变量后，系统不会立刻刷新注册表）

用户变量默认值：

-   `%PATH%` ： `%USERPROFILE%\AppData\Local\Microsoft\WindowsApps`
-   `%TEMP%` ： `%USERPROFILE%\AppData\Local\Temp`
-   `%TMP%` ： `%USERPROFILE%\AppData\Local\Temp`

系统变量默认值：

-   `%PATH%` ： `%SystemRoot%\system32;%SystemRoot%;%SystemRoot%\System32\Wbem;%SYSTEMROOT%\System32\WindowsPowerShell\v1.0\`
-   `%ComSpec%` ： `%SystemRoot%\system32\cmd.exe`
-   `%PATHEXT%` ： `.COM;.EXE;.BAT;.CMD;.VBS;.VBE;.JS;.JSE;.WSF;.WSH;.MSC`
-   `%DriverData%` ： `C:\Windows\System32\Drivers\DriverData`
-   `%PSModulePath%` ： `%ProgramFiles%\WindowsPowerShell\Modules;%SystemRoot%\system32\WindowsPowerShell\v1.0\Modules`
-   `%TEMP%` ： `%SystemRoot%\TEMP`
-   `%TMP%` ： `%SystemRoot%\TEMP`
-   `%USERNAME%` ： `SYSTEM`
-   `%windir%` ： `%SystemRoot%`


## scoop 方便的软件安装工具 {#scoop-方便的软件安装工具}

Scoop 是一个面向 Windows 的命令行安装程序（包管理器），旨在简化在 Windows 系统上安装、更新和管理开源命令行工具和应用程序的过程。

主要特点包括：

-   **无需管理员权限** ：默认将软件安装到用户目录（如 `~\scoop` ），避免系统污染。
-   **使用简单** ：通过简洁的命令（如 `scoop install <app>` ）即可完成软件的安装。
-   **基于 Git 和 JSON 清单** ：软件定义以 JSON 格式存储在称为“bucket”的仓库中，便于维护和扩展。
-   **支持多 bucket** ：除了官方主仓库（main bucket），还支持额外的社区或私有 bucket（如 `extras` 、 `versions`  等）。
-   **自动处理 PATH 和依赖** ：安装后自动配置环境变量，部分软件会自动安装所需依赖（如 Visual C++ Redistributables）。


### 为什么不用 `winget` {#为什么不用-winget}

因为到目前位置，我也不知道如何设置 `winget` 安装软件的目录，我不想把所有的软件都安装到 C 盘，所以能用 `Scoop` 安装的软件，我就用 `Scoop` 安装，
如果无法使用 `Scoop` 来安装，就使用 `Winget` 来安装了。


### 安装 scoop {#安装-scoop}


#### 设置环境变量 {#设置环境变量}

```bash
setx SCOOP "D:\Scoop"
setx SCOOP_GLOBAL "D:\ScoopGlobalApps"
```


#### 打开powershell，依次输入下面的命令 {#打开powershell-依次输入下面的命令}

```bash
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
```

```bash
irm get.scoop.sh | iex
```


### 配置国内镜像源 {#配置国内镜像源}


#### 先删除默认 main 源 {#先删除默认-main-源}

```bash
scoop bucket rm main
```

可以通过如下的命令查看已经安装的 bucket 清单，根据实际需要将对应的 bucket 删除，然后换成国内的源。

```bash
scoop bucket list
```

你可能可以看到如下的结果：

```bash
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

```bash
scoop bucket add extras https://mirror.nju.edu.cn/git/scoop-extras.git/
scoop bucket add java https://mirror.nju.edu.cn/git/scoop-java.git/
scoop bucket add main https://mirror.nju.edu.cn/git/scoop-main.git/
scoop bucket add nerd-fonts https://mirror.nju.edu.cn/git/scoop-nerd-fonts.git/
scoop bucket add nirsoft https://mirror.nju.edu.cn/git/scoop-nirsoft.git/
scoop bucket add nonportable https://mirror.nju.edu.cn/git/scoop-nonportable.git/
scoop bucket add versions https://mirror.nju.edu.cn/git/scoop-versions.git/
```


#### 恢复回官方源 {#恢复回官方源}

```bash
scoop bucket rm main
scoop bucket rm extras
scoop bucket add main
scoop bucket add extras
```


### 配置 {#配置}

开启缓存，避免重复下载

```bash
scoop config cache_enabled true
```


### 安装常用工具 {#安装常用工具}

```bash
scoop install git aria2 coreutils fzf grep gzip make ripgrep rga wget which fd 7zip ag altsnap ast-grep astyle autojump curl delta direnv everything everything-cli ffmpeg geekuninstaller  hugo hugo-extended mpv pandoc scoop-search gpg busybox
```


### 使用aria2加速下载 {#使用aria2加速下载}

```bash
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

```bash
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

```bash
scoop config /?
```


### 查找软件 {#查找软件}

```bash
scoop search emacs
```

```bash
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

```bash
scoop install emacs-kl
```


### Listary 应用启动器和文件快速搜索 {#listary-应用启动器和文件快速搜索}

```bash
scoop install listary
```


### PDF 查看工具 {#pdf-查看工具}

```bash
scoop install sumatrapdf
```


### 改键工具 {#改键工具}

```bash
scoop install sharpkeys
```


### Busybox-常用的命令行工具 {#busybox-常用的命令行工具}

```shell
scoop install busybox
```


### 安装浏览器 {#安装浏览器}

```shell
scoop install googlechrome
```


### Obsidian-笔记软件 {#obsidian-笔记软件}

```shell
scoop install obsidian
```


### 轻巧的文本编辑软件-Sublime {#轻巧的文本编辑软件-sublime}

```shell
scoop install sublime-text
```


### Pandoc-文件格式转换工具 {#pandoc-文件格式转换工具}

```shell
scoop install pandoc
```


### Octave-开源数据软件 {#octave-开源数据软件}

```shell
scoop install octave
```


### Everything {#everything}

```shell
scoop install everything everything-cli
```


### Draw.io {#draw-dot-io}

```shell
scoop install draw.io
```


### 截图工具 {#截图工具}

```bash
scoop install snipaste
```


### 视频播放软件 {#视频播放软件}

```bash
scoop install potplayer
```


### 数据库客户端 {#数据库客户端}

```bash
scoop install dbeaver
```


### postman 的替代品 bruno {#postman-的替代品-bruno}

```bash
scoop install bruno
```


### yt-dlp 下载网站视频 {#yt-dlp-下载网站视频}

如果你希望将哔哩上的视频下载到本地电脑上，在没有网络的时候也可以观看，你可以选择使用哔哩的客户端同步，也可以使用
yt-dlp 这个软件下载成 MP4 格式，然后使用你喜欢的视频播放器来观看。

当然，这个软件也不只能下载哔哩上的视频，可以下载很多网站上的视频的。


#### 软件安装 {#软件安装}

```shell
scoop install ffmpeg yt-dlp
```

yt-dlp 依赖 ffmpeg，所以你必须安装。


#### 在 firefox 中登录哔哩 {#在-firefox-中登录哔哩}


#### 你可以使用如下的命令来下载视频 {#你可以使用如下的命令来下载视频}

```shell
yt-dlp  --cookies-from-browser firefox --download-archive D:\Documents\yt-dlp\archives.txt --output "%(playlist_title)s/%(upload_date)s - P%(playlist_index)04d - %(title)s.%(ext)s" --format "bestvideo[ext=mp4]+bestaudio[ext=m4a]/best" 视频的网址
```

-   --cookies-from-browser firefox 在使用 yt-dlp 下载需要登录才能访问的音视频时，--cookies-from-browser 是最便捷且安全的身份认证方式之一，它可以直接从浏览器读取已登录的 Cookie 信息，避免手动导出或构造 Cookie。使用 firefox 中的 cookies 信息登录，将 firefox 替换为你已登录的浏览器名称（支持 chrome、edge、safari、opera 等）
-   --download-archive D:\Documents\yt-dlp\archives.txt 将下载过的视频的 ID 保存在这个文件中，避免重复下载
-   --output "%(playlist_title)s/%(upload_date)s - P%(playlist_index)04d - %(title)s.%(ext)s" 下载到本地的视频的文件名称
-   --format "bestvideo[ext=mp4]+bestaudio[ext=m4a]/best" 以最好的视频质量和音频质量下载


#### 有一些值得追的系列，自动下载 {#有一些值得追的系列-自动下载}

将需要追的系列的 URL 保存到 URL.txt 文件中，格式如下：

```shell
# 文明之旅
https://space.bilibili.com/3546593938639500/channel/collectiondetail?sid=4220708

# 合集·【长江】吃饭故事
https://space.bilibili.com/39627524/channel/collectiondetail?sid=5219365
```

然后使用如下命令来下载，注意，执行命令的目录就是下载视频的目录：

```shell
yt-dlp  --cookies-from-browser firefox --download-archive D:\Documents\yt-dlp\archives.txt --output "%(playlist_title)s/%(upload_date)s - P%(playlist_index)04d - %(title)s.%(ext)s" --format "bestvideo[ext=mp4]+bestaudio[ext=m4a]/best"  -a D:\Documents\yt-dlp\urls.txt
```


#### 只下载音频 {#只下载音频}

如果有一些有声书，可以通过如下的命令来下载：

```shell
yt-dlp  --cookies-from-browser firefox --download-archive D:\Documents\yt-dlp\archives.txt --output "%(playlist_title)s/%(upload_date)s - P%(playlist_index)04d - %(title)s.%(ext)s" --format "bestaudio[ext=m4a]/best" 视频网址
```


#### 当然你也可以将这些长的命令写进 powershell 中，变成一个段的函数 {#当然你也可以将这些长的命令写进-powershell-中-变成一个段的函数}

```shell
vim $PROFILE
```

如果打开文件不成功，就根据提示创建对应的文件夹和文件。

将以下代码添加到 $PROFILE 这个文件中：

```shell
function y {
    yt-dlp  --cookies-from-browser firefox `
            --download-archive D:\Documents\yt-dlp\archives.txt `
            --output "%(playlist_title)s/%(upload_date)s - P%(playlist_index)04d - %(title)s.%(ext)s" `
            --format "bestvideo[ext=mp4]+bestaudio[ext=m4a]/best" `
            $args
}
function y1 {
    yt-dlp  --cookies-from-browser firefox `
            --download-archive D:\Documents\yt-dlp\archives.txt `
            --output "%(playlist_title)s/%(upload_date)s - P%(playlist_index)04d - %(title)s.%(ext)s" `
            --format "bestvideo[ext=mp4]+bestaudio[ext=m4a]/best"  `
            -a D:\Documents\yt-dlp\urls.txt
}
function y3 {
    yt-dlp  --cookies-from-browser firefox `
            --download-archive D:\Documents\yt-dlp\archives.txt `
            --output "%(playlist_title)s/%(upload_date)s - P%(playlist_index)04d - %(title)s.%(ext)s" `
            --format "bestaudio[ext=m4a]/best" `
            $args
}
```

重新启动 powershell 后，你就可以使用 <kbd>y 视频网址</kbd> 来下载视频，~y1~ 命令直接下载保存的视频系列， <kbd>y3 视频地址</kbd> 来下载音频文件。


### Motrix 下载工具 {#motrix-下载工具}

```bash
scoop install motrix
```


### SharpKey  键位重映射工具 {#sharpkey-键位重映射工具}

```bash
scoop install sharpkey
```

{{< figure src="/images/dev-envs.org/2026-01-24_17-59-48_screenshot.png" width="90%" >}}

{{< figure src="/images/dev-envs.org/2026-01-24_18-00-38_screenshot.png" width="90%" >}}

可以在上图中用鼠标选择对应的键，也可以通过点击对应 `Type Key` 按钮然后在键盘上敲击对应的键来选择，输入完成
后，然后点击 `OK` 按钮。

{{< figure src="/images/dev-envs.org/2026-01-24_18-02-55_screenshot.png" width="90%" >}}

可以看到添加的映射关系在图中位置 1 显示，然后点击 `Write to Regist` 按钮，将这个映射关系保存到 windows 系统
的注册表中，然后重新启动电脑使得这个映射关系生效。


### 显示当前软件是否有需要更新 {#显示当前软件是否有需要更新}

```bash
scoop status
```

```bash
Scoop is up to date.
Everything is ok!
```

如果返回的是上面的消息，则所有安装的软件都不需要更新。


### 软件更新 {#软件更新}

更新指定的软件

```bash
scoop update deno
```

更新所有软件：

```bash
scoop update -a
```


### 卸载软件 {#卸载软件}

```bash
scoop uninstall peazip
```

```bash
Uninstalling 'peazip' (10.8.0).
Removing shim 'peazip.shim'.
Removing shim 'peazip.exe'.
Removing shortcut ~\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Scoop Apps\PeaZip.lnk
Unlinking D:\Scoop\apps\peazip\current
'peazip' was uninstalled.
```


### 删除软件的旧版本 {#删除软件的旧版本}

```bash
scoop cleanup *
```

会显示删除的所有的版本信息：

```bash
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

```bash
scoop search maple
```

```bash
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

```bash
scoop download Maple-Mono-NF-CN
```

```bash
INFO  Downloading 'Maple-Mono-NF-CN' [64bit] from nerd-fonts bucket
Starting download with aria2 ...
Download: [#694632 55MiB/152MiB(36%) CN:5 DL:332KiB ETA:4m57s]
```

当出现如下最后一行的信息时，表示已经下载完成。

```bash
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

{{< figure src="/images/dev-envs.org/2026-01-16_14-43-09_screenshot.png" width="90%" >}}

需要手工解压缩：

{{< figure src="/images/dev-envs.org/2026-01-16_14-43-55_screenshot.png" width="90%" >}}

选中所有的字体文件（以 ttf 结尾的文件），然后鼠标右键菜单中选择 **为所有用户安装** :

{{< figure src="/images/dev-envs.org/2026-01-16_14-49-30_screenshot.png" width="90%" >}}


### 常用的字体 {#常用的字体}


#### 落霞孤鹜中文字体 {#落霞孤鹜中文字体}

```bash
scoop search lxgw
```

```bash
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

```bash
scoop search source
```

```bash
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


#### Iosevka 英文字体-是中文字体宽度的一半 {#iosevka-英文字体-是中文字体宽度的一半}

```bash
scoop search iosevka
```

```bash
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


#### Fira Code-是中文字体宽度的 0.6 {#fira-code-是中文字体宽度的-0-dot-6}

```bash
scoop search firacode
```

```bash
Results from local buckets...

Name              Version Source     Binaries
----              ------- ------     --------
FiraCode-NF-Mono  3.4.0   nerd-fonts
FiraCode-NF-Propo 3.4.0   nerd-fonts
FiraCode-NF       3.4.0   nerd-fonts
FiraCode-Script   0.0.28  nerd-fonts
FiraCode          6.2     nerd-fonts
```

```bash
scoop download FiraCode-NF-Mono
```


## Rime 中文输入法-可以配置各种输入法 {#rime-中文输入法-可以配置各种输入法}


### 为什么用 Rime？ {#为什么用-rime}

明明对于大多数用户来说，类似搜狗输入法、微信输入法、乃至于手心输入法之类的主流输入法，已经完全够用了啊？

事实上，Rime 适合的用户，大多是：

-   喜欢极简/干净/小而美
-   极度反感广告
-   有高度定制需求
-   对输入安全有需求
-   对输入速度有追求
-   对切换多种输入方案有需求
-   对输入标点快符、自定义短语有需求
-   使用小众输入方案，如双拼、音形、形码
-   对输入生僻字有需求，如常常输入古书、文献上的字等
-   对输入精确的繁体字、外来字、外语字有需求
-   部分程序员
-   部分文案、编辑、网文写手
-   打字圈、竞速圈用户

其中，使用小众输入方案的用户是 Rime 用户群体最常见的来源之一。

例如：使用双拼、音形、形码的用户，是最容易接触到 Rime 的。

说得明确些，对于这类用户，我个人 100% 推荐使用 Rime。

理由是：Rime 对小众方案的支持几乎是开箱即用的，在 GitHub 与任意方案的群里，都能找到现成的方案对应的 Rime 包。直接下载复制到 Rime 的用户文件夹目录，右键一点托盘重新部署，稍等片刻让 Rime 自动生成对应文件，就能直接使用。

此时就会发现 Rime 的独一档优势：

-   主流输入法几乎不可能支持小众方案，即使支持，也不会完善；
-   Rime 的高定制性，让小众方案的开箱即用包基本都定制了大量功能（例如反查、以词定字、辅助码、重复上屏、快捷输入等），非常好用；
-   几乎所有小众方案都支持的标点快符功能，让输入标点符号时双手再也不用离开主键区，输入流畅度飞跃式提升。（这条对文案、网文写手等用户群体来说非常有用）


### 我使用 Rime 的理由 {#我使用-rime-的理由}

我要使用带辅助码的自然码输入法，原来周志农开发的自然码输入法不再维护，无法继续使用，在 github 上找到了一个开源的 Rime 码表，于是采用了 Rime。
发现原来的词库太小，然后又将一些开源的词库转换成自然码输入法的词库，但是多音字会有些问题，在使用的过程中不断的修正中。

我不使用大模型是因为我很多时候都使用辅助码来提高输入的效率，如果你需要使用大模型来提高输入效率，可以在 <https://github.com/amzxyz/RIME-LMDG/releases> 中下载  wanxiang-lts-zh-hans.gram 保存到用户文件夹。

使用我的配置，从  <https://github.com/donaldsdlo/weasel> 克隆到本地目录，比如我克隆到了 D:\home\rime 中。


### 安装 Rime 输入法 {#安装-rime-输入法}

从  <https://rime.im/> 下载最新的版本进行安装：

{{< figure src="/images/dev-envs.org/PixPin_2026-01-30_10-57-13.png" width="90%" >}}

{{< figure src="/images/dev-envs.org/PixPin_2026-01-30_10-57-32.png" width="90%" >}}

{{< figure src="/images/dev-envs.org/PixPin_2026-01-30_10-58-00.png" width="90%" >}}

在这里我们需要指定用户文件夹在前面克隆的目录：

{{< figure src="/images/dev-envs.org/PixPin_2026-01-30_10-58-23.png" width="90%" >}}

{{< figure src="/images/dev-envs.org/PixPin_2026-01-30_10-58-36.png" width="90%" >}}

{{< figure src="/images/dev-envs.org/PixPin_2026-01-30_10-58-57.png" width="90%" >}}

{{< figure src="/images/dev-envs.org/PixPin_2026-01-30_10-59-11.png" width="90%" >}}

{{< figure src="/images/dev-envs.org/PixPin_2026-01-30_10-59-28.png" width="90%" >}}

{{< figure src="/images/dev-envs.org/PixPin_2026-01-30_10-59-39.png" width="90%" >}}

如果你使用带辅助码的自然码输入法，你就可以直接使用了。


### 使用其他的输入法方案 {#使用其他的输入法方案}

如果你需要使用其他的输入法，可以在 default.custom.yaml 文件中，调整 schema 的顺序或者把需要的输入法的注释去掉：

```yaml
  schema_list:
    - schema: zrm2000
    # - schema: wubi86_jidian
    # - schema: openfly
    # - schema: rime_ice
    # - schema: double_pinyin_flypy
    - schema: numbers
    # - schema: double_pinyin
    - schema: melt_eng
    - schema: latex
```

修改完成后需要重新部署 Rime 输入法。

如果要使用大模型，按照前面的网址下载后保存到 D:\home\rime 文件夹中，然后将 zrm2000.custom.yaml 中的如下行中的注释去掉，再重新部署输入法：

```yaml
# patch:
#   grammar:
#     language: wanxiang-lts-zh-hans
#     collocation_max_length: 5
#     collocation_min_length: 2
#   translator/contextual_suggestions: true
#   translator/max_homophones: 7
#   translator/max_homographs: 7
```

去掉注释后的配置文件如下：

```yaml
patch:
  grammar:
    language: wanxiang-lts-zh-hans
    collocation_max_length: 5
    collocation_min_length: 2
  translator/contextual_suggestions: true
  translator/max_homophones: 7
  translator/max_homographs: 7
```


### 自然码双拼输入法辅助码键位图 {#自然码双拼输入法辅助码键位图}

{{< figure src="/images/dev-envs.org/ziranmashurufa.jpg" width="90%" >}}


## Windows Terminal {#windows-terminal}

```bash
scoop install windows-terminal
```


## Powershell {#powershell}


### 查找 Powershell {#查找-powershell}

```bash
winget search --id Microsoft.PowerShell
```

```bash
名称               ID                           版本    源
---------------------------------------------------------------
PowerShell         Microsoft.PowerShell         7.5.4.0 winget
PowerShell Preview Microsoft.PowerShell.Preview 7.6.0.6 winget
```


### 安装 Powershell {#安装-powershell}

```bash
winget install --id Microsoft.PowerShell --source winget
```


### 设置 Windows Terminal 默认打开的是新版本的 Powershell {#设置-windows-terminal-默认打开的是新版本的-powershell}

打开 Windows Termial

{{< figure src="/images/dev-envs.org/2026-01-20_09-02-04_screenshot.png" width="90%" >}}

通过 Ctrl+, 快捷键打开设置界面

{{< figure src="/images/dev-envs.org/2026-01-20_09-02-58_screenshot.png" width="90%" >}}


### 查看 Powershell 的配置文件 {#查看-powershell-的配置文件}

```bash
echo $PROFILE
```

```bash
D:\Documents\PowerShell\Microsoft.PowerShell_profile.ps1
```

需要添加的配置和一些函数都可以写在这个文件中。


## MSYS2 {#msys2}


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

```bash
setx UV_PYTHON_INSTALL_DIR D:\uv\python
setx UV_TOOL_DIR D:\uv\tools
```


#### 使用国内镜像 {#使用国内镜像}

在文件 ~/.config/uv/uv.toml 中添加如下内容：

```toml
[[index]]
url = "https://mirrors.xjtu.edu.cn/docs/pypi/"
default = true
```


#### 采用 UV 来管理 python 版本和项目虚拟环境，安装 UV 软件： {#采用-uv-来管理-python-版本和项目虚拟环境-安装-uv-软件}

```bash
scoop install uv
```

安装完成后，可以通过以下命令验证安装是否成功：

```bash
uv --version
```

安装正确会得到版本号：

```bash
uv 0.9.26 (ee4f00362 2026-01-15)
```


#### 创建系统默认的 Python 环境 {#创建系统默认的-python-环境}

在 D:\python-envs 目录中：

```bash
uv init default-python --python 3.14
```

```bash
cd default-python
```

安装包：

```bash
uv add requests
```

指定版本约束

```bash
uv add 'requests==2.31.0'
```

添加 Git 依赖:

```bash
uv add git+https://github.com/psf/requests
```

将指定包更新到最新的兼容版本，同时保持锁文件中其他依赖不变:

```bash
uv lock --upgrade-package requests
```

从 requirements.txt 文件添加所有依赖:

```bash
uv add -r requirements.txt -c constraints.txt
```

删除包：

```bash
uv remove requests
```

将 default-python\\.venv\Scripts 的完整目录添加到 PATH 环境变量的最前面，这样就可以使用这个环境下的 python 作为系统的默认 python 了。


#### 要为 uv 命令启用 Powershell 自动补全，在 Powershell 中运行以下对应命令： {#要为-uv-命令启用-powershell-自动补全-在-powershell-中运行以下对应命令}

```bash
if (!(Test-Path -Path $PROFILE)) {
  New-Item -ItemType File -Path $PROFILE -Force
}

Add-Content -Path $PROFILE -Value '(& uv generate-shell-completion powershell) | Out-String | Invoke-Expression'
```


#### 使用 uv 管理多版本 Python {#使用-uv-管理多版本-python}


##### 显示可安装以及已经安装的 Python 版本： {#显示可安装以及已经安装的-python-版本}

```bash
uv python list
```

```bash
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

```bash
uv python install 3.9
```

```bash
cpython-3.9.25-windows-x86_64-none (download) ------------------------------ 1.73 MiB/21.67 MiB
```

出现如下的消息时表示已经安装完成：

```bash
Installed Python 3.9.25 in 2m 31s
 + cpython-3.9.25-windows-x86_64-none (python3.9.exe)
```

也可以使用完整的名称来安装 Python:

```bash
uv python install pypy-3.8.16-windows-x86_64-none
```

```bash
pypy-3.8.16-windows-x86_64-none (download) ------------------------------ 1.58 MiB/29.98 MiB
```

出现如下的消息时表示已经安装完成：

```bash
Installed Python 3.8.16 in 13m 42s
 + pypy-3.8.16-windows-x86_64-none (python3.8.exe)
```


##### 已经安装的版本，在后续使用到此版本的时候，UV 不会重复下载。 {#已经安装的版本-在后续使用到此版本的时候-uv-不会重复下载}


##### 查看安装的结果 {#查看安装的结果}

```bash
uv python list
```

```bash
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

```bash
uv python dir
```

```bash
D:\uv\python
```


##### 移除已安装的版本 {#移除已安装的版本}

```bash
uv python uninstall 3.9
```

```bash
Searching for Python versions matching: Python 3.9
Uninstalled Python 3.9.25 in 483ms
 - cpython-3.9.25-windows-x86_64-none (python3.9.exe)
```

也可以通过完整的 Python 版本名称来移除：

```bash
uv python uninstall pypy-3.8.16-windows-x86_64-none
```

```bash
Searching for Python versions matching: pypy-3.8.16-windows-x86_64-none
Uninstalled Python 3.8.16 in 431ms
 - pypy-3.8.16-windows-x86_64-none (python3.8.exe)
```


#### 管理项目 {#管理项目}


##### 创建一个项目 {#创建一个项目}

```bash
PS E:\tmp> uv init test04 --python 3.14
```

```bash
Initialized project `test04` at `E:\tmp\test04`
```

执行完这个命令后，会创建 `test04` 目录并在其中创建如下的文件：

```bash
PS E:\tmp\test04> ls
```

```bash
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
    ```bash
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

```bash
PS E:\tmp\test04> uv add openpyxl
```

```bash
Using CPython 3.14.0
Creating virtual environment at: .venv
Resolved 3 packages in 426ms
Installed 2 packages in 498ms
 + et-xmlfile==2.0.0
 + openpyxl==3.1.5
```

添加只在开发时使用的包

```bash
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

```bash
PS E:\tmp\test04> uv run .\main.py
```

程序的输出如下（输出的内容根据你的文件中的内容会不太一样）：

```bash
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

```bash
PS E:\tmp\test04> uv build
```

```bash
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

```bash
PS E:\tmp\test04> uv tree
```

```bash
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

```bash
uv tool install aider-chat ruff ty basedpyright black
```

安装工具的时候指定 Python 版本：

```bash
uv tool install aider-chat --python 3.11
```

查看已经安装的工具：

```bash
uv tool list
```

```bash
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

```bash
uv tool upgrade ruff
```

升级所有工具

```bash
uv tool upgrade --all
```


### Pycharm {#pycharm}


#### 安装 Pycharm {#安装-pycharm}

查找有哪些版本的 Pycharm:

```bash
scoop search pycharm
```

```bash
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

安装社区版本的 Pycharm:

```bash
scoop install pycharm
```


#### 设置 Pycharm 创建新项目的默认目录 {#设置-pycharm-创建新项目的默认目录}

打开配置界面：

{{< figure src="/images/dev-envs.org/2026-01-22_10-08-54_screenshot.png" width="90%" >}}

找到 **默认项目目录** 然后选择需要保存新的项目目录，然后点确定并重启 IDE 就可以了。

{{< figure src="/images/dev-envs.org/2026-01-22_10-09-42_screenshot.png" width="90%" >}}


#### 创建新项目 {#创建新项目}

{{< figure src="/images/dev-envs.org/2026-01-22_10-11-22_screenshot.png" width="90%" >}}

{{< figure src="/images/dev-envs.org/2026-01-22_10-12-45_screenshot.png" width="90%" >}}

1.  输入项目的目录
2.  选择使用 Git 来管理项目版本
3.  选择使用 UV 来管理项目的 Python 虚拟环境
4.  选择使用的 Python 版本
5.  选择使用的 UV 的可执行文件，一般使用默认的就可以了
6.  确认上面的选项后点击 `创建` 按钮创建项目

{{< figure src="/images/dev-envs.org/2026-01-22_10-13-37_screenshot.png" width="90%" >}}

```bash
PS E:\codes\python\test04> ls
```

```bash
    Directory: E:\codes\python\test04

Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
d----           2026/1/22    10:13                .idea
d----           2026/1/22    10:12                .venv
-a---           2026/1/22    10:13            502 main.py
-a---           2026/1/22    10:12            131 pyproject.toml
```

也可以在 pycharm 中通过 Alt+F12 打开终端：

{{< figure src="/images/dev-envs.org/2026-01-22_10-15-52_screenshot.png" width="90%" >}}

然后就可以执行命令了：

比如安装 openxyxl 包：

{{< figure src="/images/dev-envs.org/2026-01-22_10-16-31_screenshot.png" width="90%" >}}


## Node {#node}


## Rust {#rust}


## Java {#java}


### 软件安装 {#软件安装}


#### JDK {#jdk}

```bash
scoop search openjdk
```

```bash
Results from local buckets...

Name                Version    Source Binaries
----                -------    ------ --------
openjdk-ea          25.0.2-10  java
openjdk             25.0.2-10  java
openjdk10           10.0.2-13  java
openjdk11           11.0.2-9   java
openjdk12           12.0.2-10  java
openjdk13           13.0.2-8   java
openjdk14           14.0.2-12  java
openjdk15           15.0.2-7   java
openjdk16           16.0.2-7   java
openjdk17           17.0.2-8   java
openjdk18           18.0.2.1-1 java
openjdk19           19.0.2-7   java
openjdk20           20.0.2-9   java
openjdk21           21.0.2-13  java
openjdk22           22.0.2-9   java
openjdk23           23.0.2-7   java
openjdk24           24.0.2-12  java
openjdk25           25.0.2-10  java
openjdk7-unofficial 7u80-b32   java
openjdk8-redhat-jre 8u342-b07  java
openjdk8-redhat     8u342-b07  java
openjdk9            9.0.4-12   java
```

这里安装最新的 JDK 版本：

```bash
scoop install openjdk25
```


#### IDE {#ide}

```bash
scoop search idea
```

```bash
Results from local buckets...

Name                 Version                  Source   Binaries
----                 -------                  ------   --------
gridea               0.9.3                    extras
idea-ultimate        2025.3.1.1-253.29346.240 extras
idea                 2025.2.6.1-252.28539.33  extras
idea-eap             2025.2.2-252.26199.7     versions
idea-rc              2025.2.4-252.27397.28    versions
idea-ultimate-eap    2026.1-261.17801.55      versions
idea-ultimate-latest 261.17801.55             versions
idea-ultimate-rc     2025.3.1-253.29346.50    versions
```

安装社区版本：

```bash
scoop install idea
```


#### Maven {#maven}

```bash
scoop search maven
```

```bash
Results from local buckets...

Name   Version    Source   Binaries
----   -------    ------   --------
maven  3.9.12     main
maven3 3.9.12     versions
maven4 4.0.0-rc-5 versions
```

安装最新版本：

```bash
scoop install maven4
```


## C/C++ {#c-c-plus-plus}


## TexLive {#texlive}

<https://mirrors.tuna.tsinghua.edu.cn/help/CTAN/>

TeX Live 是目前使用最为广泛的 TeX 发行版，支持 Windows、Linux 和 macOS。其中，在 macOS 上发行的版本称为 MacTeX。


### 安装方法 {#安装方法}

TeX Live 发行版的常见安装方法可以参考如下文档。

<https://mirrors.tuna.tsinghua.edu.cn/CTAN/info/install-latex-guide-zh-cn/install-latex-guide-zh-cn.pdf>

除每年更新的完整版 ISO 镜像以外，CTAN 镜像中也包含在线安装器。这种方法可以使安装的所有宏包均为最新版本，但受网络连接状况影响较大。操作方法为（ _很可能需要管理员权限_ ）：

1.  下载 install-tl.zip 并解压缩
    <https://mirrors.tuna.tsinghua.edu.cn/CTAN/systems/texlive/tlnet/install-tl.zip>
2.  Windows 下双击运行其中的 `install-tl.bat` 。如果有图形化界面，可以在进入安装器前的右下角按钮指定使用镜像源。


### 切换镜像 {#切换镜像}

TeX Live 使用的 CTAN 镜像源可以从内置的包管理器 `tlmgr`  更改（ _很可能需要管理员权限_ ）。

在命令行中执行

```bash
tlmgr option repository https://mirrors.tuna.tsinghua.edu.cn/CTAN/systems/texlive/tlnet
```

即可永久更改镜像源。

如果只需要临时切换，可以用如下命令：

```bash
tlmgr update --all --repository https://mirrors.tuna.tsinghua.edu.cn/CTAN/systems/texlive/tlnet
```

其中的 `update --all`  指令可根据需要修改。


### 下载自定义的 template {#下载自定义的-template}

我将 Texlive 安装在 D:\texlive\\ 下，可以将 template 下载到 D:\texlive\texmf-local\tex\latex\local 这个目录中：

```shell
PS D:\texlive\texmf-local\tex\latex\local> git clone https://github.com/kimim/ElegantBook.git
```

```tex
% Created 2025-12-29 周一 11:54
% Intended LaTeX compiler: pdflatex
\documentclass[lang=cn,color=blue]{elegantbook}
                        % 中文默认字体：方正书宋_GBK，粗体为思源宋体半粗体，斜体为方正楷体_GBK
                        \setCJKmainfont{LXGW Neo ZhiSong Plus}[BoldFont={Source Han Serif SC SemiBold}, ItalicFont={Source Han Serif SC ExtraLight}]
                        % 中文无衬线字体：方正黑体_GBK，粗体为思源黑体中粗体
                        \setCJKsansfont{LXGW Neo XiHei Plus}[BoldFont={Source Han Sans SC Medium}]
                        % 中文等宽字体：方正仿宋_GBK
                        \setCJKmonofont{Zhuque Fangsong (technical preview)}

                        \newCJKfontfamily\songti{LXGW Neo ZhiSong Plus}[BoldFont={Source Han Serif SC SemiBold}]
                        \newCJKfontfamily\xbsong{Source Han Serif SC SemiBold} % 小标宋
                        \newCJKfontfamily\dbsong{Source Han Serif SC Bold} % 大标宋
                        \newCJKfontfamily\cusong{Source Han Serif SC Heavy} % 粗宋
                        \newCJKfontfamily\heiti{LXGW Neo XiHei Plus}[BoldFont={Source Han Sans SC Medium}]
                        \newCJKfontfamily\dahei{Source Han Sans SC Medium} % 大黑
                        \newCJKfontfamily\cuhei{Source Han Sans SC Bold} % 粗黑
                        \newCJKfontfamily\fangsong{Zhuque Fangsong (technical preview)}
                        \newCJKfontfamily\kaiti{Source Han Serif SC ExtraLight}

                        \setcounter{tocdepth}{3}
                        \logo{logo-blue.png}
                        \cover{cover.jpg}
                        \graphicspath{{D:/texlive/texmf-local/tex/latex/local/ElegantBook/figure/}}
                        \graphicspath{{D:/texlive/texmf-local/tex/latex/local/ElegantBook/image/}}
                        \usepackage{svg} % <- 引入 svg 宏包
                        \usepackage{minted}
                        % 统一代码块设置
                        \setminted{frame=single, linenos, breaklines, autogobble, fontsize=\small, baselinestretch=1}
                        \usepackage{cleveref}
\colorlet{color-theme}{main}  % 绑定到 ElegantBook 主色
\usepackage{unicode-math}  % 加载 unicode-math 宏包
\author{张三}
\date{\today}
\title{微分几何引论\\\medskip
\large 曲线与曲面}
\hypersetup{
  pdfauthor={张三},
  pdftitle={微分几何引论},
  pdfkeywords={},
  pdfsubject={}}\begin{document}

\maketitle
\tableofcontents

%\maketitle
%\frontmatter

%\tableofcontents

\mainmatter
\chapter{过滤}
\label{sec:org298f4ce}
\section{定理示例}
\label{sec:org05b1ae2}
这是一个重要定理。
Update (2024-09-08): Read this article in Japanese at Qiita or at Emacs-JP.
更新（2024-09-08）：在 Qiita 或 Emacs-JP 上阅读这篇文章

You’re using Avy wrong.  你用 Avy 的方式不对。

Too harsh? Let me rephrase: you’re barely using Avy. Still too broad? Okay, the noninflammatory version: Avy, the Emacs package to jump around the screen, lends itself to efficient composable usage that’s obscured by default.
太严厉了？让我换个说法：你几乎没用 Avy。还是太宽泛了？好吧，非炎症版本：Avy，Emacs 的屏幕跳跃包，适合高效的组合使用，但默认情况下被隐藏了。

Without burying the lede any further, here’s a demo that uses a single Avy command (avy-goto-char-timer) to do various things in multiple buffers and windows, all without manually moving the cursor:
不再埋没主要线索，这里有一个演示，使用单个 Avy 命令（ avy-goto-char-timer ）在多个缓冲区和窗口中做各种事情，而无需手动移动光标：
\section{复制文本}
\label{sec:org6510ecc}
复制文本，删除行或区域，移动文本，标记文本，调出帮助缓冲区，查找定义，搜索谷歌，检查我的拼写，等等。我再次强调：Avy 定义了数十个跳跃命令，但我只用了其中一个。这篇文章详细解释了如何创建你自己的版本，但更重要的是试图解释为什么这是一个好主意。

This is the first of two parts in a series on Avy, an Emacs package for jumping around efficiently with the keyboard. Part 1 is about about supercharging built-in customization to do anything with Avy, or some approximation thereof. Part 2 will be a more technical (elisp-y) dive into writing more complex features for your individual needs. If you are interested in the short elisp snippets in this document, they are collated into a single file here.
这是关于 Avy 这个 Emacs 插件的两部分系列文章中的第一部分，Avy 是一个用于通过键盘高效跳转的 Emacs 插件。第一部分是关于超级增强内置自定义功能，用 Avy（或者其某种近似）来做任何事情。第二部分将更深入地探讨为你的个人需求编写更复杂功能的（elisp）技术细节。如果你对这个文档中的简短 elisp 代码片段感兴趣，它们已经被整理到一个单独的文件中。
\chapter{选择}
\label{sec:orgf4a5876}
\section{f1}
\label{sec:org7e88c21}
We see the same pattern repeated in most interactions with Emacs whose primary purpose isn’t typing text. To perform a task, we Filter, Select and Act in sequence:
我们在大多数不是以文本输入为主要目的的 Emacs 交互中看到同样的模式重复出现。为了执行一个任务，我们按顺序进行过滤、选择和执行：

Filter: Winnow a large pile of candidates to a smaller number, usually by typing in some text. These candidates can be anything, see below for examples.
过滤：将大量候选者筛选成较小的数量，通常通过输入一些文本来实现。这些候选者可以是任何东西，下面是一些例子。

Select: Specify a candidate as the one you need, usually with visual confirmation. If you filter a list down to one candidate, it’s automatically selected.
选择：指定您需要的候选者，通常需要视觉确认。如果您将列表筛选至一个候选者，它将自动被选中。

Act: Run the task with this candidate as an argument.
执行：使用此候选者作为参数运行任务。

Want to open a file? Invoke a command, then type in text to filter a list of completions, select a completion, find-file.
想要打开文件？调用命令，然后输入文本以筛选补全列表，选择一个补全项，找到文件。
Switch buffers? Type to filter, select a buffer, switch.
切换缓冲区？输入文本以筛选，选择一个缓冲区，切换。
Autocomplete a symbol in code? Type a few characters to narrow a pop-up list, choose a candidate, confirm.
代码中自动补全符号？输入几个字符来缩小弹出列表，选择一个候选项，确认。

As ever, this model is a simplification. Helm, Ivy, Dired \& co let you select multiple candidates to act on, for instance. We will put this qualification aside while we explore this idea.
如同以往，这个模型是一种简化。Helm、Ivy、Dired 等允许你选择多个候选项来执行操作，例如。我们将暂时放下这个限定，以便我们探索这个想法。

This observation leads to several interesting ideas. For one, the Filter → Select → Act process is often thought of as a single operation. Decoupling the filtering, selection and action phases (in code and in our heads) frees us to consider a flock of possibilities. Here’s minibuffer interaction:
这一观察引出了一些有趣的想法。首先，过滤→选择→执行的过程通常被认为是一个单一操作。将过滤、选择和执行阶段（在代码和在我们的头脑中）解耦，使我们能够考虑一大堆可能性。这是 minibuffer 交互：

When you type (after C-s), you automatically filter buffer text and select the nearest match. You can select each subsequent match in turn, or jump to the first or last match. The Act here is the process of moving the cursor to the match location, but it can be one of a few things, like running occur or query-replace on the search string. Many Isearch commands simultaneously filter, select and act, so we’re fitting a square peg in a round hole here2.
当你输入（在 C-s 之后），你会自动过滤缓冲区文本并选择最近的匹配项。你可以依次选择每个后续匹配项，或跳转到第一个或最后一个匹配项。这里的 Act 是将光标移动到匹配位置的过程，但它可以是几件事情中的一个，比如在搜索字符串上运行 occur 或 query-replace 。许多 Isearch 命令同时过滤、选择和执行操作，所以我们在这里是削足适履 2 。

If you’ve spent any time using Isearch, you can appreciate the tradeoff involved in dividing a task into these three independently configurable phases. Lumping two or all three into a single operation makes Isearch a wicked fast keyboard interaction. When I use Isearch my brain is usually trying to catch up to my fingers. On the other hand, the advantage of modularity is expressive power. The three phase process is slower on the whole, but we can do a whole lot more by plugging in different pieces into each of the Filter , Select and Act slots. To see this, you have only to consider how many disparate tasks the minibuffer handles, and in how many different ways!
如果你使用过 Isearch，就能体会到将任务分为这三个独立配置阶段所涉及的权衡。将两阶段或全部三个阶段合并为一个操作，可以让 Isearch 成为一项非常快速的键盘交互。当我使用 Isearch 时，我的大脑通常都在努力跟上我的手指。另一方面，模块化的优势在于表达能力。虽然三个阶段整个过程较慢，但我们可以通过将不同的部件插入到过滤、选择和执行槽中来完成更多的事情。要看到这一点，你只需要考虑小缓冲区处理了多少不同的任务，以及有多少不同的方式！

But back to Isearch: what can we do to decouple the three stages here? Not much without modifying its guts. It’s all elisp, so that’s not a tall order. For example, Protesilaos Stavrou adds many intuitive actions (such as marking candidates) to Isearch in this video. But it turns out we don’t need to modify Isearch, because Avy exists, has a killer Filter feature, and it separates the three stages like a champ. This makes for some very intriguing possibilities.
但回到 Isearch：我们能做些什么来解耦这三个阶段呢？如果不修改其内部结构，那就做不了太多。它全部是用 elisp 编写的，所以这并不是什么艰巨的任务。例如，Protesilaos Stavrou 在这个视频中为 Isearch 添加了许多直观的操作（例如标记候选）。但事实证明，我们不需要修改 Isearch，因为 Avy 存在，具有杀手级的过滤功能，并且像冠军一样分离了这三个阶段。这使得出现了一些非常有趣的可能性。
Wait, what’s Avy?  等等，什么是 Avy？

Avy is authored by the prolific abo-abo (Oleh Krehel), who also wrote Ivy, Counsel, Ace-Window, Hydra, Swiper and many other mainstays of the Emacs package ecosystem that you’ve probably used. If you’re reading this, chances are you already know (and probably use) Avy. So here’s a very short version from the documentation:
Avy 由多产的 abo-abo（Oleh Krehel）编写，他还编写了 Ivy、Counsel、Ace-Window、Hydra、Swiper 和许多其他您可能已经使用过的 Emacs 软件包生态系统中的主要软件。如果您正在阅读此内容，那么您很可能已经知道（并且可能正在使用）Avy。所以这里是从文档中的一个非常简短的版本：

avy is a GNU Emacs package for jumping to visible text using a char-based decision tree.
avy 是一个 GNU Emacs 软件包，用于使用基于字符的决策树跳转到可见文本。

You can call an Avy command and type in some text. Any match for this text on the frame (or all Emacs frames if desired) becomes a selection candidate, with some hint characters overlaid on top. Here I type in “an” and all strings in the frame that match it are highlighted:
您可以调用一个 Avy 命令并输入一些文本。在框架（或如果需要，在所有 Emacs 框架）上与此文本匹配的任何字符串都成为选择候选，并在上面覆盖一些提示字符。我在这里输入“an”，框架中所有匹配该字符串的内容都被突出显示：

Typing in one of the hints then jumps the cursor to that location. Here I jump to this sentence from another window:
输入一个提示后，光标会跳转到该位置。这里我从另一个窗口跳到这个句子：
Play by play  比赛解说

Typical Avy usage looks something like this: Jump to a location that matches your text (across all windows), then jump back with pop-global-mark (C-x C-SPC). In a later section I go into more detail on jumping back and forth with Avy. Here is a demo of this process where I jump twice with Avy and then jump back in sequence:
典型的 Avy 使用方式看起来是这样的：跳转到与你的文本匹配的位置（跨所有窗口），然后使用 pop-global-mark （ C-x C-SPC ）跳回。在后面的部分我将更详细地介绍如何使用 Avy 来回跳转。这里有一个演示这个过程，我用 Avy 跳转了两次，然后按顺序跳回：
Play by play  逐步说明

At least that’s the official description. You can peruse the README for more information, but what I find mystifying is that…
至少这是官方描述。你可以查阅 README 以获取更多信息，但我发现令人费解的是……
…Avy’s documentation leaves out the best part
…Avy 的文档遗漏了最好的部分

Avy handles filtering automatically and the selection is made through a char-based decision tree. Here’s how it fits into our three part interaction model.
Avy 自动处理过滤，选择是通过基于字符的决策树进行的。这是它如何融入我们三部分交互模型中的。
Filter,  过滤，

Before you call Avy every text character on your screen is a potential candidate for selection. The possibilites are all laid out for you, and there are too many of them!
在你调用 Avy 之前，屏幕上的每个文本字符都是选择的一个潜在候选。所有可能性都为你展开，而且太多了！

You filter the candidate pool with Avy similar to how you would in the minibuffer, by typing text. This reduces the size of the pool to those that match your input. Avy provides dozens of filtering styles. It can: only consider candidates above/below point, only beginnings of words, only the current window (or frame), only whitespace, only beginnings of lines, only headings in Org files, the list goes on.
你可以通过在最小化缓冲区中输入文本来使用 Avy 过滤候选池，就像在 minibuffer 中一样。这会将池的大小减少到与你的输入匹配的那些。Avy 提供了数十种过滤样式。它可以：仅考虑点以上的候选/点以下的候选，仅考虑单词的开头，仅考虑当前窗口（或框架），仅考虑空白，仅考虑行的开头，仅考虑 Org 文件中的标题，等等。
Filtering commands in Avy
Avy 中的过滤命令















Filtering in Avy is independent of the selection method (as it should be), but there is a dizzying collection of filtering methods. I assume the idea is that the user will pick a couple of commands that they need most often and commit only those to memory.
Avy 中的过滤与选择方法独立（这应该是这样），但过滤方法种类繁多，令人眼花缭乱。我猜测的思路是用户将选择他们最常用的几条命令，并只将这些命令牢记在心。

Here’s the problem: We want to use our mental bandwidth for the problem we’re trying to solve with the text editor, not the editor itself. Conscious decision-making is expensive and distracting. As of now we need to decide on the fly between Isearch and Avy to find and act on things. If you use a fancy search tool like Swiper, Helm-swoop or Consult-line, you now have three options. Having a bunch of Avy commands on top is a recipe for mental gridlock. To that end, we just pick the most adaptable, flexible and general-purpose Avy command (avy-goto-char-timer) for everything.
这里的问题是：我们希望将我们的心理带宽用于我们试图用文本编辑器解决的问题，而不是编辑器本身。有意识的决策是昂贵且分散注意力的。目前，我们需要在飞行中决定在 Isearch 和 Avy 之间选择以查找和操作项目。如果你使用像 Swiper、Helm-swoop 或 Consult-line 这样的高级搜索工具，现在有三个选项。在顶部添加一堆 Avy 命令是导致心理混乱的公式。为此，我们只为所有事情选择最适应、灵活和通用的 Avy 命令（ avy-goto-char-timer ）。

(global-set-key (kbd "M-j") 'avy-goto-char-timer)

Further below I make the case that you don’t need to make even this decision, you can always use Isearch and switch to Avy as needed.
在下面我会论证你甚至不需要做这个决定，你可以随时使用 Isearch 并根据需要切换到 Avy。

To be clear, this decision cost has to be balanced against the cost of frequent busywork and chronic context switching that Avy helps avoid. There is a case to be made for adapting Avy’s flexible filtering options to our needs, and the number of packages that offer Avy-based candidate filtering (for everything from linting errors to buffer selection) attests to this. We will examine this in depth in Part II.
换句话说，这个决定成本需要与 Avy 帮助避免的频繁琐事和慢性上下文切换成本相平衡。有理由认为需要根据我们的需求调整 Avy 的灵活过滤选项，而提供基于 Avy 的候选过滤的软件包数量（从语法检查错误到缓冲区选择）证明了这一点。我们将在第二部分深入探讨这一点。

But in this piece we are interested in a different, much less explored aspect of Avy.
但在这篇文章中，我们感兴趣的是 Avy 的一个不同、且很少被探索的方面。
Select,  选择，

Every selection method that Avy offers involves typing characters that map to screen locations. This is quite different from Isearch, where you call isearch-repeat-forward (C-s, possibly with a numerical prefix argument) or the minibuffer, where you navigate a completions buffer or list with C-n and C-p. Avy’s selection method is generally faster because it minimizes, by design, the length of the character sequences it uses, and we have ten fingers that can access ∼40 keys in O(1) time. The fact that we’re often looking directly where we mean to jump means we don’t need to parse an entire screen of gibberish. Unfortunately for this article, this means using Avy is much more intuitive than looking at screenshots or watching demos.
Avy 提供的每一种选择方法都涉及输入映射到屏幕位置的字符。这与 Isearch 不同，Isearch 中你调用 isearch-repeat-forward （ C-s ，可能带有数字前缀参数）或使用 minibuffer，在 completions 缓冲区或列表中用 C-n 和 C-p 进行导航。Avy 的选择方法通常更快，因为其设计上最小化了使用的字符序列的长度，而且我们有十个手指可以在 O(1)时间内访问约 40 个键。我们通常直接跳转到我们想要的位置，这意味着我们不需要解析整个屏幕的乱码。不幸的是，对于这篇文章来说，使用 Avy 比看截图或观看演示更直观。

This excellent design leaves us with little reason to tinker with the selection phase: it’s sufficiently modular and accommodating of different filter and act stages. You can customize avy-style if you want to change the set or positions of characters used for selection. Here is an example of using simple words to select candidates:
这个出色设计让我们几乎没有理由去调整选择阶段：它足够模块化，能够适应不同的过滤和执行阶段。如果你想改变用于选择的角色集或位置，可以自定义 avy-style 。这里是一个使用简单词汇选择候选人的例子：

We will pay more attention to the selection operation in part II as well.
我们在第二部分也会更多地关注选择操作。
Act!  行动！

This brings us to the focus of this article. The stated purpose of Avy, jumping to things, makes it sound like a (contextually) faster Isearch. But jumping is only one of many possibilities. Avy provides a “dispatch list”, a collection of actions you can perform on a candidate, and they are all treated on equal footing with the jump action. You can show these commands any time you use Avy with ?:
这就引出了本文的重点。Avy 的声明目的是跳转到项目，听起来像是一个（上下文中）更快的 Isearch。但跳转只是许多可能性中的一种。Avy 提供了一个“分发列表”，一组可以对候选项目执行的操作，它们都与跳转操作处于平等的地位。你可以在使用 Avy 时随时通过 ? 显示这些命令：

This means we are free to leverage Avy’s unique filtering and selection method to whatever action we want to carry out at any location on the screen. Our interaction model now ends in a block that looks something like this:
这意味着我们可以利用 Avy 独特的过滤和选择方法来执行屏幕上任何位置的任何操作。我们的交互模型现在以一个看起来像这样的代码块结束：

Additionally, Avy also defines a few commands that run different actions, like copying text from anywhere on screen:
此外，Avy 还定义了一些执行不同操作的命令，例如从屏幕上的任何位置复制文本：

Kill  删除 	Copy  复制 	Move  移动
avy-kill-ring-save-whole-line
复制整行 	avy-copy-line  复制当前行 	avy-move-line  移动当前行
avy-kill-ring-save-region
avy 剪切区域保存 	avy-copy-region  avy 复制区域 	avy-move-region  avy 移动区域
avy-kill-region  avy 剪切区域 		avy-transpose-lines-in-region
交换区域内的行
avy-kill-whole-line  删除整行 		avy-org-refile-as-child  将 org 模块作为子模块重新组织

The problem with this approach is that it doesn’t scale. Each of these commands defines a full Filter → Select → Act process, and we quickly run out of headspace and keyboard room if we want any kind of versatility or coverage. They’re also not dynamic enough: you’re locked into the pipeline and cannot change your mind once you start the command.
这种方法的问题是它无法扩展。每个命令都定义了一个完整的 Filter → Select → Act 过程，如果我们想要任何种类的多功能性或覆盖范围，我们会很快用完空间和键盘空间。它们也不够动态：一旦开始命令，你就被锁定在管道中，无法改变主意。

Folks love Vim’s editing model for a reason: it’s a mini-language where knowing M actions (verbs) and N cursor motions gives you M × N composite operations. This (M + N) → (M × N) ratio pays off quadratically with the effort you put into learning verbs and motions in Vim. Easymotion, which is Vim’s version of Avy3, has part of this composability built-in as a result. We seek to bring some of this to Avy, and (because this is Emacs) do a lot more than combining motions with verbs. We won’t need to step into Avy’s source code for this, it has all the hooks we need already.
大家喜欢 Vim 的编辑模式是有原因的：它是一个微型语言，知道 M 个动作（动词）和 N 个光标移动就能让你得到 M × N 个复合操作。这种（M + N）→（M × N）的比例随着你对 Vim 中动词和移动的学习投入呈平方级增长。Easymotion 是 Vim 版本的 Avy 3 ，因此它内置了部分这种可组合性。我们希望将其中一些特性带到 Avy 中，并且（因为这是 Emacs）做比将移动与动词组合更多的事情。我们不需要进入 Avy 的源代码来实现这一点，它已经提供了我们需要的所有钩子。
Avy actions  Avy 操作

The basic usage for running an arbitrary action with Avy is as follows:
使用 Avy 运行任意操作的基本用法如下：

Call an Avy command. Any command will do, I stick to avy-goto-char-timer.
调用 Avy 命令。任何命令都可以，我坚持使用 avy-goto-char-timer 。
Filter: Type in some text to shrink the candidate pool from the entire screen to a few locations.
过滤：输入一些文本，将整个屏幕的候选池缩小到几个位置。
Act: Specify the action you want to run. You can pull up the dispatch help with ?, although you won’t have to if you set it up right, see Remembering to Avy.
执行：指定你想要执行的操作。你可以使用 ? 调出分发帮助，虽然如果你设置得当，就不需要，参见记住使用 Avy。
Select: Pick one of the candidates to run the action on.
选择：从候选池中选择一个要执行操作的对象。

Here are some things I frequently do with Avy. Note that you can do this on any text in your frame, not just the active window!
这里是我经常用 Avy 做的一些事情。请注意，你可以在任何文本中进行这些操作，而不仅仅是活动窗口！

First, taking the annoyance out of some common editing actions with Avy. If you use Vim and Easymotion, you get the first few actions below for free:
首先，用 Avy 消除一些常见编辑操作的不便。如果你使用 Vim 和 Easymotion，你将免费获得以下几个操作：
A note about these demos
关于这些演示的说明

For clarity, I set Avy to desaturate the screen and to “pulse” the line during a few of these actions. These are not enabled by default. I also slowed down the operations by adding a delay to make them easier to follow. In actual usage these are instantaneous.
为了清晰，我将 Avy 设置为降低屏幕饱和度并在执行其中一些操作时“脉冲”该行。这些默认情况下是禁用的。我还通过添加延迟来减慢了操作速度，以便更容易跟随。在实际使用中，这些操作是即时完成的。

The keys Avy uses to dispatch actions on candidates are specified in avy-dispatch-alist.
Avy 用于在候选对象上分发操作的键指定在 avy-dispatch-alist 中。

We will also need to ensure that these keys don’t coincide with the ones Avy uses as selection hints on screen. Consider customizing avy-keys for this.
我们还需要确保这些键不与 Avy 在屏幕上用作选择提示的键相冲突。考虑自定义 avy-keys 。

Kill a candidate word, sexp or line
删除一个候选词、sexp 或行

Killing words or s-expressions is built-in. I added an action to kill a line. In this demo I quickly squash some typos and delete a comment, then remove some code in a different window:
删除单词或 s-expressions 是内置的。我添加了一个操作来删除一行。在这个演示中，我快速修正了一些拼写错误并删除了一条注释，然后在不同的窗口中删除了一些代码：
Play by play  逐步说明

(defun avy-action-kill-whole-line (pt)
  (save-excursion
    (goto-char pt)
    (kill-whole-line))
  (select-window
   (cdr
    (ring-ref avy-ring 0)))
\begin{enumerate}
\item
\end{enumerate}

(setf (alist-get ?k avy-dispatch-alist) 'avy-action-kill-stay
      (alist-get ?K avy-dispatch-alist) 'avy-action-kill-whole-line)

Yank a candidate word, sexp or line
拉取候选词、sexp 或行
\section{f2}
\label{sec:orgd090bc4}
Copy to the kill-ring or copy to point in your buffer. In this demo I copy some text from a man page into my file:
复制到剪贴板或复制到缓冲区的点。在这个演示中，我从手册中复制了一些文本到我的文件：
Play by play  逐步说明
\begin{lstlisting}[language=Lisp,numbers=none]
  (defun avy-action-copy-whole-line (pt)
    (save-excursion
      (goto-char pt)
      (cl-destructuring-bind (start . end)
          (bounds-of-thing-at-point 'line)
        (copy-region-as-kill start end)))
    (select-window
     (cdr
      (ring-ref avy-ring 0)))
    t)

  (defun avy-action-yank-whole-line (pt)
    (avy-action-copy-whole-line pt)
    (save-excursion (yank))
    t)

  (setf (alist-get ?y avy-dispatch-alist) 'avy-action-yank
        (alist-get ?w avy-dispatch-alist) 'avy-action-copy
        (alist-get ?W avy-dispatch-alist) 'avy-action-copy-whole-line
        (alist-get ?Y avy-dispatch-alist) 'avy-action-yank-whole-line)
\end{lstlisting}

Note that Avy actually defines separate commands for this: avy-copy-line and avy-copy-region to copy lines and regions from anywhere in the frame. These are a little faster since they have the action stage baked into the function call. You might be better served by these. But we want to avoid the mental burden of remembering too many top level commands, so we work in two simpler stages: call avy-goto-char-timer (to filter and select) and then dispatch on our selected candidate as we see fit.
注意 Avy 实际上为这个定义了不同的命令： avy-copy-line 和 avy-copy-region 来从缓冲区的任何地方复制行和区域。这些稍微快一点，因为它们将操作阶段嵌入到函数调用中。你可能更适合使用这些。但我们想避免记住太多顶级命令的精神负担，所以我们分为两个更简单的阶段：调用 avy-goto-char-timer （过滤和选择），然后根据我们选择的内容适当地分发。
Move a candidate word, sexp or line
移动候选词、sexp 或行

Avy calls this “teleport”, I call it “transpose”, either way it’s bound to t. In this demo I move text around the buffer… without moving (much) around the buffer:
Avy 称之为“传送”，我称之为“转置”，无论如何它都绑定到 t 。在这个演示中我移动缓冲区中的文本……而几乎没有在缓冲区中移动：
Play by play  逐步说明

(defun avy-action-teleport-whole-line (pt)
    (avy-action-kill-whole-line pt)
    (save-excursion (yank)) t)

(setf (alist-get ?t avy-dispatch-alist) 'avy-action-teleport
      (alist-get ?T avy-dispatch-alist) 'avy-action-teleport-whole-line)

Zap to a candidate position
快速定位到候选位置

This is built-in and bound to z by default:
这是默认绑定到 z 的内置功能：
Play by play  逐步说明

Mark a candidate word or sexp
标记候选单词或 sexp

Also built in, m by default. This isn’t different from jumping to the candidate using Avy and calling mark-sexp, but it is more convenient:
默认情况下内置了 m 。这与使用 Avy 跳转到候选并调用 mark-sexp 没有区别，但更方便：
Your browser does not support the video tag.
Play by play  逐步说明

Mark the region from point to a candidate
从一点到候选点标记区域

Avy sets the mark before it jumps, so you could use C-x C-x to activate the region, but this saves you the trouble.
Avy 在跳跃前设置标记，所以你可以使用 C-x C-x 来激活区域，但这会为你节省麻烦。
Your browser does not support the video tag.
Play by play  逐步说明

(defun avy-action-mark-to-char (pt)
  (activate-mark)
  (goto-char pt))

(setf (alist-get ?  avy-dispatch-alist) 'avy-action-mark-to-char)

Next, some contextual actions automagicked by Avy:
接下来，一些由 Avy 自动完成的上下文操作：
ispell a candidate word
检查候选词

This is built-in, bound to i by default.
这是内置的，默认绑定到 i 。
\section{python code}
\label{sec:org4d6fc96}

\begin{lstlisting}[language=Python,numbers=none]
#
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.


def find():
    j = 10
    for i in range(0, 10):
        print(j + i)


def methodname(self, arg):
    pass


if __name__ == "__main__":
    f = 100
    print("free start")
    find()
    print(f)

\end{lstlisting}
\chapter{chatu}
\label{sec:orgfb1913a}

sdjfksajf

\begin{center}
\includesvg[width=0.5\textwidth]{../attached/draws_out/f1-1}
\label{org101aff6}
\end{center}

sjdfkasjf
\begin{center}
\includesvg[width=0.4\textwidth]{e:/booktest/attached/draws_out/elegantbook.org/f2-2}
\label{orgb199073}
\end{center}
\chapter{表格}
\label{sec:org70adb03}

\begin{table}[htbp]
\caption{表 1}
\centering
\begin{tabular}{lr}
name & score\\
\hline
donald & 100\\
iris & 99\\
\end{tabular}
\end{table}
\chapter{数学公式}
\label{sec:org0295ec1}

$$f(x)=10x$$

我来看看 \emph{斜体字} \textbf{粗体字} 。
\end{document}
```

你可以查看 <https://github.com/donaldsdlo/book_template> 中 build/test.tex 以及 test.pdf 来查看对应的文件。

编译的命令如下：

```shell
xelatex   -shell-escape  -8bit -interaction=nonstopmode -synctex=1 -output-directorr test.tex
```

其中主要跟关注的内容为，指定文档的 class：

```tex
\documentclass[lang=cn,color=blue]{elegantbook}
```

指定引用的图片的目录：

```tex
\graphicspath{{D:/texlive/texmf-local/tex/latex/local/ElegantBook/figure/}}
\graphicspath{{D:/texlive/texmf-local/tex/latex/local/ElegantBook/image/}}
```


## WSL2 {#wsl2}


### 先决条件 {#先决条件}

必须运行 Windows 10 版本 2004 及更高版本（内部版本 19041 及更高版本）或 Windows 11 才能使用以下命令。 如果使用的是早期版本，请参阅 [手动安装页](https://learn.microsoft.com/zh-cn/windows/wsl/install-manual)。


### 安装 WSL 命令 {#安装-wsl-命令}

现在，可以使用单个命令安装运行 WSL 所需的所有内容。 右键单击并选择“以 **管理员**  身份运行”，在管理员模式下打开 PowerShell，输入 wsl --install 命令，然后重新启动计算机。

```bash
wsl --install
```

此命令将启用运行 WSL 并安装 Linux 的 Ubuntu 分发所需的功能。


### 如果不能按上面的方式安装，则使用如下方式安装 {#如果不能按上面的方式安装-则使用如下方式安装}

```bash
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```


### 安装新的 Linux 分发版时将默认版本设置为 WSL 2 {#安装新的-linux-分发版时将默认版本设置为-wsl-2}

```bash
wsl.exe --set-default-version 2
```


### 列出可用的 Linux 分发版 {#列出可用的-linux-分发版}

```bash
wsl -l -o
```


### Update WSL {#update-wsl}

```bash
wsl --update
```

要更新到最新的预发行版本，请换用以下命令：

```bash
wsl --update --pre-release
```


### 在 WSL 上安装 Arch Linux {#在-wsl-上安装-arch-linux}

```bash
wsl --install -d archlinux --name Arch --location E:\WSLOS\Arch
```

下载安装程序:

```bash
PS C:\Users\donal> wsl --install -d archlinux --name Arch --location E:\WSLOS\Arch
正在下载: Arch Linux
[=====                      9.8%                           ]

```

安装完成后终端显示：

```bash
PS C:\Users\donal> wsl --install -d archlinux --name Arch --location E:\WSLOS\Arch
正在下载: Arch Linux
正在安装: Arch Linux
已成功安装分发。可以通过 “wsl.exe -d Arch” 启动它
正在启动 Arch...
Welcome to the Arch Linux WSL image!

This image is maintained at <https://gitlab.archlinux.org/archlinux/archlinux-wsl>.

Please, report bugs at <https://gitlab.archlinux.org/archlinux/archlinux-wsl/-/issues>.
Note that WSL 1 is not supported.

For more information about this WSL image and its usage (including "tips and tricks" and troubleshooting steps), see the related Arch Wiki page at <https://wiki.archlinux.org/title/Install_Arch_Linux_on_WSL>.

While images are built regularly, it is strongly recommended running "pacman -Syu" right after the first launch due to the rolling release nature of Arch Linux.

Generating pacman keys...
==> Generating pacman master key. This may take some time.
==> Updating trust database...
Done
[root@DESKTOP-92CHCK7 donal]#
```

同时会显示图形界面：

{{< figure src="/images/dev-envs.org/_20251106_105407_oK5vp2.png" width="90%" >}}


### 如果上面的方式安装缓慢，可以从镜像站下载文件后从文件安装 {#如果上面的方式安装缓慢-可以从镜像站下载文件后从文件安装}


#### 查找镜像下载 URL {#查找镜像下载-url}

可以在如下的网站上查看具体的版本：

<https://mirrors.tuna.tsinghua.edu.cn/archlinux/wsl/>

{{< figure src="/images/dev-envs.org/2025-11-27_14-19-43_screenshot.png" width="90%" >}}

{{< figure src="/images/dev-envs.org/2025-11-27_14-20-36_screenshot.png" width="90%" >}}

得到 URL：<https://mirrors.tuna.tsinghua.edu.cn/archlinux/wsl/latest/archlinux.wsl> 然后你就可以通过任意的下载工具下载此文件了。

如果你是一个 ubuntu 发行版的使用者，你也可以从 <https://mirrors.tuna.tsinghua.edu.cn/ubuntu-releases/25.10/> 中找到对应的版本进行下载。


#### 从文件安装 Arch Linux WSL {#从文件安装-arch-linux-wsl}

```bash
wsl --install --from-file archlinux.wsl --location D:\WSL\archlinux\ --name archlinux
```

其中的 --from-file 和 --location 的参数需要根据实际情况调整。


### 添加国内镜像 {#添加国内镜像}

编辑 `/etc/pacman.d/mirrorlist` ，在文件的最顶端添加：

```bash
Server = https://mirrors.xjtu.edu.cn/archlinux/$repo/os/$arch
```

更新软件包缓存：

```bash
pacman -Syyu
```


### 确认是否已经启用了 `systemd` 服务 {#确认是否已经启用了-systemd-服务}

```bash
[root@DESKTOP-92CHCK7 donal]# systemctl status
```

```bash
● DESKTOP-92CHCK7
    State: running
    Units: 339 loaded (incl. loaded aliases)
     Jobs: 0 queued
   Failed: 0 units
    Since: Thu 2025-11-06 10:52:03 CST; 4min 58s ago
  systemd: 258.1-1-arch
   CGroup: /
           ├─init.scope
           │ ├─  1 /sbin/init
           │ ├─  2 /init
           │ ├─  8 plan9 --control-socket 7 --log-level 4 --server-fd 8 --pipe-fd 10 --log-truncate
           │ ├─231 /init
           │ ├─232 /init
           │ ├─233 /usr/bin/bash
           │ ├─320 systemctl status
           │ └─321 "(pager)"
           ├─system.slice
           │ ├─dbus-broker.service
           │ │ ├─214 /usr/bin/dbus-broker-launch --scope system --audit
           │ │ └─215 dbus-broker --log 10 --controller 9 --machine-id e055bdab25604b729b245f253abd5e5f --max-bytes 536870912 --max-fds 4096 --max-matches 16384 --audit
           │ ├─systemd-homed.service
           │ │ └─216 /usr/lib/systemd/systemd-homed
           │ ├─systemd-journald.service
           │ │ └─45 /usr/lib/systemd/systemd-journald
           │ ├─systemd-logind.service
           │ │ └─217 /usr/lib/systemd/systemd-logind
           │ ├─systemd-networkd.service
           │ │ └─107 /usr/lib/systemd/systemd-networkd
           │ ├─systemd-nsresourced.service
           │ │ ├─76 /usr/lib/systemd/systemd-nsresourced
           │ │ ├─80 "systemd-nsresourcework: waiting..."
           │ │ ├─81 "systemd-nsresourcework: waiting..."
           │ │ ├─82 "systemd-nsresourcework: waiting..."
           │ │ ├─83 "systemd-nsresourcework: waiting..."
           │ │ └─84 "systemd-nsresourcework: waiting..."
           │ ├─systemd-resolved.service
           │ │ └─96 /usr/lib/systemd/systemd-resolved
           │ ├─systemd-udevd.service
           │ │ └─udev
           │ │   └─106 /usr/lib/systemd/systemd-udevd
           │ └─systemd-userdbd.service
           │   ├─ 77 /usr/lib/systemd/systemd-userdbd
           │   ├─197 "systemd-userwork: waiting..."
           │   ├─198 "systemd-userwork: waiting..."
           │   └─199 "systemd-userwork: waiting..."
           └─user.slice
             └─user-0.slice
               ├─session-c1.scope
               │ ├─262 "login -- root"
               │ └─280 -bash
               └─user@0.service
                 └─init.scope
                   ├─267 /usr/lib/systemd/systemd --user
                   └─269 "(sd-pam)"
```


### 更新系统 {#更新系统}

```bash
pacman -Syyuu
```

```bash
:: Synchronizing package databases...
 core downloading...
 extra downloading...
:: Starting full system upgrade...
resolving dependencies...
looking for conflicting packages...

Package (2)         Old Version  New Version  Net Change  Download Size

core/device-mapper  2.03.36-1    2.03.36-2      0.00 MiB       0.28 MiB
core/iana-etc       20250612-1   20251030-1     0.01 MiB       0.39 MiB

Total Download Size:   0.67 MiB
Total Installed Size:  4.76 MiB
Net Upgrade Size:      0.01 MiB

:: Proceed with installation? [Y/n] y
:: Retrieving packages...
 iana-etc-20251030-1-any downloading...
 device-mapper-2.03.36-2-x86_64 downloading...
checking keyring...
checking package integrity...
loading package files...
checking for file conflicts...
:: Processing package changes...
upgrading iana-etc...
upgrading device-mapper...
:: Running post-transaction hooks...
(1/4) Reloading system manager configuration...
(2/4) Restarting marked services...
(3/4) Reloading device manager configuration...
(4/4) Arming ConditionNeedsUpdate...
[root@DESKTOP-92CHCK7 donal]#
```


### 安装熟悉的 NeoVIM {#安装熟悉的-neovim}

```bash
[root@DESKTOP-92CHCK7 donal]# pacman -S neovim
```


### 修改镜像源 {#修改镜像源}

<https://mirrors.xjtu.edu.cn/docs/archlinux>

文件 /etc/pacman.d/mirrorlist 原内容：

```bash
Server = https://fastly.mirror.pkgbuild.com/$repo/os/$arch
Server = https://geo.mirror.pkgbuild.com/$repo/os/$arch
```

编辑 /etc/pacman.d/mirrorlist，在文件的最顶端添加：

```bash
Server = https://mirrors.xjtu.edu.cn/archlinux/$repo/os/$arch
```

使用如下命令修改文件：

```bash
[root@DESKTOP-92CHCK7 donal]# nvim /etc/pacman.d/mirrorlist
```

修改完成后的内容：

```bash
Server = https://mirrors.xjtu.edu.cn/archlinux/$repo/os/$arch
Server = https://fastly.mirror.pkgbuild.com/$repo/os/$arch
Server = https://geo.mirror.pkgbuild.com/$repo/os/$arch
```

更新软件包缓存：

```bash
pacman -Syyu
```

两次 `y`  能避免从 **损坏的** 镜像切换到 **正常的** 镜像时出现的问题。

如果您从一个较新的镜像切换到较旧的镜像，以下命令可以降级部分包，以避免系统的部分更新。

```bash
pacman -Syyuu
```


### 安装一些常用软件 {#安装一些常用软件}

```bash
pacman -Sy --needed base-devel git fastfetch bash-completion tree ripgrep ripgrep-all fd
```


### 安装和配置 Docker {#安装和配置-docker}


#### 安装 Docker {#安装-docker}

```bash
pacman -S docker docker-compose
```


#### 启动 Docker 守护进程 {#启动-docker-守护进程}

```bash
systemctl start docker.service
```

建议启用 Docker 服务，以便 Docker 守护进程在系统启动时自动启动。

```bash
systemctl enable docker.service
```


#### 查看 Docker 服务状态 {#查看-docker-服务状态}

```bash
systemctl status docker.service
```

```bash
[root@DESKTOP-92CHCK7 donal]# systemctl status docker.service
● docker.service - Docker Application Container Engine
     Loaded: loaded (/usr/lib/systemd/system/docker.service; disabled; preset: disabled)
     Active: active (running) since Thu 2025-11-06 15:25:23 CST; 25s ago
 Invocation: 31c258ff57734662a7bef3815d63f71e
TriggeredBy: ● docker.socket
       Docs: https://docs.docker.com
   Main PID: 1692 (dockerd)
      Tasks: 12
     Memory: 23.8M (peak: 25.6M)
        CPU: 277ms
     CGroup: /system.slice/docker.service
             └─1692 /usr/bin/dockerd -H fd:// --containerd=/run/containerd/containerd.sock

Nov 06 15:25:23 DESKTOP-92CHCK7 dockerd[1692]: time="2025-11-06T15:25:23.040538308+08:00" level=info msg="CDI directory does not exist, skipping: failed to monitor for changes: no such file or directory" dir=/var/run/cdi
Nov 06 15:25:23 DESKTOP-92CHCK7 dockerd[1692]: time="2025-11-06T15:25:23.051611156+08:00" level=info msg="Creating a containerd client" address=/run/containerd/containerd.sock timeout=1m0s
Nov 06 15:25:23 DESKTOP-92CHCK7 dockerd[1692]: time="2025-11-06T15:25:23.158342485+08:00" level=info msg="Loading containers: start."
Nov 06 15:25:23 DESKTOP-92CHCK7 dockerd[1692]: time="2025-11-06T15:25:23.445920972+08:00" level=info msg="Loading containers: done."
Nov 06 15:25:23 DESKTOP-92CHCK7 dockerd[1692]: time="2025-11-06T15:25:23.476819753+08:00" level=info msg="Docker daemon" commit=89c5e8fd66 containerd-snapshotter=false storage-driver=overlay2 version=28.5.2
Nov 06 15:25:23 DESKTOP-92CHCK7 dockerd[1692]: time="2025-11-06T15:25:23.477204532+08:00" level=info msg="Initializing buildkit"
Nov 06 15:25:23 DESKTOP-92CHCK7 dockerd[1692]: time="2025-11-06T15:25:23.570329696+08:00" level=info msg="Completed buildkit initialization"
Nov 06 15:25:23 DESKTOP-92CHCK7 dockerd[1692]: time="2025-11-06T15:25:23.578868047+08:00" level=info msg="Daemon has completed initialization"
Nov 06 15:25:23 DESKTOP-92CHCK7 dockerd[1692]: time="2025-11-06T15:25:23.578973779+08:00" level=info msg="API listen on /run/docker.sock"
Nov 06 15:25:23 DESKTOP-92CHCK7 systemd[1]: Started Docker Application Container Engine.
```


#### 将用户添加到 Docker 组 {#将用户添加到-docker-组}

```bash
usermod -aG docker $USER
```


#### 换源 {#换源}


##### 创建目录 {#创建目录}

```bash
mkdir -p /etc/docker
```


##### 向配置文件写入镜像源 {#向配置文件写入镜像源}

```bash
tee /etc/docker/daemon.json <<-'EOF'
{
    "registry-mirrors": [
    	"https://docker.m.daocloud.io",
    	"https://docker.imgdb.de",
    	"https://docker-0.unsee.tech",
    	"https://docker.hlmirror.com",
    	"https://docker.1ms.run",
    	"https://func.ink",
    	"https://lispy.org",
    	"https://docker.xiaogenban1993.com"
    ]
}
EOF
```


##### 重启 Docker 服务 {#重启-docker-服务}

```bash
systemctl daemon-reload && systemctl restart docker
```


##### 验证 {#验证}

```bash
docker pull hello-world
```

```bash
Using default tag: latest
latest: Pulling from library/hello-world
17eec7bbc9d7: Pull complete
Digest: sha256:56433a6be3fda188089fb548eae3d91df3ed0d6589f7c2656121b911198df065
Status: Downloaded newer image for hello-world:latest
docker.io/library/hello-world:latest
```


### 安装 python 管理工具 {#安装-python-管理工具}

```bash
pacman -S uv
```

根据 <https://mirrors.xjtu.edu.cn/docs/pypi> 的说明配置国内源

```bash
~/.config/uv/
```

创建完目录后通过以下命令编辑配置文件：

```bash
nvim ~/.config/uv/uv.toml
```

文件中的内容如下：

```toml
[[index]]
url = "https://mirrors.xjtu.edu.cn/pypi/simple/"
default = true
```

Arch Linux 系统本身没有安装 python，可以通过 UV 创建一个环境，把对应的目录放入到环境变量 PATH 中就可以了。

```bash
[root@DESKTOP-92CHCK7 donal]# python --version
bash: python: command not found
[root@DESKTOP-92CHCK7 donal]# python3 --version
bash: python3: command not found
```

在用户目录中创建一个目录并进入到该目录：

```bash
[root@DESKTOP-92CHCK7 donal]# cd ~/
[root@DESKTOP-92CHCK7 ~]# pwd
/root
[root@DESKTOP-92CHCK7 ~]# mkdir python
[root@DESKTOP-92CHCK7 ~]# cd python/
```

查看可用的 python 版本：

```bash
uv python list
```

```bash
cpython-3.15.0a1-linux-x86_64-gnu                 <download available>
cpython-3.15.0a1+freethreaded-linux-x86_64-gnu    <download available>
cpython-3.14.0-linux-x86_64-gnu                   <download available>
cpython-3.14.0+freethreaded-linux-x86_64-gnu      <download available>
cpython-3.13.9-linux-x86_64-gnu                   <download available>
cpython-3.13.9+freethreaded-linux-x86_64-gnu      <download available>
cpython-3.12.12-linux-x86_64-gnu                  <download available>
cpython-3.11.14-linux-x86_64-gnu                  <download available>
cpython-3.10.19-linux-x86_64-gnu                  <download available>
cpython-3.9.24-linux-x86_64-gnu                   <download available>
cpython-3.8.20-linux-x86_64-gnu                   <download available>
pypy-3.11.13-linux-x86_64-gnu                     <download available>
pypy-3.10.16-linux-x86_64-gnu                     <download available>
pypy-3.9.19-linux-x86_64-gnu                      <download available>
pypy-3.8.16-linux-x86_64-gnu                      <download available>
graalpy-3.12.0-linux-x86_64-gnu                   <download available>
graalpy-3.11.0-linux-x86_64-gnu                   <download available>
graalpy-3.10.0-linux-x86_64-gnu                   <download available>
graalpy-3.8.5-linux-x86_64-gnu                    <download available>
```

选择一个合适的版本安装

```bash
uv init --python cpython-3.14.0-linux-x86_64-gnu
```

安装一个包才会实际安装 python:

```bash
[root@DESKTOP-92CHCK7 python]# uv add requests
```

```bash
Resolved 6 packages in 1.33s
Prepared 5 packages in 684ms
Installed 5 packages in 7ms
 + certifi==2025.10.5
 + charset-normalizer==3.4.4
 + idna==3.11
 + requests==2.32.5
 + urllib3==2.5.0
```

在文件 ~/.bashrc 中配置环境变量 PATH:

```bash
export PATH=/root/python/.venv/bin:$PATH
```

配置完了要立即生效，可以执行命令：

```bash
source ~/.bashrc
```

现在就可以查询到 python 版本了：

```bash
[root@DESKTOP-92CHCK7 bin]# python --version
Python 3.14.0
```


### 备份 Arch {#备份-arch}

```bash
wsl --export Arch E:\backups\arch.tar
```

```bash
正在导出，这可能需要几分钟时间。 (1531 MB): ./etc/pacman.d/gnupg/S.gpg-agent.ssh: pax format cannot archive sockets: ./etc/pacman.d/gnupg/S.gpg-agent: pax format cannot archive sockets: ./etc/pacman.d/gnupg/S.keyboxd: pax format cannot archive sockets: ./etc/pacman.d/gnupg/S.gpg-agent.extra: pax format cannot archive sockets: ./etc/pacman.d/gnupg/S.dirmngr: pax format cannot archive sockets: ./etc/pacman.d/gnupg/S.gpg-agent.browser: pax format cannot archi (4116 MB)
```

看上去导出的文件还是比较大的，有没有必要备份呢？


### 问题处理 {#问题处理}


#### Locales {#locales}

```bash
PS D:\Documents\codes\python\study> wsl
-bash: warning: setlocale: LC_CTYPE: cannot change locale (en_US.UTF-8): No such file or directory
-bash: warning: setlocale: LC_CTYPE: cannot change locale (en_US.UTF-8): No such file or directory
-bash: warning: setlocale: LC_COLLATE: cannot change locale (en_US.UTF-8): No such file or directory
```

```bash
# 编辑 locale.gen 文件
sudo nvim /etc/locale.gen

# 取消注释 en_US.UTF-8 UTF-8 这一行（删除行首的 #）
# 找到这一行并确保是这样的：
en_US.UTF-8 UTF-8

# 生成 locales
sudo locale-gen

# 设置系统locale
sudo nvim /etc/locale.conf
```


### 字体安装 {#字体安装}

```bash
mkdir -p ~/.local/share/fonts/
```

将字体文件复制到此目录中，然后执行：

```bash
fc-cache -f -v
```


### 输入法 {#输入法}

```bash
pacman -S fcitx5 fcitx5-configtool fcitx5-gtk fcitx5-qt fcitx5-chinese-addons librime librime-data fcitx5-rime
```

安装字体支持

```bash
pacman -S noto-fonts-cjk noto-fonts-emoji
```

先手动运行

```bash
fcitx5 --disable=wayland -d
```

```bash
fcitx5-configtool
```


### 删除 Arch Linux {#删除-arch-linux}

```shell
PS D:\home\.emacs.d> wsl -l
```

```shell
适用于 Linux 的 Windows 子系统分发:
archlinux (默认值)
debian
```

进行删除

```shell
PS D:\home\.emacs.d> wsl --unregister archlinux
```

删除后会自动确认一个默认值：

```shell
PS D:\home\.emacs.d> wsl -l
适用于 Linux 的 Windows 子系统分发:
debian (默认值)
```


## 虚拟机管理 {#虚拟机管理}


### 设置默认的目录，节省 C 盘空间 {#设置默认的目录-节省-c-盘空间}

默认情况下，vagrant 会把相关的文件都保存在 %USERPROFILE%\\.vagrant.d 目录中，可以通过设置环境变量 VAGRANT_HOME
来调整到其他盘符下，以节省 C 盘的空间。

```shell
setx VAGRANT_HOME d:\.vagrant.d
```


### 相关软件安装 {#相关软件安装}

```shell
winget install Oracle.VirtualBox
winget install Hashicorp.Vagrant
```


### 虚拟机默认位置 {#虚拟机默认位置}

```shell
VBoxManage setproperty machinefolder "D:\VirtualBoxVMs"
```


### 查找 vagrant box {#查找-vagrant-box}

<https://portal.cloud.hashicorp.com/vagrant/discover>

{{< figure src="/images/dev-envs.org/2026-01-26_15-27-13_screenshot.png" width="90%" >}}

复制要下载的 Box 的名称，然后使用如下的名称将 Box 下载到本地：

```shell
vagrant box add  cloud-image/debian-13
```

```shell
==> box: Loading metadata for box 'cloud-image/debian-13'
    box: URL: https://vagrantcloud.com/api/v2/vagrant/cloud-image/debian-13
This box can work with multiple providers! The providers that it
can work with are listed below. Please review the list and choose
the provider you will be working with.

1) libvirt
2) qemu
3) virtualbox

Enter your choice:
```

我使用 virtualbox，所以我选择 3,然后就开始下载了:

```shell
==> box: Loading metadata for box 'cloud-image/debian-13'
    box: URL: https://vagrantcloud.com/api/v2/vagrant/cloud-image/debian-13
This box can work with multiple providers! The providers that it
can work with are listed below. Please review the list and choose
the provider you will be working with.

1) libvirt
2) qemu
3) virtualbox

Enter your choice: 3
==> box: Adding box 'cloud-image/debian-13' (v20260112.2355.0) for provider: virtualbox (amd64)
    box: Downloading: https://vagrantcloud.com/cloud-image/boxes/debian-13/versions/20260112.2355.0/providers/virtualbox/amd64/vagrant.box
Progress: 0% (Rate: 76073/s, Estimated time remaining: 4:51:49)
```

```shell
==> box: Loading metadata for box 'cloud-image/debian-13'
    box: URL: https://vagrantcloud.com/api/v2/vagrant/cloud-image/debian-13
This box can work with multiple providers! The providers that it
can work with are listed below. Please review the list and choose
the provider you will be working with.

1) libvirt
2) qemu
3) virtualbox

Enter your choice: 3
==> box: Adding box 'cloud-image/debian-13' (v20260112.2355.0) for provider: virtualbox (amd64)
    box: Downloading: https://vagrantcloud.com/cloud-image/boxes/debian-13/versions/20260112.2355.0/providers/virtualbox/amd64/vagrant.box
    box:
==> box: Successfully added box 'cloud-image/debian-13' (v20260112.2355.0) for 'virtualbox (amd64)'!
```

出现最后一行的成功消息后，表示添加成功了，可以使用这个 Box 来创建虚拟机了。

可以通过如下的命令检查 Box：

```shell
vagrant box list
```

```shell
cloud-image/debian-13 (virtualbox, 20260112.2355.0, (amd64))
```

如果下载的速度很慢，你也可以将这个 URL 复制出来，然后使用其他的下载工具下载 ,然后通过如下的命令来添加 Box：

```shell
vagrant box add my/debian13 D:\data\downloads\cloud-image-debian-13-virtualbox.box
```

```shell
==> box: Box file was not detected as metadata. Adding it directly...
==> box: Adding box 'my/debian13' (v0) for provider: (amd64)
    box: Unpacking necessary files from: file:///D:/data/downloads/cloud-image-debian-13-virtualbox.box
    box:
==> box: Successfully added box 'my/debian13' (v0) for '(amd64)'!
```

查看 Box:

```shell
vagrant box list
```

```shell
cloud-image/debian-13 (virtualbox, 20260112.2355.0, (amd64))
my/debian13           (virtualbox, 0, (amd64))
```

可以看到自己命名的 Box 已经添加到系统中了。


### 创建虚拟机 {#创建虚拟机}


#### Virtualbox 这是个失败的例子，但是应该是可以成功的，不知道跟什么冲突了 {#virtualbox-这是个失败的例子-但是应该是可以成功的-不知道跟什么冲突了}

虚拟机我都放在 D:\VirtualBoxVMs 目录中，然后在这个目录中创建一个目录，例如 debian13 ，然后在命令行中进入到这个目录：

```shell
PS D:\VirtualBoxVMs\debian13> vagrant init cloud-image/debian-13
```

```shell
A `Vagrantfile` has been placed in this directory. You are now
ready to `vagrant up` your first virtual environment! Please read
the comments in the Vagrantfile as well as documentation on
`vagrantup.com` for more information on using Vagrant.
```

执行完命令后会提示生成了一个 \`Vagrantfile\` 文件，此文件是用 Ruby 语言编写的虚拟机描述文件，使用如下命令启动虚拟机：

```shell
PS D:\VirtualBoxVMs\debian13> vagrant up
```

```shell
ringing machine 'default' up with 'virtualbox' provider...
==> default: Importing base box 'cloud-image/debian-13'...
==> default: Generating MAC address for NAT networking...
==> default: Checking if box 'cloud-image/debian-13' version '20260112.2355.0' is up to date...
==> default: Setting the name of the VM: debian13_default_1769414455947_44388
==> default: Clearing any previously set network interfaces...
==> default: Preparing network interfaces based on configuration...
    default: Adapter 1: nat
==> default: Forwarding ports...
    default: 22 (guest) => 2222 (host) (adapter 1)
==> default: Booting VM...
There was an error while executing `VBoxManage`, a CLI used by Vagrant
for controlling VirtualBox. The command and stderr is shown below.

Command: ["startvm", "211f21bc-c624-4782-9d03-3081241fdad0", "--type", "headless"]

Stderr: VBoxManage.exe: error: The virtual machine 'debian13_default_1769414455947_44388' has terminated unexpectedly during startup with exit code -1073741819 (0xc0000005)
VBoxManage.exe: error: Details: code E_FAIL (0x80004005), component MachineWrap, interface IMachine
```

但是碰到了这个错误，似乎是 WSL 与 VirtualBox 有冲突。

删除创建的虚拟机：

```shell
PS D:\VirtualBoxVMs\debian13> vagrant destroy
```

```shell
    default: Are you sure you want to destroy the 'default' VM? [y/N]
```

恢复 Y ：

```shell
    default: Are you sure you want to destroy the 'default' VM? [y/N] y
==> default: Destroying VM and associated drives...
```


#### VMWare {#vmware}


##### 安装 VMWare Workstation {#安装-vmware-workstation}

<https://www.vmware.com/products/desktop-hypervisor/workstation-and-fusion> 从此网站上下载 VMWare Workstation pro ，然后
手动安装并设置默认的虚拟机目录：

{{< figure src="/images/dev-envs.org/2026-01-26_16-44-11_screenshot.png" width="90%" >}}

{{< figure src="/images/dev-envs.org/2026-01-26_16-44-36_screenshot.png" width="90%" >}}


##### 从网站 <https://developer.hashicorp.com/vagrant/install/vmware> 上下载 Vagrant VMware Utility 并安装 {#从网站-https-developer-dot-hashicorp-dot-com-vagrant-install-vmware-上下载-vagrant-vmware-utility-并安装}


##### 安装 vmware-desktop 插件 {#安装-vmware-desktop-插件}

```shell
PS D:\VirtualBoxVMs\debian13> vagrant plugin install vagrant-vmware-desktop
```

```shell
Installing the 'vagrant-vmware-desktop' plugin. This can take a few minutes...
Fetching hashdiff-1.2.1.gem
Fetching crack-1.0.1.gem
Fetching public_suffix-7.0.2.gem
Fetching addressable-2.8.8.gem
Fetching webmock-3.26.1.gem
Fetching rspec-support-3.13.6.gem
Fetching diff-lcs-1.6.2.gem
Fetching rspec-expectations-3.13.5.gem
Fetching rspec-core-3.13.6.gem
Fetching rspec-its-2.0.0.gem
Fetching rspec-mocks-3.13.7.gem
Fetching rspec-3.13.2.gem
Fetching rake-13.3.1.gem
Fetching vagrant-vmware-desktop-3.0.5.gem
Thank you for installing the Vagrant VMware Desktop
plugin. This plugin requires the Vagrant VMware
Utility to be installed. To learn more about the
Vagrant VMware Utility, please visit:

  https://www.vagrantup.com/docs/providers/vmware/vagrant-vmware-utility

To install the Vagrant VMware Utility, please
download the appropriate installer for your
system from:

  https://www.vagrantup.com/downloads/vmware
Successfully uninstalled addressable-2.8.8
Successfully uninstalled crack-1.0.1
Removing htmldiff
Removing ldiff
Successfully uninstalled diff-lcs-1.6.2
Successfully uninstalled hashdiff-1.2.1
Successfully uninstalled public_suffix-7.0.2
Removing rake
Successfully uninstalled rake-13.3.1
Successfully uninstalled rspec-3.13.2
Removing rspec
Successfully uninstalled rspec-core-3.13.6
Successfully uninstalled rspec-expectations-3.13.5
Successfully uninstalled rspec-its-2.0.0
Successfully uninstalled rspec-mocks-3.13.7
Successfully uninstalled rspec-support-3.13.6
Successfully uninstalled webmock-3.26.1
Installed the plugin 'vagrant-vmware-desktop (3.0.5)'!
Post install message from the 'vagrant-vmware-desktop' plugin:

Thank you for installing the Vagrant VMware Desktop
plugin. This plugin requires the Vagrant VMware
Utility to be installed. To learn more about the
Vagrant VMware Utility, please visit:

  https://www.vagrantup.com/docs/providers/vmware/vagrant-vmware-utility

To install the Vagrant VMware Utility, please
download the appropriate installer for your
system from:

  https://www.vagrantup.com/downloads/vmware
```


##### 重新下载支持 vmware_desktop 的 Box {#重新下载支持-vmware-desktop-的-box}

{{< figure src="/images/dev-envs.org/2026-01-26_16-53-13_screenshot.png" width="90%" >}}

```shell
vagrant box add svincent/debian13
```

```shell
==> box: Loading metadata for box 'svincent/debian13'
    box: URL: https://vagrantcloud.com/api/v2/vagrant/svincent/debian13
This box can work with multiple providers! The providers that it
can work with are listed below. Please review the list and choose
the provider you will be working with.

1) libvirt
2) virtualbox
3) vmware_desktop

Enter your choice:
```

输入 3 后回车

```shell
Enter your choice: 3
==> box: Adding box 'svincent/debian13' (v1.2.0) for provider: vmware_desktop (amd64)
    box: Downloading: https://vagrantcloud.com/svincent/boxes/debian13/versions/1.2.0/providers/vmware_desktop/amd64/vagrant.box
    box:
    box: Calculating and comparing box checksum...
==> box: Successfully added box 'svincent/debian13' (v1.2.0) for 'vmware_desktop (amd64)'!
PS D:\>
```


##### 初始化虚拟机 {#初始化虚拟机}

```shell
PS D:\VirtualBoxVMs\debian13> vagrant init svincent/debian13
```

```shell
A `Vagrantfile` has been placed in this directory. You are now
ready to `vagrant up` your first virtual environment! Please read
the comments in the Vagrantfile as well as documentation on
`vagrantup.com` for more information on using Vagrant.
```


##### 启动虚拟机 {#启动虚拟机}

```shell
PS D:\VirtualBoxVMs\debian13> vagrant up --provider=vmware_desktop
```

这个过程需要花费几分钟的时间，等到结束：

```shell
Bringing machine 'default' up with 'vmware_desktop' provider...
==> default: Cloning VMware VM: 'svincent/debian13'. This can take some time...
==> default: Checking if box 'svincent/debian13' version '1.2.0' is up to date...
==> default: Verifying vmnet devices are healthy...
==> default: Preparing network adapters...
==> default: Starting the VMware VM...
==> default: Waiting for the VM to receive an address...
==> default: Forwarding ports...
    default: -- 22 => 2222
==> default: Waiting for machine to boot. This may take a few minutes...
    default: SSH address: 127.0.0.1:2222
    default: SSH username: vagrant
    default: SSH auth method: private key
    default:
    default: Vagrant insecure key detected. Vagrant will automatically replace
    default: this with a newly generated keypair for better security.
    default:
    default: Inserting generated public key within guest...
    default: Removing insecure key from the guest if it's present...
    default: Key inserted! Disconnecting and reconnecting using new SSH key...
==> default: Machine booted and ready!
==> default: Configuring network adapters within the VM...
```


##### 登录到这个虚拟机 {#登录到这个虚拟机}

```shell
PS D:\VirtualBoxVMs\debian13> vagrant ssh
```

```shell
vagrant@debian13:~$
```

出现如上的提示符，表示登录到了虚拟机中了。

**root 和 vagrant 用户密码都是 vagrant**


##### 停止虚拟机 {#停止虚拟机}

```shell
vagrant halt
```


##### 销毁虚拟机 {#销毁虚拟机}

```shell
vagrant destroy
```


##### 批量创建虚拟机 {#批量创建虚拟机}

```ruby
# Vagrantfile 示例
Vagrant.configure("2") do |config|
  (1..3).each do |i|
    config.vm.define "server#{i}" do |server|
      server.vm.box = "ubuntu/focal64"
      server.vm.network "private_network", ip: "192.168.50.#{100 + i}"
    end
  end
end
```

通过上述配置文件，可以快速创建 3 台虚拟机，每台虚拟机的 IP 地址分别为 192.168.50.101、192.168.50.102 和 192.168.50.103。

启动批量虚拟机的命令如下：

```shell
vagrant up
```

销毁批量虚拟机的命令如下：

```shell
vagrant destroy -f
```


## NeoVIM {#neovim}

我只会一些 VIM 相关等操作，不懂 VIM 的相关配置，所以我使用一个网络上发布的配置。

安装 neovide

```shell
scoop install neovide
```

```shell
Updating Scoop...
Updating Buckets...
 * 08a96210c61a ppsspp-dev: Update to version 1.19.3-1478-ge71e1d260e    games        77 minutes ago
 * bcafc586b552 openmsx-dev: Update to version 21.0-190-g60ff4c7ba       games        77 minutes ago
 * ca8006ff2add duckstation-preview: Update to version 20260129-g130494f games        77 minutes ago
 * d9b6f6aaab7c cs-demo-manager: Update to version 3.18.2                games        77 minutes ago
 * 91b434d3ff77 rpcs3: Update to version 0.0.39-18741                    games        5 hours ago
 * 4dfa0d647238 ppsspp-dev: Update to version 1.19.3-1472-g8de5b45bbe    games        5 hours ago
 * 4d8ac09004d1 openmsx-dev: Update to version 21.0-189-gb9d7c346c       games        5 hours ago
 * b88b953dc226 vscode-dev: Update to version 1.109.0-09a6795            scoop-misc   3 hours ago
 * aba5229aa11d opencode-x: Update to version 1.1.4.8f8ee09              scoop-misc   3 hours ago
Scoop was updated successfully!
Installing 'neovide' (0.15.2) [64bit] from 'extras' bucket
Starting download with aria2 ...
Download: Download Results:
Download: gid   |stat|avg speed  |path/URI
Download: ======+====+===========+=======================================================
Download: 34a69e|OK  |   0.9MiB/s|D:/Scoop/cache/neovide#0.15.2#784a84a.zip
Download: Status Legend:
Download: (OK):download completed.
Checking hash of neovide.exe.zip ... ok.
Extracting neovide.exe.zip ... done.
Linking D:\Scoop\apps\neovide\current => D:\Scoop\apps\neovide\0.15.2
Creating shim for 'neovide'.
Making D:\Scoop\shims\neovide.exe a GUI binary.
Creating shortcut for Neovide (neovide.exe)
Running post_install script...done.
'neovide' (0.15.2) was installed successfully!
Notes
-----
Add Open with Neovide as a context menu option by running:
reg import "D:\Scoop\apps\neovide\current\install-context.reg"
```

根据上面的提示之行：

```shell
reg import "D:\Scoop\apps\neovide\current\install-context.reg"
```

从 github 上下载 AstroNvim 的配制到如下目录中（记得前面环境变量的配制）：

```shell
PS D:\home\.config> git clone --depth 1 https://github.com/AstroNvim/template nvim
```

出现以下信息表示克隆完成：

```shell
Cloning into 'nvim'...
remote: Enumerating objects: 21, done.
remote: Counting objects: 100% (21/21), done.
remote: Compressing objects: 100% (19/19), done.
remote: Total 21 (delta 0), reused 8 (delta 0), pack-reused 0 (from 0)
Receiving objects: 100% (21/21), 9.68 KiB | 2.42 MiB/s, done.
```

克隆完成后启动 neovide，会出现如下的信息，neovide 在自动安装一些插件：

{{< figure src="/images/dev-envs.org/2026-01-29_14-14-40_screenshot.png" width="90%" >}}

安装完成后出现如下的介面：

{{< figure src="/images/dev-envs.org/2026-01-29_14-18-36_screenshot.png" width="90%" >}}

使用空格以及界面上提示的快捷键来进行操作：

{{< figure src="/images/dev-envs.org/2026-01-29_14-19-56_screenshot.png" width="90%" >}}

然后按 f 键后出现如下的介面：

{{< figure src="/images/dev-envs.org/2026-01-29_14-21-03_screenshot.png" width="90%" >}}

再按 f 键查找文件：

{{< figure src="/images/dev-envs.org/2026-01-29_14-21-52_screenshot.png" width="90%" >}}

回车打开文件：

{{< figure src="/images/dev-envs.org/2026-01-29_14-22-23_screenshot.png" width="90%" >}}

然后就跟正常的 Vim 一样操作了，详细到操作可以参考 <https://docs.astronvim.com/> 。


## GPG/文件加密 {#gpg-文件加密}


### 安装 {#安装}

```bash
scoop install gpg
```

验证是否安装成功：

```bash
gpg --version
```

```bash
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

```bash
gpg --gen-key
```

输入回车，系统会给出提示：

```bash
gpg (GnuPG) 2.5.16; Copyright (C) 2025 g10 Code GmbH
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

gpg: keybox 'D:\\Scoop\\apps\\gpg\\current\\home\\pubring.kbx' created
Note: Use "gpg --full-generate-key" for a full featured key generation dialog.

GnuPG needs to construct a user ID to identify your key.

Real name:
```

一次输入名字以及邮箱：

```bash
Real name: Donald Lo
Email address: donald.sd.lo@gmail.com
You selected this USER-ID:
    "Donald Lo <donald.sd.lo@gmail.com>"

Change (N)ame, (E)mail, or (O)kay/(Q)uit?
```

确认名字和邮箱后输入 o 后回车，会弹出一个输入密码保护 key 的对话框：

{{< figure src="/images/dev-envs.org/2026-01-21_15-37-56_screenshot.png" width="90%" >}}

输入密码后回车，由于我输入的密码过于简单，弹出如下的对话框：

{{< figure src="/images/dev-envs.org/2026-01-21_15-38-17_screenshot.png" width="90%" >}}

点击 Take this one anyway 按钮，会让你确认密码：

{{< figure src="/images/dev-envs.org/2026-01-21_15-38-37_screenshot.png" width="90%" >}}

再此输入密码后点击 OK 就会生成 key。

{{< figure src="/images/dev-envs.org/2026-01-21_15-41-04_screenshot.png" width="90%" >}}

如果要更多选项，可以使用如下命令生成 key：

```bash
gpg --full-generate-key
```


### 生成一个文本文件 {#生成一个文本文件}

```bash
PS E:\tmp\test04> cat .\test01.txt
```

其中的内容如下：

```bash
01
02
03
04
```


### 加密文件 {#加密文件}

```bash
PS E:\tmp\test04> gpg --recipient "Donald Lo <donald.sd.lo@gmail.com>" --output test01.txt.gpg --encrypt .\test01.txt
```

```bash
gpg: checking the trustdb
gpg: marginals needed: 3  completes needed: 1  trust model: pgp
gpg: depth: 0  valid:   1  signed:   0  trust: 0-, 0q, 0n, 0m, 0f, 1u
gpg: next trustdb check due at 2029-01-20
```

查看加密后的文件内容

```bash
PS E:\tmp\test04> cat test01.txt.gpg
```

内容完全混乱了，无法识别：

```bash
�^+7I␦^�+�@�lQr���&�4   �{�JQ�,%_��h9��
0�b�� �D������_o��-�a�s�b��мu�O1�h����u�p��[    �ZM�S�upn����j}ۑ�ŀ����G�����Ŷ��m�*V;U{gXFU%�R����[�*��s�0�{X�㏌�0FZ"T
```


### 解密 {#解密}

```bash
PS E:\tmp\test04> gpg --output test.de.txt --decrypt test01.txt.gpg
```

回车，如果提示要输入密码就输入之前输入的密码，之后会显示如下的消息：

```bash
gpg: encrypted with cv25519 key, ID 2B37491A5EF82BAB, created 2026-01-21
      "Donald Lo <donald.sd.lo@gmail.com>"
```

查看解密之后的文件：

```bash
PS E:\tmp\test04> cat test.de.txt
```

```bash
01
02
03
04
```


## 测试数学公式 {#测试数学公式}

这是一个行内的数学公式： \\(n^2 = 10\\)

\\[ n + 1 = x + y \\]

这是末尾的字符。

营造法式
