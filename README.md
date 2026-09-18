# EvoSphere

EvoSphere is a turn-based fantasy board game inspired by Monopoly-style board
movement and creature capture and evolution. Players move around a 40-tile
board, collect Evorans, control tiles, evolve their team, and reduce opposing
players' Avatar Points.

## Current Status

EvoSphere is a playable terminal MVP. It uses structured programming: game
state is stored in `struct` values and behavior is implemented by separate
free functions. The terminal MVP is still under active testing and does not
yet include the planned GUI, saved games, audio, or online multiplayer.

The planned terminal version includes:

- Two or three players
- Two Energy Orbs for movement
- 40 board tiles
- Wild Evoran battles and capture
- Player-owned Evoran tiles
- Guardian encounters
- Teleport Terminals
- Blessing Shrine and Chaos Rift events
- Evolution using Evolution Gems
- Avatar Point defeat and winner detection

The future version will add a GUI application and network multiplayer.

## Technology

- C++17
- CMake
- Structured programming using `struct` data and separate functions
- Terminal input and output for the MVP

## Project Structure

```text
assets/      Game artwork and interface assets
docs/        Project documentation and planning
include/     Header files
src/         Source files
tests/       Automated tests
tools/       Development notes and tools
```

Important code areas:

```text
Core/       Player, Evoran, Board, Tile, Game, and turn data
Systems/    Movement, battle, capture, event, evolution, and teleport rules
Console/    Terminal input, output, and game flow
data/       Fixed Evoran, board, and event data
Utils/      Constants, random utilities, and shared helpers
```

The console program starts with `runConsoleGame(ConsoleGameState*)`.
`ConsoleInput` and `ConsoleRenderer` are namespaces of free functions, and the
core gameplay layer remains independent of terminal input and output.

## Requirements

Install:

- A C++17-compatible compiler
- CMake 3.16 or newer

## Build

From the project root, run:

```powershell
cmake -S . -B build
cmake --build build --config Debug
```

## Test

The board and battle regression tests are enabled by default through CTest:

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

## Run

```powershell
.\build\Debug\EvoSphere.exe
```

The exact executable location may differ depending on the compiler and CMake
generator.

## Development Workflow

1. Pull the latest changes from `dev`.
2. Create a feature branch for your task.
3. Make small, focused changes.
4. Build and test the project.
5. Commit with a clear message.
6. Open a pull request to `dev`.

## Documentation

Project planning and explanations are available in the `docs/` directory,
including:

- `EvoSphere_Current_Gameplay_Logic.md`
- `evosphere_evoran_roster.md`
- `EvoSphere_Development_Roadmap.md`
- `terminal_mvp_issues.md`
- `gui_network_multiplayer_issues.md`
- `team-contributions.md`
- `Code_Explanation_Guide.md`
