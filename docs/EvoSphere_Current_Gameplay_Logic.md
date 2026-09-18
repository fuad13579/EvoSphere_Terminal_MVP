# EvoSphere_Gameplay_Logic.pdf

## Seite 1

EvoSphere Gameplay Logic
EvoSphere
Basic Game Description with Current Game Logic
EvoSphere is a turn-based strategy board game inspired by Monopoly-style board movement
and Pokémon-style creature capture and evolution . Players move around a 40-tile fantasy
board, capture elemental creatures called Evorans , control territories, evolve their team, and
damage opponents’ Avatar Points until only one player remains.
Core Idea
At the beginning of the game, each player receives one starter Evoran . This starter becomes the
player’s first creature and is used to battle wild Evorans on the board.
Players move around the board by casting two Energy Orbs , which work like dice. The total
number from the two orbs determines how many tiles the player moves.
The main goal is to:
- Capture Evorans
- Own territories
- Evolve Evorans
- Damage opponents
- Reduce enemy Avatar Points to 0
The game ends when all opponents’ Avatar Points are nullified and only one player remains.
1 Board Structure
The board contains 40 tiles , arranged like a Monopoly-style loop. The tile distribution is:
- 1 Origin Gate / GO tile
- 23 normal Evoran tiles
- 3 Guardian Evoran tiles
- 4 Teleport Terminal tiles
- 3 Blessing Shrine tiles
- 3 Chaos Rift tiles
- 3 special ownable tiles
The board is divided into 4 major sections . Each section contains 2 elemental territories .
Example:
After the Origin Gate, the first few tiles may contain three Nature Evorans.
Together, those three Nature Evorans form the Nature Territory.
Other territories may include: Fire, Water, Nature, Electric, Rock, Air, Dark, Psychic / Mystic.
Each territory contains multiple Evoran tiles. If a player captures all Evorans of a territory,
they gain a special territory advantage .
1

## Seite 2

EvoSphere Gameplay Logic
2 Starting the Game
At the start:
- Each player chooses or receives one starter Evoran.
- Each player starts with Avatar Points.
- Each player starts at the Origin Gate.
- Each player has 0 Evolution Gems.
Starter Evorans can include:
- Cindroki — Fire
- Aquillo — Water
- Leafari — Nature
- Voltrik — Electric
These starter Evorans are used to fight and capture wild Evorans on the board.
3 Turn Flow
Each turn follows this flow:
Current player starts turn
↓
Player casts two Energy Orbs
↓
Player moves forward based on the total orb value
↓
Player lands on a tile
↓
Tile action is resolved
↓
Player status is updated
↓
Game checks if anyone is defeated
↓
Turn passes to the next player
Example:
Player 1 casts Energy Orbs: 4 + 3 = 7
Player 1 moves 7 tiles forward
Player 1 lands on a wild Fire Evoran tile
A battle encounter begins
4 Wild Evoran Capture Logic
When a player lands on a wild Evoran tile , the player cannot capture it instantly.
Player lands on wild Evoran
↓
Player selects one owned Evoran
↓
2

## Seite 3

EvoSphere Gameplay Logic
Player battles the wild Evoran
↓
Both Evorans use HP and damage stats
↓
If the wild Evoran becomes weak enough, it can be captured
↓
Captured Evoran becomes owned by the player
↓
The tile also becomes owned by that player
For the terminal MVP:
If the wild Evoran HP becomes 30% or less, capture succeeds automatically.
This makes capturing more strategic because players must use their owned Evorans wisely
instead of relying only on random chance.

### 4.1 Defeated Evoran and Team Defeat Rule

```text
When an Evoran reaches 0 HP, it is defeated but remains owned by its player.
A defeated Evoran cannot battle, capture a Wild Evoran, or deal defensive tile damage.

When the owner completes one full lap and passes Origin Gate, each defeated owned
Evoran revives with 50% of its maximum HP.

When a player's last active Evoran is defeated, that player loses 20 Avatar Points once.
The player cannot start Wild Evoran battles until at least one owned Evoran is revived or healed.

The player is eliminated only when their Avatar Points reach 0.
Blessing Shrine effects can also restore HP to a defeated Evoran.
```

