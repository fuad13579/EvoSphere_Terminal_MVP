# EvoSphere Development Roadmap

This roadmap explains exactly how to build **EvoSphere** step by step, starting from the current GitHub project structure and ending with a playable GUI version.

EvoSphere is a turn-based fantasy board strategy game inspired by Monopoly-style board movement and Pokemon-style creature capture/evolution. The first goal is a **terminal MVP**. The second goal is a **GUI/raylib version** that reuses the same core logic.

---

## Current Project Structure Reference

The uploaded GitHub ZIP already contains a good skeleton:

```text
EvoSphere_MVP-main/
├── assets/
│   ├── guardians/
│   ├── sprites/
│   └── ui/
├── docs/
│   ├── EvoSphere_Current_Gameplay_Logic.md
│   ├── evosphere_evoran_roster.md
│   ├── architecture.md
│   ├── asset-pipeline.md
│   ├── gameplay-rules.md
│   ├── git-workflow.md
│   ├── progress.md
│   └── roadmap.md
├── include/
│   ├── Console/
│   ├── Core/
│   ├── Engine/
│   ├── Graphics/
│   ├── Scenes/
│   ├── Systems/
│   ├── Utils/
│   └── data/
├── src/
│   ├── Console/
│   ├── Core/
│   ├── Engine/
│   ├── Graphics/
│   ├── Scenes/
│   ├── Systems/
│   └── main.cpp
├── tests/
├── tools/
├── CMakeLists.txt
├── README.md
└── .gitignore
```

Important observation:

```text
Most code files are currently empty placeholders.
That is good for planning, but now the team must fill them in a controlled order.
```

---

# Roadmap Overview

The development is divided into two major sections:

```text
Section 1: From scratch to terminal version
Section 2: From terminal version to GUI version
```

The most important engineering rule:

```text
Core game logic must not depend on terminal or GUI.
Terminal and GUI are only different ways to display and control the same game.
```

That means:

```text
Core/      = game objects and rules
Systems/   = gameplay mechanics
Console/   = terminal input/output
Graphics/  = visual rendering later
Engine/    = GUI application framework later
Scenes/    = GUI screens later
```

---

# Section 1 — From Scratch to Terminal Version

## Terminal Version Goal

The terminal version should allow players to:

```text
1. Start the game
2. Choose 2 or 3 players
3. Choose starter Evorans
4. Move around a 40-tile board using two Energy Orbs
5. Battle and capture wild Evorans
6. Own Evoran tiles
7. Damage opponents through owned tiles
8. Trigger Blessing Shrine and Chaos Rift events
9. Use Teleport Terminals
10. Challenge Guardian Evorans
11. Own special relic/resource tiles
12. Evolve Evorans using Evolution Gems
13. Lose when Avatar Points reach 0
14. Declare the last surviving player as winner
```

---

## Terminal Development Rule

For the terminal version, focus only on these folders:

```text
include/Core/
src/Core/
include/Systems/
src/Systems/
include/Console/
src/Console/
include/data/
src/data/          <-- create this folder
include/Utils/
src/main.cpp
CMakeLists.txt
README.md
docs/
tests/
```

Ignore these until the GUI stage:

```text
include/Engine/
src/Engine/
include/Graphics/
src/Graphics/
include/Scenes/
src/Scenes/
assets/
```

They can stay in the repo, but do not build the terminal version around them.

---

## Phase 0 — Repository Setup and Cleanup

### Objective
Make the project clean, buildable, and team-ready.

### Files to work on

```text
CMakeLists.txt
README.md
.gitignore
docs/git-workflow.md
docs/progress.md
```

### Tasks

```text
1. Add a proper CMakeLists.txt.
2. Set C++ standard to C++17.
3. Make sure src/main.cpp is included in the build.
4. Add include/ as an include directory.
5. Update README.md with setup and run commands.
6. Keep main as stable branch and dev as development branch.
7. Protect main from direct pushes.
8. Use feature branches for team work.
```

### Important cleanup

The current project has both:

```text
include/Console/ConsoleRenderer.h
include/Console/ConsoleRenderer.hpp
```

Choose one style. Recommended:

```text
Keep:    ConsoleRenderer.hpp
Remove:  ConsoleRenderer.h
```

Do this to avoid confusion.

### Acceptance criteria

```text
The project can compile and print: "Welcome to EvoSphere".
```

### Suggested branch

```text
chore/project-build-setup
```

---

## Phase 1 — Constants, Enums, and Random Utility

### Objective
Create shared constants and types before writing game structs and functions.

### Files to complete

```text
include/Utils/Constants.h
include/Utils/Random.h
```

Optional later:

```text
include/Utils/Logger.h
```

### Tasks

Create constants:

```text
BOARD_SIZE = 40
STARTING_AVATAR_POINTS = 100
MAX_AVATAR_POINTS = 120
STARTING_EVOLUTION_GEMS = 0
EVOLUTION_COST = 3
ORIGIN_GATE_REWARD_GEMS = 1
ORIGIN_GATE_HEAL_AMOUNT = 10
CAPTURE_HP_THRESHOLD_PERCENT = 30
```

Create enums:

```cpp
ElementType
TileType
EvoranCategory
EventType
GamePhase
```

Suggested enum values:

```text
ElementType:
None, Fire, Water, Nature, Electric, Rock, Air, Dark, Mystic

TileType:
OriginGate, WildEvoran, Guardian, Teleport, BlessingShrine, ChaosRift, SpecialOwnable

EvoranCategory:
Starter, Wild, Guardian

EventType:
Blessing, Chaos
```

Create random helper functions:

```text
rollOrb()             -> returns 1 to 6
rollTwoOrbs()         -> returns orb1, orb2, total
randomIndex(max)      -> returns random valid index
```

### Acceptance criteria

```text
All other files can include Constants.h without duplicate definitions.
Random orb rolls work from 1 to 6.
```

### Suggested branch

```text
feature/constants-random
```

---

