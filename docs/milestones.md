# EvoSphere Milestones

## Purpose

This document defines clear checkpoints from the current project state to the final version. It is designed for team planning, presentation preparation, and progress tracking.

The project is divided into two major sections:

```text
Section 1: From scratch to runnable terminal game
Section 2: From terminal game to GUI version
```

---

# Section 1: From Scratch to Terminal Version

## Milestone 0 — Repository Setup and Team Workflow

### Goal

Prepare the project repository so every member can work safely without breaking `main`.

### Tasks

- Create or verify project folder structure.
- Keep `main` as stable/demo branch.
- Create `dev` as active development branch.
- Protect `main` from direct pushes.
- Create team feature branches.
- Add `.gitignore`.
- Add basic `README.md`.
- Add documentation files in `docs/`.

### Required Files

```text
README.md
.gitignore
CMakeLists.txt
docs/architecture.md
docs/git-workflow.md
docs/milestones.md
```

### Done When

- All members can clone the repo.
- All members can checkout `dev`.
- No one pushes directly to `main`.
- Project structure is visible in GitHub.

---

## Milestone 1 — Build System and First Run

### Goal

Make the project compile and run a basic terminal program.

### Tasks

- Complete `CMakeLists.txt`.
- Complete `src/main.cpp`.
- Print a simple welcome message.
- Verify the executable runs locally.

### Required Files

```text
CMakeLists.txt
src/main.cpp
```

### Done When

Running the program prints:

```text
Welcome to EvoSphere
```

---

## Milestone 2 — Constants and Basic Types

### Goal

Create shared constants and enums used across the project.

### Tasks

- Add board size.
- Add starting Avatar Points.
- Add Evolution Gem cost.
- Add tile types.
- Add element types.
- Add Evoran category/type if needed.

### Required Files

```text
include/Utils/Constants.h
include/Utils/Random.h
```

### Done When

The project has shared definitions for:

```text
BOARD_SIZE = 40
TileType
ElementType
STARTING_AVATAR_POINTS
EVOLUTION_GEM_COST
```

---

## Milestone 3 — Evoran Model

### Goal

Create the Evoran class used by starters, wild Evorans, evolved Evorans, and guardians.

### Tasks

- Store Evoran name.
- Store evolved form name.
- Store element type.
- Store max HP and current HP.
- Store damage.
- Store owner ID.
- Store evolved status.
- Add `takeDamage()`.
- Add `heal()`.
- Add `evolve()`.
- Add `isDefeated()`.

### Required Files

```text
include/Core/Evoran.h
src/Core/Evoran.cpp
```

### Done When

A starter Evoran can be created and printed with name, HP, damage, and type.

---

## Milestone 4 — Player Model

### Goal

Create the Player class.

### Tasks

- Store player ID.
- Store avatar name.
- Store Avatar Points.
- Store Evolution Gems.
- Store current board position.
- Store owned Evorans.
- Add `addEvoran()`.
- Add `takeAvatarDamage()`.
- Add `healAvatar()`.
- Add `addEvolutionGems()`.
- Add `moveTo()`.
- Add `isDefeated()`.

### Required Files

```text
include/Core/Player.h
src/Core/Player.cpp
```

### Done When

A player can be created with Avatar Points and can own a starter Evoran.

---

## Milestone 5 — Tile and Board Model

### Goal

Create the 40-tile board structure.

### Tasks

- Create `Tile` class.
- Store tile index.
- Store tile name.
- Store tile type.
- Store element type.
- Store owner ID.
- Store linked Evoran if applicable.
- Create `Board` class.
- Store exactly 40 tiles.
- Add `getTile(index)`.
- Add board wrapping support.
- Add method to print/debug board layout.

### Required Files

```text
include/Core/Tile.h
src/Core/Tile.cpp

include/Core/Board.h
src/Core/Board.cpp
```

### Done When

The terminal can print all 40 board tiles with index, name, and type.

---

## Milestone 6 — Game Data

### Goal

Move fixed Evoran, board, and event data into data files.

### Tasks

- Define 4 starter Evorans.
- Define 23 wild Evorans.
- Define 3 Guardian Evorans.
- Define 40 board tiles.
- Define 3 Blessing events.
- Define 3 Chaos events.