5 Opponent-Owned Evoran Tile Logic
If a player lands on a Wild Evoran tile already owned by an opponent, the landing player
selects one active owned Evoran to battle the Evoran defending that tile.
Example:
Player 1 lands on Player 2’s Pyroclast tile
Player 1 selects an active Evoran
The selected Evoran attacks Pyroclast
Pyroclast counterattacks if it is still active

Basic rules:
- Battle damage reduces Evoran HP only. Normal opponent-tile battles do not reduce Avatar Points.
- A defeated defending Evoran cannot battle or counterattack. The tile remains owned by its owner.
- A defeated attacking Evoran cannot be selected.
- If either player's last active Evoran is defeated, that player receives the one-time
  20 Avatar Point survival penalty.
- Avatar Points can still be reduced by Guardian curses, Chaos Rift effects, special-tile
  penalties, or other direct Avatar Point rules.

An evolved defender has higher HP and damage, making its tile harder for opponents to challenge.
6 Own Evoran Tile Logic
If a player lands on their own Evoran tile, they do not take damage.
Possible MVP reward:
- Gain small Avatar Point recovery, or
- Gain small Evolution Gem progress, or
- No effect for first version
For the first terminal version, this can be kept simple.
7 Territory Control Logic
Each elemental territory contains a group of Evorans.
3

## Seite 4

EvoSphere Gameplay Logic
Example:
Nature Territory:
- Mossari
- Thorniva
- Florayn
If one player captures all Evorans in a territory, they control that full territory. Territory control
gives a special advantage. Possible examples:
- Fire Territory → owned Fire Evorans deal extra damage
- Nature Territory → small healing bonus
- Water Territory → better defense
- Electric Territory → movement or turn advantage
- Dark Territory → extra Avatar Point damage
- Psychic Territory → special event control
For the terminal MVP, territory advantage can be simple:
If a player owns a full territory, Evorans in that territory deal bonus damage.
8 Guardian Evoran Logic
There are 3 Guardian Evorans , placed in three major corner tiles of the board. Guardians are
legendary Evorans with special powers.
Current guardians:
- Solvyrion — Guardian of Radiance and Preservation
- Noctharax — Guardian of Ruin and Corruption
- Aequorion — Guardian of Balance and Fate
When a player lands on a Guardian tile:
A Guardian encounter begins.
The player does not battle the Guardian, and Guardians do not evolve.
Guardian effects are predefined as follows:

```text
Solvyrion randomly grants one blessing:
- Heal 20 Avatar Points.
- Gain 2 Evolution Gems.
- Heal 10 Avatar Points and gain 1 Evolution Gem.

Noctharax randomly applies one curse:
- Lose 35 Avatar Points.
- Lose 1 Evolution Gem.
- Lose 15 Avatar Points.

Aequorion lets the player choose one path:
- Balance: heal 10 Avatar Points and gain 1 Evolution Gem.
- Fate: 50% chance to heal 25 Avatar Points and gain 2 Evolution Gems;
  50% chance to lose 25 Avatar Points.
```
9 Teleport Terminal Logic
There are 4 Teleport Terminal tiles , one in each board section.
When a player lands on a Teleport Terminal:
The player is randomly teleported to another Teleport Terminal.
4

## Seite 5

EvoSphere Gameplay Logic
Example:
Player lands on Teleport Terminal 1.
Game randomly selects Terminal 3.
Player moves instantly to Terminal 3.
This adds unpredictability and prevents the board from feeling too linear.
10 Blessing Shrine and Chaos Rift Logic
There are 6 event tiles: 3 Blessing Shrine tiles and 3 Chaos Rift tiles. These are inspired by
Monopoly’s Community Chest and Chance/Mystery tiles.
Blessing Shrine
Blessing Shrine gives positive effects. Examples:
- Gain 1 Evolution Gem
- Heal Avatar Points
- Increase Evoran HP
- Increase Evoran damage temporarily
- Move forward
Chaos Rift
Chaos Rift gives risky or negative effects. Examples:
- Lose Avatar Points
- Lose Evolution Gem
- Move backward
- Opponent gains a bonus
- Temporary damage reduction
Example event:
Blessing Shrine: Your active Evoran gains 20% damage boost.
Chaos Rift: Your Avatar loses 15 Avatar Points.
11 Special Ownable Tiles
There are 3 unknown special tiles that are not fully planned yet. For now, they can be treated
as ownable relic tiles .
Possible names:
- Gemstone Mine
- Orb Forge
- Ancient Relic Shrine
Possible effects:
- Generate Evolution Gems
- Give small Avatar Point recovery
- Boost capture or battle
- Provide passive income-like reward
5

