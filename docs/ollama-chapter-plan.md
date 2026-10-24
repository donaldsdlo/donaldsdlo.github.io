# dev-envs.org 新增章节规划：Windows 下的 Ollama

目标文件：`content-org/tools/dev-envs.org`（追加到文件末尾，即 `* Python 环境安装和配置` 之后）
章节定位：一级章节 `* Ollama-本地大模型运行环境`
预估篇幅：约 320-380 行 org 源码（含 3 张表格、约 14 个代码块、6 张截图）

---

## 0. 范围裁决（先解决冲突）

你选了"命令行到 API"深度，同时勾选了 Emacs / Open WebUI / VS Code 三个集成端。
按原骨架两者不可兼得，本规划采用如下化解方式，**只此一处需你确认**：

| 项 | 处理 |
|----|------|
| 集成端 | **折叠为一个二级章节 `** 接入其他工具`**，下挂三个三级小节，各 20-30 行 |
| Open WebUI | 只给一条 `docker run` 命令 + `OLLAMA_BASE_URL` 说明，**不展开 Docker Desktop / WSL2 安装**（那是另一个大坑，单独成文更合适） |
| Emacs | 只给 gptel 一段 `use-package` 配置 + 一条 `M-x gptel` 用法；ellama 仅列出包名与用途，不写完整配置 |
| VS Code | Continue 只给 `config.json` 里的 `models` 片段；Cline 一句话带过 |

其余部分严格保持"命令行到 API"的深度。

---

## 1. 章节结构（org 大纲）

```
* Ollama-本地大模型运行环境
** 为什么用 Ollama
** 安装
*** 系统要求
*** 方式一：官方安装器（推荐）
*** 方式二：scoop（仅 CLI）
*** 验证安装
** 把模型目录迁到 D 盘
** 模型选型：按显存分档
** 常用命令
** 环境变量调优
** 调用 REST API
** 接入其他工具
*** Emacs：gptel
*** Open WebUI（Docker）
*** VS Code：Continue
** 排错
** 卸载与清理
```

一级章节命名沿用全文习惯：`* Scoop 方便的软件安装工具`、`* Powershell`、`* MSYS2`、`* Python 环境安装和配置`——都是"工具名 + 短说明"的形式。

---

## 2. 逐节内容规格

### `** 为什么用 Ollama`
一段导语 + 一张 3 列对比表，回答"为什么不用云端 API / LM Studio / llama.cpp"。

| 方案 | 界面 | 模型来源 | 本地 API | 说明 |
|------|------|----------|----------|------|
| Ollama | 托盘 + 命令行 | ollama.com library（curated tag） | 是，`localhost:11434` | 一条命令跑起来，开发者友好 |
| LM Studio | 完整图形界面 | 应用内搜 Hugging Face | 是，需手动开 server | 适合不想碰终端的人；模型各自存一份，磁盘翻倍 |
| 云端 API | —— | —— | 否 | 要联网、要付费、数据出本机 |

一句话点明 Ollama 的核心价值：**模型权重不出本机、离线可用、对外暴露一个稳定的 OpenAI 风格 REST 端口**。

### `** 安装`
- 系统要求（列表）：Windows 10 22H2+（Home/Pro）；NVIDIA 驱动 452.39+ 或 AMD Radeon 最新驱动；程序本体 ≥ 4GB，模型另算。
- 方式一（官方安装器）：

```powershell
# 命令行安装（等效于下载 OllamaSetup.exe）
irm https://ollama.com/install.ps1 | iex

# 或已下载安装包时，指定安装目录
OllamaSetup.exe /DIR="D:\Programs\Ollama"
```

说明三点：不需要管理员权限；默认装到用户目录；装完自动后台运行、托盘出现羊驼图标。
- 方式二（scoop）：

```powershell
scoop install main/ollama
```

**必须写清差异**：scoop 版只有 CLI，没有托盘 GUI、不会后台自启，用之前要自己 `ollama serve`；全文其他软件一律 scoop，这里破例，理由见 ADR 0001。
- 验证：`ollama --version`、`ollama list`（空列表而非报错即正常）。

### `** 把模型目录迁到 D 盘` ← 本章最高价值的一节
1. 说明默认位置 `C:\Users\<用户名>\.ollama\models`，7B/8B 模型约 5GB，几个模型就能吃掉 C 盘。
2. 设置用户变量（两条路都给，与前文"环境变量"章节呼应）：

```powershell
[Environment]::SetEnvironmentVariable("OLLAMA_MODELS", "D:\Ollama\Models", "User")
```

以及图形界面：设置 → 搜索"环境变量" → 编辑账户环境变量 → 新建 `OLLAMA_MODELS`。
3. **最大的坑，要单独加粗提示**：环境变量是 Ollama *启动时*读取的，改完必须右键托盘图标 Quit、再重新从开始菜单启动，否则不生效。
4. 迁移已有模型：先退出 Ollama，把旧目录的 `manifests` 和 `blobs` 剪到新目录。
5. 验证：拉一个 270MB 的小模型，确认文件真的落在 D 盘。

