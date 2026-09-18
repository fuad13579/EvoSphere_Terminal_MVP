# EvoSphere Architecture

## 1. Purpose

This document explains how the EvoSphere codebase is organized and why the project is divided into separate modules.

EvoSphere is a turn-based fantasy board strategy game inspired by Monopoly-style movement and Pokémon-style creature capture/evolution. The project will first be completed as a terminal game, then expanded into a GUI version using raylib.

The main architecture goal is:

```text
Keep the game logic independent from the terminal/GUI display.
```

This means the core rules should work even if the output changes from terminal text to raylib graphics.

---

## 2. Current Project Structure

The current GitHub already has this structure:

```text
EvoSphere_MVP/
│
├── assets/
│   ├── sprites/
│   ├── guardians/
│   └── ui/
│
├── docs/
│   ├── EvoSphere_Current_Gameplay_Logic.md
│   ├── evosphere_evoran_roster.md
│   ├── architecture.md
│   ├── gameplay-rules.md
│   ├── git-workflow.md
│   ├── roadmap.md
│   └── progress.md
│
├── include/
│   ├── Console/
│   ├── Core/
│   ├── Engine/
│   ├── Graphics/
│   ├── Scenes/
│   ├── Systems/
│   ├── Utils/
│   └── data/
│
├── src/
│   ├── Console/
│   ├── Core/
│   ├── Engine/
│   ├── Graphics/
│   ├── Scenes/
│   ├── Systems/
│   └── main.cpp
│
├── tests/
├── tools/
├── CMakeLists.txt
├── README.md
└── .gitignore
```

---

## 3. Architecture Layers

EvoSphere should be treated as four layers.

```text
Application Layer
    ↓
Presentation Layer
    ↓
Game Logic Layer
    ↓
Data / Utility Layer
```

---

## 4. Application Layer

### Files

```text
src/main.cpp
include/Core/Game.h
src/Core/Game.cpp
```

### Responsibility

The application layer starts and controls the game.

`main.cpp` should stay very small.

Expected final idea:

```cpp
int main()
{
    ConsoleGame game;
    game.run();
    return 0;
}
```

### Why this matters

If `main.cpp` becomes large, the project becomes difficult to explain and maintain. The presentation instructions clearly say every line of code must be explainable, so the game must be modular.

---

## 5. Presentation Layer

The presentation layer handles input and output.

For the terminal version, this means terminal printing and terminal input.

For the GUI version, this means raylib rendering and mouse/keyboard input.

---

## 6. Terminal Presentation Layer

### Files

```text
include/Console/ConsoleGame.hpp
src/Console/ConsoleGame.cpp

include/Console/ConsoleInput.hpp
src/Console/ConsoleInput.cpp

include/Console/ConsoleRenderer.hpp
src/Console/ConsoleRenderer.cpp
```

### Responsibility

| File | Responsibility |
|---|---|
| `ConsoleGame` | Runs the terminal game loop |
| `ConsoleInput` | Reads and validates player input |
| `ConsoleRenderer` | Prints game state and messages |

### Examples

`ConsoleInput` should handle:

```text
- player count input
- avatar name input
- starter selection input
- battle choice input
- evolution choice input
```

`ConsoleRenderer` should handle:

```text
- welcome screen
- player status
- turn summary
- movement result
- tile information
- battle result
- winner message
```

### Rule

```text
Console files can print.
Core and Systems files should not directly print.
```

This keeps the logic reusable for the GUI version.

---

## 7. Game Logic Layer: Core

The `Core/` folder contains the main game objects.

### Files

```text
include/Core/Evoran.h
src/Core/Evoran.cpp

include/Core/Player.h
src/Core/Player.cpp

include/Core/Tile.h
src/Core/Tile.cpp

include/Core/Board.h
src/Core/Board.cpp

include/Core/EventCard.h
src/Core/EventCard.cpp

include/Core/Guardian.h
src/Core/Guardian.cpp

include/Core/TurnManager.h
src/Core/TurnManager.cpp

include/Core/Game.h
src/Core/Game.cpp
```

### Responsibility Table

| Class | Responsibility |
|---|---|
| `Evoran` | Stores creature name, type, HP, damage, evolution state |
| `Player` | Stores player name, Avatar Points, gems, position, owned Evorans |
| `Tile` | Stores board tile index, type, element, owner, linked Evoran |
| `Board` | Stores and manages the 40 board tiles |
| `EventCard` | Stores Blessing/Chaos event information |
| `Guardian` | Stores legendary Guardian Evoran information |
| `TurnManager` | Controls current turn and next player |
| `Game` | Coordinates full game state and system calls |

### Design Rule

Core should store state and provide simple behavior.

Example:

