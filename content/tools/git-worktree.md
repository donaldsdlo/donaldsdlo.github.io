---
title: "git worktree"
author: ["Donald Lo"]
date: 2026-08-29
lastmod: 2026-08-29T13:26:00+08:00
tags: ["git", "worktree"]
draft: false
---

<div class="ox-hugo-toc toc">

<div class="heading">&#30446;&#24405;</div>

- [引言](#引言)
- [git worktree 是什么](#git-worktree-是什么)
- [branch 与 worktree 的区别](#branch-与-worktree-的区别)
- [基础命令](#基础命令)
    - [创建](#创建)
    - [查看当前有哪些 worktree](#查看当前有哪些-worktree)
    - [删除与清理](#删除与清理)
- [痛点详解：自动下载的大文件](#痛点详解-自动下载的大文件)
    - [Node.js 的 node_modules](#node-dot-js-的-node-modules)
    - [Emacs 配置里自动下载的 package](#emacs-配置里自动下载的-package)
- [解决方案](#解决方案)
    - [第一步：确保依赖不进版本库](#第一步-确保依赖不进版本库)
    - [第二步：node_modules 共享](#第二步-node-modules-共享)
    - [第三步：Emacs 包共享](#第三步-emacs-包共享)
    - [第四步：用钩子自动建链（省心）](#第四步-用钩子自动建链-省心)
- [完整工作流示例](#完整工作流示例)
- [小结](#小结)

</div>
<!--endtoc-->



## 引言 {#引言}

最近在折腾一个比较棘手的项目时，我重新认识了 Git 的 `git worktree` 功能。
它允许你在多个独立目录中同时工作在多个分支上，而这些目录共享同一份底层的
仓库历史。

本文在其基础上，重点讨论一个原文没有覆盖、却在实际工程中非常关键的痛点：
当项目里充斥着大量「自动下载」的文件（例如 Node.js 的 `node_modules` 、
Emacs 配置里自动拉取的 package）时，worktree 会带来什么麻烦，又该如何化解。

之所以要单独聊这个，是因为 worktree 的本质就是「每个分支一个独立工作目录」。
一旦你为功能分支、热修分支各开一个 worktree，依赖目录就会被复制（或重新下载）
N 份——对动辄几百 MB 甚至上 GB 的 `node_modules` 、Emacs 包来说，这既是磁盘灾难，
也是时间黑洞。

> 核心理念： `git worktree` 解决的是「并行分支」的问题，而「依赖共享」需要额外的约定来配合。


## git worktree 是什么 {#git-worktree-是什么}

简单说，worktree 让你在不切换分支的前提下，为同一个仓库创建多个「工作目录」。
它们之间共享同一个 `.git` 对象数据库（object database），但各自拥有独立的工作区状态。

```text
~/Herd/
├── my-project/          # 主 worktree，分支 main
│   └── .git/            # 主 git 目录
├── my-project-feature/  # 链接 worktree，分支 feature/login-form
└── my-project-hotfix/   # 链接 worktree，分支 hotfix/payment-bug
```

注意：主 worktree 里是真正的 `.git/` 目录；而新创建的链接 worktree 里只有一个
`.git` \*文件\*（不是目录），它只是指向主仓库 `.git/worktrees/<name>/` 的指针。
这也是为什么依赖目录不会自动「共享」——它们根本不在 `.git` 里，而在各自的工作区中。


## branch 与 worktree 的区别 {#branch-与-worktree-的区别}

传统做法要在多个分支间来回，靠的是不断地 `git checkout` / `git switch` 和
`git stash` ，生产事故一打断就容易丢状态、找不着北。worktree 则给每个分支一个专属目录：

```bash
# 把已有分支建成一个 worktree
git worktree add ../my-project-feature feature-branch

# 或一步创建「新分支 + 新 worktree」
git worktree add -b new-feature ../my-project-new-feature
```

这样每个目录都能独立编辑、提交、推送，互不干扰。一个重要的限制是：
**同一个分支不能同时被多个 worktree 检出** 。这反而促成了一个清爽的映射——
「一个任务、一个分支、一个目录」，让你在大脑里始终知道自己在哪。


## 基础命令 {#基础命令}


### 创建 {#创建}

```bash
git worktree add -b feature/checkout ../shop-checkout   # 基于当前 HEAD 新建分支
git worktree add ../shop-hotfix hotfix/payment-fail     # 基于已存在的分支
git worktree add --detach ../shop-experiment            #  detached HEAD，纯实验
```


### 查看当前有哪些 worktree {#查看当前有哪些-worktree}

```bash
git worktree list
```

输出类似：

```text
/Users/barrd/Herd/shop                 66c16256 [main]
/Users/barrd/Herd/shop-checkout        0c8ba118 [feature/checkout]
/Users/barrd/Herd/shop-payment-hotfix  a16e4be2 [hotfix/payment-fail]
```


### 删除与清理 {#删除与清理}

```bash
git worktree remove ../my-project-feature   # 仅能删「干净」的 worktree（无未提交改动）
git worktree remove --force ../my-project-feature  # 强制删除（慎用）

git worktree prune            # 清理手动删目录后残留的元数据
git worktree prune --expire 7.days.ago   # 只清理 7 天前失效的元数据
```

`git worktree remove` 只会删工作目录， **不会** 删分支本身；主 worktree 也无法被它删除。


## 痛点详解：自动下载的大文件 {#痛点详解-自动下载的大文件}

当我们把工程实践搬进 worktree，真正的麻烦来了。下面两类依赖在个人项目里最常见。


### Node.js 的 node_modules {#node-dot-js-的-node-modules}

假设你的前端项目 `shop` 有一个 800MB 的 `node_modules` 。按上面方式开两个 worktree：

```text
~/Herd/
├── shop/             # node_modules: 800MB
├── shop-checkout/    # 需要再 npm install → 又 800MB
└── shop-payment-hotfix/  # 又 npm install → 再 800MB
```

`node_modules` 不在 `.git` 里，Git 不会帮你共享它。结果：

-   \*磁盘\*：N 个 worktree 就是 N × 800MB。
-   \*时间\*：每个 worktree 都要重新 `npm install` / `pnpm install` ，慢。
-   \*缓存一致性\*：改了某个依赖版本，要在每个 worktree 分别重装才同步。


### Emacs 配置里自动下载的 package {#emacs-配置里自动下载的-package}

Emacs 的包管理有两种典型形态，对 worktree 的「友好度」完全不同：

-   **straight.el** ：默认把仓库克隆与构建产物放在 `~/.emacs.d/straight/` ，
    这个目录在 `.emacs.d` **之外** 的仓库目录里（其实在 `.emacs.d` 内但不在你的
    工程 repo 内），因此天然跨 worktree 共享，几乎不用特殊处理。
-   **package.el (elpa) / quelpa / 手动配置** ：若你把 `package-user-dir` 指向工程
    仓库内部（例如 `./.emacs.d/elpa` ），或者你的 `.emacs.d` 本身就是用 worktree
    管理的 Git 仓库，那么每个 worktree 都会重新下载、编译几百个包；
    此外 `eln-cache` （原生编译缓存）、 `auto-save-list` 、 `tramp` 等自动生成的目录
    也会在各 worktree 里散落一份，既占空间又容易在合并时产生无意义冲突。


## 解决方案 {#解决方案}

思路只有一个： **让「会膨胀的自动下载内容」待在仓库之外，再用软链（symlink）挂回每个 worktree** 。
这样既不被 Git 跟踪，又能 N 个 worktree 共享同一份物理文件。


### 第一步：确保依赖不进版本库 {#第一步-确保依赖不进版本库}

工程级用 `.gitignore` ，本地私有忽略用 `.git/info/exclude` （不会被提交、不污染团队）：

```text
# .gitignore（提交给团队）
node_modules/
.elpa/
eln-cache/
auto-save-list/
```

```bash
# 仅本地的额外忽略，写进 .git/info/exclude 即可
echo "node_modules/" >> .git/info/exclude
```


### 第二步：node_modules 共享 {#第二步-node-modules-共享}

做法 A——集中安装 + 软链（最通用，不挑包管理器）：

```bash
# 1. 在一个统一位置装好依赖
mkdir -p ~/Herd/_shared/shop && cd ~/Herd/_shared/shop
npm install        # 只装这一次

# 2. 给每个 worktree 挂软链
cd ~/Herd/shop && ln -s ../_shared/shop/node_modules ./node_modules
cd ~/Herd/shop-checkout && ln -s ../_shared/shop/node_modules ./node_modules
```

做法 B——直接用 pnpm（推荐长期使用）：pnpm 有一个全局 store（ `~/.pnpm-store` ），
各 worktree 的 `node_modules` 只是指向 store 的硬链接，几乎不占额外空间，也不用你手动建链：

```bash
pnpm install   # 在每个 worktree 里跑即可，内容来自全局 store 的硬链
```

yarn 的 PnP（Plug'n'Play）模式同理，可以不生成 `node_modules` 目录，从根本上规避复制。


### 第三步：Emacs 包共享 {#第三步-emacs-包共享}

straight.el 基本不用动；如果你用的是 elpa/quelpa，或把 `.emacs.d` 本身用 worktree 管理，
请把包目录与缓存指到 repo 之外，或用软链共享：

```emacs-lisp
;; 把包目录放到仓库外（写进早期初始化的 early-init.el 或 init.el 顶部）
(setq package-user-dir (expand-file-name "~/.emacs.d/elpa-shared"))
(setq native-comp-eln-load-path
      (list (expand-file-name "~/.emacs.d/eln-cache-shared")))

;; 若 .emacs.d 用 worktree 管理，把自动生成目录软链到统一位置
(let ((shared-dir "~/.emacs.d/shared/"))
  (make-directory shared-dir t)
  (dolist (d '("auto-save-list" "tramp" "transient"))
    (let ((target (expand-file-name d shared-dir)))
      (make-directory target t)
      (set (intern (format "%s-directory" d)) target))))
```

当 `.emacs.d` 作为 Git 仓库开 worktree 时，记得把 `elpa/` 、 `eln-cache/` 、
`auto-save-list/` 写进该仓库的 `.gitignore` ，避免污染提交。


### 第四步：用钩子自动建链（省心） {#第四步-用钩子自动建链-省心}

每次 `git worktree add` 后手动建链很烦。可以加一个 `post-checkout` 钩子，
在新建 worktree 时自动软链共享依赖：

```bash
# .git/hooks/post-checkout
#!/usr/bin/env bash
# 参数：前一个 HEAD、新 HEAD、是否切换了分支(1)
prev=$1; new=$2; flag=$3
[ "$flag" = "1" ] || exit 0

# 仅当处于链接 worktree 时生效（主 worktree 跳过）
git rev-parse --is-inside-work-tree >/dev/null 2>&1 || exit 0

SHARED=~/Herd/_shared/shop
# 若 repo 根下有 node_modules 软链目标则建链
if [ -d "$SHARED/node_modules" ] && [ ! -e node_modules ]; then
  ln -s "$SHARED/node_modules" node_modules
  echo "[hook] 已为 worktree 链接共享 node_modules"
fi
```

```bash
chmod +x .git/hooks/post-checkout
```

注意： `.git/hooks/` 不被提交。若要团队共享，请把钩子放进仓库的 `scripts/` 并提供
`core.hooksPath` 配置：

```bash
git config core.hooksPath .githooks
```


## 完整工作流示例 {#完整工作流示例}

```bash
cd ~/Herd/shop                      # 主 worktree，main

# 1. 开功能 worktree（钩子会自动软链 node_modules）
git worktree add -b feature/checkout ../shop-checkout
cd ../shop-checkout
# node_modules 已是软链，直接开干

# 2. 生产事故！开热修 worktree
cd ~/Herd/shop
git worktree add -b hotfix/payment-fail ../shop-hotfix
cd ../shop-hotfix
# 在热修目录里修 bug、测试；功能分支的工作区原封不动

# 3. 热修完成，合并回 main
cd ~/Herd/shop && git checkout main
git merge hotfix/payment-fail
git push

# 4. 清理
cd ~/Herd/shop
git worktree remove ../shop-hotfix          # 删工作目录，分支保留
git worktree remove ../shop-checkout        # 功能做完也清理
git worktree prune                          # 顺手清掉残留元数据
```


## 小结 {#小结}

`git worktree` 非常适合「并行功能 + 突发热修」的场景，能显著减少上下文切换与
`git stash` 的焦虑。但请记住：它只共享 `.git` 里的历史， **不** 共享工作区里的依赖。
对于 `node_modules` 、Emacs 自动下载的 package 这类大体积自动生成内容，关键对策是：

1.  用 `.gitignore` / `.git/info/exclude` 把它们挡在版本库外；
2.  把它们放进仓库之外的统一目录，再用软链挂回各 worktree（或改用 pnpm / yarn PnP 这类「零复制」方案）；
3.  Emacs 优先用 `straight.el` ，或把 `package-user-dir` / `eln-cache` 指向 repo 外；
4.  用 `post-checkout` 钩子把建链过程自动化。

做到这几点，你就能既享受 worktree 的并行红利，又不至于被重复的依赖下载拖垮磁盘与时间。
