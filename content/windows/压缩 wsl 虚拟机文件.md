---
title: "压缩 WSL 虚拟机文件"
date: 2026-06-03
lastmod: 2026-06-03T15:15:52+08:00
tags: ["WSL"]
draft: false
---

用了一段时间后，WSL 虚拟机文件不断的膨胀。

使用如下的命令行可以进行压缩：

```bash
diskpart
# 选中 vhdx 文件;
select vdisk file="D:\VirtualBoxVMs\WSL\Arch\ext4.vhdx"
# 以只读模式附加;
attach vdisk readonly
# 开始压缩;
compact vdisk
# 压缩完成后分离;
detach vdis
# 退出 Diskpart;
exit
```
