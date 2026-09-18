# Terminal MVP Issues

This document lists the main issues that must be solved before EvoSphere can
run as a complete terminal game.


## 1. Build and Project Setup

- Complete `CMakeLists.txt`.
- Set the project to use C++17.
- Add all required `src/` files to the build.
- Add `include/` as an include directory.
- Create missing `src/data/` files for the data headers.
- Remove or resolve duplicate files such as `ConsoleRenderer.h` and
  `ConsoleRenderer.hpp`.
- Confirm that the project builds without warnings or errors.

## 2. Programming Style Consistency

- Keep the project structured-programming based.
- Use `struct` for data storage.
- Use separate functions instead of classes and member functions.
- Use `Player*` or `Evoran*` when a function changes data.
- Use `const Player*` or `const Evoran*` when a function only reads data.
- Keep terminal input/output inside `Console/`.
- Do not print directly from Core or Systems code.

## 3. Core Data Structures

- Complete `Evoran.h` and `Evoran.cpp`.
- Complete `Player.h` and `Player.cpp`.
- Complete `Tile.h` and `Tile.cpp`.
- Complete `Board.h` and `Board.cpp`.
- Complete `EventCard.h` and `EventCard.cpp`.
- Complete `Guardian.h` and `Guardian.cpp`.
- Complete `TurnManager.h` and `TurnManager.cpp`.
- Complete `Game.h` and `Game.cpp`.
- Ensure all structs and function declarations match their `.cpp` files.
- Handle null pointers and invalid values safely.

## 4. Evoran Data and Rules

- Add the four starter Evorans.
- Add the 23 wild Evorans from the roster document.
- Add the three Guardian Evorans.
- Store base HP, damage, evolved HP, and evolved damage.
- Store element type, category, evolved name, and owner ID.
- Allow each Evoran to evolve only once.
- Prevent HP from becoming negative.
- Prevent healing from exceeding maximum HP.
- Use the 30% HP capture threshold.

## 5. Player Rules

- Support two or three players.
- Start each player with 100 Avatar Points.
- Start each player with zero Evolution Gems.
- Start each player at the Origin Gate.
- Give each player one starter Evoran.
- Add and remove Evolution Gems safely.
- Add captured Evorans to the player's collection.
- Keep defeated Evorans in the player's collection.
- Prevent defeated Evorans from battling, capturing, or defending tiles.
- Revive each defeated owned Evoran with 50% of its maximum HP when its owner passes Origin Gate after one full lap.
- Apply a one-time 20 Avatar Point penalty when a player's last active Evoran is defeated.
- Detect when Avatar Points reach zero.
- Mark defeated players so they no longer take turns.

## 6. Board and Tile Data

- Define all 40 board tiles.
- Add one Origin Gate.
- Add 23 wild Evoran tiles.
- Add three Guardian tiles.
- Add four Teleport Terminals.
- Add three Blessing Shrines.
- Add three Chaos Rifts.
- Add three special ownable tiles.
- Assign tile names, types, elements, and territories.
- Track tile ownership.
- Wrap movement from tile 39 back to tile 0.

## 7. Static Data Files

- Implement `EvoranDatabase`.
- Implement `BoardData`.
- Implement `EventDatabase`.
- Keep fixed game data outside `main.cpp`.
- Make database functions return safe data when a name or index is invalid.

## 8. Movement and Turn Flow

- Implement two Energy Orb rolls from 1 to 6.
- Add the two orb values to calculate movement.
- Move the current player around the 40-tile board.
- Detect when a player passes the Origin Gate.
- Give one Evolution Gem when passing the Origin Gate.
- Restore 10 Avatar Points when passing the Origin Gate.
- Revive defeated owned Evorans with 50% of their maximum HP when passing Origin Gate after a full lap.
- Skip defeated players.
- Switch to the next active player.
- Stop the turn loop when the game is over.

## 9. Tile Actions

- Resolve wild Evoran tiles.
- Resolve opponent-owned Evoran tiles.
- Resolve the current player's own tiles.
- Resolve Guardian encounters.
- Resolve Teleport Terminals.
- Resolve Blessing Shrines.
- Resolve Chaos Rifts.
- Resolve special ownable tiles.
- Prevent one tile action from triggering incorrectly more than once.

## 10. Battle and Capture

