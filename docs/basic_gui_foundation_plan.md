# Basic GUI Foundation Plan

## Purpose

This document defines the first graphical user interface for EvoSphere.

The first GUI should be simple, readable, and playable. It should reuse the
existing `Core/`, `Systems/`, `data/`, and `Utils/` game logic. The GUI must
not recreate movement, battle, capture, event, or evolution rules.

The first version uses simple shapes, text, colours, HP bars, buttons, and
minimal animations. Artwork, polished sprites, sound, and Figma/Photoshop
assets can replace these temporary visuals later.

## Main GUI Layout

The main game screen should use four areas:

```text
┌──────────────────────────────────────────────────────────────────────────────┐
│ EVOSPHERE                         Round 4 • Fuad's Turn                      │
├───────────────────┬──────────────────────────────────┬───────────────────────┤
│ PLAYER / AVATAR   │          40-TILE BOARD           │ EVORAN TEAM           │
│                   │                                  │                       │
│ Avatar: Fuad      │      [tile] [tile] [tile]        │ Active Evoran         │
│ Avatar Points: 85 │   [tile]                 [tile]  │ Cindroki              │
│ Evolution Gems: 2 │   [tile]    EVOSPHERE    [tile]  │ HP: 95 / 95           │
│ Position: Tile 17 │   [tile]       CORE      [tile]  │ Damage: 24            │
│                   │   [tile]                 [tile]  │                       │
│ Territory progress│      [tile] [tile] [tile]        │ Owned Evorans         │
│ Nature: 2 / 3     │                                  │ • Cindroki            │
│ Fire: 1 / 3       │   [ Cast Energy Orbs ]           │ • Mossari             │
├───────────────────┴──────────────────────────────────┴───────────────────────┤
│ GAME LOG                                                                     │
│ > Fuad cast the Energy Orbs: 4 + 6 = 10.                                    │
│ > Fuad moved 10 tiles ahead to Tile 17.                                     │
│ > Fuad faced wild Evoran: Tidalux.                                          │
└──────────────────────────────────────────────────────────────────────────────┘
```

### Top Bar

The top bar always shows:

```text
EvoSphere title
Current round
Current avatar's turn
Settings button
Quit button
```

After rolling, it should also show the two Energy Orb values and their total.

```text
Energy Orbs: 4 + 6 = 10
```

### Left Panel: Player and Avatar Data

Show information for the current player:

```text
Avatar name
Avatar Points
Evolution Gems
Current tile number
Current tile name/type
Territory progress
Active territory bonuses
```

Show small opponent summary cards below or beside the current player data:

```text
Siam • 70 Avatar Points • 2 Evorans • Tile 25
```

This helps players understand who is winning without opening another screen.

### Middle Area: 40-Tile Board

The board is the largest part of the screen. It should be a loop of 40 tiles
with an EvoSphere logo, map art, or simple background in the middle.

Each tile should show:

```text
Tile number
Tile icon
Element colour when applicable
Avatar-coloured border and owner badge when it is owned
Player token(s) standing on it
```

The fixed special positions are:

```text
Origin Gate:       0
Blessing Shrines:  2, 17, 32
Chaos Rifts:       7, 22, 36
Teleport Terminals: 5, 15, 25, 35
Solvyrion:         10
Aequorion:         20
Noctharax:         30
Gemstone Mine:     12
Orb Forge:         27
Ancient Relic Shrine: 38
```

Suggested temporary visual language:

| Type | Basic visual |
|---|---|
| Origin Gate | Large gold portal |
| Wild Evoran | Element-coloured creature tile |
| Owned Evoran | Owner-colour border and token |
| Blessing Shrine | Green/cyan glowing shrine |
| Chaos Rift | Purple/red vortex or crack |
| Teleport Terminal | Blue energy ring |
| Guardian | Gold legendary icon/card |
| Special relic | Gold relic icon |

Suggested element colours:

```text
Nature:   green
Fire:     red/orange
Water:    blue
Electric: yellow
Rock:     brown/gray
Air:      light cyan
Dark:     purple
Mystic:   pink/violet
```

### Tile Ownership and Full Territory Control

Use two separate visual layers so the tile's element remains readable:

```text
Tile background/icon = element or tile type
Tile border and small badge = avatar colour of the tile owner
```

Example:

```text
Pyroclast remains orange/red because it is a Fire Evoran.
If Fuad owns it, it receives Fuad's cyan border and small F badge.
If Siam owns it, it receives Siam's purple border and small S badge.
```

Do not replace element colours with player colours.

When one player owns every Evoran tile in an elemental territory, show a
stronger full-territory-control visual:

```text
Keep the owner's border on every territory tile.
Draw a connected owner-coloured glow or line between those territory tiles.
Show a Controlled badge in the player panel.
Show the territory bonus beside the badge.
```

Example:

