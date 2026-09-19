# EvoSphere Terminal MVP

EvoSphere Terminal MVP is the original console prototype of EvoSphere: a
turn-based fantasy board game with creature battles, capture, evolution, and
territory control. It was built as a proof of concept for the core gameplay
systems.

This repository is a historical MVP archive and it does not contain graphical or networked version of
EvoSphere.

## Features

- Two or three local players
- A 40-tile board with two Energy Orbs for movement
- Wild Evoran encounters, battles, and capture
- Player-owned Evoran and special tiles
- Territory ownership bonuses
- Origin Gate rewards and defeated-Evoran revival
- Guardian encounters
- Teleport Terminals
- Blessing Shrine and Chaos Rift events
- One-step Evoran evolution using Evolution Gems
- Avatar Point defeat and winner detection

## Requirements

- CMake 3.16 or newer
- A C++17 compiler

On Windows, install either Visual Studio or Build Tools with the **Desktop
development with C++** workload, or an MSYS2 MinGW C++ toolchain. CMake must
be able to find the selected compiler.

## Build

From the repository root:

```powershell
cmake -S . -B build
cmake --build build --config Debug
```

If you use MSYS2 MinGW, configure with its generator instead:

```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

## Run

With a Visual Studio multi-configuration build:

```powershell
.\build\Debug\EvoSphere.exe
```

With a MinGW single-configuration build:

```powershell
.\build\EvoSphere.exe
```

At startup, choose two or three players, enter avatar names, select unique
starter Evorans, then use the numbered terminal menu. Roll the Orbs once per
turn; after rolling, choose **End Turn** from the same menu entry.

## Tests

The automated tests cover Board, Evoran, Player, Movement, Battle, and
Evolution behaviour:

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

For a MinGW single-configuration build, omit `-C Debug`:

```powershell
ctest --test-dir build --output-on-failure
```

## Project Structure

```text
include/       Public headers
src/Core/      Board, Tile, Player, Evoran, Guardian, game state, turns
src/Systems/   Movement, battle, capture, events, evolution, teleportation
src/Console/   Terminal input, output, and game loop
src/data/      Fixed board, Evoran, and event data
include/Utils/ Constants and random helpers
tests/         Automated regression tests
docs/          Historical design and gameplay documentation
```

The gameplay rules are intentionally separated from terminal rendering and
input. `src/main.cpp` launches `runConsoleGame`, which drives the Core and
Systems modules.

## Known Limitations

- This is a local terminal game; it has no GUI, saved games, audio, or online
  multiplayer.
- Automated tests do not yet cover every system, particularly events,
  Guardians, teleportation, turn management, and full console interaction.

## Contributors

See [docs/team-contributions.md](docs/team-contributions.md) for the recorded
team contributions.

## License

No root project license has been selected for this repository. Unless the team
adds one, the project source is not offered under an explicit open-source
license.

## Status

Archived terminal MVP. Active EvoSphere development continues elsewhere.
