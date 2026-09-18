# EvoSphere Evoran Roster and MVP Stats

This document defines the current terminal-version roster for **EvoSphere**.

The stats are **MVP balancing values**, not final production values. They are designed for a playable terminal prototype first. After playtesting, HP, damage, capture difficulty, territory bonuses, and guardian rewards should be adjusted.

---

## 1. Core Stat Rules

### Basic Fields

| Field | Meaning |
|---|---|
| Name | Current Evoran name |
| Evolved Form | One-step evolved name |
| Type | Elemental type |
| Role | Gameplay identity |
| Base HP | Health before evolution |
| Base Damage | Damage before evolution |
| Evolved HP | Health after evolution |
| Evolved Damage | Damage after evolution |
| Capture Difficulty | Easy, Medium, Hard, Very Hard |
| Tile Role | How the Evoran appears on the board |

### Evolution Rule

For the MVP version:

```text
3 Evolution Gems = evolve one owned Evoran
Each Evoran can evolve only once
Evolved Evorans gain increased HP and damage
```

### Battle-Before-Capture Rule

For the MVP version:

```text
A wild Evoran cannot be captured directly.
The player must battle it first using one owned Evoran.
If the wild Evoran's HP becomes 30% or less of its max HP, capture succeeds automatically.
```

### Defeated Evoran and Team Defeat Rule

```text
An Evoran at 0 HP remains owned but cannot battle, capture, or defend its tile.
When its owner completes one full lap and passes Origin Gate, it revives with 50% of its maximum HP.
If a player's last active Evoran is defeated, the player loses 20 Avatar Points once.
The player is eliminated only when their Avatar Points reach 0.
```

---

# 2. Starter Evorans

Starter Evorans are given to players at the beginning of the game. They are slightly balanced so no starter is strictly superior.

| # | Starter Name | Evolved Form | Type | Role | Base HP | Base Damage | Evolved HP | Evolved Damage | Notes |
|---|---|---|---|---|---:|---:|---:|---:|---|
| 1 | Cindroki | Cindrava | Fire | Attacker | 95 | 24 | 125 | 36 | Strong early damage, lower durability |
| 2 | Leafari | Floravyn | Nature | Balanced / Sustain | 110 | 19 | 145 | 30 | Safer starter, good survivability |
| 3 | Aquillo | Aquarion | Water | Defensive | 120 | 17 | 155 | 28 | High HP, lower damage |
| 4 | Voltrik | Voltrion | Electric | Speed / Burst | 90 | 26 | 120 | 38 | High damage, fragile |

---

# 3. Wild Board Evorans

There are **23 wild Evorans** placed across the board. Capturing them allows players to own tiles and complete territories.

---

## 3.1 Nature Territory

| # | Name | Evolved Form | Type | Role | Base HP | Base Damage | Evolved HP | Evolved Damage | Capture Difficulty | Tile Role |
|---|---|---|---|---|---:|---:|---:|---:|---|---|
| 1 | Mossari | Mossarion | Nature | Tank / Support | 115 | 16 | 150 | 26 | Easy | Wild Evoran Tile |
| 2 | Thorniva | Thornivine | Nature | Counter Attacker | 100 | 21 | 135 | 32 | Medium | Wild Evoran Tile |
| 3 | Florayn | Floralith | Nature | Healer / Balanced | 105 | 19 | 140 | 30 | Medium | Wild Evoran Tile |

### Suggested Nature Territory Bonus

```text
If one player owns all Nature Evorans, their Nature Evorans recover +5 HP after battle.
```

---

## 3.2 Rock Territory

| # | Name | Evolved Form | Type | Role | Base HP | Base Damage | Evolved HP | Evolved Damage | Capture Difficulty | Tile Role |
|---|---|---|---|---|---:|---:|---:|---:|---|---|
| 4 | Pebloru | Peblorion | Rock | Defensive | 125 | 15 | 165 | 25 | Easy | Wild Evoran Tile |
| 5 | Cragorn | Cragorak | Rock | Heavy Defender | 135 | 18 | 175 | 29 | Medium | Wild Evoran Tile |
| 6 | Basaldrum | Basaldrake | Rock | Fortress / High HP | 150 | 16 | 190 | 28 | Hard | Wild Evoran Tile |

### Suggested Rock Territory Bonus

```text
If one player owns all Rock Evorans, Rock Evoran tiles reduce incoming battle damage by 5.
```

---

## 3.3 Electric Territory

