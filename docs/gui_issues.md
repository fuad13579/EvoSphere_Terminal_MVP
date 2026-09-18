# EvoSphere GUI Issue List

This document contains GitHub issue ideas for building the EvoSphere GUI after
the terminal MVP. Complete the issues in order where possible.

## 1. Set Up the raylib GUI Foundation

### Objective

Add raylib and create a working desktop window with a basic application loop.

### Files

```text
CMakeLists.txt
src/main.cpp
include/Engine/Application.h
src/Engine/Application.cpp
include/Engine/WindowManager.h
src/Engine/WindowManager.cpp
```

### Tasks

- Add raylib as a project dependency.
- Link raylib in CMake.
- Create a raylib window.
- Create the event loop, update loop, and draw loop.
- Close the window safely when the user presses the close button.
- Keep `Core/`, `Systems/`, `data/`, and `Utils/` independent from raylib.

### Acceptance Criteria

```text
The project builds with raylib.
The game opens a desktop window.
The window closes safely.
The terminal game logic is not moved into GUI files.
```

### Suggested Branch

```text
feature/gui-foundation
```

---

## 2. Implement Scene Management

### Objective

Allow the GUI to switch between menu, starter selection, board, and battle
screens.

### Files

```text
include/Engine/SceneManager.h
src/Engine/SceneManager.cpp
include/Scenes/Scene.h
```

### Tasks

- Define a simple procedural scene state.
- Add scene types for Menu, Starter Selection, Board, and Battle.
- Allow the application loop to update and draw the active scene.
- Allow safe transitions between scenes.

### Acceptance Criteria

```text
The game can open MenuScene.
The game can switch to StarterSelectionScene.
The game can switch to BoardScene.
The game can return to MenuScene after the game ends.
```

### Suggested Branch

```text
feature/scene-manager
```

---

## 3. Build the Main Menu Scene

### Objective

Create the first screen shown when the game opens.

### Files

```text
include/Scenes/MenuScene.h
src/Scenes/MenuScene.cpp
include/Graphics/UIRenderer.h
src/Graphics/UIRenderer.cpp
```

### Tasks

- Show EvoSphere title and a simple cosmic background.
- Add Start Game button.
- Add Rules button.
- Add Exit button.
- Let the player choose 2 or 3 players after Start Game.

### Acceptance Criteria

```text
The menu is readable at normal desktop resolution.
Buttons react to mouse input.
Start Game opens starter selection.
Exit closes the application safely.
```

### Suggested Branch

```text
feature/menu-scene
```

---

## 4. Create Starter Selection UI

### Objective

Collect avatar names and let every player select one unique starter Evoran.

### Files

```text
include/Scenes/StarterSelectionScene.h
src/Scenes/StarterSelectionScene.cpp
include/Graphics/CardRenderer.h
src/Graphics/CardRenderer.cpp
```

### Tasks

- Add avatar name text input.
- Show starter cards for Cindroki, Leafari, Aquillo, and Voltrik.
- Show each starter's element, HP, and damage.
- Disable or remove a starter after another player selects it.
- Initialize players using the existing Player and Evoran functions.
- Move to BoardScene after all players select starters.

### Acceptance Criteria

```text
Each player enters one avatar name.
The same starter cannot be chosen twice.
Selected starters are added to the correct player.
BoardScene opens after setup completes.
```

### Suggested Branch

```text
feature/starter-selection-ui
```

---

## 5. Render the 40-Tile Board

### Objective

Draw the complete EvoSphere board with the correct tile data and types.

### Files

```text
include/Scenes/BoardScene.h
src/Scenes/BoardScene.cpp
include/Graphics/BoardRenderer.h
src/Graphics/BoardRenderer.cpp
```

### Tasks

- Draw a 40-tile loop board.
- Use `BoardData.cpp` indexes and tile types.
- Draw Origin Gate, Wild Evoran tiles, Guardians, Teleport Terminals,
  Blessing Shrines, Chaos Rifts, and Special Ownable tiles.
- Use basic element colours for Wild Evoran territory tiles.
- Show tile number and simple tile icon.
- Show an avatar-coloured border and small owner badge when an Evoran tile is owned.
- Keep the element colour or tile-type icon visible inside the owner border.
- Dim the Evoran icon but keep the owner border when a defending Evoran is defeated.
- When a player owns a full territory, connect its territory tiles with an
  avatar-coloured glow or line and show a Controlled badge with the territory bonus.
