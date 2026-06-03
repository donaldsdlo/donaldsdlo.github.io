# CLAUDE.md This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Summary

Personal bilingual (primarily Chinese) technical blog: Hugo static site → GitHub Pages. Content authored in Emacs org-mode, exported via ox-hugo to Markdown, then built by Hugo.

## Build Commands

```bash
hugo server -D                          # Dev server with drafts
hugo server -D --navigateToChanged      # Dev server, auto-navigate to changed files
hugo --minify                           # Production build
rm -rf public                           # Clean build output
hugo list all                           # List all content
hugo config                             # Inspect resolved config
```

No test suite. No package.json at root level.

## Content Architecture

**Two-tier content system — org-mode is source of truth:**

1. `content-org/` — Hand-edited `.org` files (PRIMARY SOURCE)
2. `content/` — Auto-generated `.md` from ox-hugo export (DO NOT EDIT DIRECTLY)

Content sections: `acm/`, `windows/`, `math/`, `life/`, `post/`

**Export workflow:** Edit `.org` → Emacs `C-c C-e H H` → generates `.md` in `content/` → Hugo builds to `public/`

**Key paths:**
- `static/images/<article-name>/` — Article images
- `static/ox-hugo/` — ox-hugo generated images
- `static/ltximg/` — LaTeX rendered images
- `attached/draws/` — Drawio diagram sources
- `layouts/` — Custom template overrides (shortcodes, render hooks, widgets)
- `themes/hugo-theme-stack/` — Active theme (forked submodule)

## Org-Mode Content Format

Always edit `.org` files, never the generated `.md`. Required header:

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

Org syntax (NOT markdown): `*bold*`, `=code=`, `[[url][text]]`, `#+BEGIN_QUOTE`, `*`/`**`/`***` headings.

Image references use relative paths: `[[file:../../static/images/article-name/image.png]]`

## Deployment

- GitHub Actions (`.github/workflows/hugo.yml`) auto-deploys on push to `master`
- Hugo 0.154.5 extended + Dart Sass in CI
- Output: GitHub Pages
- Theme submodule checkout: `git submodule update --init --recursive`

## Commit Convention

Format: `<type>: <subject>` — Types: `add`, `update`, `fix`, `style`, `refactor`, `docs`

## Language

Respond in Simplified Chinese (简体中文) by default.
