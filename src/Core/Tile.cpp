#include "Core/Tile.h" // Uses the Tile data structure and declarations.

namespace
{
    const std::string EMPTY_TEXT; // Supplies a safe empty string for missing tiles.

    std::string defaultTileName(TileType tileType) // Creates a readable name when no Evoran name exists.
    {
        switch (tileType)
        {
        case TileType::OriginGate: return "Origin Gate";
        case TileType::WildEvoran: return "Wild Evoran";
        case TileType::Guardian: return "Guardian";
        case TileType::Teleport: return "Teleport Terminal";
        case TileType::BlessingShrine: return "Blessing Shrine";
        case TileType::ChaosRift: return "Chaos Rift";
        case TileType::SpecialOwnable: return "Special Ownable";
        }

        return "Unknown Tile"; // Handles unexpected enum values safely.
    }
}

Tile createTile(int index, TileType tileType, EvoSphere::ElementType elementType, const std::string& territoryName, const std::string& linkedEvoranName, bool ownable) // Creates a complete tile record.
{
    Tile tile; // Starts with the safe defaults in Tile.h.
    tile.index = index; // Saves the board position.
    tile.tileType = tileType; // Saves the tile category.
    tile.elementType = elementType; // Saves the tile element.
    tile.territoryName = territoryName; // Saves the territory name.
    tile.linkedEvoranName = linkedEvoranName; // Saves the connected Evoran or Guardian name.
    if (linkedEvoranName.empty())
    {
        tile.name = defaultTileName(tileType);
    }
    else
    {
        tile.name = linkedEvoranName;
    }
    tile.ownable = ownable; // Saves whether players may own this tile.
    return tile; // Returns the initialized Tile value.
}

int getIndex(const Tile* tile) // Reads an index safely.
{
    if (tile == nullptr)
    {
        return -1;
    }

    return tile->index;
}

const std::string& getName(const Tile* tile) // Reads a name safely.
{
    if (tile == nullptr)
    {
        return EMPTY_TEXT;
    }

    return tile->name;
}

TileType getTileType(const Tile* tile) // Reads a tile type safely.
{
    if (tile == nullptr)
    {
        return TileType::OriginGate;
    }

    return tile->tileType;
}

EvoSphere::ElementType getElementType(const Tile* tile) // Reads an element safely.
{
    if (tile == nullptr)
    {
        return EvoSphere::ElementType::None;
    }

    return tile->elementType;
}

int getOwnerId(const Tile* tile) // Reads an owner safely.
{
    if (tile == nullptr)
    {
        return -1;
    }

    return tile->ownerId;
}

bool setOwnerId(Tile* tile, int ownerId) // Stores a player owner or clears ownership.
{
    if (tile == nullptr || !tile->ownable || ownerId < -1) return false; // Rejects invalid ownership changes.
    tile->ownerId = ownerId; // Saves the new owner ID.
    return true; // Reports success.
}

bool isOwned(const Tile* tile) { return tile != nullptr && tile->ownable && tile->ownerId >= 0; } // Checks ownership safely.
bool isOwnedBy(const Tile* tile, int playerId) { return playerId >= 0 && isOwned(tile) && tile->ownerId == playerId; } // Checks a specific owner.
bool isOwnedByOpponent(const Tile* tile, int playerId) { return playerId >= 0 && isOwned(tile) && tile->ownerId != playerId; } // Checks an opponent owner.

const std::string& getLinkedEvoranName(const Tile* tile) // Reads the linked name safely.
{
    if (tile == nullptr)
    {
        return EMPTY_TEXT;
    }

    return tile->linkedEvoranName;
}

bool setLinkedEvoranName(Tile* tile, const std::string& linkedEvoranName) // Changes the linked Evoran name.
{
    if (tile == nullptr) return false; // Rejects a missing tile.
    tile->linkedEvoranName = linkedEvoranName; // Stores the requested name.
    if (linkedEvoranName.empty())
    {
        tile->name = defaultTileName(tile->tileType);
    }
    else
    {
        tile->name = linkedEvoranName;
    }
    return true; // Reports success.
}

const std::string& getTerritoryName(const Tile* tile) // Reads a territory safely.
{
    if (tile == nullptr)
    {
        return EMPTY_TEXT;
    }

    return tile->territoryName;
}
bool isTileOwnable(const Tile* tile) { return tile != nullptr && tile->ownable; } // Checks whether ownership is allowed.

const EvoSphere::Evoran* getWildEvoran(const Tile* tile) // Reads the Evoran stored on a wild tile.
{
    if (tile == nullptr || tile->tileType != TileType::WildEvoran)
    {
        return nullptr;
    }

    return &tile->wildEvoran;
}

bool setWildEvoran(Tile* tile, const EvoSphere::Evoran* evoran) // Copies battle data onto a wild tile.
{
    if (tile == nullptr || evoran == nullptr || tile->tileType != TileType::WildEvoran) return false; // Validates both inputs.
    tile->wildEvoran = *evoran; // Copies the Evoran data onto this tile.
    return true; // Reports success.
}
