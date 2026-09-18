# EvoSphere Development Progress

## Current Stage

The project is currently in the terminal MVP foundation stage. The main data
structures and utility headers have been started using structured programming
with `struct` values and separate functions.

## Completed

### Project Structure

- Created the project folder and file structure.
- Added the main `assets`, `docs`, `include`, `src`, `tests`, and `tools`
  folders.


### Documentation

- Added gameplay logic documentation.
- Added the Evoran roster and MVP statistics.
- Added the code explanation guide.
- Added terminal MVP issues and completion requirements.
- Added GUI, application, and network multiplayer issues.
- Updated the roadmap for structured programming.

### Utilities

- Added shared board, player, orb, evolution, capture, event, and Guardian
  constants in `include/Utils/Constants.h`.
- Added `ElementType`, `TileType`, `EvoranCategory`, `EventType`, and
  `GamePhase` enumerations.
- Added random Energy Orb and random-index helpers in
  `include/Utils/Random.h`.

### Core Foundation

- Added the structured `Evoran` data structure in `include/Core/Evoran.h`.
- Added Evoran initialization, HP, damage, healing, ownership, defeat, and
  one-step evolution functions in `src/Core/Evoran.cpp`.
- Added the structured `Player` data structure and player function declarations
  in `include/Core/Player.h`.
- Added the initial player function implementations in `src/Core/Player.cpp`.
- Added the basic `GameState` and game-state helper functions in `Game.h` and
  `Game.cpp`.

## In Progress

- Complete and verify the `Tile` implementation.
- Complete and verify the `Board` implementation.
- Complete `Guardian`, `EventCard`, and `TurnManager` logic.
- Implement the Evoran, board, and event databases.
- Connect the Core data structures to the Systems layer.
- Complete the terminal game loop and console interface.
- Add and run tests for the completed functions.
- Complete and verify the CMake build configuration.

## Not Started for the Terminal MVP

- Full movement and turn flow.
- Battle-before-capture gameplay.
- Opponent-owned tile damage.
- Blessing Shrine and Chaos Rift events.
- Teleport Terminal behavior.
- Guardian encounters.
- Territory control bonuses.
- Complete Evolution Gem flow.
- Final win-condition integration.

## Future Work

After the terminal MVP is stable, the project will move to:

- GUI application screens and rendering.
- Asset and audio integration.
- Save and load support.
- Backend and server-authoritative multiplayer.
- Online lobbies and synchronized multiplayer matches.
- Connection recovery, security, testing, and release packaging.

## Current Development Rule

Continue using structured programming:

- Use `struct` for data.
- Use separate free functions for operations.
- Use pointers when functions modify existing data.
- Use `const` pointers when functions only read data.
- Keep Core and Systems independent from terminal and GUI output.
