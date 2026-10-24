# Ollama 章节以官方安装器为主、scoop 仅作备选

dev-envs.org 全文的软件安装几乎一律用 `scoop install`（Scoop、winget、字体、VS Code、yt-dlp 等）。Ollama 章节破例：主推官方 `OllamaSetup.exe`，只在末尾补一行 `scoop install main/ollama` 并注明差异。

原因是 scoop 版只提供 CLI，没有托盘 GUI、不会随系统后台自启，用之前要手动 `ollama serve`；而本章后续内容（模型目录迁移要"退出托盘再重启"、`ollama ps` 看驻留）都建立在官方版的常驻服务之上。用 scoop 版会让读者卡在"命令能用但服务没起"。官方安装器同样无需管理员权限、同样装在用户目录，与本站"不污染系统"的取向并不冲突。

## Consequences

- 读者会问"为什么这里不 scoop"，因此文中必须显式写出差异，不能默默换工具。
- 后续若 scoop 的 ollama manifest 补齐了托盘/服务，本决定应重新评估。