```text
Fire Territory  ● ● ●  CONTROLLED ✓
Owner: Fuad
Bonus: Fire Evorans deal +20% damage
```

If a defending Evoran is defeated, keep the tile's owner border because the
tile remains owned. Dim the Evoran icon and show a defeated symbol because it
cannot defend until revived.

Hovering or selecting a tile should show a tooltip:

```text
Tile 19 • Water Territory
Wild Evoran: Mistora
Owner: None
```

`BoardRenderer` should calculate and store a screen position and hover/click
area for every tile. It draws tile state from `Board` and must not contain a
second hardcoded copy of the board layout. `BoardScene` handles mouse input and
decides what a hovered or selected tile means.

Player tokens should appear on their current tile positions. If multiple
players share one tile, arrange their tokens beside each other so every token
remains visible. Highlight the active player's tile and briefly highlight the
movement destination.

The board should scale for supported desktop resolutions while keeping tile
numbers and icons readable. If an image asset is missing, draw a fallback
shape, colour, or text label instead of failing or crashing.

### Right Panel: Evoran Team Data

The right panel shows the current player's active and owned Evorans.

The active Evoran card should show:

```text
Name
Element
HP bar and HP value
Damage
Evolved or unevolved state
Ready or Defeated state
```

Below it, list all owned Evorans as smaller cards.

Defeated Evorans must look dimmed and show:

```text
Defeated
Cannot battle or capture
Revives after passing Origin Gate
```

### Bottom Area: Game Log

The game log replaces the terminal output. It should show the latest 5 to 8
messages and allow scrolling to older messages.

Examples:

```text
🎲 Fuad cast the Energy Orbs: 4 + 6 = 10.
➜ Fuad moved 10 tiles ahead to Tile 17.
✨ Blessing Shrine activated.
⚔ Wild Tidalux appeared.
```

Every gameplay system should be able to send a readable message to the log.
The GUI should use a shared function such as:

```cpp
addGameLog("Fuad moved 10 tiles ahead.");
```

## MenuScene

`MenuScene` is the first screen when the game starts.

It should contain:

```text
EvoSphere title/logo
Start Game button
Rules button
Exit button
```

After the player presses Start Game, ask for the number of players:

```text
2 players
3 players
```

The first version does not need animated backgrounds. A dark cosmic background,
simple title, and clear buttons are enough.

## StarterSelectionScene

This scene collects avatar names and lets each player choose a starter Evoran.

For each player:

```text
Enter Avatar Name
Choose Starter Evoran
```

Show four starter cards:

```text
Cindroki • Fire
Leafari • Nature
Aquillo • Water
Voltrik • Electric
```

Each card should show its name, element, HP, and damage.

Starter selection is unique. After a player selects a starter, disable or
remove that card for the remaining players.

```text
Player 1 selected Cindroki.
Cindroki card becomes unavailable for Player 2.
```

## BoardScene

`BoardScene` is the main gameplay screen. It contains the top bar, player
panel, board, Evoran panel, action buttons, and game log.

Main actions:

```text
Cast Energy Orbs
View Team
Evolve Evoran
End Turn
```

The GUI must disable actions that are not currently allowed. For example,
`End Turn` should be disabled before the current player rolls, and `Evolve`
should be disabled when the player has fewer than 3 Evolution Gems.

When an avatar rolls, use a minimal token movement animation:

```text
Move the player token one tile at a time.
Use a short delay between tiles.
End on the final tile and open the relevant popup.
```

No complex animations are required for the first version.

## BattleScene or Battle Popup

For the basic GUI, battles should be a centered popup over `BoardScene`.
There is no need for a separate full-screen battle scene initially.

```text
┌────────────────── EVORAN BATTLE ──────────────────┐
│ Your Evoran                    Opponent Evoran    │
│ Cindroki                       Tidalux             │
│ Fire                           Water               │
│                                                     │
│ HP  95 / 95                    HP  42 / 80         │
│ ████████████                   ██████░░░░░░        │
│ Damage: 24                     Damage: 18          │
│                                                     │
│ [ Attack ]  [ Capture ]  [ Retreat ]               │
└─────────────────────────────────────────────────────┘
```

### Wild Evoran Battle

Flow:

```text
Player lands on a Wild Evoran tile.
Player chooses an active owned Evoran.
Battle popup opens.
Player attacks.
HP bars update.
Capture becomes available at 30% Wild Evoran HP or lower.
```

`Capture` must be disabled until the Wild Evoran is weak enough.

### Opponent-Owned Tile Battle

When an avatar lands on an opponent-owned Evoran tile, show the attacking
Evoran, defender, defender owner, and both HP bars.

The battle continues until one Evoran is defeated. For the first GUI, use a
single `Start Battle` button, then display each attack result in the popup and
game log.

Minimal battle feedback:

```text
Flash the attacking card briefly.
Reduce the defender HP bar smoothly.
Show floating text such as -24 HP.
Dim and shake a defeated Evoran card once.
```

## Event Popup

Event popups appear for Blessing Shrine and Chaos Rift tiles.

### Blessing Shrine

Use a positive green/cyan card. Show:

```text
Blessing Shrine
Selected effect
Selected territory when applicable
Whether the effect applied or faded away
```

### Chaos Rift

Use a purple/red danger card. Show the curse, movement result, or territory
effect clearly.

If an event moves a player, animate the token to its new position. Resolve the
new tile according to the final gameplay rule, while preventing an infinite
event chain.

## Guardian Popup

Guardian encounters do not use Evoran battle UI.

### Solvyrion

Show a radiant gold/white popup and the randomly selected blessing:

```text
Heal 20 Avatar Points
Gain 2 Evolution Gems
Heal 10 Avatar Points and gain 1 Evolution Gem
```

### Noctharax

Show a dark purple/red popup and the randomly selected curse:

```text
Lose 35 Avatar Points
Lose 1 Evolution Gem
Lose 15 Avatar Points
```

### Aequorion

Show two large player-choice buttons:

```text
[ Balance ]
Heal 10 Avatar Points and gain 1 Evolution Gem

[ Fate ]
50% blessing or 50% curse
```

After the player chooses, display the result before returning to `BoardScene`.

## Evolution Popup

The Evolution popup should list the current player's eligible Evorans.

For each Evoran, show:

```text
Current name → evolved name
Current HP → evolved HP
Current damage → evolved damage
Evolution Gem cost: 3
```

Example:

```text
Cindroki → Cindrava
HP: 95 → 125
Damage: 24 → 36
[ Evolve for 3 Gems ]
```

Disable an Evoran card when:

```text
The player has fewer than 3 Evolution Gems.
The Evoran has already evolved.
```

Ask for confirmation before spending gems:

```text
Evolve Cindroki for 3 Evolution Gems?
[ Confirm ] [ Cancel ]
```

## Active Effects and Territory Progress

Show territory progress in the player panel with simple indicators:

```text
Nature Territory  ● ● ○   2 / 3
Fire Territory    ● ○ ○   1 / 3
Nature Controlled ✓
```

Show active temporary effects in a small status row:

```text
Fire Territory: +20% damage
Air Territory: backward movement protection ready
Orb Forge: movement bonus used this round
```

## Additional UI Requirements

The first GUI should also include:

```text
Minimum supported resolution: 1280 × 720
Board legend for tile icons and colours
Hover tooltip for board tiles
Turn-change banner, for example: Siam's Turn
Disabled buttons for unavailable actions
Confirmation prompts for evolution and other important choices
Pause/settings button
Game-over screen with winner and final statistics
```

Use a responsive layout. At the minimum resolution, side panels should scroll
or collapse instead of covering the board. Keep permanent information limited
to the current turn, essential player resources, active Evoran, and available
actions. Show extra tile, territory, and Evoran details through hover tooltips
or expandable panels.

The current turn and the next valid action should have the strongest visual
priority. Use readable text sizes and colour combinations with sufficient
contrast; do not communicate important state through colour alone. Add keyboard
navigation for menus, buttons, popups, and common turn actions.

Keep movement, battle, popup, and turn-change animations short. Animations
should explain a result without making players wait through every turn.

The game-over screen should show:

```text
Winner avatar
Final Avatar Points
Owned Evorans
Territories controlled
Play Again button
Return to Menu button
```

## Implementation Order

Build the GUI in this order:

1. Add raylib to `CMakeLists.txt`.
2. Implement `WindowManager` to create and close a window.
3. Implement `Application` with the event, update, and draw loop.
4. Implement a basic `BoardScene` with static panels and 40 board tiles.
5. Add player tokens and the bottom game log.
6. Add the Cast Energy Orbs and End Turn actions.
7. Add `StarterSelectionScene`.
8. Add simple battle, event, Guardian, and evolution popups.
9. Add minimal movement, HP-bar, and popup animations.
10. Replace temporary shapes with assets from Figma, Photoshop, or original art.

## Files for the First GUI Milestone

Start with these files:

```text
CMakeLists.txt
src/main.cpp

include/Engine/WindowManager.h
src/Engine/WindowManager.cpp

include/Engine/Application.h
src/Engine/Application.cpp

include/Scenes/Scene.h
include/Scenes/BoardScene.h
src/Scenes/BoardScene.cpp

include/Graphics/BoardRenderer.h
src/Graphics/BoardRenderer.cpp

include/Graphics/UIRenderer.h
src/Graphics/UIRenderer.cpp
```

Do not rewrite the current gameplay logic folders:

```text
Core/
Systems/
data/
Utils/
```

The GUI should read game state and call the existing game functions. It should
only draw the results and collect player input.
