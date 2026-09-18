# EvoSphere Team Contributions

## Purpose

This document defines who is responsible for each part of EvoSphere. It helps the team divide work clearly and prepares each member for presentation Q&A.

Each member must be able to explain the files and logic they worked on.

---

## Team Strategy

The project is divided by systems, not by random files.

```text
Shahriar: Board and Movement
Fuad: Player, Evoran, Battle, Capture
Musfiq: Game Flow, Console, Events, Integration
```

This division matches the terminal MVP architecture:

```text
Core/     = game objects
Systems/  = gameplay rules
Console/  = terminal input/output
data/     = fixed game data
```

---

# Shahriar — Board and Movement Lead

## Main Responsibility

Member 1 owns the board structure, tile system, and movement logic.

## Files

```text
include/Core/Tile.h
src/Core/Tile.cpp

include/Core/Board.h
src/Core/Board.cpp

include/Systems/MovementSystem.h
src/Systems/MovementSystem.cpp

include/Systems/TeleportSystem.h
src/Systems/TeleportSystem.cpp

include/data/BoardData.hpp
src/data/BoardData.cpp
```

## Tasks

- Create tile structure.
- Create 40-tile board.
- Add tile types.
- Add board wrapping.
- Add Energy Orb movement.
- Detect passing Origin Gate.
- Add Origin Gate rewards.
- Add teleport terminal positions.
- Implement teleport logic.
- Support tile ownership updates.
- Assign element and territory names to every tile.
- Add the Origin Gate, Guardian, event, teleport, and special ownable tiles.
- Handle landing on the player's own tile.
- Handle landing on an opponent-owned tile through the integration API.
- Add board-data validation for exactly 40 tiles.
- Test board wrapping and movement boundaries.
- Test teleport selection and terminal positions.

## Additional Files

```text
tests/test_board.cpp
tests/test_movement.cpp
tests/test_teleport.cpp
```




# Fuad — Player, Evoran, Battle, and Capture Lead

## Main Responsibility

Member 2 owns the creature logic and player state.

## Files

```text
include/Core/Evoran.h
src/Core/Evoran.cpp

include/Core/Player.h
src/Core/Player.cpp

include/Core/Guardian.h
src/Core/Guardian.cpp

include/Systems/BattleSystem.h
src/Systems/BattleSystem.cpp

include/Systems/CaptureSystem.h
src/Systems/CaptureSystem.cpp

include/Systems/EvolutionSystem.h
src/Systems/EvolutionSystem.cpp

include/data/EvoranDatabase.hpp
src/data/EvoranDatabase.cpp
```

## Tasks

- Create Evoran model.
- Create Player model.
- Add starter Evorans.
- Add wild Evorans.
- Add evolved form data.
- Add Guardian Evorans.
- Implement Evoran HP and damage.
- Implement Avatar Point damage.
- Implement battle-before-capture logic.
- Implement one-step evolution.
- Implement safe null-pointer and invalid-value handling.
- Apply the 30% wild Evoran capture threshold.
- Apply opponent-owned tile damage using the defending Evoran's damage.
- Apply the three-Evolution-Gem evolution cost.
- Prevent an Evoran from evolving more than once.
- Implement Guardian effects, blessings, and curses.
- Keep Guardian logic separate from Evoran battle and evolution logic.
- Validate that all roster entries match the roster document.

## Additional Files

```text
tests/test_evoran.cpp
tests/test_player.cpp
tests/test_capture.cpp
tests/test_guardian.cpp
tests/test_evolution.cpp
```



---

# Musfiq — Game Flow, Console, Events, and Integration Lead

## Main Responsibility

Member 3 owns the game loop, turn system, events, win condition, and integration between all systems.

## Files

```text
include/Core/Game.h
src/Core/Game.cpp

include/Core/TurnManager.h
src/Core/TurnManager.cpp

include/Core/EventCard.h
src/Core/EventCard.cpp

include/Systems/EventSystem.h
src/Systems/EventSystem.cpp

include/data/EventDatabase.hpp
src/data/EventDatabase.cpp

include/Console/ConsoleGame.hpp
src/Console/ConsoleGame.cpp

include/Console/ConsoleInput.hpp
src/Console/ConsoleInput.cpp

include/Console/ConsoleRenderer.hpp
src/Console/ConsoleRenderer.cpp

src/main.cpp
```

## Tasks

- Create terminal game loop.
- Ask player count.
- Ask avatar names.
- Handle starter selection.
- Show player status.
- Manage turn order.
- Resolve landed tile actions.
- Trigger event system.
- Check defeat and winner.
- Keep terminal output readable.
- Integrate code from Member 1 and Member 2.
- Implement the complete game-state initialization.
- Resolve every tile action in the correct order.
- Skip defeated players when selecting the next turn.
- Apply Origin Gate rewards after movement.
- Check the win condition after every action.
- Keep terminal output in the Console layer.
- Validate player count, names, choices, and numeric input.
- Display battle, capture, event, teleport, and Guardian results.
- Add the final winner and game-over flow.

## Additional Files

```text
tests/test_turn.cpp
tests/test_turn_manager.cpp
tests/test_event.cpp
tests/test_game.cpp
```

`ConsoleGame.cpp` and `ConsoleInput.cpp` should be created because their
headers already exist. `ConsoleRenderer.cpp` should use the existing
`ConsoleRenderer.hpp` file.


---

# Shared Responsibilities

All members are responsible for:

```text
- Pulling latest dev before starting work
- Creating small commits
- Writing clear commit messages
- Opening pull requests to dev
- Reviewing teammates' code
- Testing their own features
- Explaining their own code during Q&A
- Running the full CMake build before opening a pull request
- Adding tests for each completed feature
- Checking that header declarations match source definitions
- Reporting integration problems to Member 3

## Shared Build and Release Tasks

These tasks must be completed together because they affect the whole project:

```text
- Complete CMakeLists.txt.
- Set the project to C++17.
- Add all required terminal MVP source files.
- Add include/ as an include directory.
- Add the missing src/data/ source files.
- Keep ConsoleRenderer.hpp as the single renderer header style.
- Confirm the project builds without warnings or errors.
```

Suggested shared verification command:

```powershell
cmake -S . -B build
cmake --build build
```
```

---

# Branch Ownership

For the first development stage, the team may use three larger feature branches:

```text
feature/board-system
feature/creature-system
feature/gameflow-system
```

## Branch Mapping

| Branch | Owner | Main Work |
|---|---|---|
| `feature/Shahriar/board-system` | Member 1 | Board, Tile, Movement, Teleport |
| `feature/Fuad/creature-system` | Member 2 | Player, Evoran, Battle, Capture, Evolution, Guardian |
| `feature/Musfiq/gameflow-system` | Member 3 | Turn flow, Console UI, Events, Win condition, Integration |

---
