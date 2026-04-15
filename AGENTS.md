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