| # | Name | Evolved Form | Type | Role | Base HP | Base Damage | Evolved HP | Evolved Damage | Capture Difficulty | Tile Role |
|---|---|---|---|---|---:|---:|---:|---:|---|---|
| 7 | Sparqit | Sparqion | Electric | Fast Attacker | 85 | 25 | 115 | 37 | Easy | Wild Evoran Tile |
| 8 | Ionixu | Ionivolt | Electric | Burst Damage | 95 | 27 | 125 | 40 | Medium | Wild Evoran Tile |
| 9 | Thundravo | Thundravox | Electric | Heavy Burst | 105 | 30 | 140 | 44 | Hard | Wild Evoran Tile |

### Suggested Electric Territory Bonus

```text
If one player owns all Electric Evorans, they may add +1 to one Energy Orb roll once per full round.
```

---

## 3.4 Fire Territory

| # | Name | Evolved Form | Type | Role | Base HP | Base Damage | Evolved HP | Evolved Damage | Capture Difficulty | Tile Role |
|---|---|---|---|---|---:|---:|---:|---:|---|---|
| 10 | Emberu | Emberion | Fire | Attacker | 90 | 24 | 120 | 36 | Easy | Wild Evoran Tile |
| 11 | Flarexon | Flarexar | Fire | Aggressive Attacker | 100 | 28 | 130 | 42 | Medium | Wild Evoran Tile |
| 12 | Pyroclast | Pyroclaxon | Fire | High Damage | 110 | 31 | 145 | 46 | Hard | Wild Evoran Tile |

### Suggested Fire Territory Bonus

```text
If one player owns all Fire Evorans, Fire Evoran tiles deal +5 Avatar Point damage to opponents.
```

---

## 3.5 Water Territory

| # | Name | Evolved Form | Type | Role | Base HP | Base Damage | Evolved HP | Evolved Damage | Capture Difficulty | Tile Role |
|---|---|---|---|---|---:|---:|---:|---:|---|---|
| 13 | Ripplin | Ripplora | Water | Balanced | 105 | 19 | 140 | 30 | Easy | Wild Evoran Tile |
| 14 | Mistora | Mistovyn | Water | Defensive / Utility | 115 | 18 | 150 | 29 | Medium | Wild Evoran Tile |
| 15 | Tidalux | Tidalorian | Water | High HP Balanced | 130 | 22 | 170 | 34 | Hard | Wild Evoran Tile |

### Suggested Water Territory Bonus

```text
If one player owns all Water Evorans, they heal +10 Avatar Points when passing Origin Gate.
```

---

## 3.6 Air Territory

| # | Name | Evolved Form | Type | Role | Base HP | Base Damage | Evolved HP | Evolved Damage | Capture Difficulty | Tile Role |
|---|---|---|---|---|---:|---:|---:|---:|---|---|
| 16 | Galevi | Galevyr | Air | Agile Bird | 90 | 23 | 120 | 35 | Easy | Wild Evoran Tile |
| 17 | Driftail | Driftalon | Air | Evasive / Balanced | 100 | 22 | 135 | 34 | Medium | Wild Evoran Tile |
| 18 | Zephyrox | Zephyron | Air | Storm Attacker | 105 | 27 | 140 | 41 | Hard | Wild Evoran Tile |

### Suggested Air Territory Bonus

```text
If one player owns all Air Evorans, they may ignore one backward movement effect from Chaos Rift per round.
```

---

## 3.7 Dark Territory

| # | Name | Evolved Form | Type | Role | Base HP | Base Damage | Evolved HP | Evolved Damage | Capture Difficulty | Tile Role |
|---|---|---|---|---|---:|---:|---:|---:|---|---|
| 19 | Duskleaf | Duskthorn | Dark | Trickster | 100 | 24 | 135 | 36 | Medium | Wild Evoran Tile |
| 20 | Umbraxo | Umbraxor | Dark | Assassin | 95 | 30 | 125 | 44 | Hard | Wild Evoran Tile |
| 21 | Voidmar | Voidmare | Dark | High Risk Damage | 110 | 33 | 145 | 49 | Very Hard | Wild Evoran Tile |

### Suggested Dark Territory Bonus

```text
If one player owns all Dark Evorans, their Dark Evorans deal +7 damage when defending their tiles.
```

---

## 3.8 Mystic / Psychic Territory

| # | Name | Evolved Form | Type | Role | Base HP | Base Damage | Evolved HP | Evolved Damage | Capture Difficulty | Tile Role |
|---|---|---|---|---|---:|---:|---:|---:|---|---|
| 22 | Auramind | Auramage | Mystic / Psychic | Control / Utility | 105 | 26 | 140 | 39 | Hard | Wild Evoran Tile |
| 23 | Runelith | Runelorian | Mystic / Psychic | Ancient Defender | 125 | 24 | 165 | 37 | Very Hard | Wild Evoran Tile |

### Suggested Mystic / Psychic Territory Bonus

```text
If one player owns all Mystic/Psychic Evorans, they may reroll one event result once per full round.
```

---

# 4. Guardian Evorans

