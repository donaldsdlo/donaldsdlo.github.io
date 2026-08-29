---
title: "OpenCode cannot access Hugging Face"
author: ["Donald Lo"]
date: 2026-04-15
lastmod: 2026-08-29T11:25:00+08:00
tags: ["Opencode"]
draft: false
---

在使用 Opencode 的时候碰到无法下载 <https://huggingface.co/Xenova/all-MiniLM-L6-v2/resolve/main/tokenizer_config.json> 这个文件都问题。
试了设置环境变量 HF_ENDPOINT 为	<https://hf-mirror.com> 然后重启 windows terminal 也没用，最后无奈，直接改 js 代码中等链接，才解决了这个
问题，不过更新和重新安装会导致需要重新修改代码：

```bash
PS D:\home\.cache\opencode\node_modules\@huggingface\transformers> fd . -t f -x sed -i 's|https://huggingface.co|https://hf-mirror.com|g'
```

在 windows 中我是通过 Listary 快速找到 huggingface 目录，然后执行命令进行修改到。