## Seite 6

EvoSphere Gameplay Logic
For MVP, keep them simple:
If a player owns a relic tile, they receive a small reward when passing Origin Gate.
12 Origin Gate / GO Tile Logic
The first tile is the Origin Gate , similar to Monopoly’s GO tile. Players start here. When a player
completes a full board cycle and reaches or passes the Origin Gate again, they receive rewards.
Possible rewards:
- Evolution Gems
- Avatar Points
- Small healing / bonus resources
Current MVP rule:
When a player passes Origin Gate:
Gain Evolution Gems
Gain Avatar Point recovery
Revive each defeated owned Evoran with 50% of its maximum HP
Example:
Player passes Origin Gate.
Player gains 1 Evolution Gem.
Player recovers 10 Avatar Points.
Any defeated owned Evorans revive with 50% of their maximum HP.
13 Evolution Logic
EvoSphere currently uses one-step evolution . That means each Evoran can evolve once.
Basic evolution rule:
Player spends Evolution Gems
↓
Player chooses one owned Evoran
↓
That Evoran evolves
↓
Its HP and damage increase
Example:
Cindroki evolves into Cindrava.
HP increases. Damage increases.
The evolved Evoran becomes stronger when defending tiles or battling.
For MVP:
- 3 Evolution Gems = evolve one Evoran
- Evolved Evoran gets increased HP and damage
- Each Evoran can evolve only once
6

## Seite 7

EvoSphere Gameplay Logic
14 Avatar Point and Win Condition
Each player has Avatar Points . Avatar Points represent the life force of the player’s avatar.
Players lose Avatar Points when:
- They lose Guardian encounters
- They receive negative Chaos Rift effects
- Their last active Evoran is defeated, which causes a one-time 20 Avatar Point penalty
When a player’s Avatar Points reach 0:
That player is defeated.
They no longer take turns.
The game continues until only one player remains.
Final win condition:
Last player with Avatar Points remaining wins the game.
15 Full Gameplay Summary
In simple form:
- Players start at Origin Gate with one starter Evoran.
- They cast two Energy Orbs to move around a 40-tile board.
- When they land on wild Evorans, they battle them first and capture them after weakening
them.
- Captured Evorans make the tile owned by that player.
- If opponents land on owned Evoran tiles, their selected Evoran battles the defending Evoran.
- Players can complete elemental territories to gain advantages.
- Teleport tiles move players randomly across the board.
- Blessing Shrine and Chaos Rift tiles give good or bad effects.
- Guardian tiles trigger fixed blessing or curse effects.
- Passing Origin Gate gives Evolution Gems and Avatar Point rewards.
- Players use Evolution Gems to evolve Evorans once.
- The game ends when all opponents’ Avatar Points are reduced to zero.
Clean Final Description
EvoSphere is a turn-based elemental creature strategy board game where players move around a
40-tile board using two Energy Orbs. Each player begins with a starter Evoran and captures more
Evorans by battling and weakening them. Captured Evorans allow players to control tiles and
eventually complete elemental territories for special advantages. If a player lands on an opponent-
owned Evoran tile, their selected Evoran battles the defending Evoran. The board also contains teleport terminals,
blessing tiles, chaos tiles, special ownable relic tiles, and three legendary Guardian Evorans with
powerful effects. Players earn Evolution Gems by completing board cycles through the Origin Gate
and can use them to evolve their Evorans once. The game continues until players’ Avatar Points
are reduced to zero, and the last surviving player becomes the winner.
7
