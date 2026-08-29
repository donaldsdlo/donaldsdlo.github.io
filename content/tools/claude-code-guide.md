---
title: "Claude Code 完整使用指南"
author: ["Donald Lo"]
date: 2026-07-03
lastmod: 2026-08-29T11:27:00+08:00
tags: ["claude-code", "AI", "coding"]
draft: false
---

<div class="ox-hugo-toc toc">

<div class="heading">&#30446;&#24405;</div>

- [Claude Code 在各系统的安装](#claude-code-在各系统的安装)
    - [macOS / Linux / WSL](#macos-linux-wsl)
    - [Windows 原生](#windows-原生)
    - [VS Code 扩展](#vs-code-扩展)
    - [桌面应用](#桌面应用)
    - [JetBrains 插件](#jetbrains-插件)
    - [更新与卸载](#更新与卸载)
- [使用 Claude Code 连接 DeepSeek](#使用-claude-code-连接-deepseek)
    - [方案一：使用 CCS（Claude Code Switch）](#方案一-使用-ccs-claude-code-switch)
    - [方案二：使用 CLIProxyAPI](#方案二-使用-cliproxyapi)
    - [方案三：手动配置代理](#方案三-手动配置代理)
- [使用 Claude Code 连接 GLM](#使用-claude-code-连接-glm)
    - [使用 CCS 连接 GLM](#使用-ccs-连接-glm)
    - [手动配置](#手动配置)
    - [注意事项](#注意事项)
- [使用 Claude Code 连接 Ollama](#使用-claude-code-连接-ollama)
    - [Ollama 安装](#ollama-安装)
    - [使用 CCS 连接 Ollama](#使用-ccs-连接-ollama)
    - [手动配置](#手动配置)
    - [实用建议](#实用建议)
- [通过 CLIProxyAPI 和 CCS 连接 Nvidia NIM](#通过-cliproxyapi-和-ccs-连接-nvidia-nim)
    - [什么是 CLIProxyAPI](#什么是-cliproxyapi)
    - [安装 CLIProxyAPI](#安装-cliproxyapi)
    - [什么是 CCS](#什么是-ccs)
    - [配置 Nvidia NIM](#配置-nvidia-nim)
    - [CCS 常用命令](#ccs-常用命令)
    - [Docker 快速启动](#docker-快速启动)
- [什么是 Skill？如何使用 Skill？](#什么是-skill-如何使用-skill)
    - [Skill 是什么](#skill-是什么)
    - [Skill 的存放位置](#skill-的存放位置)
    - [创建第一个 Skill](#创建第一个-skill)
    - [Skill 的 Frontmatter 字段](#skill-的-frontmatter-字段)
    - [代码和写作相关推荐 Skill](#代码和写作相关推荐-skill)
        - [内置 Skill](#内置-skill)
        - [社区代码 Skill](#社区代码-skill)
        - [写作 Skill](#写作-skill)
- [什么是 MCP？推荐几个 MCP Server](#什么是-mcp-推荐几个-mcp-server)
    - [MCP 是什么](#mcp-是什么)
    - [MCP Server 的安装方式](#mcp-server-的安装方式)
        - [远程 HTTP 服务器（推荐）](#远程-http-服务器-推荐)
        - [本地 stdio 服务器](#本地-stdio-服务器)
        - [管理 MCP 服务器](#管理-mcp-服务器)
    - [MCP Server 的作用域](#mcp-server-的作用域)
    - [推荐的 MCP Server](#推荐的-mcp-server)
        - [开发工具类](#开发工具类)
        - [办公协作类](#办公协作类)
        - [自建 MCP Server](#自建-mcp-server)
    - [OAuth 认证](#oauth-认证)
- [使用 Claude Code 构建一个完整的 Python 新项目](#使用-claude-code-构建一个完整的-python-新项目)
    - [启动 Claude Code](#启动-claude-code)
    - [给 Claude Code 下指令](#给-claude-code-下指令)
    - [Claude Code 生成的典型项目结构](#claude-code-生成的典型项目结构)
    - [继续迭代](#继续迭代)
    - [CLAUDE.md 的作用](#claude-dot-md-的作用)
    - [关键提示](#关键提示)
- [使用 Claude Code 修改一个现有的 Python 项目](#使用-claude-code-修改一个现有的-python-项目)
    - [打开现有项目](#打开现有项目)
    - [让 Claude Code 先了解项目](#让-claude-code-先了解项目)
    - [修 Bug](#修-bug)
    - [添加功能](#添加功能)
    - [重构](#重构)
    - [代码审查](#代码审查)
    - [修改现有项目的最佳实践](#修改现有项目的最佳实践)
        - [先建 CLAUDE.md](#先建-claude-dot-md)
        - [小步修改](#小步修改)
        - [检查 diff](#检查-diff)
        - [善用 `--resume`](#善用-resume)
        - [用 Skill 封装重复操作](#用-skill-封装重复操作)
- [总结](#总结)

</div>
<!--endtoc-->

2025 年 Anthropic 发布了 Claude Code——一个运行在终端里的 AI 编程助手。它不是浏览器里聊天的 Claude，而是能读代码、改文件、跑命令的 Agent。你告诉它「把登录模块的密码校验逻辑修一下」，它读完代码，找到位置，改好，跑测试，把结果告诉你。

Claude Code 的核心思路：你不写代码，你指挥一个懂代码的 Agent 写。它读整个仓库，理解上下文，跨文件操作，执行 shell 命令，提交 git commit。它不是补全工具，是协作者。


## Claude Code 在各系统的安装 {#claude-code-在各系统的安装}

Claude Code 支持多平台安装：macOS、Linux、WSL、Windows 原生、VS Code 扩展、桌面应用和 JetBrains 插件。


### macOS / Linux / WSL {#macos-linux-wsl}

打开终端，一条命令：

```bash
curl -fsSL https://claude.ai/install.sh | bash
```

安装完成后，在任意项目目录启动：

```bash
cd your-project
claude
```

首次启动会要求登录。登录后即可使用。

macOS 还可以用 Homebrew 安装：

```bash
brew install --cask claude-code
```

`claude-code` 跟踪稳定版本，大约落后一周。 `claude-code@latest` 跟踪最新版本。


### Windows 原生 {#windows-原生}

PowerShell：

```powershell
irm https://claude.ai/install.ps1 | iex
```

CMD：

```batch
curl -fsSL https://claude.ai/install.cmd -o install.cmd && install.cmd && del install.cmd
```

也可以用 WinGet：

```powershell
winget install Anthropic.ClaudeCode
```

建议安装 Git for Windows，这样 Claude Code 能用 Bash 工具。没有 Git for Windows 的话，Claude Code 会用 PowerShell 作为 shell 工具。


### VS Code 扩展 {#vs-code-扩展}

在 VS Code 扩展市场搜索 "Claude Code" 安装，或直接用命令：

-   打开扩展视图（ `Ctrl+Shift+X` ）
-   搜索 "Claude Code"
-   安装后，打开命令面板（ `Ctrl+Shift+P` ），输入 "Claude Code"，选择 **Open in New Tab**


### 桌面应用 {#桌面应用}

独立应用，不需要在 IDE 或终端里运行。支持视觉 diff 审查、多会话并行、定时任务。

下载地址：

-   macOS：Intel 和 Apple Silicon
-   Windows：x64 和 ARM64

安装后启动 Claude，登录，点击 **Code** 标签页即可。


### JetBrains 插件 {#jetbrains-插件}

支持 IntelliJ IDEA、PyCharm、WebStorm 等。从 JetBrains Marketplace 安装 Claude Code 插件，重启 IDE。插件需要单独安装 Claude Code CLI。


### 更新与卸载 {#更新与卸载}

原生安装自动后台更新。Homebrew 和 WinGet 安装需要手动：

```bash
brew upgrade claude-code
winget upgrade Anthropic.ClaudeCode
```


## 使用 Claude Code 连接 DeepSeek {#使用-claude-code-连接-deepseek}

DeepSeek 是国产大模型中的佼佼者，尤其 DeepSeek-V3 和 DeepSeek-R1 在代码生成上表现突出。Claude Code 支持通过 `ANTHROPIC_BASE_URL` 指向第三方 OpenAI 兼容 API，但直接连接 DeepSeek 存在格式不兼容问题——Claude Code 发送 Anthropic 格式请求，DeepSeek 接收 OpenAI 格式。

解决方案有两条路。


### 方案一：使用 CCS（Claude Code Switch） {#方案一-使用-ccs-claude-code-switch}

CCS 是社区开发的多提供商管理工具，内置格式转换代理，能自动把 Anthropic 格式的请求翻译成 OpenAI 格式发给 DeepSeek。

安装：

```bash
npm install -g @kaitranntt/ccs
ccs config
```

配置 DeepSeek 提供商：

```bash
ccs api create --preset deepseek
```

启动 DeepSeek 会话：

```bash
ccs deepseek
```

CCS 会启动本地代理，监听 Anthropic 兼容端点，将请求翻译后转发给 DeepSeek API。


### 方案二：使用 CLIProxyAPI {#方案二-使用-cliproxyapi}

CLIProxyAPI 是另一个代理工具，支持格式转换和多账号轮询。详见后文 [通过 CLIProxyAPI 和 CCS 连接 Nvidia NIM](#通过-cliproxyapi-和-ccs-连接-nvidia-nim) 章节。


### 方案三：手动配置代理 {#方案三-手动配置代理}

如果你有自己的格式转换代理（比如 LiteLLM），可以直接设置环境变量：

```bash
export ANTHROPIC_BASE_URL=http://localhost:4000  # 你的代理地址
export ANTHROPIC_API_KEY=your-deepseek-api-key
export ANTHROPIC_MODEL=deepseek-chat
```

然后正常启动 `claude` 即可。

注意：直接把 `ANTHROPIC_BASE_URL` 指向 DeepSeek 官方 API（ `https://api.deepseek.com` ）不可行，因为 Claude Code 发送的是 Anthropic 格式，DeepSeek 无法解析。


## 使用 Claude Code 连接 GLM {#使用-claude-code-连接-glm}

GLM 是智谱 AI 的大模型系列，包括 GLM-4 等。连接思路和 DeepSeek 类似：需要一个格式转换层。


### 使用 CCS 连接 GLM {#使用-ccs-连接-glm}

CCS 内置了 GLM 预设：

```bash
ccs api create --preset glm
ccs glm
```

CCS 的本地代理会处理 Anthropic → OpenAI 格式转换，并把请求路由到智谱 API。


### 手动配置 {#手动配置}

如果你用自定义代理，设置环境变量：

```bash
export ANTHROPIC_BASE_URL=http://localhost:8080  # 代理地址
export ANTHROPIC_API_KEY=your-zhipu-api-key
export ANTHROPIC_MODEL=glm-4
```


### 注意事项 {#注意事项}

-   GLM API 的 base URL 通常是 `https://open.bigmodel.cn/api/paas/v4/`
-   直接指向此 URL 同样不可行，需要格式转换
-   智谱 API 的 key 格式与 Anthropic 不同，某些代理可能需要额外适配


## 使用 Claude Code 连接 Ollama {#使用-claude-code-连接-ollama}

Ollama 让你在本地跑大模型，数据不出机器。Claude Code 连接 Ollama 的核心问题还是格式：Ollama 暴露的是 OpenAI 兼容端点，Claude Code 发 Anthropic 格式。


### Ollama 安装 {#ollama-安装}

先装 Ollama：

```bash
# macOS / Linux
curl -fsSL https://ollama.com/install.sh | sh

# Windows
# 从 https://ollama.com/download 下载安装包
```

拉模型：

```bash
ollama pull llama3
ollama pull qwen2.5-coder
```

启动服务（默认端口 11434）：

```bash
ollama serve
```


### 使用 CCS 连接 Ollama {#使用-ccs-连接-ollama}

```bash
ccs api create --preset ollama
ccs ollama
```

CCS 启动本地代理，将 Anthropic 格式请求翻译为 OpenAI 格式，转发到 `http://localhost:11434` 。


### 手动配置 {#手动配置}

有代理层时：

```bash
export ANTHROPIC_BASE_URL=http://localhost:4000  # 代理地址
export ANTHROPIC_MODEL=llama3
```

Ollama 本地使用不需要 API key，但代理层可能需要配置。


### 实用建议 {#实用建议}

-   代码任务推荐 `qwen2.5-coder` 或 `deepseek-coder-v2` ，这些模型在代码生成上比通用模型好
-   本地模型的上下文窗口有限，不适合大仓库的深度操作
-   适合场景：离线开发、隐私敏感代码、快速问答


## 通过 CLIProxyAPI 和 CCS 连接 Nvidia NIM {#通过-cliproxyapi-和-ccs-连接-nvidia-nim}

Nvidia NIM（NVIDIA Inference Microservices）是 Nvidia 提供的模型推理服务，支持 Meta Llama、Mistral、NV-Embed 等模型。通过 CLIProxyAPI 和 CCS 可以让 Claude Code 使用 NIM 上的模型。


### 什么是 CLIProxyAPI {#什么是-cliproxyapi}

CLIProxyAPI（<https://github.com/router-for-me/CLIProxyAPI> ）是一个代理服务器，把 CLI 工具的请求包装成 OpenAI/Gemini/Claude 兼容的 API 接口。它支持：

-   Claude Code、Codex、Grok Build 的 OAuth 登录
-   多账号轮询负载均衡
-   流式和非流式响应
-   函数调用/工具支持


### 安装 CLIProxyAPI {#安装-cliproxyapi}

Docker 方式（推荐）：

```bash
# 下载 docker-compose.yaml
curl -fsSL https://raw.githubusercontent.com/router-for-me/CLIProxyAPI/main/docker-compose.yml -o docker-compose.yaml

# 启动
docker compose up -d
```

CLIProxyAPI 默认监听 `http://localhost:8317` 。

手动安装：从 GitHub Releases 下载对应平台的二进制文件。


### 什么是 CCS {#什么是-ccs}

CCS（Claude Code Switch，<https://github.com/kaitranntt/ccs> ）是基于 CLIProxyAPI 的多提供商管理器。它内置了 CLIProxyAPI 运行时，加上图形化仪表盘、提供商切换、配额监控等功能。

CCS 提供了 50+ 提供商预设，包括 Nvidia NIM。


### 配置 Nvidia NIM {#配置-nvidia-nim}

方法一：用 CCS 预设

```bash
# 安装 CCS
npm install -g @kaitranntt/ccs

# 配置
ccs config

# 创建 NIM 提供商配置
ccs api create --preset nim

# 启动
ccs nim
```

方法二：手动配置 CLIProxyAPI

编辑 CLIProxyAPI 的配置文件（ `config.yaml` ），添加 NIM 作为 OpenAI 兼容上游：

```yaml
providers:
  - name: nvidia-nim
    type: openai-compatible
    base_url: https://integrate.api.nvidia.com/v1
    api_key: your-nvidia-api-key
    models:
      - meta/llama-3.1-405b-instruct
      - nvidia/llama-3.1-nemotron-70b-instruct
```

然后在 Claude Code 中指向 CLIProxyAPI 代理：

```bash
export ANTHROPIC_BASE_URL=http://localhost:8317/v1
export ANTHROPIC_API_KEY=your-cliproxyapi-key
claude
```


### CCS 常用命令 {#ccs-常用命令}

```bash
ccs                      # 用默认 Claude 启动
ccs codex                # 用 OpenAI Codex 启动
ccs --target droid glm   # 用 GLM 启动
ccs ollama               # 用 Ollama 启动
ccs nim                  # 用 Nvidia NIM 启动
```


### Docker 快速启动 {#docker-快速启动}

```bash
curl -fsSL https://ccs.kaitran.ca/docker-compose.yaml -o docker-compose.yaml
docker compose up -d
```

仪表盘在 `http://localhost:3000` ，CLIProxyAPI 在 `http://localhost:8317` 。


## 什么是 Skill？如何使用 Skill？ {#什么是-skill-如何使用-skill}


### Skill 是什么 {#skill-是什么}

Skill 是 Claude Code 的扩展机制。你写一个 `SKILL.md` 文件，里面放指令，Claude Code 就多了一项能力。Skill 和 `CLAUDE.md` 的区别： `CLAUDE.md` 的内容每次会话都加载，Skill 的内容只在调用时加载——省 token。

什么时候该创建 Skill？当你发现自己反复粘贴同一段指令、检查清单、或多步骤流程到聊天里时，就该把它变成 Skill。


### Skill 的存放位置 {#skill-的存放位置}

| 位置 | 路径                                     | 适用范围 |
|----|----------------------------------------|------|
| 个人 | `~/.claude/skills/<skill-name>/SKILL.md` | 你的所有项目 |
| 项目 | `.claude/skills/<skill-name>/SKILL.md`   | 仅当前项目 |
| 插件 | `<plugin>/skills/<skill-name>/SKILL.md`  | 插件启用时 |


### 创建第一个 Skill {#创建第一个-skill}

创建目录：

```bash
mkdir -p ~/.claude/skills/summarize-changes
```

写 `SKILL.md` ：

```yaml
---
description: 总结未提交的变更并标记风险。当用户问改了什么、要生成 commit message、或要 review diff 时使用。
---

## 当前变更

!`git diff HEAD`

## 指令

用两三个要点总结上面的变更，然后列出你注意到的风险，比如缺少错误处理、硬编码值、需要更新的测试。如果 diff 为空，说没有未提交的变更。
```

``!=`git diff HEAD`!`` 这行是动态上下文注入：Claude Code 执行命令，把输出替换到 Skill 内容里，Claude 看到的是实际 diff 而不是命令。

使用：

-   让 Claude 自动触发：问「我改了什么？」
-   手动触发：输入 `/summarize-changes`


### Skill 的 Frontmatter 字段 {#skill-的-frontmatter-字段}

```yaml
---
name: my-skill
description: 这个 Skill 做什么
disable-model-invocation: true    # 只能手动调用，Claude 不会自动触发
user-invocable: false              # 只能 Claude 触发，用户不能 /name 调用
allowed-tools: Bash(git add *) Bash(git commit *)  # 预授权工具
context: fork                      # 在子 Agent 中运行
model: opus                        # 使用指定模型
---
```


### 代码和写作相关推荐 Skill {#代码和写作相关推荐-skill}


#### 内置 Skill {#内置-skill}

Claude Code 自带以下 Skill：

-   `/code-review` ：代码审查
-   `/debug` ：调试
-   `/batch` ：批量操作
-   `/loop` ：循环执行
-   `/claude-api` ：Claude API 相关
-   `/run` ：启动和驱动你的应用
-   `/verify` ：构建并验证代码变更


#### 社区代码 Skill {#社区代码-skill}

| Skill 名称             | 用途              | 安装方式                                                 |
|----------------------|-----------------|------------------------------------------------------|
| `code-review-expert`   | 专家级代码审查    | 插件市场安装                                             |
| `tdd-workflow`         | TDD 开发工作流    | 插件市场安装                                             |
| `systematic-debugging` | 系统化调试        | 插件市场安装                                             |
| `skill-creator`        | 创建新 Skill 的 Skill | `/plugin install skill-creator@claude-plugins-official`  |
| `mcp-server-dev`       | 构建 MCP 服务器   | `/plugin install mcp-server-dev@claude-plugins-official` |


#### 写作 Skill {#写作-skill}

| Skill 名称         | 用途      |
|------------------|---------|
| `article-writing`  | 长文写作  |
| `editor`           | 编辑和校对 |
| `content-creator`  | 博客和社交媒体内容 |
| `technical-writer` | 技术文档  |

安装插件方式的 Skill：

```text
/plugin install skill-creator@claude-plugins-official
/reload-plugins
```


## 什么是 MCP？推荐几个 MCP Server {#什么是-mcp-推荐几个-mcp-server}


### MCP 是什么 {#mcp-是什么}

MCP（Model Context Protocol）是 Anthropic 提出的开放标准，让 AI 工具能连接外部数据源和工具。通过 MCP，Claude Code 可以读取 Google Drive 里的设计文档、更新 Jira 里的任务、从 Slack 拉数据、查询数据库。

MCP 的核心思路：Claude Code 通过 MCP 服务器这个中间层，访问你的各种外部工具。你不用在聊天里手动复制粘贴数据，Claude Code 直接从源头获取。


### MCP Server 的安装方式 {#mcp-server-的安装方式}


#### 远程 HTTP 服务器（推荐） {#远程-http-服务器-推荐}

```bash
# 基本语法
claude mcp add --transport http <name> <url>

# 示例：连接 Notion
claude mcp add --transport http notion https://mcp.notion.com/mcp

# 带 Bearer Token
claude mcp add --transport http secure-api https://api.example.com/mcp \
  --header "Authorization: Bearer your-token"
```


#### 本地 stdio 服务器 {#本地-stdio-服务器}

```bash
# 示例：添加 Airtable 服务器
claude mcp add --env AIRTABLE_API_KEY=YOUR_KEY --transport stdio airtable \
  -- npx -y airtable-mcp-server
```

注意：stdio 服务器要用 `--` 分隔 Claude 的选项和服务器的参数。


#### 管理 MCP 服务器 {#管理-mcp-服务器}

```bash
claude mcp list           # 列出所有配置的服务器
claude mcp get github     # 查看特定服务器详情
claude mcp remove github  # 移除服务器
/mcp                      # 在 Claude Code 内查看状态
```


### MCP Server 的作用域 {#mcp-server-的作用域}

| 作用域 | 存储位置         | 共享方式 |
|-----|--------------|------|
| 本地 | `~/.claude.json` | 不共享   |
| 项目 | `.mcp.json`      | 通过版本控制共享 |
| 用户 | `~/.claude.json` | 跨项目可用 |


### 推荐的 MCP Server {#推荐的-mcp-server}


#### 开发工具类 {#开发工具类}

| Server     | 功能          | 安装命令                                                                                                                     |
|------------|-------------|--------------------------------------------------------------------------------------------------------------------------|
| GitHub     | PR、Issue、代码审查 | `claude mcp add --transport http github https://api.githubcopilot.com/mcp/ --header "Authorization: Bearer YOUR_GITHUB_PAT"` |
| Sentry     | 错误监控      | `claude mcp add --transport http sentry https://mcp.sentry.dev/mcp`                                                          |
| PostgreSQL | 数据库查询    | `claude mcp add --transport stdio db -- npx -y @bytebase/dbhub --dsn "postgresql://..."`                                     |
| Filesystem | 文件系统操作  | `claude mcp add --transport stdio filesystem -- npx -y @anthropic/mcp-server-filesystem /path/to/dir`                        |


#### 办公协作类 {#办公协作类}

| Server       | 功能   | 安装命令                                                            |
|--------------|------|-----------------------------------------------------------------|
| Notion       | 知识库和笔记 | `claude mcp add --transport http notion https://mcp.notion.com/mcp` |
| Slack        | 团队沟通 | 需要先在 claude.ai 配置                                             |
| Google Drive | 文档管理 | 需要先在 claude.ai 配置                                             |


#### 自建 MCP Server {#自建-mcp-server}

可以用官方插件脚手架：

```text
/plugin install mcp-server-dev@claude-plugins-official
/reload-plugins
/mcp-server-dev:build-mcp-server
```

Claude 会问你的使用场景，然后生成 HTTP 或 stdio 类型的服务器模板。


### OAuth 认证 {#oauth-认证}

很多云端 MCP Server 需要认证。Claude Code 支持 OAuth 2.0：

1.  添加需要认证的服务器
2.  在 Claude Code 里运行 `/mcp`
3.  按照浏览器登录流程完成认证

命令行也可以认证：

```bash
claude mcp login sentry      # 登录
claude mcp logout sentry     # 登出
```


## 使用 Claude Code 构建一个完整的 Python 新项目 {#使用-claude-code-构建一个完整的-python-新项目}

本节演示从零开始用 Claude Code 构建一个 Python Web 项目——一个简单的任务管理 API。


### 启动 Claude Code {#启动-claude-code}

```bash
mkdir task-api && cd task-api
claude
```


### 给 Claude Code 下指令 {#给-claude-code-下指令}

```text
请帮我创建一个 Python FastAPI 项目，实现一个任务管理 REST API。要求：
1. 使用 FastAPI 框架
2. 使用 SQLite 作为数据库（通过 SQLAlchemy）
3. 实现以下端点：
   - GET /tasks - 列出所有任务
   - POST /tasks - 创建任务
   - GET /tasks/{id} - 获取单个任务
   - PUT /tasks/{id} - 更新任务
   - DELETE /tasks/{id} - 删除任务
4. 包含 Pydantic 模型
5. 写好单元测试
6. 包含 requirements.txt 和 README.md
7. 初始化 git 仓库
```

Claude Code 会：

1.  创建项目结构
2.  写代码文件
3.  安装依赖
4.  跑测试
5.  初始化 git


### Claude Code 生成的典型项目结构 {#claude-code-生成的典型项目结构}

```text
task-api/
├── app/
│   ├── __init__.py
│   ├── main.py
│   ├── models.py
│   ├── schemas.py
│   ├── database.py
│   └── routers/
│       └── tasks.py
├── tests/
│   ├── __init__.py
│   └── test_tasks.py
├── requirements.txt
├── README.md
└── .gitignore
```


### 继续迭代 {#继续迭代}

创建好后，你可以继续给指令：

```text
给任务添加优先级字段，可以是 high、medium、low，默认 medium。更新所有相关代码和测试。
```

```text
添加分页支持，GET /tasks 支持 page 和 size 参数。
```

```text
提交当前的修改，commit message 要清晰。
```


### CLAUDE.md 的作用 {#claude-dot-md-的作用}

在项目根目录创建 `CLAUDE.md` ，写上项目规范，Claude Code 每次启动都会读：

```markdown
# Task API 项目规范

## 技术栈
- Python 3.11+
- FastAPI
- SQLAlchemy + SQLite
- Pytest

## 代码规范
- 使用 type hints
- 函数不超过 30 行
- 所有端点必须有对应的测试

## 测试
运行测试：pytest tests/
```


### 关键提示 {#关键提示}

-   **一次说清需求** ：Claude Code 能处理复杂指令，把要求一次列完比拆成多轮效率高
-   **验证再信任** ：生成的代码要跑测试，看结果，不要盲目用
-   **用 CLAUDE.md 约束** ：项目规范写进去，减少每次重复说明
-   **渐进式迭代** ：先搭骨架，再加功能，每次改动跑测试确认


## 使用 Claude Code 修改一个现有的 Python 项目 {#使用-claude-code-修改一个现有的-python-项目}

修改已有项目和创建新项目的区别在于：Claude Code 需要先理解现有代码。


### 打开现有项目 {#打开现有项目}

```bash
cd existing-python-project
claude
```


### 让 Claude Code 先了解项目 {#让-claude-code-先了解项目}

```text
先帮我分析一下这个项目的结构、技术栈和主要功能。
```

Claude Code 会读取项目文件，理解结构，给你一个概览。这一步很关键——它建立上下文，后续操作更准确。


### 修 Bug {#修-bug}

```text
用户报告了一个 bug：创建任务时，如果标题为空字符串，服务器返回 500 而不是 400。
请找到问题，修复，并添加测试防止回归。
```

Claude Code 会：

1.  定位到处理创建任务的代码
2.  找到缺少输入验证的地方
3.  添加验证逻辑
4.  写测试验证修复


### 添加功能 {#添加功能}

```text
给项目添加用户认证。使用 JWT token。需要：
1. 添加 User 模型
2. 添加注册和登录端点
3. 保护任务端点，只有认证用户才能访问
4. 每个用户只能看到自己的任务
5. 更新测试
```


### 重构 {#重构}

```text
把 tasks router 里的业务逻辑抽取到 service 层，遵循三层架构（router -> service -> database）。
保持所有现有测试通过。
```


### 代码审查 {#代码审查}

```text
审查最近三次 commit 的改动，指出潜在问题和改进建议。
```

或者直接用内置 Skill：

```text
/code-review
```


### 修改现有项目的最佳实践 {#修改现有项目的最佳实践}


#### 先建 CLAUDE.md {#先建-claude-dot-md}

在项目根目录写上关键信息，帮 Claude Code 快速理解项目：

```markdown
# 项目说明

## 架构
- FastAPI 应用
- 路由层：app/routers/
- 业务层：app/services/
- 数据层：app/models/

## 关键命令
- 跑测试：pytest tests/
- 启动开发服务器：uvicorn app.main:app --reload
- 代码格式化：black app/ tests/

## 注意事项
- 不要动 app/database.py，它由 DBA 维护
- 测试用 SQLite，生产用 PostgreSQL
```


#### 小步修改 {#小步修改}

每次只改一个东西，改完跑测试确认。不要一口气让 Claude Code 改十个文件——出了问题不好定位。


#### 检查 diff {#检查-diff}

每次改动后用 `/code-review` 或 `git diff` 看看 Claude Code 到底改了什么。


#### 善用 `--resume` {#善用-resume}

上次会话没做完？下次启动时恢复：

```bash
claude --resume
```


#### 用 Skill 封装重复操作 {#用-skill-封装重复操作}

如果你每次都要说「跑测试、格式化、提交」，把它变成 Skill：

```yaml
---
name: commit-safe
description: 跑测试、格式化、然后提交
disable-model-invocation: true
allowed-tools: Bash(pytest *) Bash(black *) Bash(git add *) Bash(git commit *)
---

1. 跑测试：pytest tests/
2. 格式化：black app/ tests/
3. 查看变更：git status
4. 暂存变更：git add -A
5. 提交：git commit -m "$ARGUMENTS"
```

使用： `/commit-safe fix: 修复空标题 500 错误`


## 总结 {#总结}

Claude Code 把 AI 从聊天框搬到了终端。它不是代码补全，是能读仓库、改文件、跑命令、提 PR 的 Agent。连接各种模型（DeepSeek、GLM、Ollama、NIM）需要格式转换代理，CCS 和 CLIProxyAPI 解决了这个问题。Skill 让你封装重复流程，MCP 让 Claude Code 连接外部工具。用好 CLAUDE.md，Claude Code 就不只是工具，是你的项目搭档。
