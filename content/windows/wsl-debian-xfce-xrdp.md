---
title: "WSL Debian XFCE with XRDP"
author: ["Donald Lo"]
date: 2026-01-28
lastmod: 2026-01-28T16:21:11+08:00
tags: ["WSL", "XRDP"]
draft: false
---

<div class="ox-hugo-toc toc">

<div class="heading">&#30446;&#24405;</div>

- [安装 WSL Debian](#安装-wsl-debian)
- [查看安装的 Debian 的版本](#查看安装的-debian-的版本)
- [替换国内源](#替换国内源)
- [安装 XFCE 桌面](#安装-xfce-桌面)
- [安装 Dbus](#安装-dbus)
- [安装 XDRP](#安装-xdrp)
- [在 Windows 中使用 Remote Desktop Connection 来连接桌面](#在-windows-中使用-remote-desktop-connection-来连接桌面)

</div>
<!--endtoc-->

之前都是使用虚拟机来安装 Linux 系统，使用 WSL 安装 Linux 系统确实比较方便，安装上桌面以后也可以达到
以前虚拟机的功能：


## 安装 WSL Debian {#安装-wsl-debian}

通过以下点命令来安装：

```shell
wsl --install -d debian --name debian --location D:\VirtualBoxVMs\WSL\Debian
```

```shell
正在下载: Debian GNU/Linux
正在安装: Debian GNU/Linux
已成功安装分发。可以通过 “wsl.exe -d debian” 启动它
正在启动 debian...
Please create a default UNIX user account. The username does not need to match your Windows username.
For more information visit: https://aka.ms/wslusers
Enter new UNIX username:
```

中间会提醒输入新的账号：

```shell
Enter new UNIX username: donald
New password:
Retype new password:
passwd: password updated successfully
usermod: no changes
```

输入新的账号以及输入两次密码后安装完成。


## 查看安装的 Debian 的版本 {#查看安装的-debian-的版本}

```shell
donald@DESKTOP-92CHCK7:/mnt/d$ cat /etc/os-release
```

```shell
PRETTY_NAME="Debian GNU/Linux 13 (trixie)"
NAME="Debian GNU/Linux"
VERSION_ID="13"
VERSION="13 (trixie)"
VERSION_CODENAME=trixie
DEBIAN_VERSION_FULL=13.0
ID=debian
HOME_URL="https://www.debian.org/"
SUPPORT_URL="https://www.debian.org/support"
BUG_REPORT_URL="https://bugs.debian.org/"
```

从上面都输出可以看出安装都是 13 版本：


## 替换国内源 {#替换国内源}

先备份老大配置文件：

```shell
sudo cp /etc/apt/sources.list /etc/apt/sources.list.backup
```

在如下的网址中 <https://mirrors.tuna.tsinghua.edu.cn/help/debian/> ，安装图中 1,2 标示的选项后，将 3 中的
文本复制出来。

{{< figure src="/images/wsl-debian-xfce-xrdp.org/2026-01-28_16-06-22_screenshot.png" width="90%" >}}

通过以下命令修改文件内容：

```shell
sudo vi /etc/apt/sources.list
```

先删除其中的所有内容，然后把上面网址中的内容（我把 https 改成了 http）粘贴到这个文件并保存，然后执行以下命令：

```shell
sudo apt update
sudo apt upgrade
```


## 安装 XFCE 桌面 {#安装-xfce-桌面}

```shell
sudo apt install xfce4 xfce4-goodies
```


## 安装 Dbus {#安装-dbus}

```shell
sudo apt install -y dbus dbus-x11
```


## 安装 XDRP {#安装-xdrp}

```shell
sudo apt install xrdp
```

执行如下命令来修改配置文件：

```shell
sudo cp /etc/xrdp/xrdp.ini /etc/xrdp/xrdp.ini.bak
sudo sed -i 's/3389/3390/g' /etc/xrdp/xrdp.ini
sudo sed -i 's/max_bpp=32/#max_bpp=32\nmax_bpp=128/g' /etc/xrdp/xrdp.ini
sudo sed -i 's/xserverbpp=24/#xserverbpp=24\nxserverbpp=128/g' /etc/xrdp/xrdp.ini
```

将账号添加到 Group 中：

```shell
sudo usermod -a -G ssl-cert xrdp
```


## 在 Windows 中使用 Remote Desktop Connection 来连接桌面 {#在-windows-中使用-remote-desktop-connection-来连接桌面}

localhost:3390

{{< figure src="/images/wsl-debian-xfce-xrdp.org/2026-01-28_16-11-55_screenshot.png" width="90%" >}}

{{< figure src="/images/wsl-debian-xfce-xrdp.org/2026-01-28_16-13-13_screenshot.png" width="90%" >}}

输入账号和密码后回车：

{{< figure src="/images/wsl-debian-xfce-xrdp.org/2026-01-28_16-13-54_screenshot.png" width="90%" >}}