## Phase 2 — Evoran Core Model

### Objective
Build the main Evoran struct used by starters, wild Evorans, captured Evorans, and guardians.

### Files to complete

```text
include/Core/Evoran.h
src/Core/Evoran.cpp
```

### Required fields

```text
name
evolvedName
elementType
category
maxHp
currentHp
damage
evolvedMaxHp
evolvedDamage
isEvolved
ownerId
```

### Required functions

```text
getName()
getDisplayName()
getElementType()
getCurrentHp()
getMaxHp()
getDamage()
getOwnerId()
setOwnerId()
takeDamage(amount)
heal(amount)
isDefeated()
canEvolve()
evolve()
resetHp()
```

### Acceptance criteria

```text
Can create Cindroki, Leafari, Aquillo, and Voltrik.
Can damage an Evoran.
Can evolve an Evoran once.
Evolved Evoran has increased HP and damage.
```

### Suggested branch

```text
feature/evoran-model
```

---

## Phase 3 — Player Core Model

### Objective
Create the player/avatar state using structured programming.

The project uses plain `struct` data and separate functions. Do not use a
`class`, private members, constructors, or member functions for this phase.

### Files to complete

```text
include/Core/Player.h
src/Core/Player.cpp
```

### Required struct fields

```text
playerId
avatarName
avatarPoints
evolutionGems
currentPosition
ownedEvorans
isDefeated
```

### Required free functions

```text
getPlayerId(player)
getAvatarName(player)
getAvatarPoints(player)
getEvolutionGems(player)
getCurrentPosition(player)
movePlayerTo(player, position)
addEvolutionGems(player, amount)
spendEvolutionGems(player, amount)
takeAvatarDamage(player, amount)
healAvatar(player, amount)
addEvoran(player, evoran)
getOwnedEvorans(player)
hasOwnedEvorans(player)
getStrongestEvoran(player)
isDefeated(player)
isAlive(player)
```

Example style:

```cpp
struct Player
{
    int playerId;
    std::string avatarName;
    int avatarPoints;
    int evolutionGems;
    int currentPosition;
    std::vector<Evoran> ownedEvorans;
};

void takeAvatarDamage(Player* player, int amount);
bool isDefeated(const Player* player);
```

Functions that only read player data should use `const Player*`. Functions that
modify a player should use `Player*`.

### Acceptance criteria

```text
Can create 2 or 3 players.
Each player can receive a starter Evoran.
Each player can move positions.
Each player can take Avatar Point damage.
Player becomes defeated when Avatar Points reach 0.
```

### Suggested branch

```text
feature/player-model
```

---



---

## Phase 3A — Game State and Coordinator

### Objective
Create the central game-state structure that connects players, the board, and
the gameplay systems.

### Files to complete

```text
include/Core/Game.h
src/Core/Game.cpp
```

### Responsibilities

```text
- Store the current players and player count.
- Store the current board and game status.
- Initialize a new game.
- Track whether the game is over.
- Detect defeated players.
- Find the last active player.
- Store the winner information.
- Coordinate calls between Core and Systems functions.
```

`Game.cpp` should coordinate the game without duplicating movement, battle,
capture, event, or evolution rules. Those rules belong in their own Systems
files.

### Acceptance criteria

```text
Game state can be initialized safely.
Active players can be counted.
Defeated players are skipped.
The winner is detected when only one active player remains.
```

### Suggested branch

```text
feature/game-state-coordinator
```

## Phase 4 — Tile Core Model

### Objective
Represent every board space as a tile.

### Files to complete

```text
include/Core/Tile.h
src/Core/Tile.cpp
```

### Required fields

```text
index
name
tileType
elementType
ownerId
linkedEvoranName
territoryName
```

### Required functions

```text
getIndex()
getName()
getTileType()
getElementType()
getOwnerId()
setOwnerId()
isOwned()
isOwnedBy(playerId)
isOwnedByOpponent(playerId)
getLinkedEvoranName()
setLinkedEvoranName()
getTerritoryName()
```

### Acceptance criteria

```text
Can create Origin Gate tile.
Can create Wild Evoran tile.
Can create Guardian tile.
Can create Teleport tile.
Can set and read tile owner.
```

### Suggested branch

```text
feature/tile-model
```

---

### Phase 5 — Static Game Data



### Objective
Move fixed game data out of main.cpp and into database/data files.

### Existing headers

```text
include/data/EvoranDatabase.hpp
include/data/BoardData.hpp
include/data/EventDatabase.hpp
```

### Source files to create

```text
src/data/EvoranDatabase.cpp
src/data/BoardData.cpp
src/data/EventDatabase.cpp
```

### EvoranDatabase tasks

```text
1. Return 4 starter Evorans.
2. Return 23 wild Evorans.
3. Return 3 Guardian Evorans.
4. Search Evoran by name.
```

### BoardData tasks

```text
1. Define all 40 tile positions.
2. Assign tile type for each index.
3. Assign element and territory name.
4. Assign linked Evoran names to wild Evoran tiles.
5. Assign Guardian names to Guardian tiles.
6. Store 4 Teleport Terminal indexes.
```

### EventDatabase tasks

```text
1. Define at least 3 Blessing Shrine events.
2. Define at least 3 Chaos Rift events.
3. Return random event by type.
```

### Acceptance criteria

```text
Game data can be created without hardcoding inside main.cpp.
Board has exactly 40 tiles.
Starter and wild Evoran lists are available from database files.
```

### Suggested branch

```text
feature/game-data
```



---

## Phase 6 — Board System

### Objective
Create the playable 40-tile board.

### Files to complete

```text
include/Core/Board.h
src/Core/Board.cpp
```

### Required fields

```text
vector<Tile> tiles
map<string, Evoran> evoransByName
vector<int> teleportTileIndexes
```

### Required functions

