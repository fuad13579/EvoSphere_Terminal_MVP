# EvoSphere GUI Manual Test Checklist

## Setup

- Build the `Debug` configuration successfully.
- Open the GUI with `EvoSphere.exe`.
- Verify the window cannot be reduced below 1280 x 720.

## Menu and Starter Selection

- Select Start Game and choose both 2-player and 3-player setup in separate runs.
- Enter an avatar name for every player.
- Confirm that a starter Evoran disappears after another player chooses it.
- Confirm that the Board scene opens after all starters are selected.
- Open Rules and return to the main menu.
- Exit from the menu safely.

## Board and Turns

- Verify all 40 tiles, tile numbers, type symbols, player tokens, panels, and game log are visible.
- Hover a tile and verify its tooltip shows tile data.
- Cast Energy Orbs and verify the active token moves one tile at a time.
- Verify the destination highlight matches the final player position.
- End a turn and verify the next avatar becomes active.
- Verify Origin Gate rewards and Evoran revival after a full lap.

## Encounters and Popups

- Land on a Wild Evoran tile, choose an active Evoran, and resolve the battle.
- Verify captured Evorans and owned-tile borders update after a successful capture.
- Land on an opponent-owned tile and verify the defender and result are shown.
- Verify Blessing Shrine and Chaos Rift popups show their selected result.
- Verify Teleport Terminal moves the token to a different terminal.
- Verify Solvyrion, Noctharax, and Aequorion Guardian outcomes update resources.
- Verify evolution requires three Evolution Gems and updates the selected Evoran.

## End Game

- Reduce all but one avatar to zero Avatar Points.
- Verify the game-over popup names the winner.
- Verify Return to Menu resets GUI setup.

## Regression

- Run CTest and confirm existing Core/System tests still pass.
- Run the terminal version with `EvoSphere.exe --terminal`.
