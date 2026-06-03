---
title: "EndeavourOS"
author: ["Donald Lo"]
date: 2026-05-13
lastmod: 2026-05-25T16:19:51+08:00
tags: ["EndeavourOS", "Arch", "Linux"]
draft: false
---

<div class="ox-hugo-toc toc">

<div class="heading">&#30446;&#24405;</div>

- [为什么选择 EndeavourOS](#为什么选择-endeavouros)
    - [主要优势](#主要优势)
    - [与 Arch Linux 的区别](#与-arch-linux-的区别)
    - [系统要求](#系统要求)
- [安装步骤](#安装步骤)
    - [准备工作](#准备工作)
        - [下载 ISO 镜像](#下载-iso-镜像)
        - [制作启动 U 盘](#制作启动-u-盘)
            - [Windows 系统](#windows-系统)
            - [Linux 系统](#linux-系统)
            - [macOS 系统](#macos-系统)
    - [启动并进入安装环境](#启动并进入安装环境)
    - [安装完成](#安装完成)
- [安装后配置](#安装后配置)
    - [更新系统](#更新系统)
    - [使用 stow 管理配置文件](#使用-stow-管理配置文件)
        - [什么是 stow](#什么是-stow)
        - [stow 的优势](#stow-的优势)
        - [安装 stow](#安装-stow)
        - [目录结构](#目录结构)
        - [基本操作](#基本操作)
        - [使用前注意事项](#使用前注意事项)
        - [完整流程示例](#完整流程示例)
        - [配合版本控制](#配合版本控制)
        - [常见问题](#常见问题)
    - [Docker](#docker)
    - [常用软件安装](#常用软件安装)
- [常见问题](#常见问题)
    - [VirtualBox 中无法识别 USB 设备](#virtualbox-中无法识别-usb-设备)
    - [屏幕分辨率异常](#屏幕分辨率异常)
    - [网络连接问题](#网络连接问题)

</div>
<!--endtoc-->



## 为什么选择 EndeavourOS {#为什么选择-endeavouros}

EndeavourOS 是一个基于 Arch Linux 的发行版，它兼具 Arch Linux 的强大定制性和开箱即用的便利性。对于想要学习 Linux 系统但又不想从零配置的用户来说，是一个理想的选择。


### 主要优势 {#主要优势}

-   `开箱即用` — 无需手动配置桌面环境、网络、引导程序等基础组件
-   `滚动更新` — 始终使用最新的软件包，无需担心版本过旧
-   `强大的 AUR` — 访问 Arch 用户仓库，拥有海量软件资源
-   `轻量灵活` — 可根据需求自由选择桌面环境和系统组件
-   `社区活跃` — 友好的中文社区支持，遇到问题容易找到解决方案


### 与 Arch Linux 的区别 {#与-arch-linux-的区别}

| 特性 | Arch Linux | EndeavourOS |
|----|------------|-------------|
| 安装方式 | 命令行手动安装 | 图形化安装界面 |
| 初始配置 | 完全手动   | 自动检测并配置硬件 |
| 学习曲线 | 陡峭       | 平缓        |
| 适合人群 | 有经验的用户 | 初学者到中级用户 |


### 系统要求 {#系统要求}

-   CPU: 64位处理器
-   内存: 至少 2GB（推荐 4GB+）
-   硬盘: 至少 20GB 可用空间
-   显卡: 支持 UEFI 或 BIOS 启动


## 安装步骤 {#安装步骤}


### 准备工作 {#准备工作}


#### 下载 ISO 镜像 {#下载-iso-镜像}

从 EndeavourOS 官网下载最新的 ISO 镜像文件：

-   官方网站：<https://endeavouros.com/latest-release/>
-   下载链接：<https://github.com/endeavouros-team/EndeavourOS/releases>

建议使用 BT 种子或国内镜像源下载，可获得更快的下载速度。


#### 制作启动 U 盘 {#制作启动-u-盘}

将 ISO 文件刻录到 U 盘有以下几种方式：


##### Windows 系统 {#windows-系统}

推荐使用 `Rufus` 或 `balenaEtcher` 工具：

`Rufus` （推荐）：

1.  下载并打开 Rufus：<https://rufus.ie/>
2.  插入 U 盘（容量至少 4GB）
3.  选择 U 盘设备
4.  点击「选择」按钮，加载 ISO 文件
5.  分区方案选择 `GPT`
6.  目标系统类型选择 `UEFI（非 CSM）`
7.  点击「开始」等待刻录完成

`balenaEtcher` ：

1.  下载并打开 balenaEtcher：<https://etcher.balena.io/>
2.  点击「Flash from file」，选择 ISO 文件
3.  选择目标 U 盘
4.  点击「Flash!」开始刻录


##### Linux 系统 {#linux-系统}

`balenaEtcher` （图形界面）：
与 Windows 相同操作步骤。

`dd 命令` （命令行）：

```bash
sudo dd if=/path/to/endeavouros.iso of=/dev/sdX bs=4M status=progress oflag=sync
```

注意：将 `/dev/sdX` 替换为你的 U 盘设备号（如 `/dev/sdb` ）。可以通过 `lsblk` 或 `sudo fdisk -l` 查看。

`Ventoy` （推荐长期使用）：

1.  安装 Ventoy：<https://www.ventoy.net/>
2.  将 U 盘分为两个分区（第一个为 Ventoy 分区，第二个可用于存储数据）
3.  将 ISO 文件复制到 Ventoy 分区即可启动

`Rufus` 也提供 Linux 版本。


##### macOS 系统 {#macos-系统}

`balenaEtcher` （推荐）：
与 Windows 相同操作步骤。

`dd 命令` ：

```bash
sudo dd if=/path/to/endeavouros.iso of=/dev/diskN bs=4m status=progress
```

注意：使用 `diskutil list` 查看 U 盘编号。刻录完成后使用 `diskutil eject /dev/diskN` 弹出 U 盘。

| 工具         | 平台          | 难度 | 特点            |
|------------|-------------|----|---------------|
| Rufus        | Windows/Linux | 简单 | 轻量快速，支持多种分区方案 |
| balenaEtcher | Win/Mac/Linux | 简单 | 跨平台，界面简洁 |
| Ventoy       | Win/Mac/Linux | 简单 | 多 ISO 共存，无需反复刻录 |
| dd           | Linux/Mac     | 中等 | 命令行，高效    |


### 启动并进入安装环境 {#启动并进入安装环境}

加载 ISO 镜像后，系统会进入桌面环境。EndeavourOS 提供实时桌面环境，可以在安装前体验系统界面。
![](/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_11_07_40.png)

点击 <kbd>Start th Installer</kbd> 开始安装：
![](/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_11_07_52.png)
EndeavourOS 提供两种安装方式：

-   `在线安装` — 使用最新的软件包和桌面环境
-   `离线安装` — 使用预打包的系统镜像

选择「在线安装」可以获得最新的系统体验。

![](/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_11_08_00.png)
稍等片刻会出现如下的欢迎界面：
![](/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_11_08_31.png)
选择美式英语，如果选择简体中文，后续的一些目录啥的都会自动设置成中文，后续命令行的操作会比较麻烦，这里就先设置成英语，
后面安装简体中文字体就可以正常显示中文：
![](/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_11_08_40.png)
在此选择时区为上海。
![](/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_11_08_51.png)
选择键盘
![](/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_11_09_01.png)
EndeavourOS 支持多种桌面环境，包括：

-   GNOME — 现代简洁的界面
-   KDE Plasma — 功能丰富的可定制桌面
-   XFCE — 轻量级，适合老旧硬件
-   Cinnamon — 类似 Windows 的操作体验
-   其他桌面环境...

根据个人喜好和硬件配置选择合适的桌面环境。

这里选择 桌面环境，这里选择轻量级的 Xfce4

![](/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_11_09_17.png)
选择需要安装的软件包
![](/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_11_09_24.png)
选择启动器
![](/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_11_09_36.png)
设置硬盘，这里简化操作，选择整个硬盘都用来安装系统，你可以根据实际情况做分区。
![](/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_11_09_55.png)
设置账号和密码。
![](/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_11_10_03.png)
最后确认相关的信息，然后按 <kbd>Install</kbd> 确认安装。
![](/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_11_10_08.png)
点击 <kbd>Install Now</kbd> 进行安装。
![](/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_11_10_14.png)
这里会显示安装的进度，稍等回来确认是否安装完成。

![](/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_13_13_54.png)
这里显示安装完成，把 U 盘取出，勾选 <kbd>Restart now</kbd> ，然后点击 <kbd>Done</kbd> 。


### 安装完成 {#安装完成}

{{< figure src="/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_14_06_57.png" >}}

重新启动后的界面如图。

{{< figure src="/content-org/windows/EndeavourOS.org/VirtualBox_ArchLinux_13_05_2026_13_26_45.png" >}}

登录系统后界面如图示。


## 安装后配置 {#安装后配置}


### 更新系统 {#更新系统}

```bash
sudo pacman -Syu
```


### 使用 stow 管理配置文件 {#使用-stow-管理配置文件}

`stow` 是一个 GNU 项目，用于通过符号链接的方式将配置文件（dotfiles）从统一目录管理起来，广泛用于在多台机器间同步配置。


#### 什么是 stow {#什么是-stow}

stow 的核心理念是将所有 dotfile 集中放在一个仓库目录中（如 =~/.dotfiles=），然后通过符号链接将文件分发到它们应该在的位置。这样只需一个 git 仓库就能管理所有配置，新机器上 clone 下来跑一条命令即可完整恢复。


#### stow 的优势 {#stow-的优势}

-   `备份简单` — 一个 git 仓库包含所有配置
-   `迁移便捷` — 新机器 clone 后运行 `stow` 即可自动链接
-   `版本控制` — 所有配置文件纳入 git，方便追踪修改历史
-   `原子操作` — stow/unstow 可以随时切换，不影响原始文件
-   `跨发行版通用` — home 目录下的配置文件在不同系统间大多通用


#### 安装 stow {#安装-stow}

在 Arch/EndeavourOS 上：

```bash
sudo pacman -S stow
```


#### 目录结构 {#目录结构}

推荐使用如下目录结构：

```text
~/.dotfiles/
├── bash/
│   └── .bashrc
├── vim/
│   └── .vimrc
├── git/
│   └── .gitconfig
├── tmux/
│   └── .tmux.conf
└── nvim/
    └── config/
        └── init.lua
```

每个子目录对应一个"软件包"（package），stow 会将该目录内的文件链接到上级目录（即 =~/=）。


#### 基本操作 {#基本操作}

```bash
cd ~/.dotfiles

stow bash         # 将 bash/ 下的文件链接到 ~
stow git vim nvim # 同时链接多个包
stow -R bash      # 重新链接（配置文件有更新时）
stow -D bash      # 删除 bash 的符号链接（取消管理）
stow -D *         # 取消所有符号链接
stow --adopt      # 将现有文件替换为符号链接（谨慎使用）
```

`--adopt` 选项会强制用符号链接替换当前目录下的文件，适用于接管已有的配置文件。


#### 使用前注意事项 {#使用前注意事项}

stow 在执行时会检查目标文件是否已存在。如果目标位置已有文件（非 stow 创建的符号链接），stow 会报错，不会覆盖。此时需要手动处理：

1.  如果是旧配置文件，先备份：
    ```bash
       mv ~/.bashrc ~/.bashrc.bak
    ```
2.  然后再执行 stow。
3.  对比新旧配置的差异，确保没有遗漏重要设置。


#### 完整流程示例 {#完整流程示例}

以管理 `.bashrc` 为例：

1.  创建目录结构：
    ```bash
       mkdir -p ~/.dotfiles/bash
    ```
2.  将现有的 `~/.bashrc` 移入仓库：
    ```bash
       mv ~/.bashrc ~/.dotfiles/bash/.bashrc
    ```
3.  初始化 git 仓库并提交：
    ```bash
       cd ~/.dotfiles
       git init
       git add .
       git commit -m "feat: initial dotfiles"
    ```
4.  执行 stow：
    ```bash
       stow bash
    ```
5.  验证链接是否正确：
    ```bash
       ls -la ~/.bashrc
       # 输出类似：.bashrc -> /home/user/.dotfiles/bash/.bashrc
    ```

在新机器上：

```bash
git clone https://github.com/yourname/dotfiles.git ~/.dotfiles
cd ~/.dotfiles
stow bash git vim tmux nvim
```


#### 配合版本控制 {#配合版本控制}

建议将 `~/.dotfiles` 托管到 GitHub/Gitee：

```bash
cd ~/.dotfiles
git remote add origin https://github.com/yourname/dotfiles.git
git push -u origin master
```

使用私有仓库可以保护包含敏感信息（如 `.gitconfig` 中的用户名/邮箱）的文件。


#### 常见问题 {#常见问题}

-   `stow 报 "existing target is not a symlink"` ：目标文件已存在，先手动移走或备份
-   `符号链接指向错误路径` ：检查是否在 `~/.dotfiles` 目录下执行 stow
-   `某些目录无法链接` ：有些软件会自己创建目录，确保目标父目录存在后再 stow


### Docker {#docker}


### 常用软件安装 {#常用软件安装}

```bash
yay -S visual-studio-code-bin    # VS Code
yay -S google-chrome            # Chrome 浏览器
yay -S netease-cloud-music      # 网易云音乐
yay -S wps-office               # WPS Office
```


## 常见问题 {#常见问题}


### VirtualBox 中无法识别 USB 设备 {#virtualbox-中无法识别-usb-设备}

确保已安装 VirtualBox 扩展包，并在虚拟机设置中启用 USB 控制器。


### 屏幕分辨率异常 {#屏幕分辨率异常}

安装 `virtualbox-guest-utils` 和 `virtualbox-guest-drivers` 包。

```bash
sudo pacman -S virtualbox-guest-utils
sudo systemctl enable vboxservice
sudo systemctl start vboxservice
```


### 网络连接问题 {#网络连接问题}

检查 NetworkManager 服务状态：

```bash
sudo systemctl status NetworkManager
sudo systemctl restart NetworkManager
```