```text
initializeBoard()
getTile(index)
getTileConst(index)
getBoardSize()
setTileOwner(index, playerId)
getTeleportTileIndexes()
getEvoranOnTile(index)
updateEvoranOnTile(index, evoran)
printDebugBoard()
getTerritoryTiles(territoryName)
doesPlayerOwnTerritory(playerId, territoryName)
```

### Acceptance criteria

```text
Board creates exactly 40 tiles.
Board can return tile information by index.
Board can update tile ownership.
Board can list teleport terminal positions.
Board can check territory ownership.
```

### Suggested branch

```text
feature/board-system
```

---

## Phase 7 — Movement System

### Objective
Move players around the board using two Energy Orbs.

### Files to complete

```text
include/Systems/MovementSystem.h
src/Systems/MovementSystem.cpp
```

### Required functions

```text
rollEnergyOrbs()
movePlayer(Player& player, int rollTotal)
didPassOriginGate(oldPosition, newPosition, rollTotal)
applyOriginGateReward(Player& player)
```

### Rules

```text
Player position wraps after tile 39.
If player passes or lands on Origin Gate after a full loop, player gets reward.
Origin Gate reward: +1 Evolution Gem and +10 Avatar Points.
Passing Origin Gate also revives each defeated owned Evoran with 50% of its maximum HP.
```

### Acceptance criteria

```text
Player can roll two Energy Orbs.
Player position updates correctly.
Position wraps around the 40-tile board.
Passing Origin Gate gives rewards.
Passing Origin Gate revives defeated owned Evorans at 50% maximum HP.
```

### Suggested branch

```text
feature/movement-system
```

---

## Phase 8 — Turn Manager

### Objective
Control player turns.

### Files to complete

```text
include/Core/TurnManager.h
src/Core/TurnManager.cpp
```

### Required fields

```text
currentPlayerIndex
roundNumber
```

### Required functions

```text
getCurrentPlayer(players)
nextTurn(players)
skipDefeatedPlayers(players)
getRoundNumber()
getAlivePlayerCount(players)
getWinner(players)
```

### Rules

```text
Turns rotate between players.
Defeated players are skipped.
A new round starts after the last alive player completes a turn.
Game ends when one player remains alive.
```

### Acceptance criteria

```text
Works for both 2-player and 3-player games.
Current player changes correctly.
Defeated players do not get turns.
Round number increases correctly.
```

### Suggested branch

```text
feature/turn-manager
```

---

## Phase 9 — Console Input and Renderer

### Objective
Create a clean terminal interface.

### Files to complete

```text
include/Console/ConsoleInput.hpp
src/Console/ConsoleInput.cpp

include/Console/ConsoleRenderer.hpp
src/Console/ConsoleRenderer.cpp
```

### ConsoleInput responsibilities

```text
askPlayerCount()
askAvatarName(playerNumber)
askStarterChoice(starterList)
askEvoranChoice(ownedEvorans)
askMenuChoice()
waitForEnter()
```

### ConsoleRenderer responsibilities

```text
printWelcome()
printGameRulesSummary()
printPlayerStatus(player)
printTurnStart(player, roundNumber)
printRollResult(orb1, orb2, total)
printMovementResult(oldPosition, newPosition)
printTileInfo(tile)
printBattleResult()
printCaptureResult()
printEventResult()
printEvolutionResult()
printGuardianResult()
printWinner(player)
printError(message)
```

### Acceptance criteria

```text
No game rule should be hidden.
A viewer should understand the demo from terminal output alone.
Input validation prevents crashes from wrong numbers.
```

### Suggested branch

```text
feature/console-interface
```

---

## Phase 10 — ConsoleGame and Main Game Loop

### Objective
Connect player creation, starter selection, board creation, movement, and turn switching into a runnable terminal loop.

### Files to complete

```text
include/Console/ConsoleGame.hpp
src/Console/ConsoleGame.cpp
src/main.cpp
```

### main.cpp rule

`main.cpp` should stay very small:

```cpp
#include "Console/ConsoleGame.hpp"

int main() {
    ConsoleGame game;
    game.run();
    return 0;
}
```

### ConsoleGame responsibilities

```text
setupGame()
createPlayers()
selectStarters()
initializeBoard()
run()
runTurn()
resolveTileAction()
checkGameOver()
```

### Acceptance criteria

```text
The game starts from main.cpp.
Players are created.
Starters are selected.
Board is initialized.
Players roll and move.
Turns switch.
Landed tile information is shown.
```

### Milestone 1: Movement-only terminal game

At this point, the game should run even without capture, battle, events, guardians, or evolution.

Expected flow:

```text
Welcome to EvoSphere
Choose player count
Enter avatar names
Choose starter Evorans
Player 1 turn
Roll: 3 + 4 = 7
Move to Tile 7
Show tile information
Player 2 turn
...
```

### Suggested branch

```text
feature/terminal-game-loop
```

---

## Phase 11 — Battle System

### Objective
Create reusable battle logic for wild capture battles and future GUI battle scenes. Guardian effects are handled separately.

### Files to complete

```text
include/Systems/BattleSystem.h
src/Systems/BattleSystem.cpp
```

### Required functions

```text
attack(Evoran& attacker, Evoran& defender)
runWildBattle(Player& player, Evoran& selectedEvoran, Evoran& wildEvoran)
calculatePower(Evoran evoran)
resolveOpponentTileDamage(Player& currentPlayer, Evoran defendingEvoran)
applyGuardianEffect(Player* player, const Guardian* guardian)
```

### Rules

```text
Damage reduces Evoran HP in Evoran-vs-Evoran battle.
Landing on an opponent-owned Evoran tile starts an Evoran-vs-Evoran battle.
Normal battle damage does not reduce Avatar Points directly.
A defeated Evoran cannot battle, capture, or defend its tile.
It remains owned and cannot capture a Wild Evoran.
It revives with 50% of its maximum HP when its owner completes a full lap and passes Origin Gate.
When a player's last active Evoran is defeated, apply a one-time 20 Avatar Point penalty.
```

### Acceptance criteria

