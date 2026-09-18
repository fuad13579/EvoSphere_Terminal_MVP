# EvoSphere Git Workflow

## Purpose

This document defines how the EvoSphere team should use Git and GitHub safely.

The main goals are:

```text
- Keep main stable
- Avoid accidental broken code
- Avoid large commits
- Make each contribution traceable
- Make code review possible
```

---

## Branch Strategy

Use three main branch types.

```text
main      = stable/demo-ready code
dev       = active development branch
feature/* = task or system-specific work
```

---

## Branch Meaning

## `main`

`main` is the stable branch.

Only working, tested, presentation-ready code should be merged into `main`.

Rules:

```text
- Do not push directly to main
- main should be protected
- merge into main only through PR from dev
- main should always compile
```

---

## `dev`

`dev` is the active development branch.

Feature branches should merge into `dev` first.

Rules:

```text
- Pull latest dev before creating a feature branch
- Feature branches merge into dev
- dev may temporarily have bugs, but should be fixed quickly
```

---

## `feature/*`

Feature branches are used for specific tasks.

Examples:

```text
feature/board-system
feature/creature-system
feature/gameflow-system
feature/teleport-logic
feature/battle-before-capture
feature/evolution-system
```

---

# Recommended Three-Branch Team Setup

For the first terminal MVP, the team can use these three feature branches:

```text
feature/Shahriar/board-system
feature/Fuad/creature-system
feature/Musfiq/gameflow-system
```

## Branch Responsibilities

| Branch | Main Responsibility |
|---|---|
| `feature/board-system` | Board, Tile, Movement, Teleport |
| `feature/creature-system` | Player, Evoran, Battle, Capture, Evolution, Guardian |
| `feature/gameflow-system` | TurnManager, Console, Events, Win condition, Integration |

This is simpler for a beginner team than creating one branch for every small logic.

---

# Daily Workflow

## Step 1 — Start from dev

```bash
git checkout dev
git pull origin dev
```

## Step 2 — Create or switch to your feature branch

If creating for the first time:

```bash
git checkout -b feature/board-system
```

If branch already exists locally:

```bash
git checkout feature/board-system
```

## Step 3 — Work in small parts

Do not code many unrelated systems before committing.

Good:

```text
Add Tile 
Add Board
Add movement wrapping
```

Bad:

```text
Final code
Update everything
Complete game
```

## Step 4 — Commit small changes

```bash
git status
git add .
git commit -m "Add Tile class"
```

## Step 5 — Push branch

First push:

```bash
git push -u origin feature/board-system
```

After first push:

```bash
git push
```

## Step 6 — Open Pull Request

Create PR:

```text
feature/board-system → dev
```

After testing and review, merge into `dev`.

---

# Release Workflow

When `dev` is stable:

```text
dev → main
```

Use a pull request from `dev` to `main`.

Do not directly push:

```bash
git push origin main
```

unless the team has explicitly agreed and branch protection allows it.

---

# Commit Rules

## Good Commit Messages

Use this style:

```text
Add Player class
Add Evoran damage logic
Implement board wrapping
Fix starter selection input
Add teleport terminal detection
```

## Bad Commit Messages

Avoid:

```text
Update
Final
Done
Bug fix
Game complete
Everything added
```

---

# Commit Size Rule

One commit should represent one small logical change.

Good example:

```text
Commit 1: Add TileType enum
Commit 2: Add Tile class
Commit 3: Add Board class
Commit 4: Initialize 40 tiles
Commit 5: Add movement wrapping
```

Bad example:

```text
Commit 1: Add board, player, battle, capture, events, evolution, and UI
```

Large commits are risky because:

```text
- Hard to review
- Hard to debug
- Hard to explain during presentation
- Penalized by the course instructions
```

---

# Pull Request Rules

Every PR should include:

```text
- What was added
- What files changed
- How it was tested
- Any known issues
```

## PR Template

```markdown
## Summary
Briefly explain what this PR adds.

## Changed Files
- file 1
- file 2

## How to Test
1. Build the project.
2. Run the terminal game.
3. Check the feature.

## Notes
Mention limitations or future changes.
```

---

# Conflict Handling

If Git shows a merge conflict:

```text
Do not randomly delete code.
Do not force push.
Ask the integration lead before resolving.
```

Basic safe steps:

```bash
git status
```

Then inspect conflicted files manually.

---





If push fails after making repo private, try:

```text
- Sign in to GitHub from VS Code
- Remove old GitHub credentials from Windows Credential Manager
- Use a Personal Access Token if Git asks for password
```

---

# Protected main Branch

`main` should be protected.

Recommended protection rules:

```text
- Require pull request before merging
- Require at least 1 approval
- Do not allow force pushes
- Do not allow deletion
- Restrict direct push access
```

---

# What Not to Do

Do not do these:

```bash
git push origin main
```

without approval.

Do not do:

```bash
git push --force
```

unless the whole team knows exactly why.

Do not commit files you do not understand.

Do not merge code that does not compile.

---

# Final Team Rule

Before every work session:

```bash
git checkout dev
git pull origin dev
```

Before every presentation/demo:

```text
Make sure main is stable, clean, and runnable.
```