- Add hover tooltip with tile name, territory, linked Evoran, and owner.
- Add a small tile-colour/icon legend.
- Draw player tokens on their current tile positions.
- Arrange multiple player tokens clearly when they share the same tile.
- Highlight the active player's tile and the destination tile during movement.
- Store a screen position and hover/click area for every tile.
- Scale the board and tile labels for supported window resolutions.
- Support a minimum window resolution of 1280 × 720.
- Show territory grouping before and after a territory becomes controlled.
- Read tile content and ownership from `Board`; do not duplicate game data in
  `BoardRenderer`.
- Use fallback shapes or text when a tile icon or texture is missing.
- Keep responsibilities separate: `BoardRenderer` draws the board, while
  `BoardScene` handles input and interprets hovered or selected tiles.

### Acceptance Criteria

```text
All 40 tiles are visible.
Each special tile appears at its correct index.
Owned tiles visibly show their owner.
Element colours remain readable on owned tiles.
Full controlled territories visibly show their owner and territory bonus.
Hovering a tile shows correct tile information.
Player tokens appear on their correct board positions.
Multiple player tokens can appear clearly on one tile.
The active player and movement destination are visually highlighted.
Every tile can be hovered or clicked accurately.
The board remains readable at supported window resolutions.
The complete board remains usable at 1280 × 720.
BoardRenderer reads state from Board without duplicating game data.
Missing visual assets do not crash the game.
```

### Suggested Branch

```text
feature/board-renderer
```

---

## 6. Add Player and Evoran Information Panels

### Objective

Show current player data, opponent summaries, active Evoran data, and owned
Evoran cards around the board.

### Files

```text
include/Graphics/PlayerRenderer.h
src/Graphics/PlayerRenderer.cpp
include/Graphics/CardRenderer.h
src/Graphics/CardRenderer.cpp
include/Graphics/UIRenderer.h
src/Graphics/UIRenderer.cpp
```

### Tasks

- Add left player/avatar panel.
- Show Avatar Points, Evolution Gems, board position, and territory progress.
- Add compact opponent summary cards.
- Add right Evoran panel.
- Show active Evoran HP, damage, element, and evolved state.
- List owned Evorans with HP bars.
- Dim defeated Evorans and show their revival reminder.
- Show active territory effects and temporary status effects.
- Let long player and Evoran panels scroll or collapse at smaller resolutions.
- Keep detailed Evoran and territory information in tooltips or expandable
  sections instead of permanently crowding the screen.

### Acceptance Criteria

```text
Current player information updates after game actions.
Opponent cards show basic live information.
Evoran HP bars reflect actual Evoran HP.
Defeated Evorans are visually distinct.
Side panels remain usable without covering the board at 1280 × 720.
```

### Suggested Branch

```text
feature/player-evoran-panels
```

---

## 7. Add Game Log and Action Controls

### Objective

Replace terminal messages with an on-screen game log and context-aware buttons.

### Files

```text
include/Graphics/UIRenderer.h
src/Graphics/UIRenderer.cpp
include/Scenes/BoardScene.h
src/Scenes/BoardScene.cpp
```

### Tasks

- Add a scrollable game log below the board.
- Add a shared `addGameLog(...)` helper or equivalent GUI log mechanism.
- Show movement, battle, capture, event, Guardian, teleport, evolution, and
  Origin Gate messages.
- Add Cast Energy Orbs, End Turn, View Team, and Evolve buttons.
- Disable buttons when the action is unavailable.
- Show current round, current avatar, and Energy Orb result in the top bar.
- Give the current turn and next valid action the strongest visual priority.
- Add keyboard navigation for menus, buttons, popups, and common turn actions.
- Use readable text and accessible colour contrast; do not communicate
  important state through colour alone.

### Acceptance Criteria

```text
The latest 5 to 8 messages are visible.
Older messages can be reviewed by scrolling.
Only valid actions are clickable.
The log explains important gameplay results clearly.
The main controls can be used with either mouse or keyboard.
```

### Suggested Branch

```text
feature/gui-game-log-controls
```

---

## 8. Animate Player Movement

### Objective

Add a minimal visual movement animation for player tokens.