```text
Selected player Evoran can damage wild Evoran.
Wild Evoran can attack back.
Evoran defeat is detected.
Opponent-owned tile battle damages Evorans but not Avatar Points directly.
The player is eliminated only when Avatar Points reach 0.
```

### Suggested branch

```text
feature/battle-system
```

---

## Phase 12 — Capture System

### Objective
Implement official battle-before-capture rule.

### Files to complete

```text
include/Systems/CaptureSystem.h
src/Systems/CaptureSystem.cpp
```

### Required functions

```text
canCapture(wildEvoran)
captureEvoran(Player& player, Board& board, tileIndex)
handleWildEvoranEncounter(Player& player, Board& board, tileIndex)
```

### Rules

```text
A wild Evoran cannot be captured directly.
The player selects one owned Evoran.
The selected Evoran battles the wild Evoran.
If the wild Evoran HP becomes 30% or less, capture succeeds automatically.
Captured Evoran is added to the player's owned list.
The tile owner becomes the current player.
If the player has no active Evorans, they cannot start a Wild Evoran battle.
```

### Acceptance criteria

```text
Player must battle before capture.
Capture cannot happen at full HP.
Captured Evoran becomes owned by player.
Captured tile becomes owned by player.
If player selected Evoran loses, capture fails.
```

### Suggested branch

```text
feature/capture-system
```

---

## Phase 13 — Opponent-Owned Tile Battle

### Objective
Make tile ownership meaningful and make the game progress toward an ending.

### Files involved

```text
include/Systems/BattleSystem.h
src/Systems/BattleSystem.cpp
include/Core/Game.h
src/Core/Game.cpp
include/Core/Board.h
src/Core/Board.cpp
```

### Rule

```text
If a player lands on an opponent-owned Evoran tile:
    current player selects one active owned Evoran.
    selected Evoran battles the defending Evoran.
    both attacks reduce Evoran HP only.
    the defender counterattacks only if it remains active.
    normal battle damage does not reduce Avatar Points directly.
```

### Acceptance criteria

```text
Landing on own tile causes no battle.
Landing on wild tile starts capture encounter.
Landing on opponent-owned tile starts Evoran-vs-Evoran battle.
Defeated defending Evorans cannot battle, but their tiles remain owned.
The last-active-Evoran penalty can still defeat a player through Avatar Point loss.
```

### Suggested branch

```text
feature/opponent-tile-damage
```

---

## Phase 14 — Event System

### Objective
Implement Blessing Shrine and Chaos Rift effects.

### Files to complete

```text
include/Core/EventCard.h
src/Core/EventCard.cpp
include/Systems/EventSystem.h
src/Systems/EventSystem.cpp
include/data/EventDatabase.hpp
src/data/EventDatabase.cpp
```

### Required event types

```text
Blessing Shrine = positive event
Chaos Rift = negative/risky event
```

### Minimum Blessing effects

```text
Gain 1 Evolution Gem
Heal 15 Avatar Points
Increase selected Evoran HP by 15
```

### Minimum Chaos effects

```text
Lose 15 Avatar Points
Lose 1 Evolution Gem if available
Move backward 3 tiles
```

### Acceptance criteria

```text
Blessing Shrine randomly triggers a positive event.
Chaos Rift randomly triggers a negative/risky event.
Event effect changes player state correctly.
Terminal output clearly explains the event.
```

### Suggested branch

```text
feature/event-system
```

---

## Phase 15 — Teleport System

### Objective
Implement 4 Teleport Terminals.

### Files to complete

```text
include/Systems/TeleportSystem.h
src/Systems/TeleportSystem.cpp
```

### Required functions

```text
isTeleportTile(tile)
chooseDestination(currentTeleportIndex, teleportIndexes)
teleportPlayer(Player& player, Board& board)
```

### Rules

```text
There are 4 Teleport Terminal tiles.
When a player lands on one, they move randomly to a different Teleport Terminal.
The player cannot teleport to the same terminal.
```

### Acceptance criteria

```text
Player teleports only from teleport tiles.
Destination is another teleport terminal.
Player position updates correctly.
Terminal output shows source and destination.
```

### Suggested branch

```text
feature/teleport-system
```

---

## Phase 16 — Evolution System

### Objective
Allow one-step Evoran evolution.

### Files to complete

```text
include/Systems/EvolutionSystem.h
src/Systems/EvolutionSystem.cpp
```

### Required functions

```text
canEvolve(player, evoran)
evolveSelectedEvoran(Player& player, evoranIndex)
showEvolutionOptions(player)
```

### Rules

```text
3 Evolution Gems = evolve one owned Evoran.
Each Evoran evolves only once.
Evolution increases HP and damage.
Evolution Gems are deducted after successful evolution.
```

### Acceptance criteria

```text
Player cannot evolve without enough gems.
Player cannot evolve an already evolved Evoran.
Evolved Evoran has updated name, HP, and damage.
Evolution result is shown in terminal.
```

### Suggested branch

```text
feature/evolution-system
```

---

## Phase 17 — Guardian System

### Objective
Add 3 legendary Guardian encounters.

### Files to complete

```text
include/Core/Guardian.h
src/Core/Guardian.cpp
```

Also use:

```text
include/Systems/BattleSystem.h
src/Systems/BattleSystem.cpp
```

### Guardians

```text
Solvyrion  - Radiance / Preservation
Noctharax  - Ruin / Corruption
Aequorion  - Balance / Fate
```

### MVP rules

```text
Player lands on Guardian tile.
Identify the Guardian.
Solvyrion randomly grants one blessing: +20 Avatar Points, +2 Evolution Gems,
or +10 Avatar Points and +1 Evolution Gem.
Noctharax randomly applies one curse: -35 Avatar Points, -1 Evolution Gem,
or -15 Avatar Points.
Aequorion lets the player choose Balance or Fate.
Balance gives +10 Avatar Points and +1 Evolution Gem.
Fate has a 50% chance for +25 Avatar Points and +2 Evolution Gems,
or a 50% chance for -25 Avatar Points.
Update player Avatar Points and Evolution Gems.
```