### Required Files

```text
include/data/EvoranDatabase.hpp
src/data/EvoranDatabase.cpp

include/data/BoardData.hpp
src/data/BoardData.cpp

include/data/EventDatabase.hpp
src/data/EventDatabase.cpp
```

### Done When

The game can load starter Evorans and create the board from data functions instead of hardcoding everything in `main.cpp`.

---

## Milestone 7 — Movement System

### Goal

Allow players to cast two Energy Orbs and move around the board.

### Tasks

- Roll two numbers from 1 to 6.
- Add roll values.
- Move player forward.
- Wrap around after tile 39.
- Detect passing Origin Gate.
- Apply Origin Gate reward.

### Required Files

```text
include/Systems/MovementSystem.h
src/Systems/MovementSystem.cpp
include/Utils/Random.h
```

### Done When

A player can roll, move, wrap around the board, and receive Origin Gate rewards.

---

## Milestone 8 — Turn Manager

### Goal

Control turn order.

### Tasks

- Store current player index.
- Get current player.
- Move to next player.
- Support 2-player and 3-player games.
- Skip defeated players.

### Required Files

```text
include/Core/TurnManager.h
src/Core/TurnManager.cpp
```

### Done When

Turns switch correctly between players.

---

## Milestone 9 — Console Layer and Starter Selection

### Goal

Build the terminal interface.

### Tasks

- Ask number of players.
- Ask avatar names.
- Display starter Evorans.
- Let each player choose a starter.
- Print player status.
- Print turn messages.
- Print landed tile information.

### Required Files

```text
include/Console/ConsoleGame.hpp
src/Console/ConsoleGame.cpp

include/Console/ConsoleInput.hpp
src/Console/ConsoleInput.cpp

include/Console/ConsoleRenderer.hpp
src/Console/ConsoleRenderer.cpp
```

### Done When

The game can start from terminal, create players, choose starters, and begin turns.

---

## Milestone 10 — Basic Game Loop

### Goal

Connect player, board, movement, and turn logic into one playable terminal loop.

### Tasks

- Initialize players.
- Initialize board.
- Initialize turn manager.
- Run repeated turns.
- Move player each turn.
- Display landed tile.
- Switch turns.

### Required Files

```text
include/Core/Game.h
src/Core/Game.cpp
src/main.cpp
```

### Done When

A movement-only terminal game works:

```text
Player 1 turn → roll → move → show tile → Player 2 turn
```

---

## Milestone 11 — Battle System

### Goal

Allow Evorans to battle.

### Tasks

- Select attacking Evoran.
- Apply damage to target Evoran.
- Check if an Evoran is defeated.
- Support repeated attack turns for wild encounters.
- Support Avatar Point damage from opponent-owned tiles.

### Required Files

```text
include/Systems/BattleSystem.h
src/Systems/BattleSystem.cpp
```

### Done When

An Evoran can damage another Evoran and Avatar Points can decrease from opponent-owned tile damage.

---

## Milestone 12 — Battle-Before-Capture System

### Goal

Implement official EvoSphere capture logic.

### Tasks

- Detect wild Evoran tile.
- Let player select one owned Evoran.
- Start battle with wild Evoran.
- Reduce wild Evoran HP.
- Reduce player Evoran HP.
- Capture when wild Evoran HP is 30% or less.
- Add captured Evoran to player.
- Mark tile owner.

### Required Files

```text
include/Systems/CaptureSystem.h
src/Systems/CaptureSystem.cpp
include/Systems/BattleSystem.h
src/Systems/BattleSystem.cpp
```

### Done When

A player can capture a wild Evoran only after weakening it in battle.

---

## Milestone 13 — Event System

### Goal

Implement Blessing Shrine and Chaos Rift tiles.

### Tasks

- Detect Blessing Shrine tile.
- Detect Chaos Rift tile.
- Randomly choose event.
- Apply effect to player or Evoran.
- Print event result.

### Required Files

```text
include/Core/EventCard.h
src/Core/EventCard.cpp
include/Systems/EventSystem.h
src/Systems/EventSystem.cpp
include/data/EventDatabase.hpp
src/data/EventDatabase.cpp
```