```text
Player stores Avatar Points.
BattleSystem decides how damage is applied.
```

This prevents one class from doing too many jobs.

---

## 8. Game Logic Layer: Systems

The `Systems/` folder contains gameplay rules.

### Files

```text
include/Systems/MovementSystem.h
src/Systems/MovementSystem.cpp

include/Systems/BattleSystem.h
src/Systems/BattleSystem.cpp

include/Systems/CaptureSystem.h
src/Systems/CaptureSystem.cpp

include/Systems/EventSystem.h
src/Systems/EventSystem.cpp

include/Systems/EvolutionSystem.h
src/Systems/EvolutionSystem.cpp

include/Systems/TeleportSystem.h
src/Systems/TeleportSystem.cpp
```

### Responsibility Table

| System | Responsibility |
|---|---|
| `MovementSystem` | Rolls Energy Orbs, moves players, handles board wrapping |
| `BattleSystem` | Handles Evoran attacks and Avatar Point damage |
| `CaptureSystem` | Handles battle-before-capture logic |
| `EventSystem` | Applies Blessing Shrine and Chaos Rift events |
| `EvolutionSystem` | Evolves Evorans using Evolution Gems |
| `TeleportSystem` | Moves player from one teleport terminal to another |

### Why systems are separate

Each system represents one gameplay rule. This makes the code easier to test and explain.

Bad design:

```text
All movement, battle, capture, events, and evolution inside main.cpp
```

Good design:

```text
MovementSystem handles movement.
BattleSystem handles battle.
CaptureSystem handles capture.
EvolutionSystem handles evolution.
```

---

## 9. Data Layer

### Files

```text
include/data/EvoranDatabase.hpp
src/data/EvoranDatabase.cpp

include/data/BoardData.hpp
src/data/BoardData.cpp

include/data/EventDatabase.hpp
src/data/EventDatabase.cpp
```

### Responsibility

The data layer stores fixed game data.

Examples:

```text
- 4 starter Evorans
- 23 wild Evorans
- evolved form names
- 3 Guardian Evorans
- 40 tile layout
- event card descriptions
- territory groups
```

### Why this matters

Game data should not be hardcoded inside the game loop. If we want to change Evoran stats later, we should update the data file, not the entire game logic.

---

## 10. Utility Layer

### Files

```text
include/Utils/Constants.h
include/Utils/Random.h
include/Utils/Logger.h
```

### Responsibility

Utility files provide shared helper code.

`Constants.h` should store:

```text
BOARD_SIZE = 40
STARTING_AVATAR_POINTS
EVOLUTION_GEM_COST
CAPTURE_HP_THRESHOLD
```

`Random.h` should store:

```text
rollEnergyOrb()
randomInt(min, max)
chooseRandomIndex()
```

`Logger.h` is optional for the terminal MVP.

---

## 11. GUI/Future Architecture

The current ZIP already contains future GUI folders.

```text
include/Engine/
src/Engine/

include/Graphics/
src/Graphics/

include/Scenes/
src/Scenes/
```

These should not be the focus during terminal MVP.

### Future Responsibility

| Folder | Future Use |
|---|---|
| `Engine/` | Window, assets, input, time, scene management |
| `Graphics/` | Board rendering, cards, player tokens, UI |
| `Scenes/` | Menu screen, board screen, battle screen |

### Important Rule

The GUI version should reuse the same `Core/`, `Systems/`, and `data/` logic.

```text
Terminal version uses Console/.
GUI version uses Engine/, Graphics/, and Scenes/.
Core gameplay logic remains the same.
```

---

## 12. Terminal MVP Flow

```text
main.cpp
↓
ConsoleGame.run()
↓
Game initializes players, board, and data
↓
TurnManager selects current player
↓
MovementSystem rolls Energy Orbs and moves player
↓
Game checks landed tile
↓
Relevant system resolves tile action
↓
TurnManager switches player
↓
Game checks win condition
```

---

## 13. GUI Version Flow

```text
main.cpp
↓
Application starts raylib window
↓
SceneManager loads MenuScene
↓
BoardScene displays board and player tokens
↓
Game logic still handled by Game/Core/Systems
↓
Graphics render the result of game state
```

---

## 14. Code Quality Rules

To keep the project clean:

```text
- No large main.cpp
- No random global variables
- No duplicate logic
- No direct printing inside Core/Systems
- One class should have one clear purpose
- Use small functions with clear names
- Keep commits small
- Every member must understand the files they edit
```

---

## 15. Current Priority

For the terminal MVP, focus only on:

```text
src/main.cpp
Core/
Systems/
Console/
data/
Utils/
CMakeLists.txt
```

Do not spend time on:

```text
Engine/
Graphics/
Scenes/
assets/
```

until the terminal game is playable.