### Possible rewards

```text
Solvyrion: Randomly gain 2 Evolution Gems, heal 20 Avatar Points,
or gain 1 Evolution Gem and heal 10 Avatar Points
Aequorion Balance: Gain 1 Evolution Gem and heal 10 Avatar Points
Aequorion Fate success: Gain 2 Evolution Gems and heal 25 Avatar Points
```

### Possible loss penalty

```text
Noctharax: Randomly lose 35 Avatar Points, 1 Evolution Gem, or 15 Avatar Points
Aequorion Fate failure: Lose 25 Avatar Points
```

### Acceptance criteria

```text
Solvyrion randomly selects one blessing and Noctharax randomly selects one curse.
Aequorion supports the Balance or Fate player choice.
Each Guardian has a name, title, type, special power, blessing, and curse.
The effect updates the player's Avatar Points, Evolution Gems, or position.
Terminal output explains the encounter.
```

### Suggested branch

```text
feature/guardian-system
```

---

## Phase 18 — Special Ownable Tile System

### Objective
Implement the 3 unknown ownable tiles as relic/resource tiles.

### Suggested tile names

```text
Gemstone Mine
Orb Forge
Ancient Relic Shrine
```

### Files involved

```text
include/Core/Tile.h
src/Core/Tile.cpp
include/Core/Board.h
src/Core/Board.cpp
include/Core/Game.h
src/Core/Game.cpp
```

### MVP rules

```text
If unowned: current player claims the tile.
If owned by current player: current player receives a small reward.
If owned by opponent: owner receives a reward or current player receives a penalty.
When owner passes Origin Gate: each owned special tile gives an extra reward.
```

### Simple first implementation

```text
Each owned special tile gives +1 Evolution Gem when the owner passes Origin Gate.
```

### Acceptance criteria

```text
There are exactly 3 special ownable tiles.
Players can claim unowned special tiles.
Ownership is stored correctly.
Special tile rewards trigger correctly.
Terminal output explains what happened.
```

### Suggested branch

```text
feature/special-ownable-tiles
```

---

## Phase 19 — Territory Control Bonus

### Objective
Reward players for completing a full elemental territory.

### Files involved

```text
include/Core/Board.h
src/Core/Board.cpp
include/Core/Game.h
src/Core/Game.cpp
include/Systems/BattleSystem.h
src/Systems/BattleSystem.cpp
```

### MVP rule

```text
If a player owns all Evorans in one territory:
    Evorans in that territory deal +5 bonus damage when defending the tile.
```

### Optional later territory bonuses

```text
Nature   -> heal after battle
Fire     -> bonus damage
Water    -> damage reduction
Electric -> movement bonus
Rock     -> defense bonus
Air      -> teleport/movement advantage
Dark     -> extra Avatar damage
Mystic   -> event control
```

### Acceptance criteria

```text
Board can detect full territory ownership.
Territory bonus applies only to the correct owner.
Bonus is shown in terminal.
```

### Suggested branch

```text
feature/territory-bonus
```

---

## Phase 20 — Win Condition and Game Over

### Objective
End the game correctly.

### Files involved

```text
include/Core/Game.h
src/Core/Game.cpp
include/Core/TurnManager.h
src/Core/TurnManager.cpp
include/Console/ConsoleRenderer.hpp
src/Console/ConsoleRenderer.cpp
```

### Rules

```text
If Avatar Points <= 0, player is defeated.
Defeated players are skipped.
Game ends when only one player remains alive.
Last alive player is the winner.
```

### Acceptance criteria

```text
Player defeat is detected immediately.
Defeated players stop taking turns.
Winner is printed clearly.
Game loop stops after winner is declared.
```

### Suggested branch

```text
feature/win-condition
```

---

## Phase 21 — Tests for Terminal Version

### Objective
Protect the logic from breaking.

### Existing test files

```text
tests/test_board.cpp
tests/test_capture.cpp
tests/test_event.cpp
tests/test_evoran.cpp
tests/test_guardian.cpp
tests/test_movement.cpp
tests/test_player.cpp
tests/test_teleport.cpp
tests/test_turn.cpp
tests/test_turn_manager.cpp
```

### Minimum tests before terminal MVP demo

```text
1. Evoran can take damage and evolve.
2. Player can receive starter and take Avatar damage.
3. Board has exactly 40 tiles.
4. Movement wraps correctly after tile 39.
5. Passing Origin Gate gives reward.
6. TurnManager skips defeated players.
7. Capture succeeds after wild HP <= 30%.
8. Teleport never selects same terminal.
9. Event effects modify player state.
10. Game ends when one player remains.
```

### Suggested branch

```text
test/terminal-core-systems
```

---

## Phase 22 — Terminal Polish and Demo Readiness

### Objective
Make the terminal version understandable for presentation.

### Files involved

```text
src/Console/ConsoleRenderer.cpp
src/Console/ConsoleGame.cpp
README.md
docs/gameplay-rules.md
docs/progress.md
```

### Tasks

```text
1. Add clean turn separators.
2. Show player Avatar Points, Evolution Gems, position, and owned Evorans.
3. Show roll result clearly.
4. Show tile action clearly.
5. Show battle and capture clearly.
6. Show event/teleport/evolution/guardian result clearly.
7. Add press-enter pauses between turns.
8. Remove debug-only messages.
9. Update README run instructions.
10. Update progress.md with completed systems.
```

### Acceptance criteria

```text
A non-programmer can understand what is happening by watching the terminal.
A full match can start, progress, and end.
```

### Suggested branch

```text
feature/terminal-demo-polish
```

---

## Terminal Version Final Definition of Done

The terminal version is ready only when all items below work:

```text
[ ] Project builds successfully with CMake.
[ ] Game starts from main.cpp.
[ ] 2-player and 3-player setup works.
[ ] Starter selection works.
[ ] 40-tile board is initialized.
[ ] Two Energy Orbs movement works.
[ ] Passing Origin Gate gives rewards.
[ ] Wild Evoran battle-before-capture works.
[ ] Captured tile ownership works.
[ ] Opponent-owned tile battle works.
[ ] Blessing Shrine events work.
[ ] Chaos Rift events work.
[ ] Teleport Terminals work.
[ ] Evolution works.
[ ] Guardian encounters work.
[ ] Special ownable tiles work.
[ ] Territory bonus works at least simply.
[ ] Avatar Point defeat works.
[ ] Winner is declared.
[ ] Terminal output is clean enough for demo.
[ ] README has setup and run instructions.
```

---

# Section 2 — From Terminal Version to GUI Version

## GUI Version Goal

The GUI version should use raylib to visually represent the same terminal game logic.

Important rule:

```text
Do not rewrite the game logic for GUI.
Reuse Core/ and Systems/.
Only replace Console/ with Engine/ + Graphics/ + Scenes/.
```

---

## GUI Folder Responsibilities

The current repo already has GUI-ready folders:

```text
include/Engine/
src/Engine/
include/Graphics/
src/Graphics/
include/Scenes/
src/Scenes/
assets/
```

Use them like this:

```text
Engine/    -> application loop, window, input, time, scene switching
Graphics/  -> draw board, players, cards, UI, sprites
Scenes/    -> menu screen, board screen, battle screen
assets/    -> sprite PNGs, guardian art, UI images, fonts later
```

---

## GUI Phase 0 — Freeze Terminal Logic API

### Objective
Prepare Core/ and Systems/ so GUI can call them without terminal code.

### Files to review

```text
include/Core/Game.h
src/Core/Game.cpp
include/Core/Board.h
src/Core/Board.cpp
include/Core/Player.h
src/Core/Player.cpp
include/Core/Tile.h
src/Core/Tile.cpp
include/Systems/*.h
src/Systems/*.cpp
```

### Tasks

```text
1. Remove direct cout/cin from Core/ and Systems/.
2. Return result objects or status strings instead of printing inside logic.
3. Keep printing only inside Console/.
4. Make Game expose clean functions for GUI.
```

### Suggested Game API for GUI

```text
startNewGame(playerNames, starterChoices)
getCurrentPlayer()
rollAndMoveCurrentPlayer()
resolveCurrentTileAction()
selectEvoranForBattle(index)
selectEvoranForEvolution(index)
endTurn()
isGameOver()
getWinner()
getBoardState()
getPlayers()
```

### Acceptance criteria

```text
Terminal still works.
Core/ and Systems/ do not depend on Console/.
GUI can read game state without parsing terminal text.
```

### Suggested branch

```text
refactor/game-api-for-gui
```

---

## GUI Phase 1 — raylib and CMake Setup

### Objective
Make a blank raylib window compile and run.

### Files to complete

```text
CMakeLists.txt
include/Engine/Application.h
src/Engine/Application.cpp
include/Engine/WindowManager.h
src/Engine/WindowManager.cpp
```

### Tasks

```text
1. Add raylib dependency to CMake.
2. Create a raylib window.
3. Set window title to EvoSphere.
4. Run basic event loop.
5. Close window correctly.
```

### Acceptance criteria

```text
Running the GUI build opens a blank EvoSphere window.
Window closes correctly.
No game logic needed yet.
```

### Suggested branch

```text
feature/raylib-window-setup
```

---

## GUI Phase 2 — Engine Layer

### Objective
Build the basic reusable game application layer.

### Files to complete

```text
include/Engine/Application.h
src/Engine/Application.cpp
include/Engine/InputManager.h
src/Engine/InputManager.cpp
include/Engine/Time.h
src/Engine/Time.cpp
include/Engine/SceneManager.h
src/Engine/SceneManager.cpp
include/Engine/AssetManager.h
src/Engine/AssetManager.cpp
```

### Responsibilities

```text
Application      -> main update/render loop
WindowManager    -> raylib window ownership
InputManager     -> mouse/keyboard input
Time             -> delta time and frame timing
SceneManager     -> switch between MenuScene, BoardScene, BattleScene
AssetManager     -> load textures/fonts once and reuse
```

### Acceptance criteria

```text
Application can run update/render loop.
SceneManager can hold current scene.
InputManager can detect basic input.
AssetManager can load a test texture.
```

### Suggested branch

```text
feature/engine-layer
```

---

## GUI Phase 3 — Scene System

### Objective
Create screens for the game.

### Files to complete

```text
include/Scenes/Scene.h
include/Scenes/MenuScene.h
src/Scenes/MenuScene.cpp
include/Scenes/BoardScene.h
src/Scenes/BoardScene.cpp
include/Scenes/BattleScene.h
src/Scenes/BattleScene.cpp
```

### Scene responsibilities

```text
Scene       -> base interface: handleInput(), update(), render()
MenuScene   -> start game, choose players/starters later
BoardScene  -> main board view and turn flow
BattleScene -> battle/capture screen later
```

### Acceptance criteria

```text
MenuScene appears first.
Pressing Enter or clicking Start switches to BoardScene.
BoardScene can render placeholder board.
```

### Suggested branch

```text
feature/gui-scenes
```

---

## GUI Phase 4 — Board Renderer

### Objective
Draw the 40-tile board visually.

### Files to complete

```text
include/Graphics/BoardRenderer.h
src/Graphics/BoardRenderer.cpp
```

### Tasks

```text
1. Draw 40 tile rectangles around a square board.
2. Use different colors/icons for tile types.
3. Show tile index or short label.
4. Highlight current player positions.
5. Highlight owned tiles by player color.
6. Show Origin Gate, Teleports, Guardians, Blessing, Chaos, and Special tiles differently.
```

### Acceptance criteria

```text
The board is readable.
All 40 tiles appear.
Player token position is visible.
Owned tiles are visually distinguishable.
```

### Suggested branch