- Allow a player to select one owned Evoran for battle.
- Apply Evoran damage and HP rules.
- Battle wild Evorans before capture.
- Capture the wild Evoran when its HP is at or below 30%.
- Assign the captured Evoran to the player.
- Assign the captured tile to the player.
- Fail the encounter if the selected Evoran is defeated.
- Handle a player with no available Evoran safely.
- Reset or preserve HP according to the agreed MVP rule.

## 11. Opponent-Owned Tile Battle

- Detect when a player lands on an opponent-owned Evoran tile.
- Let the landing player select one active owned Evoran.
- Find the owned Evoran defending the landed tile.
- Apply attacker and defender damage to Evoran HP only.
- Allow the defender to counterattack only if it remains active.
- Do not reduce Avatar Points from normal opponent-tile battle damage.
- Keep defeated defending Evorans owned, but prevent them from defending.
- Apply the one-time 20 Avatar Point penalty if a player's last active Evoran is defeated.
- Show battle damage, HP, defeat status, and no-direct-Avatar-damage messages in the terminal.

## 12. Events

- Add Blessing Shrine event cards.
- Add Chaos Rift event cards.
- Implement positive effects such as Gems and healing.
- Implement negative effects such as Avatar Point damage and backward movement.
- Apply the 15 Avatar Point Chaos Rift damage rule.
- Keep event logic separate from console printing.

## 13. Teleport Terminals

- Store the four terminal positions.
- Detect when a player lands on a terminal.
- Select another terminal randomly.
- Move the player to the selected terminal.
- Prevent teleporting to the same terminal when possible.

## 14. Evolution

- Require three Evolution Gems for one evolution.
- Allow the player to select an owned Evoran.
- Check that the Evoran has not already evolved.
- Increase HP and damage after evolution.
- Deduct the Evolution Gems only after a valid evolution.
- Prevent evolution when the player cannot afford it.

## 15. Guardian Encounters

- Add Solvyrion, Noctharax, and Aequorion.
- Store each Guardian's name, title, type, special power, blessing, and curse.
- Give Solvyrion three random blessings: heal 20 Avatar Points, gain 2 Evolution Gems, or heal 10 Avatar Points and gain 1 Evolution Gem.
- Give Noctharax three random curses: lose 35 Avatar Points, lose 1 Evolution Gem, or lose 15 Avatar Points.
- Let Aequorion offer Balance or Fate.
- Make Balance heal 10 Avatar Points and grant 1 Evolution Gem.
- Make Fate randomly grant +25 Avatar Points and +2 Evolution Gems, or remove 25 Avatar Points.
- Keep Guardians separate from normal Evoran capture and evolution.

## 16. Console Interface

- Display a welcome message.
- Ask for the number of players.
- Ask for player names.
- Allow starter selection.
- Display the current player and turn information.
- Display orb results and movement.
- Display tile actions and battle results.
- Ask for battle and evolution choices.
- Display Avatar Points, Gems, position, and owned Evorans.
- Display the winner when the game ends.
- Validate invalid input without crashing.

## 17. Game Loop Integration

- Initialize all fixed data.
- Create players.
- Give players starter Evorans.
- Create the board.
- Start the turn manager.
- Roll, move, and resolve the landed tile.
- Update player and board state.
- Check defeated players after each action.
- Continue until only one player remains.
- Print the final winner.

## 18. Testing

- Test Evoran initialization.
- Test Evoran damage, healing, defeat, and evolution.
- Test Player damage, healing, Gems, movement, and defeat.
- Test board position wrapping.
- Test tile ownership.
- Test movement and turn switching.
- Test wild Evoran capture at exactly 30% HP.
- Test opponent-owned Evoran battles and defeated defenders.
- Test Guardian rewards and penalties.
- Test events and teleporting.
- Test the two-player and three-player win conditions.
- Test invalid input and null pointers.

## 19. MVP Completion Criteria

The terminal MVP is complete when:

- The project builds successfully.
- Two or three players can start a game.
- Players receive starter Evorans.
- Players can move around all 40 tiles.
- Wild Evorans can be battled and captured.
- Tile ownership works.
- Opponent-owned tiles start Evoran-vs-Evoran battles.
- Events, teleporting, and Guardians work.
- Evorans can evolve using Evolution Gems.
- Defeated players are skipped.
- The last active player is declared the winner.
- The entire game can be played through the terminal without editing code.