### Files

```text
include/Graphics/PlayerRenderer.h
src/Graphics/PlayerRenderer.cpp
include/Engine/Time.h
src/Engine/Time.cpp
include/Scenes/BoardScene.h
src/Scenes/BoardScene.cpp
```

### Tasks

- Draw a token for each player.
- Move the token one tile at a time after an Energy Orb roll.
- Use a short delay or interpolation between tile positions.
- Keep movement and turn-change animations short enough that they do not slow
  down normal turns.
- Stop the token at the final tile before resolving the tile action.
- Show a short turn-change banner.

### Acceptance Criteria

```text
Tokens appear on the correct tiles.
Movement follows the board path in the correct direction.
The final position matches MovementSystem output.
The board remains usable after movement completes.
Animations provide feedback without delaying the turn unnecessarily.
```

### Suggested Branch

```text
feature/token-movement-animation
```

---

## 9. Implement Wild Evoran Battle Popup

### Objective

Create a minimal battle popup for Wild Evoran capture encounters.

### Files

```text
include/Scenes/BattleScene.h
src/Scenes/BattleScene.cpp
include/Graphics/CardRenderer.h
src/Graphics/CardRenderer.cpp
```

### Tasks

- Show the Wild Evoran card and selected owned Evoran card.
- Show both HP bars, HP values, damage, and elements.
- Let the player choose an active owned Evoran before battle.
- Add Attack, Capture, and Retreat controls as supported by the final game rule.
- Disable Capture until Wild Evoran HP is 30% or lower.
- Call existing BattleSystem and CaptureSystem functions.
- Add results to the game log.
- Show defeated state when an Evoran reaches 0 HP.

### Acceptance Criteria

```text
The player can select only active owned Evorans.
Attack updates the correct HP bars.
Capture is disabled above the 30% capture threshold.
Successful capture updates the board, team panel, and game log.
```

### Suggested Branch

```text
feature/wild-battle-ui
```

---

## 10. Implement Opponent-Owned Tile Battle Popup

### Objective

Show battles between a landing player's Evoran and an opponent's tile defender.

### Files

```text
include/Scenes/BattleScene.h
src/Scenes/BattleScene.cpp
include/Graphics/CardRenderer.h
src/Graphics/CardRenderer.cpp
```

### Tasks

- Show attacker, defender, defender owner, and both HP bars.
- Show territory battle effects when they apply.
- Run the battle using BattleSystem.
- Display attack and counterattack results.
- Show Evoran defeat clearly.
- Show the Avatar Point penalty when a player loses the tile battle.
- Refresh player panels and board tile visuals afterward.

### Acceptance Criteria

```text
The correct defender appears for an opponent-owned tile.
The battle result matches BattleSystem output.
Defeated Evorans become visually unavailable.
Avatar Point changes are shown clearly.
```

### Suggested Branch

```text
feature/opponent-battle-ui
```

---

## 11. Implement Event Popups

### Objective

Show clear GUI feedback for Blessing Shrine and Chaos Rift events.

### Files

```text
include/Scenes/BoardScene.h
src/Scenes/BoardScene.cpp
include/Graphics/UIRenderer.h
src/Graphics/UIRenderer.cpp
```

### Tasks

- Create a positive Blessing Shrine popup.
- Create a dangerous Chaos Rift popup.
- Show selected event type, territory, movement amount, and final result.
- Show when a territory event fades because the player does not own the
  selected territory.
- Animate event movement when it occurs.
- Prevent repeated event popups from creating an infinite chain.

### Acceptance Criteria

```text
Blessing and Chaos use visually different popups.
The popup matches EventSystem results.
Movement events update the token position correctly.
The game log records the event result.
```

### Suggested Branch

```text
feature/event-popups
```

---

## 12. Implement Guardian Popups

### Objective

Show Guardian encounters without using battle UI.

### Files

```text
include/Scenes/BoardScene.h
src/Scenes/BoardScene.cpp
include/Graphics/CardRenderer.h
src/Graphics/CardRenderer.cpp
```

### Tasks

- Add Solvyrion blessing popup.
- Add Noctharax curse popup.
- Add Aequorion choice popup with Balance and Fate buttons.
- Display the resolved Guardian result.
- Update Avatar Points and Evolution Gems visually.
- Add Guardian result to the game log.

