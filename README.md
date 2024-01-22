# Snake

Classic snake game made in C with the [raylib](https://github.com/raysan5/raylib) library.

## Live Version

A live version of this project is playable at: [https://projects.vyvy-vi.com/snake/](https://projects.vyvy-vi.com/snake/)

## Preview

https://github.com/Vyvy-vi/snake/assets/62864373/aaa7d155-74a9-40d5-9147-02b212ede41d

## Installation and setup

- Install [GNU Make](https://www.gnu.org/software/make/#download)
- Install [`raylib`](https://github.com/raysan5/raylib?tab=readme-ov-file#build-and-installation)
- Install [`pkg-config`](https://pkgconfig.freedesktop.org/releases/)
- Run `make` in the root directory. If compilation fails, try changing the `INCLUDE_RAYLIB` and `LDFLAGS` variables in the `Makefile` to the appropriate installation locations of raylib on your system.
- Refer to the [Raylib Wiki](https://github.com/raysan5/raylib/wiki#development-platforms) for further issues.
- Run the game by clicking on the `snake` executable or by running it in a terminal.

- For the web version with WASM build, run `make web`. Run `python -m http.server 8000` and open localhost:8000 in your web browser to play.

## Feedback and Bugs

If you have feedback or a bug report, please feel free to [open a GitHub issue](https://github.com/Vyvy-vi/snake/issues/new/choose)!

## License

This software is licensed under [The MIT License](LICENSE).

Copyright 2024 Vyom Jain.