```text
feature/board-renderer
```

---

## GUI Phase 5 — Player and UI Renderers

### Objective
Show player stats and basic game HUD.

### Files to complete

```text
include/Graphics/PlayerRenderer.h
src/Graphics/PlayerRenderer.cpp
include/Graphics/UIRenderer.h
src/Graphics/UIRenderer.cpp
include/Graphics/CardRenderer.h
src/Graphics/CardRenderer.cpp
```

### PlayerRenderer tasks

```text
Draw player tokens.
Show current player highlight.
Animate simple movement later.
```

### UIRenderer tasks

```text
Show current turn.
Show Avatar Points.
Show Evolution Gems.
Show current tile.
Show orb roll result.
Show message log.
Show buttons/instructions.
```

### CardRenderer tasks

```text
Show selected Evoran card.
Show HP and damage.
Show evolved status.
Show Guardian/event card later.
```

### Acceptance criteria

```text
GUI shows board + players + current turn + player stats.
User can understand basic game state visually.
```

### Suggested branch

```text
feature/gui-hud-renderers
```

---

## GUI Phase 6 — Asset Pipeline

### Objective
Organize sprites, UI, guardians, and board art.

### Folders to use

```text
assets/sprites/
assets/guardians/
assets/ui/
docs/asset-pipeline.md
tools/asset_notes.md
```

### Naming convention

```text
assets/sprites/starters/cindroki.png
assets/sprites/starters/cindrava.png
assets/sprites/wild/mossari.png
assets/sprites/wild/mossarion.png
assets/guardians/solvyrion.png
assets/ui/origin_gate.png
assets/ui/teleport_terminal.png
assets/ui/blessing_shrine.png
assets/ui/chaos_rift.png
```

### Tasks

```text
1. Keep all sprites in consistent pixel-art style.
2. Use transparent PNG when possible.
3. Keep normal Evorans around the same visual scale.
4. Make Guardians larger than normal Evorans but still pixel-art.
5. Document asset source and usage in asset-pipeline.md.
```

### Acceptance criteria

```text
Assets are organized and easy to load.
No asset is randomly placed in root folder.
GUI can load at least one starter sprite and one tile icon.
```

### Suggested branch

```text
feature/asset-pipeline
```

---

## GUI Phase 7 — Connect Game Logic to BoardScene

### Objective
Make the GUI control the existing terminal game logic.

### Files involved

```text
src/Scenes/BoardScene.cpp
src/Graphics/BoardRenderer.cpp
src/Graphics/UIRenderer.cpp
src/Core/Game.cpp
```

### Tasks

```text
1. BoardScene owns or references a Game object.
2. GUI Start button creates players and starts game.
3. Roll button calls Game roll/move logic.
4. BoardRenderer reads Board state from Game.
5. UIRenderer reads Player state from Game.
6. End Turn button calls Game/TurnManager.
```

### Acceptance criteria

```text
Clicking/pressing roll moves the current player.
Board view updates after movement.
Turn switches correctly.
Terminal is no longer required to play basic movement.
```

### Suggested branch

```text
feature/gui-game-loop
```

---

## GUI Phase 8 — GUI Tile Actions

### Objective
Visually show events, teleport, capture, damage, and rewards.

### Files involved

```text
src/Scenes/BoardScene.cpp
src/Scenes/BattleScene.cpp
src/Graphics/UIRenderer.cpp
src/Graphics/CardRenderer.cpp
src/Core/Game.cpp
src/Systems/*.cpp
```

### Tasks

```text
1. Show popup/message when player lands on tile.
2. Show wild Evoran encounter panel.
3. Show opponent-owned Evoran battle message.
4. Show Blessing/Chaos event card.
5. Show teleport animation/message.
6. Show Origin Gate reward message.
7. Show special tile claim/reward message.
8. Show Guardian encounter result.
```

### Acceptance criteria

```text
Every terminal action has a GUI equivalent.
Game state remains controlled by Core/ and Systems/.
GUI only displays and collects choices.
```

### Suggested branch

```text
feature/gui-tile-actions
```

---

## GUI Phase 9 — Battle and Capture Scene

### Objective
Make battle-before-capture feel visual.

### Files to complete

```text
include/Scenes/BattleScene.h
src/Scenes/BattleScene.cpp
include/Graphics/CardRenderer.h
src/Graphics/CardRenderer.cpp
```

### Tasks

```text
1. Show player's selected Evoran.
2. Show wild Evoran.
3. Show HP bars.
4. Add Attack button.
5. Show damage numbers/message.
6. Enable capture once wild HP <= 30%.
7. Return to BoardScene after capture/fail.
```

### Acceptance criteria

```text
Wild battle can be completed in GUI.
Capture works visually.
Game state updates correctly after returning to board.
```

### Suggested branch

```text
feature/gui-battle-capture
```

---

## GUI Phase 10 — Starter Selection and Menu Flow

### Objective
Replace terminal setup with visual setup.

### Files involved

```text
src/Scenes/MenuScene.cpp
src/Graphics/CardRenderer.cpp
src/Core/Game.cpp
```

### Tasks

```text
1. Choose 2 or 3 players.
2. Enter or select avatar names.
3. Choose starter Evoran for each player.
4. Show starter stats.
5. Start BoardScene after setup.
```

### Acceptance criteria

```text
The GUI can start a new game without terminal input.
Players can select starters visually.
```

### Suggested branch

```text
feature/gui-menu-starter-selection
```

---

## GUI Phase 11 — Animation and Visual Polish

### Objective
Make the GUI feel like a game, not only a debug board.

### Tasks

```text
1. Add simple token movement animation.
2. Add orb/dice roll animation or visual result.
3. Add tile highlight on landing.
4. Add capture success/fail animation.
5. Add damage flash/message.
6. Add Guardian encounter visual emphasis.
7. Add clean fonts and UI panels.
8. Add background board art.
```

### Acceptance criteria