### Acceptance Criteria

```text
Solvyrion and Noctharax show a random resolved outcome.
Aequorion requires a player choice.
The displayed result matches Guardian logic.
Player resources update after the popup closes.
```

### Suggested Branch

```text
feature/guardian-popups
```

---

## 13. Implement Teleport Terminal Feedback

### Objective

Show teleportation clearly and move the token to a different terminal.

### Files

```text
include/Scenes/BoardScene.h
src/Scenes/BoardScene.cpp
include/Graphics/BoardRenderer.h
src/Graphics/BoardRenderer.cpp
```

### Tasks

- Highlight the source Teleport Terminal.
- Show the selected destination terminal.
- Animate or fade the token between terminals.
- Add source and destination to the game log.
- Use the existing TeleportSystem result.

### Acceptance Criteria

```text
The token never remains at the same terminal.
The token ends on the terminal selected by TeleportSystem.
The log explains the teleport result.
```

### Suggested Branch

```text
feature/teleport-ui
```

---

## 14. Implement Evolution Popup

### Objective

Allow a player to evolve one eligible owned Evoran through the GUI.

### Files

```text
include/Scenes/BoardScene.h
src/Scenes/BoardScene.cpp
include/Graphics/CardRenderer.h
src/Graphics/CardRenderer.cpp
```

### Tasks

- Show all owned Evorans in an Evolution popup.
- Display current name, evolved name, HP increase, and damage increase.
- Show Evolution Gem cost of 3.
- Disable cards that are already evolved.
- Disable evolution if the player has fewer than 3 gems.
- Add Confirm and Cancel buttons.
- Call existing EvolutionSystem functions.

### Acceptance Criteria

```text
Only eligible Evorans can be evolved.
The player confirms before spending gems.
The Evoran card updates after evolution.
The game log explains the evolution result.
```

### Suggested Branch

```text
feature/evolution-popup
```

---

## 15. Implement Game Over and Settings UI

### Objective

End the game clearly and provide basic application controls.

### Files

```text
include/Scenes/MenuScene.h
src/Scenes/MenuScene.cpp
include/Scenes/BoardScene.h
src/Scenes/BoardScene.cpp
include/Graphics/UIRenderer.h
src/Graphics/UIRenderer.cpp
```

### Tasks

- Show a game-over overlay when one player remains.
- Show winner avatar, final Avatar Points, owned Evorans, and territories.
- Add Play Again button.
- Add Return to Menu button.
- Add basic pause/settings overlay.
- Add fullscreen and volume controls later if audio is added.

### Acceptance Criteria

```text
The winner is shown correctly.
The game can restart without closing the application.
The game can return to the main menu.
```

### Suggested Branch

```text
feature/game-over-settings-ui
```

---

## 16. Add GUI Assets and Visual Polish

### Objective

Replace temporary shapes with original or externally designed assets.

### Files

```text
assets/sprites/
assets/guardians/
assets/ui/
assets/fonts/
include/Engine/AssetManager.h
src/Engine/AssetManager.cpp
```

### Tasks

- Export UI panels, icons, and buttons from Figma if used.
- Add original Evoran and Guardian artwork.
- Add board background and tile textures.
- Add a readable game font.
- Load and reuse assets through AssetManager.
- Keep temporary shape rendering available as a fallback during development.

### Acceptance Criteria

```text
Assets load without repeated disk reads.
Missing assets fail safely.
The GUI remains readable with or without final artwork.
```

### Suggested Branch

```text
feature/gui-assets
```

---

## 17. Add GUI Testing and Manual Test Checklist

### Objective

Verify that GUI actions correctly use the existing game logic.

### Files

```text
tests/
docs/gui_manual_test_checklist.md
```

### Tasks

- Keep existing Core and Systems unit tests passing.
- Add tests for GUI-independent scene state where practical.
- Create a manual test checklist for the full GUI flow.
- Test starter selection, movement, battle, capture, events, Guardians,
  teleportation, evolution, defeat, revival, and game over.
- Test at common desktop resolutions.

### Acceptance Criteria

```text
Existing gameplay tests still pass.
GUI actions produce the same game-state results as terminal actions.
The manual checklist covers every major screen and popup.
```

### Suggested Branch

```text
feature/gui-testing
```