### Done When

Landing on event tiles changes player/game state and prints a clear result.

---

## Milestone 14 — Teleport System

### Goal

Implement the 4 Teleport Terminal tiles.

### Tasks

- Store all teleport tile indexes.
- Detect teleport tile.
- Randomly choose another teleport terminal.
- Move player to selected terminal.
- Prevent teleporting to the same terminal.

### Required Files

```text
include/Systems/TeleportSystem.h
src/Systems/TeleportSystem.cpp
```

### Done When

Landing on a teleport terminal sends the player to another terminal.

---

## Milestone 15 — Evolution System

### Goal

Allow one-step Evoran evolution.

### Tasks

- Require 3 Evolution Gems.
- Let player choose owned Evoran.
- Prevent already evolved Evoran from evolving again.
- Increase HP and damage.
- Deduct gems.
- Print evolution result.

### Required Files

```text
include/Systems/EvolutionSystem.h
src/Systems/EvolutionSystem.cpp
```

### Done When

A player can evolve one owned Evoran by spending Evolution Gems.

---

## Milestone 16 — Guardian Logic

### Goal

Implement Guardian encounters.

### Tasks

- Create 3 Guardians.
- Detect Guardian tile.
- Apply the Guardian's blessing or curse effect.
- Update Avatar Points, Evolution Gems, or position.

### Required Files

```text
include/Core/Guardian.h
src/Core/Guardian.cpp
include/Systems/BattleSystem.h
src/Systems/BattleSystem.cpp
```

### Done When

Landing on a Guardian tile triggers a fixed blessing or curse effect.

---

## Milestone 17 — Special Ownable Tiles

### Goal

Implement the 3 unknown ownable tiles as MVP relic/resource tiles.

### Tasks

- Add 3 special ownable tiles.
- Allow player to claim unowned tile.
- Store owner.
- Give reward on own tile.
- Penalize or reward owner when opponent lands there.
- Give bonus when owner passes Origin Gate.

### Required Files

```text
include/Core/Tile.h
src/Core/Tile.cpp
include/Core/Board.h
src/Core/Board.cpp
include/Core/Game.h
src/Core/Game.cpp
```

### Done When

Special tiles can be claimed and provide simple resource advantage.

---

## Milestone 18 — Win Condition and Terminal Polish

### Goal

Make the terminal version presentation-ready.

### Tasks

- Defeat player when Avatar Points reach 0.
- Skip defeated players.
- End game when one player remains.
- Print winner.
- Clean terminal output.
- Remove debug text.
- Add pause between turns.

### Required Files

```text
include/Core/Game.h
src/Core/Game.cpp
include/Core/TurnManager.h
src/Core/TurnManager.cpp
include/Console/ConsoleRenderer.hpp
src/Console/ConsoleRenderer.cpp
```

### Done When

The terminal game starts, runs, progresses, and ends with a winner.

---

# Section 2: From Terminal Version to GUI Version

## Milestone 19 — Freeze Terminal Logic

### Goal

Make sure the terminal game logic is stable before adding graphics.

### Tasks

- Test all terminal features.
- Fix gameplay bugs.
- Document final terminal rules.
- Avoid changing core logic while GUI begins.

### Done When

Terminal game is playable and can be demonstrated from start to finish.

---

## Milestone 20 — raylib Project Setup

### Goal

Prepare the project to compile with raylib.

### Tasks

- Install raylib.
- Update `CMakeLists.txt`.
- Create raylib window.
- Keep terminal game separate.
- Add basic window close handling.

### Required Files

```text
include/Engine/Application.h
src/Engine/Application.cpp
include/Engine/WindowManager.h
src/Engine/WindowManager.cpp
```

### Done When

A blank raylib window opens and closes properly.

---

## Milestone 21 — Scene System

### Goal

Create screen/state management for GUI.

### Tasks

- Create base `Scene` class.
- Create `MenuScene`.
- Create `BoardScene`.
- Create `BattleScene` placeholder.
- Add scene switching.

### Required Files

```text
include/Scenes/Scene.h
include/Scenes/MenuScene.h
src/Scenes/MenuScene.cpp
include/Scenes/BoardScene.h
src/Scenes/BoardScene.cpp
include/Scenes/BattleScene.h
src/Scenes/BattleScene.cpp
include/Engine/SceneManager.h
src/Engine/SceneManager.cpp
```

