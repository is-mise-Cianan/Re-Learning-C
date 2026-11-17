# Commands Cheat Sheet

Quick reference for building the exercises and using git with this repo.

---

## Compiling (raylib on macOS)

Run these from **inside the exercise folder** (e.g. `Exercise2/`).

### Build Pong

```bash
gcc pong.c -o pong -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
```

### Run it

```bash
./pong
```

### Build any other file

Swap the file name (`main.c`) and the output name (`game`):

```bash
gcc main.c -o game -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
```

### Build and run in one go

`&&` only runs the game if the build succeeded:

```bash
gcc pong.c -o pong -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo && ./pong
```

### Shorter version using pkg-config

`pkg-config` fills in the raylib include and library paths for you:

```bash
gcc pong.c -o pong $(pkg-config --cflags --libs raylib) -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
```

### Show warnings (recommended)

`-Wall -Wextra` makes the compiler point out likely bugs:

```bash
gcc -Wall -Wextra pong.c -o pong -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
```

### Stop a running game

Close the window, press `Esc`, or press `Ctrl+C` in the terminal.

### Remember

Edit the `.c` file → **rebuild** → run. Running `./pong` without rebuilding runs the old version.

---

## Navigating

```bash
cd ~/Documents/Projects/Gaming/C
```

```bash
cd Exercise2
```

```bash
cd ..
```

| Command | What it does |
| --- | --- |
| `pwd` | Show which folder you're in |
| `ls` | List files in this folder |
| `ls -la` | List all files, including hidden ones like `.gitignore` |

Git commands work from the `C` folder **or any folder inside it**.

---

## Git: everyday workflow

Save your progress and upload it to GitHub:

```bash
git add -A
```

```bash
git commit -m "Describe what you changed"
```

```bash
git push
```

| Command | What it does |
| --- | --- |
| `git add -A` | Stage every change in the whole repo (any folder you're in) |
| `git add .` | Stage changes in the **current folder only** |
| `git add pong.c` | Stage one specific file |
| `git commit -m "msg"` | Save the staged changes as a commit |
| `git push` | Upload your commits to GitHub |
| `git pull` | Download changes from GitHub (e.g. edits made on the website) |

---

## Git: checking what's going on

| Command | What it does |
| --- | --- |
| `git status` | What's changed, what's staged, what's untracked |
| `git diff` | Exact line changes you haven't staged yet |
| `git diff --staged` | Exact line changes you've staged but not committed |
| `git log --oneline` | Short list of past commits |
| `git log --oneline --stat` | Past commits plus which files each one changed |
| `git remote -v` | Show which GitHub repo you push to |

---

## Git: undoing things

| Command | What it does |
| --- | --- |
| `git restore pong.c` | Throw away unsaved edits to a file (back to the last commit). **Can't be undone.** |
| `git restore --staged pong.c` | Unstage a file but keep your edits |
| `git commit --amend -m "new msg"` | Fix the last commit's message (only before you've pushed it) |
| `git rm --cached pong` | Stop tracking a file (e.g. a binary added by mistake) without deleting it |

---

## Git: one-time setup (already done for this repo)

For reference, if you start a new repo later:

```bash
git init -b main
```

```bash
git remote add origin https://github.com/is-mise-Cianan/REPO-NAME.git
```

```bash
git push -u origin main
```

Or create the GitHub repo and push in one step with the GitHub CLI:

```bash
gh repo create REPO-NAME --public --source=. --remote=origin --push
```

Change where you push:

```bash
git remote set-url origin https://github.com/is-mise-Cianan/REPO-NAME.git
```

Keep your email private in commits (use your GitHub noreply address):

```bash
git config --global user.email "316173585+is-mise-Cianan@users.noreply.github.com"
```

When creating a repo on github.com for code you already have locally, leave **README, .gitignore and license all unticked**, or your first push will be rejected.

---

## .gitignore

Files listed in `.gitignore` are never added to git. This repo ignores:

- `.DS_Store` (macOS junk)
- `game`, `pong`, `*.o`, `*.out` (compiled binaries)

If you add a new exercise that builds to a new name (e.g. `breakout`), add that name to `.gitignore` so the binary doesn't get committed.
