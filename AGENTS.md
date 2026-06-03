# AGENTS.md - Project Guide for donaldsdlo.github.io

## Project Overview

This is a personal blog website built with Hugo static site generator. Content is written in Emacs org-mode files and exported to Markdown using ox-hugo. The site uses the hugo-theme-stack theme and deploys automatically to GitHub Pages via GitHub Actions.

## Build/Lint/Test Commands

### Development Server

```bash
hugo server -D
hugo server -D --navigateToChanged
hugo server -D --buildFuture
```

### Build Commands

```bash
hugo
hugo -D
hugo --minify
```

### Clean Commands

```bash
rm -rf public
```

### Validation Commands

```bash
hugo config
hugo list all
```

## Content Management

### Directory Structure

- `.github/workflows/` - GitHub Actions CI/CD
- `content-org/` - Org source files (PRIMARY SOURCE)
- `content/` - Generated Markdown files (DO NOT EDIT)
- `static/images/` - Image assets
- `themes/` - Theme files (hugo-theme-stack)

### Content Workflow

1. Create/edit org files in `content-org/` directory
2. Export to Markdown using Emacs ox-hugo (`C-c C-e H H`)
3. Preview with `hugo server -D`
4. Commit and push - GitHub Actions handles deployment

## Code Style Guidelines

### Content Output Format

When creating or editing content in `.org` files, **always use org-mode format**:
- Headings: `*`, `**`, `***` (NOT `#`, `##`, `###`)
- Bold: `*bold*` (NOT `**bold**`)
- Links: `[[url][text]]` (NOT `[text](url)`)
- Inline code: `=code=` (NOT `` `code` ``)
- Quotes: `#+BEGIN_QUOTE ... #+END_QUOTE` (NOT `> quote`)
- Lists: `- item` (same as markdown)

### Org File Format

Required headers:

```org
#+TITLE: Article Title
#+HUGO_TAGS: tag1 tag2
#+CATEGORIES: category
#+DATE: YYYY-MM-DD
#+AUTHOR: Donald Lo
#+HUGO_SECTION: section-name
#+HUGO_BASE_DIR: ../../
#+DRAFT: false
```

### Code Blocks

```org
#+begin_src bash :exports code
command here
#+end_src
```

### Images

```org
#+ATTR_ORG: :width 800
#+ATTR_HTML: :width 90%
[[file:../../static/images/article-name/image.png]]
```

Image conventions:
- Location: `static/images/article-name/`
- Naming: `YYYY-MM-DD_HH-MM-SS_description.png`

## Naming Conventions

- Org files: `kebab-case.org` (e.g., `dev-envs.org`)
- Image files: `YYYY-MM-DD_HH-MM-SS_description.png`
- Directories: lowercase, no spaces

### Git Commit Format

Format: `<type>: <subject>`

Types: `add`, `update`, `fix`, `style`, `refactor`, `docs`

Examples:
- `add: Rsync backup tutorial`
- `update: Windows development guide`
- `fix: Correct image path`

## Deployment

- Platform: GitHub Pages
- Branch: `master`
- CI/CD: GitHub Actions (`.github/workflows/hugo.yml`)
- Hugo version: 0.154.5 (extended)
- Auto-deploys on push to master

## Important Notes

1. Image Paths: Always use relative paths starting with `../../static/`
2. Draft Status: Set `#+HUGO_DRAFT: false` before publishing
3. Date Format: Use `YYYY-MM-DD` consistently
4. Encoding: UTF-8 for all files
5. Always respond in Chinese-simplified

## Common Issues

### Images Not Displaying
- Check path starts with `../../static/`
- Verify image exists in `static/images/`

### Content Not Updating
1. Re-export org file with `C-c C-e H H`
2. Verify markdown file updated in `content/`
3. Restart hugo server

### Build Fails
1. Check Hugo version (use extended version 0.154.5+)
2. Verify theme submodule: `git submodule update --init --recursive`
3. Check for syntax errors in `config.toml`

## Behavioral Guidelines

Behavioral guidelines to reduce common LLM coding mistakes. Merge with project-specific instructions as needed.

**Tradeoff:** These guidelines bias toward caution over speed. For trivial tasks, use judgment.

### 1. Think Before Coding

**Don't assume. Don't hide confusion. Surface tradeoffs.**

Before implementing:
- State your assumptions explicitly. If uncertain, ask.
- If multiple interpretations exist, present them - don't pick silently.
- If a simpler approach exists, say so. Push back when warranted.
- If something is unclear, stop. Name what's confusing. Ask.

### 2. Simplicity First

**Minimum code that solves the problem. Nothing speculative.**

- No features beyond what was asked.
- No abstractions for single-use code.
- No "flexibility" or "configurability" that wasn't requested.
- No error handling for impossible scenarios.
- If you write 200 lines and it could be 50, rewrite it.

Ask yourself: "Would a senior engineer say this is overcomplicated?" If yes, simplify.

### 3. Surgical Changes

**Touch only what you must. Clean up only your own mess.**

When editing existing code:
- Don't "improve" adjacent code, comments, or formatting.
- Don't refactor things that aren't broken.
- Match existing style, even if you'd do it differently.
- If you notice unrelated dead code, mention it - don't delete it.

When your changes create orphans:
- Remove imports/variables/functions that YOUR changes made unused.
- Don't remove pre-existing dead code unless asked.

The test: Every changed line should trace directly to the user's request.

### 4. Goal-Driven Execution

**Define success criteria. Loop until verified.**

Transform tasks into verifiable goals:
- "Add validation" → "Write tests for invalid inputs, then make them pass"
- "Fix the bug" → "Write a test that reproduces it, then make it pass"
- "Refactor X" → "Ensure tests pass before and after"

For multi-step tasks, state a brief plan:
```
1. [Step] → verify: [check]
2. [Step] → verify: [check]
3. [Step] → verify: [check]
```

Strong success criteria let you loop independently. Weak criteria ("make it work") require constant clarification.

---

**These guidelines are working if:** fewer unnecessary changes in diffs, fewer rewrites due to overcomplication, and clarifying questions come before implementation rather than after mistakes.