### Done When

The app can switch from menu screen to board screen.

---

## Milestone 22 — Asset Manager

### Goal

Load textures and fonts safely.

### Tasks

- Load Evoran sprites.
- Load Guardian sprites.
- Load UI icons.
- Load fonts.
- Avoid loading same asset multiple times.

### Required Files

```text
include/Engine/AssetManager.h
src/Engine/AssetManager.cpp
assets/sprites/
assets/guardians/
assets/ui/
```

### Done When

Assets can be loaded and displayed in a raylib window.

---

## Milestone 23 — Board Rendering

### Goal

Draw the 40-tile board visually.

### Tasks

- Draw square board layout.
- Draw 40 tiles.
- Color tiles by element/type.
- Draw Origin Gate.
- Draw Guardian corners.
- Draw Teleport terminals.
- Draw event tiles.

### Required Files

```text
include/Graphics/BoardRenderer.h
src/Graphics/BoardRenderer.cpp
include/Scenes/BoardScene.h
src/Scenes/BoardScene.cpp
```

### Done When

The GUI shows a playable board layout.

---

## Milestone 24 — Player Token Rendering

### Goal

Show players moving on the board.

### Tasks

- Draw player tokens.
- Map board index to screen position.
- Move token when player moves.
- Show multiple players on same tile.

### Required Files

```text
include/Graphics/PlayerRenderer.h
src/Graphics/PlayerRenderer.cpp
```

### Done When

Player movement is visible on the GUI board.

---

## Milestone 25 — GUI UI Renderer

### Goal

Display important game state visually.

### Tasks

- Show current player.
- Show Avatar Points.
- Show Evolution Gems.
- Show owned Evorans.
- Show Energy Orb result.
- Show action messages.
- Show buttons/placeholders.

### Required Files

```text
include/Graphics/UIRenderer.h
src/Graphics/UIRenderer.cpp
include/Graphics/CardRenderer.h
src/Graphics/CardRenderer.cpp
```

### Done When

A user can understand the current game state from the GUI.

---

## Milestone 26 — GUI Input

### Goal

Replace terminal input with keyboard/mouse input.

### Tasks

- Click/start game.
- Select starter.
- Click roll/cast orbs.
- Select Evoran for battle.
- Select Evoran for evolution.
- End turn.

### Required Files

```text
include/Engine/InputManager.h
src/Engine/InputManager.cpp
include/Scenes/BoardScene.h
src/Scenes/BoardScene.cpp
```

### Done When

The game can be played through GUI interaction instead of terminal typing.

---

## Milestone 27 — Battle and Capture GUI

### Goal

Display battle-before-capture visually.

### Tasks

- Show player Evoran.
- Show wild Evoran.
- Show HP values.
- Show attack result.
- Show capture result.
- Return to board after encounter.

### Required Files

```text
include/Scenes/BattleScene.h
src/Scenes/BattleScene.cpp
include/Graphics/CardRenderer.h
src/Graphics/CardRenderer.cpp
```

### Done When

A wild Evoran encounter can be understood visually.

---

## Milestone 28 — Event, Teleport, Guardian, Evolution GUI

### Goal

Visualize all major terminal game actions.

### Tasks

- Show event card popup.
- Show teleport message/animation placeholder.
- Show Guardian encounter result.
- Show evolution result.
- Show special ownable tile result.

### Done When

All terminal actions have GUI feedback.

---

## Milestone 29 — GUI Polish and Final Presentation Build

### Goal

Make the GUI version presentable.

### Tasks

- Improve layout.
- Add sprites.
- Add icons.
- Add readable fonts.
- Add simple animations if possible.
- Remove debug output.
- Test full match flow.

### Done When

The GUI game can be demonstrated clearly in front of teachers.

---

# Final Completion Criteria

The project is complete when:

```text
- Terminal version runs fully from start to winner.
- GUI version shows the board and game state.
- Core logic is separated from rendering.
- Git commits are small and meaningful.
- Team members can explain their own code.
- Documentation explains architecture, rules, milestones, and workflow.
```