Guardians are legendary entities placed on three major corner tiles. They are
not normal Evorans, do not evolve, and do not use HP or damage. They apply a
predefined non-battle effect when a player lands on their tile.

| # | Guardian Name | Title | Type | Special Power | Blessing | Curse |
|---|---|---|---|---|---|---|
| 1 | Solvyrion | Guardian of Radiance and Preservation | Mystic / Guardian | Radiant Aegis | Randomly: heal 20 Avatar Points, gain 2 Evolution Gems, or heal 10 Avatar Points and gain 1 Evolution Gem | None |
| 2 | Noctharax | Guardian of Ruin and Corruption | Dark / Guardian | Abyssal Brand | None | Randomly: lose 35 Avatar Points, lose 1 Evolution Gem, or lose 15 Avatar Points |
| 3 | Aequorion | Guardian of Balance and Fate | Mystic / Guardian | Equinox Decree | Balance: heal 10 Avatar Points and gain 1 Evolution Gem; Fate success: heal 25 Avatar Points and gain 2 Evolution Gems | Fate failure: lose 25 Avatar Points |

## Guardian Effect MVP Rule

For the first terminal version:

```text
When a player lands on a Guardian tile:
1. Identify the Guardian on the tile.
2. Solvyrion randomly gives one blessing, or Noctharax randomly gives one curse.
3. For Aequorion, the player chooses Balance or Fate.
4. Fate has a 50% success chance and a 50% curse chance.
5. Update the player's Avatar Points and Evolution Gems.
```

Suggested power formula:

```text
Guardian effects do not require a battle calculation.
```

---

# 5. Suggested Element Relationship for Later

This is optional for the terminal MVP. Do not implement until the core loop works.

| Type | Strong Against | Weak Against |
|---|---|---|
| Fire | Nature, Dark | Water, Rock |
| Nature | Water, Rock | Fire, Air |
| Water | Fire, Rock | Electric, Nature |
| Electric | Water, Air | Rock |
| Rock | Electric, Fire | Water, Nature |
| Air | Nature, Mystic | Electric, Rock |
| Dark | Mystic | Light / Guardian |
| Mystic / Psychic | Dark, Air | Dark, Guardian |

---

# 6. MVP Balancing Notes

## Recommended Starting Avatar Points

```text
2-player game: 100 Avatar Points each
3-player game: 120 Avatar Points each
```

## Recommended Origin Gate Reward

```text
Passing Origin Gate:
+1 Evolution Gem
+10 Avatar Points
Revive each defeated owned Evoran with 50% of its maximum HP
```

## Recommended Evolution Cost

```text
3 Evolution Gems = 1 evolution
```

## Recommended Opponent-Owned Tile Battle Rule

```text
If a player lands on an opponent-owned Evoran tile:
The landing player selects one active owned Evoran.
The selected Evoran battles the defending Evoran.
Battle damage reduces Evoran HP only.
Normal battle damage does not reduce Avatar Points.
```

## Recommended Own Tile Rule

For the first version:

```text
Landing on your own Evoran tile causes no damage and no reward.
```

Later, this can become:

```text
Landing on your own Evoran tile heals that Evoran by +5 HP.
```

---

# 7. Complete Roster Summary

## Starter Evorans

```text
Cindroki  -> Cindrava   | Fire
Leafari   -> Floravyn   | Nature
Aquillo   -> Aquarion   | Water
Voltrik   -> Voltrion   | Electric
```

## Wild Evorans

```text
Mossari    -> Mossarion    | Nature
Thorniva   -> Thornivine   | Nature
Florayn    -> Floralith    | Nature
Pebloru    -> Peblorion    | Rock
Cragorn    -> Cragorak     | Rock
Basaldrum  -> Basaldrake   | Rock
Sparqit    -> Sparqion     | Electric
Ionixu     -> Ionivolt     | Electric
Thundravo  -> Thundravox   | Electric
Emberu     -> Emberion     | Fire
Flarexon   -> Flarexar     | Fire
Pyroclast  -> Pyroclaxon   | Fire
Ripplin    -> Ripplora     | Water
Mistora    -> Mistovyn     | Water
Tidalux    -> Tidalorian   | Water
Galevi     -> Galevyr      | Air
Driftail   -> Driftalon    | Air
Zephyrox   -> Zephyron     | Air
Duskleaf   -> Duskthorn    | Dark
Umbraxo    -> Umbraxor     | Dark
Voidmar    -> Voidmare     | Dark
Auramind   -> Auramage     | Mystic / Psychic
Runelith   -> Runelorian   | Mystic / Psychic
```

## Guardian Evorans

```text
Solvyrion  | Guardian of Radiance and Preservation
Noctharax  | Guardian of Ruin and Corruption
Aequorion  | Guardian of Balance and Fate
```