```powershell
ollama pull gemma3:270m
ollama list
```

### `** 模型选型：按显存分档` ← 第二高价值的一节
给出按显存/内存分档的表。**磁盘体积用实测值**（来源：Ollama registry manifest 汇总，采集于 2026-09-29），并在表下注明"再预留 20-30% 给上下文"。

| 档位 | 推荐标签 | 磁盘占用 | 备注 |
|------|----------|----------|------|
| 核显 / 纯 CPU，16GB 内存 | `qwen3:1.7b` / `gemma3:1b` / `qwen3:4b` | 1.4GB / 0.8GB / 2.5GB | 4B 在纯 CPU 上偏慢，只适合短问答 |
| 6-8GB 显存 | `qwen3:4b` / `gemma3:4b` / `qwen3:8b` | 2.5GB / 3.3GB / 5.2GB | 8B Q4 是甜点 |
| 12-16GB 显存 | `qwen3:14b` / `gemma3:12b` / `gpt-oss:20b` | 9.3GB / 8.1GB / 13.8GB | gpt-oss 擅长推理与 agent |
| 24GB 显存以上 | `qwen3:32b` / `gemma3:27b` / `qwen3-coder:30b` | 20.2GB / 17.4GB / 18.6GB | 编码场景优先 coder 系列 |

补充两张小表/两个提示：
- **量化**：默认下载的多为 Q4_K_M，但不保证——用 `ollama show <tag>` 看实际量化。Q8 体积翻倍而质量提升有限，本地场景 Q4 即可。
- **嵌入模型单独说**：做本地检索/RAG 用的不是聊天模型，`nomic-embed-text` 仅 274MB、`qwen3-embedding:4b` 也可选。
- **许可证**：`ollama show` 会打印许可证；Gemma / Llama 是自定义许可，商用前要看清楚。

### `** 常用命令`
一个命令块 + 一张表：

```powershell
ollama run qwen3:4b          # 首次自动拉取并进入交互；/bye 退出
ollama pull qwen3:8b         # 只下载不进入交互
ollama list                  # 已下载的模型
ollama ps                    # 当前驻留在内存/显存的模型（看 Processor 列）
ollama show qwen3:8b         # 参数、量化、上下文、模板
ollama rm qwen3:8b           # 删除模型释放磁盘
ollama cp qwen3:4b my-qwen   # 复制一份用于自定义
```

交互内的斜杠命令列个小表：`/bye`、`/set parameter num_ctx 8192`、`/show`、`/?`。
再给一条带速度观测的调用：`ollama run qwen3:4b "..." --verbose`，解释 `eval rate` 约低于 15 tok/s 就该降一档。

### `** 环境变量调优`
一张表（默认值 + 建议值 + 作用）：

| 变量 | 默认 | 建议 | 作用 |
|------|------|------|------|
| `OLLAMA_HOST` | `127.0.0.1:11434` | 保持默认 | 监听地址；改 `0.0.0.0` 会暴露到局域网，需同时配防火墙 |
| `OLLAMA_MODELS` | `%HOMEPATH%\.ollama\models` | `D:\Ollama\Models` | 权重目录 |
| `OLLAMA_KEEP_ALIVE` | `5m` | 内存紧张改 `2m`，长对话改 `-1` | 模型空闲驻留时长 |
| `OLLAMA_NUM_PARALLEL` | `1` | 显存紧张保持 1 | 单模型并发请求数 |
| `OLLAMA_MAX_LOADED_MODELS` | `1`*(需核实)* | 显存小就设 1 | 同时加载的模型数 |
| `OLLAMA_DEBUG` | `0` | 排错时 `1` | 调试日志，看 `%LOCALAPPDATA%\Ollama\server.log` |

> 写作前必做：在实机上 `ollama --help` / 官方文档核对上表变量名与默认值，标 (需核实) 的两项若已移除就从表中删掉，不要凭记忆写。

### `** 调用 REST API`
三种调用方式各一段，PowerShell 用 `Invoke-RestMethod`（比 `Invoke-WebRequest` 干净）：

```powershell
(Invoke-RestMethod -Method POST -Uri http://localhost:11434/api/generate -Body (@{
    model = "qwen3:4b"; prompt = "为什么天空是蓝色的？"; stream = $false
} | ConvertTo-Json)).response
```

```bash
curl.exe -s http://localhost:11434/api/chat -d '{"model":"qwen3:4b","messages":[{"role":"user","content":"你好"}],"stream":false}'
```

```python
import requests
r = requests.post("http://localhost:11434/api/chat",
                  json={"model": "qwen3:4b",
                        "messages": [{"role": "user", "content": "你好"}],
                        "stream": False})
print(r.json()["message"]["content"])
```

要点：`/api/generate` 是单轮、`/api/chat` 是多轮消息数组；`stream` 默认 true，脚本里要显式关掉。
再补一句局域网访问：`OLLAMA_HOST=0.0.0.0:11434` + Windows 防火墙放行，并提示风险。

### `** 接入其他工具`
三个三级小节，各 20-30 行，均假定 Ollama 已在本机 11434 运行。

