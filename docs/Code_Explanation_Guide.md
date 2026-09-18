## Game.h / Game.cpp

Purpose:
Stores and updates the overall game state, including players, game status, and
the winner.

Important structures:

- `Player`: stores player information such as name, health, score, and defeated
  status.
- `GameState`: stores the player list, player count, game-over status, and
  winner index.

Important functions:

- `initializeGameState()`: connects the players to the game and resets the
  game status.
- `isPlayerDefeated()`: checks whether a player has been defeated.
- `canPlayerTakeTurn()`: checks whether a player is allowed to take a turn.
- `countActivePlayers()`: counts how many players are still active.
- `findWinnerIndex()`: finds the index of the last active player.
- `updateGameState()`: checks whether the game is over and identifies the
  winner.

How it works:

The game stores the players in `GameState`. After a player is defeated,
`updateGameState()` counts the active players. When only one player remains,
the game ends and that player becomes the winner.



## Evoran.h / Evoran.cpp

Purpose:
Stores Evoran information such as name, element type, HP, damage, evolution
status, and owner.

Important structure:

- `Evoran`: groups all data belonging to one Evoran.

Important functions:

- `initializeEvoran()`: sets the Evoran's starting data.
- `takeDamage()`: reduces the Evoran's current HP.
- `heal()`: restores HP without going above maximum HP.
- `isDefeated()`: checks whether the Evoran's HP is 0 or below.
- `canEvolve()`: checks whether the Evoran can evolve.
- `evolve()`: increases the Evoran's HP and damage one time.
- `resetHp()`: restores the Evoran's HP to maximum.

How it works:

`Evoran` stores the data in a `struct`. Separate functions read or change the
data, so the code follows structured programming.

## Player.h / Player.cpp

Purpose:
Stores player information such as name, Avatar Points, Evolution Gems, current
board position, and owned Evorans.

Important structure:

- `Player`: groups all data belonging to one player.

Important functions:

- `initializePlayer()`: sets the player's starting data.
- `movePlayerTo()`: changes the player's board position.
- `addEvolutionGems()`: adds Evolution Gems.
- `spendEvolutionGems()`: removes Gems when the player can afford the cost.
- `takeAvatarDamage()`: reduces Avatar Points.
- `healAvatar()`: restores Avatar Points up to the maximum.
- `addEvoran()`: adds a captured Evoran to the player.
- `getStrongestEvoran()`: finds the owned Evoran with the highest damage.
- `isDefeated()`: checks whether Avatar Points are 0 or below.
- `isAlive()`: checks whether the player can continue playing.

How it works:

`Player` stores the data in a `struct`. Separate functions use a `Player*` when
changing data and a `const Player*` when only reading data.

## CMakeLists.txt

Purpose:
Controls how the EvoSphere project is configured and built.

Important parts:

- `project()`: gives the project its name.
- `set(CMAKE_CXX_STANDARD 17)`: selects C++17.
- `add_executable()`: lists the source files used to build the game.
- `target_include_directories()`: tells the compiler where header files are
  located.
- `target_compile_options()`: enables compiler warnings.

How it works:

CMake creates build instructions for the compiler or IDE. It allows the team
to build the project without manually typing every source file.

```powershell
cmake -S . -B build
cmake --build build
```

The first command configures the project. The second command compiles it.
CMake does not replace the compiler; it organizes the build process for it.