```text
The game is understandable and visually presentable.
The UI is not overloaded.
Core logic remains unchanged.
```

### Suggested branch

```text
feature/gui-polish
```

---

## GUI Phase 12 — Save/Load System

### Objective
Allow saving game progress later.

### Suggested new files

```text
include/Systems/SaveSystem.h
src/Systems/SaveSystem.cpp
```

### Save data

```text
players
avatar points
evolution gems
positions
owned Evorans
tile ownership
current turn
round number
```

### Acceptance criteria

```text
Game can save to a file.
Game can load from a file.
Loaded game continues correctly.
```

### Suggested branch

```text
feature/save-load-system
```

---

## GUI Phase 13 — Packaging and Demo Build

### Objective
Prepare a version others can run.

### Tasks

```text
1. Update README with GUI build instructions.
2. Add screenshots to README.
3. Make sure assets load using relative paths.
4. Create a demo script.
5. Test fresh clone build.
6. Tag release version.
```

### Suggested commands

```bash
cmake -S . -B build
cmake --build build
./build/EvoSphere
```

On Windows, executable path may differ:

```bash
./build/Debug/EvoSphere.exe
```

### Acceptance criteria

```text
A teammate can clone the repo, build, and run the GUI game.
Demo can be recorded without editing code.
```

### Suggested branch

```text
release/gui-demo-v1
```

---

# Suggested Team Division

## Member 1 — Board and Movement Lead

Focus folders:

```text
include/Core/Board.h
src/Core/Board.cpp
include/Core/Tile.h
src/Core/Tile.cpp
include/data/BoardData.hpp
src/data/BoardData.cpp
include/Systems/MovementSystem.h
src/Systems/MovementSystem.cpp
include/Systems/TeleportSystem.h
src/Systems/TeleportSystem.cpp
```

Terminal responsibilities:

```text
Board creation
Tile types
Movement
Origin Gate reward
Teleport Terminal
Territory detection
Special ownable tile support
```

GUI responsibilities later:

```text
BoardRenderer
Tile visuals
Player position rendering support
```

---

## Member 2 — Evoran, Player, Battle Lead

Focus folders:

```text
include/Core/Evoran.h
src/Core/Evoran.cpp
include/Core/Player.h
src/Core/Player.cpp
include/Core/Guardian.h
src/Core/Guardian.cpp
include/data/EvoranDatabase.hpp
src/data/EvoranDatabase.cpp
include/Systems/BattleSystem.h
src/Systems/BattleSystem.cpp
include/Systems/CaptureSystem.h
src/Systems/CaptureSystem.cpp
include/Systems/EvolutionSystem.h
src/Systems/EvolutionSystem.cpp
```

Terminal responsibilities:

```text
Starter Evorans
Wild Evorans
Player stats
Battle-before-capture
Opponent-owned tile battle
Evolution
Guardian effects
```

GUI responsibilities later:

```text
BattleScene support
Evoran cards
HP bars
Guardian display data
```

---

## Member 3 — Game Flow and Integration Lead

Focus folders:

```text
include/Core/Game.h
src/Core/Game.cpp
include/Core/TurnManager.h
src/Core/TurnManager.cpp
include/Core/EventCard.h
src/Core/EventCard.cpp
include/Systems/EventSystem.h
src/Systems/EventSystem.cpp
include/Console/ConsoleGame.hpp
src/Console/ConsoleGame.cpp
include/Console/ConsoleInput.hpp
src/Console/ConsoleInput.cpp
include/Console/ConsoleRenderer.hpp
src/Console/ConsoleRenderer.cpp
src/main.cpp
CMakeLists.txt
README.md
```

Terminal responsibilities:

```text
Main game loop
Turn flow
Console UI
Event system
Win condition
Integration testing
README/demo readiness
```

GUI responsibilities later:

```text
Application
SceneManager
MenuScene
BoardScene integration
UIRenderer
```

---

# Recommended Git Branch Strategy

Keep:

```text
main = stable/demo version
dev = active development integration branch
feature/* = task branches
```

For 3-member beginner workflow, these larger branches are acceptable:

```text
feature/board-system
feature/creature-system
feature/gameflow-system
```

But if a task becomes risky, create a smaller branch:

```text
feature/capture-system
feature/teleport-system
feature/evolution-system
feature/gui-board-renderer
```

Never push directly to main.

---

# Recommended GitHub Issue Order

Create issues in this order:

```text
1. Project build setup
2. Constants and random utility
3. Evoran model
4. Player model
5. Tile model
6. Static game data
7. Board system
8. Movement system
9. Turn manager
10. Console input and renderer
11. Console game loop
12. Battle system
13. Battle-before-capture system
14. Opponent-owned tile battle
15. Event system
16. Teleport system
17. Evolution system
18. Guardian system
19. Special ownable tiles
20. Territory bonus
21. Win condition
22. Terminal tests
23. Terminal demo polish
24. Refactor game API for GUI
25. raylib window setup
26. Engine layer
27. Scene system
28. Board renderer
29. Player/UI/Card renderers
30. Asset pipeline
31. GUI game loop
32. GUI tile actions
33. GUI battle/capture scene
34. GUI starter selection
35. GUI polish
36. Save/load system
37. GUI demo release
```

---

# Final Build Strategy

Do not try to build everything at once.

Use this progress sequence:

```text
Progress 1: Project compiles and prints welcome message.
Progress 2: Players + starters work.
Progress 3: Board + movement + turn switching work.
Progress 4: Terminal movement-only game is playable.
Progress 5: Battle-before-capture works.
Progress 6: Opponent-owned tile battles and Avatar defeat rules work.
Progress 7: Events, teleport, evolution, guardians, special tiles work.
progress 8: Full terminal MVP can start and end.
Progress 9: raylib blank window works.
Progress 10: GUI board displays terminal game state.
Progress 11: GUI can play a basic match.
Progress 12: GUI demo is polished and recordable.
```

This keeps EvoSphere realistic, explainable, and scalable.

