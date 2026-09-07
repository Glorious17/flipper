# Puzzle 3D

This is a small university project from 2016, created to learn C++ programming.
It is a Qt/OpenGL puzzle game that supports Qt 5 and Qt 6 and builds as a native
macOS application bundle, including on Apple Silicon.

## Build on an Apple Silicon Mac

Install the command-line tools, CMake, and Qt with Homebrew:

```sh
xcode-select --install
brew install cmake qt
```

Configure and build with the Homebrew Qt installation:

```sh
cmake -S . -B build -DCMAKE_PREFIX_PATH="$(brew --prefix qt)"
cmake --build build --parallel
```

Run the application:

```sh
open build/Puzzle3D.app
```

Homebrew installs native `arm64` packages on an M1/M2/M3/M4 Mac, so no Rosetta
installation or cross-compilation setting is needed.

## Controls

- Right-drag moves the cylinder or selected block.
- Press Return to confirm the cylinder, then each block's position and rotation.
- Left-drag rotates the view; the mouse wheel zooms.
- Arrow keys move the view, and Escape restarts the game.

The older qmake project remains available for Qt Creator users, but CMake is the
recommended build system.
