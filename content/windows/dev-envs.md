+++
title = "windows 开发环境配置"
author = ["Donald Lo"]
date = 2026-01-15
lastmod = 2026-01-16T13:23:09+08:00
tags = ["windows", "dev"]
draft = false
+++

## 环境变量 {#环境变量}


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
scoop install git aria2 coreutils fzf grep gzip make ripgrep rga wget which
```


## Python 环境安装和配置 {#python-环境安装和配置}

采用 UV 来管理 python 版本和项目虚拟环境，安装 UV 软件：

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


## 测试数学公式 {#测试数学公式}

这是一个行内的数学公式： \\(n^2 = 10\\)

\\[ n + 1 = x + y \\]

这是末尾的字符。