- `*** Emacs：gptel` — 一段 `use-package` + `:straight t` 配置，声明 ollama 后端与模型列表；`M-x gptel` 发起会话、`C-u M-x gptel` 换模型。ellama 只列出用途（摘要/改写/翻译的封装），不展开。
- `*** Open WebUI（Docker）` — 一条命令：

```bash
docker run -d -p 3000:8080 --add-host=host.docker.internal:host-gateway -v open-webui:/app/backend/data --name open-webui ghcr.io/open-webui/open-webui:main
```

关键一句：容器内访问宿主机 Ollama 要用 `http://host.docker.internal:11434`（WebUI 设置里填 `OLLAMA_BASE_URL`），`localhost` 在容器里指向容器自己。
- `*** VS Code：Continue` — 只给 `config.json` 的 models 片段：

```json
{ "models": [{ "title": "Qwen3 4B", "provider": "ollama", "model": "qwen3:4b" }] }
```

Cline 一句带过（设置里 provider 选 Ollama、填 Base URL）。

### `** 排错`
5-6 条，每条"现象 → 原因 → 命令"：
1. `ollama` 不是可识别的命令 → 安装后未重开终端。
2. 改了 `OLLAMA_MODELS` 但模型仍下到 C 盘 → 托盘没退出重启（与上文呼应，互相链接）。
3. 慢得离谱 → `ollama ps` 看 Processor 列是不是 100% CPU；NVIDIA 检查驱动版本 `nvidia-smi`。
4. 11434 端口被占 → `netstat -ano | findstr :11434` 找 PID。
5. 进度条显示方块 → 终端字体换成 Maple Mono NF CN 之类的 Nerd Font（与前文字体章节呼应）。
6. 下载中断/极慢 → `ollama pull` 支持断点续传，重试即可；不要手动删 blobs 目录。

### `** 卸载与清理`
设置 → 已安装应用卸载；**卸载程序不会删除 `OLLAMA_MODELS` 指向的模型**，需手动删——这条对"腾 C 盘"的读者很重要。

---

## 3. 截图清单（写作时补，统一放 `static/images/dev-envs.org/`）

命名沿用全文约定 `YYYY-MM-DD_HH-MM-SS_description.png`，插入时配：

```org
#+ATTR_ORG: :width 800
#+ATTR_HTML: :width 90%
[[file:../../static/images/dev-envs.org/2026-10-25_10-00-00_ollama-tray.png]]
```

| # | 位置 | 内容 |
|---|------|------|
| 1 | 安装 | 安装完成后的托盘羊驼图标 |
| 2 | 迁移模型目录 | 环境变量窗口里新建的 `OLLAMA_MODELS` |
| 3 | 常用命令 | `ollama list` 的实际输出 |
| 4 | 常用命令 | `ollama ps` 输出，圈出 Processor 列（GPU/CPU 占比） |
| 5 | Emacs 集成 | gptel 的一次真实会话 |
| 6 | Open WebUI | 浏览器里 `localhost:3000` 的界面 |

---

## 4. 写作规范检查清单（对照 AGENTS.md）

- [ ] 全篇 org 语法：标题 `*`，粗体/代码 `=xxx=`，链接 `[[url][text]]`
- [ ] 代码块统一 `#+begin_src powershell :exports code` / `#+begin_src bash :exports code` / `#+begin_src json :exports code`，与前文一致
- [ ] 表格用 org 表格（`|---+---|`）
- [ ] 图片路径以 `../../static/` 开头
- [ ] 不改文件头的 `#+HUGO_TAGS` / `#+DATE` 等 front matter
- [ ] 改完后用 Emacs `C-c C-e H H` 重新导出，检查 `content/tools/dev-envs.md`
- [ ] `hugo server -D` 预览无误后提交，commit message 用 `add: xxx` 格式

---

## 5. 术语统一（本章用词，避免同义混用）

| 统一用词 | 含义 | 避免 |
|----------|------|------|
| 模型标签（tag） | 形如 `qwen3:8b` 的完整标识 | 模型名、模型版本、镜像名 |
| 量化 | 权重的存储位宽，如 Q4_K_M | 压缩、精度、裁剪 |
| 上下文窗口 | `num_ctx`，决定一次能喂多少 token | 记忆长度、上下文长度（可并列一次后统一） |
| 驻留 | `OLLAMA_KEEP_ALIVE` 控制的内存保持时间 | 缓存时间 |
| 权重目录 | `OLLAMA_MODELS` 指向的目录 | 模型库、缓存目录 |
| 卸载到 GPU | 模型层被放到显存 | 加速、上显卡 |
| 嵌入模型 | 只做向量化、不做生成的模型 | 向量模型（可并列一次） |

---

## 6. 待你确认 / 待实机核实

1. **§0 的折叠方案**（集成端压成一个二级章节、Open WebUI 不展开 Docker）——唯一需要你点头的一处。
2. 环境变量表的两项（标"需核实"）要在实机上核对后再落笔。
3. 你的实际显卡型号/显存：决定"选型表"里要不要把你自己的机器写成一个具体例子（读者很吃这种"作者实测"细节）。
