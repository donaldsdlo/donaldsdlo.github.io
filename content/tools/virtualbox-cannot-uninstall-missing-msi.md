---
title: "无法删除或重装VirtualBox，提示缺少msi安装包"
author: ["Donald Lo"]
date: 2026-05-08
lastmod: 2026-08-29T11:25:00+08:00
tags: ["Windows", "VirtualBox"]
draft: false
---

<div class="ox-hugo-toc toc">

<div class="heading">&#30446;&#24405;</div>

- [问题背景](#问题背景)
- [解决方案](#解决方案)
    - [操作步骤](#操作步骤)
        - [步骤1：下载对应版本的.exe 安装包](#步骤1-下载对应版本的-dot-exe-安装包)
        - [步骤2：使用命令行提取MSI文件](#步骤2-使用命令行提取msi文件)
        - [步骤3：找到MSI文件](#步骤3-找到msi文件)
        - [步骤4：完成卸载或修复](#步骤4-完成卸载或修复)
- [总结](#总结)

</div>
<!--endtoc-->



## 问题背景 {#问题背景}

在日常使用中，有时候VirtualBox可能会出现问题，需要卸载后重新安装。然而，当你尝试卸载或修复VirtualBox时，可能会遇到一个令人头疼的错误： **找不到msi安装包** 。

具体报错信息如下：

> 单击"确定"重试，或在下面的框中输入包含安装程序包 <kbd>VirtualBox-7.2.4-r170995-MultiArch_amd64.msi</kbd> 的文件夹的路径。

这个问题通常发生在：

-   VirtualBox 之前的安装不完整或损坏
-   某些安装文件被误删
-   通过第三方工具清理后残留注册表信息


## 解决方案 {#解决方案}

从报错信息中我们可以看到，系统需要的是 `.msi` 格式的安装包文件，但当我们从 [VirtualBox官网](https://www.virtualbox.org/wiki/Download_Old_Builds_7_2) 下载旧版本时，下载的文件是 `.exe` 格式的，而不是 `.msi` 格式的。

那么如何从 `.exe` 文件中提取出 `.msi` 文件呢？答案就是使用VirtualBox自带的解压功能。


### 操作步骤 {#操作步骤}


#### 步骤1：下载对应版本的.exe 安装包 {#步骤1-下载对应版本的-dot-exe-安装包}

首先，从VirtualBox官网下载与你当前版本匹配的 `.exe` 安装包。注意版本号要完全一致，否则即使提取了MSI也可能无法正常使用。

下载地址：<https://www.virtualbox.org/wiki/Download_Old_Builds_7_2>


#### 步骤2：使用命令行提取MSI文件 {#步骤2-使用命令行提取msi文件}

打开命令提示符（CMD）或PowerShell，然后执行以下命令：

```bash
VirtualBox-7.2.4-170995-Win.exe -x -p temp
```

其中：

-   `-x` ：表示Extract（解压）模式
-   `-p temp` ：指定解压到的文件夹名称为 `temp`

执行后，你会看到以下界面，选择要解压的组件（可以全选），然后点击Extract开始解压：

{{< figure src="/content-org/windows/无法删除或重装VirtualBox，提示缺少msi安装包.org/2026-05-08_13-03-47_screenshot.png" width="90%" >}}


#### 步骤3：找到MSI文件 {#步骤3-找到msi文件}

解压完成后，进入刚才指定的 `temp` 文件夹，你会在其中找到所需的 `.msi` 文件以及其他必要的组件：

{{< figure src="/content-org/windows/无法删除或重装VirtualBox，提示缺少msi安装包.org/2026-05-08_13-04-06_screenshot.png" width="90%" >}}


#### 步骤4：完成卸载或修复 {#步骤4-完成卸载或修复}

现在回到最初弹出错误的对话框，将路径指向你刚刚解压出来的文件夹。系统会自动找到所需的 `.msi` 文件，然后你就可以顺利完成VirtualBox的卸载或修复操作了。


## 总结 {#总结}

这个问题的根本原因在于Windows安装程序需要原始的MSI安装文件来进行维护操作。由于我们从官网下载的是自解压的 `.exe` 文件，而不是直接的MSI包，所以需要先用 `-x` 参数将其解压。

这个技巧不仅适用于VirtualBox，也适用于其他遇到类似MSI缺失问题的场景。下次遇到类似问题时，记得试试这个方法！
