#ifndef TILE_H // Prevents this header from being included more than once.
#define TILE_H // Marks this header as already included.

#include <string> // Uses std::string for tile names and territory names.
#include <array> // Uses a fixed progress slot for each supported player.

#include "Core/Evoran.h" // Uses Evoran for Wild Evoran tiles.
#include "Utils/Constants.h" // Uses TileType and ElementType.

using EvoSphere::TileType; // Lets the procedural Tile API use TileType directly.

struct Tile // Stores one board space; all behavior is in free functions below.
{
    int index = 0; // Stores the position from 0 to 39.
    std::string name; // Stores the display name of this board space.
    TileType tileType = TileType::OriginGate; // Stores the kind of board space.
    EvoSphere::ElementType elementType = EvoSphere::ElementType::None; // Stores the associated element.
    int ownerId = -1; // Stores the owning player ID, or -1 when nobody owns it.
    std::string linkedEvoranName; // Stores the wild Evoran or Guardian connected to this tile.
    std::string territoryName; // Stores the territory used for ownership bonuses.
    bool ownable = false; // Allows ownership only on appropriate tile types.
    EvoSphere::Evoran wildEvoran; // Stores the battle state for a Wild Evoran tile.
    int requiredAttunement = EvoSphere::SPECIAL_TILE_ATTUNEMENT_REQUIRED;
    std::array<int, EvoSphere::MAX_PLAYERS> attunementProgress{};
};

Tile createTile(int index, TileType tileType, EvoSphere::ElementType elementType, const std::string& territoryName, const std::string& linkedEvoranName, bool ownable); // Creates a fully initialized tile.
int getIndex(const Tile* tile); // Returns the tile index, or -1 for a missing tile.
const std::string& getName(const Tile* tile); // Returns the display name safely.
TileType getTileType(const Tile* tile); // Returns the tile kind safely.
EvoSphere::ElementType getElementType(const Tile* tile); // Returns the element safely.
int getOwnerId(const Tile* tile); // Returns the owner ID, or -1 when unowned.
bool setOwnerId(Tile* tile, int ownerId); // Sets an owner, or clears ownership with -1.
bool isOwned(const Tile* tile); // Returns true when the tile has a valid owner.
bool isOwnedBy(const Tile* tile, int playerId); // Returns true when one player owns the tile.
bool isOwnedByOpponent(const Tile* tile, int playerId); // Returns true when another player owns the tile.
const std::string& getLinkedEvoranName(const Tile* tile); // Returns the connected Evoran name safely.
bool setLinkedEvoranName(Tile* tile, const std::string& linkedEvoranName); // Changes the connected Evoran name.
const std::string& getTerritoryName(const Tile* tile); // Returns the territory name safely.
bool isTileOwnable(const Tile* tile); // Returns true when a tile may be owned.
const EvoSphere::Evoran* getWildEvoran(const Tile* tile); // Returns a wild Evoran only from Wild Evoran tiles.
bool setWildEvoran(Tile* tile, const EvoSphere::Evoran* evoran); // Copies an Evoran onto a Wild Evoran tile.

#endif // TILE_H
