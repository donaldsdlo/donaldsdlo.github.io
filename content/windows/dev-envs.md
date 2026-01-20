---
title: "windows 开发环境配置"
author: ["Donald Lo"]
date: 2026-01-15
lastmod: 2026-01-20T09:38:10+08:00
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
    - [设置 UV 相关的环境变量](#设置-uv-相关的环境变量)
    - [使用国内镜像](#使用国内镜像)
    - [采用 UV 来管理 python 版本和项目虚拟环境，安装 UV 软件：](#采用-uv-来管理-python-版本和项目虚拟环境-安装-uv-软件)
    - [要为 uv 命令启用 Powershell 自动补全，在 Powershell 中运行以下对应命令：](#要为-uv-命令启用-powershell-自动补全-在-powershell-中运行以下对应命令)
    - [使用 uv 管理多版本 Python](#使用-uv-管理多版本-python)
        - [显示可安装以及已经安装的 Python 版本：](#显示可安装以及已经安装的-python-版本)
        - [安装指定版本的 Python](#安装指定版本的-python)
        - [已经安装的版本，在后续使用到此版本的时候，UV 不会重复下载。](#已经安装的版本-在后续使用到此版本的时候-uv-不会重复下载)
        - [查看安装的结果](#查看安装的结果)
        - [Python 安装的目录](#python-安装的目录)
        - [移除已安装的版本](#移除已安装的版本)
    - [管理项目](#管理项目)
    - [安装常用工具](#安装常用工具)
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
scoop install git aria2 coreutils fzf grep gzip make ripgrep rga wget which fd 7zip ag altsnap ast-grep astyle autojump curl delta direnv everything everything-cli ffmpeg geekuninstaller  hugo hugo-extended mpv pandoc scoop-search
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
![](/images/dev-envs.org/2026-01-16_14-43-09_screenshot.png)
需要手工解压缩：
![](/images/dev-envs.org/2026-01-16_14-43-55_screenshot.png)
选中所有的字体文件（以 ttf 结尾的文件），然后鼠标右键菜单中选择 **为所有用户安装** :
![](/images/dev-envs.org/2026-01-16_14-49-30_screenshot.png)


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
![](/images/dev-envs.org/2026-01-20_09-02-04_screenshot.png)
通过 Ctrl+, 快捷键打开设置界面
![](/images/dev-envs.org/2026-01-20_09-02-58_screenshot.png)


### 查看 Powershell 的配置文件 {#查看-powershell-的配置文件}

```shell
echo $PROFILE
```

```shell
D:\Documents\PowerShell\Microsoft.PowerShell_profile.ps1
```

需要添加的配置和一些函数都可以写在这个文件中。


## Python 环境安装和配置 {#python-环境安装和配置}


### 设置 UV 相关的环境变量 {#设置-uv-相关的环境变量}

```shell
setx UV_PYTHON_INSTALL_DIR D:\uv\python
setx UV_TOOL_DIR D:\uv\tools
```


### 使用国内镜像 {#使用国内镜像}

在文件 ~/.config/uv/uv.toml 中添加如下内容：

```toml
[[index]]
url = "https://mirrors.tuna.tsinghua.edu.cn/pypi/web/simple/"
default = true
```


### 采用 UV 来管理 python 版本和项目虚拟环境，安装 UV 软件： {#采用-uv-来管理-python-版本和项目虚拟环境-安装-uv-软件}

```shell
scoop install uv
```

在 D:\python-envs 目录中：

```shell
uv init default-python --python 3.14
```

```shell
cd default-python
```

```shell
uv add requests
```

将 default-python\\.venv\Scripts 的完整目录添加到 PATH 环境变量的最前面，这样就可以使用这个环境下的 python 作为系统的默认 python 了。


### 要为 uv 命令启用 Powershell 自动补全，在 Powershell 中运行以下对应命令： {#要为-uv-命令启用-powershell-自动补全-在-powershell-中运行以下对应命令}

```shell
if (!(Test-Path -Path $PROFILE)) {
  New-Item -ItemType File -Path $PROFILE -Force
}
Add-Content -Path $PROFILE -Value '(& uv generate-shell-completion powershell) | Out-String | Invoke-Expression'
```


### 使用 uv 管理多版本 Python {#使用-uv-管理多版本-python}


#### 显示可安装以及已经安装的 Python 版本： {#显示可安装以及已经安装的-python-版本}

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


#### 安装指定版本的 Python {#安装指定版本的-python}

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


#### 已经安装的版本，在后续使用到此版本的时候，UV 不会重复下载。 {#已经安装的版本-在后续使用到此版本的时候-uv-不会重复下载}


#### 查看安装的结果 {#查看安装的结果}

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


#### Python 安装的目录 {#python-安装的目录}

```shell
uv python dir
```

```shell
D:\uv\python
```


#### 移除已安装的版本 {#移除已安装的版本}

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


### 管理项目 {#管理项目}


### 安装常用工具 {#安装常用工具}

```shell
uv tool install aider-chat
```


## 测试数学公式 {#测试数学公式}

这是一个行内的数学公式： \\(n^2 = 10\\)

\\[ n + 1 = x + y \\]

这是末尾的字符。
