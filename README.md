# Learning C with raylib

Small exercises I'm working through while learning C and game development with [raylib](https://www.raylib.com/).

## Exercises

| Folder | What it is |
| --- | --- |
| [Exercise1](Exercise1/) | First raylib window: drawing a circle |
| [Exercise2](Exercise2/) | Pong / breakout-style paddle and ball, with game over and restart |

## Building

Requires raylib (on macOS: `brew install raylib`).

From inside an exercise folder:

```bash
gcc pong.c -o pong -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib \
    -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
./pong
```

Swap `pong.c` / `pong` for the file you want to build.

## Controls (Exercise2)

- Left / Right arrows: move the paddle
- R: restart after game over
