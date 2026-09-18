#include "Core/Board.h" // Uses the Board API declarations.

#include "Core/Player.h" // Uses Player data when synchronizing owned tile defenders.
#include "data/BoardData.hpp" // Uses the fixed 40-tile layout.
#include "data/EvoranDatabase.hpp" // Uses the Wild Evoran roster.

namespace
{
    const std::vector<int> EMPTY_INDEXES; // Supplies a safe result for a missing board.
}

void initializeBoard(Board* board) // Builds the playable board from fixed game data.
{
    if (board == nullptr) return; // Rejects a missing board safely.

    const auto boardTiles = EvoSphere::createBoardTiles(); // Reads the fixed tile layout.
    const auto wildEvorans = EvoSphere::createWildEvorans(); // Reads the Wild Evoran roster.
    board->tiles.assign(boardTiles.begin(), boardTiles.end()); // Copies all 40 tiles into the Board vector.
    board->evoransByName.clear(); // Removes any old game data before a new game starts.
    board->teleportTileIndexes.clear(); // Removes old Teleport Terminal positions.

    for (const EvoSphere::Evoran& evoran : wildEvorans) // Adds every Wild Evoran to the name map.
    {
        board->evoransByName[evoran.name] = evoran; // Uses the Evoran name as the lookup key.
    }

    for (Tile& tile : board->tiles) // Connects tiles to their Evorans and finds Teleport Terminals.
    {
        if (tile.tileType == TileType::Teleport) board->teleportTileIndexes.push_back(tile.index); // Stores each Teleport Terminal index.
        const auto evoran = board->evoransByName.find(tile.linkedEvoranName); // Looks for a matching Wild Evoran.
        if (tile.tileType == TileType::WildEvoran && evoran != board->evoransByName.end()) tile.wildEvoran = evoran->second; // Copies the battle data onto the tile.
    }
}

Tile* getTile(Board* board, int index) // Returns one mutable tile by its index.
{
    if (board == nullptr || index < 0 || index >= getBoardSize(board)) return nullptr; // Rejects missing boards and invalid indexes.
    return &board->tiles[static_cast<std::size_t>(index)]; // Returns the requested tile.
}

const Tile* getTileConst(const Board* board, int index) // Returns one read-only tile by its index.
{
    if (board == nullptr || index < 0 || index >= getBoardSize(board)) return nullptr; // Rejects missing boards and invalid indexes.
    return &board->tiles[static_cast<std::size_t>(index)]; // Returns the requested tile.
}

int getBoardSize(const Board* board) // Reports the number of initialized tiles.
{
    if (board == nullptr)
    {
        return 0;
    }

    return static_cast<int>(board->tiles.size()); // Converts the vector size to the API's integer result.
}

bool setTileOwner(Board* board, int index, int playerId) // Changes tile ownership through the Board API.
{
    return setOwnerId(getTile(board, index), playerId); // Reuses Tile validation for the selected tile.
}

const std::vector<int>& getTeleportTileIndexes(const Board* board) // Reads the Teleport Terminal list.
{
    if (board == nullptr)
    {
        return EMPTY_INDEXES;
    }

    return board->teleportTileIndexes; // Returns the board's Teleport Terminal list.
}

EvoSphere::Evoran* getEvoranOnTile(Board* board, int index) // Returns mutable Wild Evoran data.
{
    Tile* tile = getTile(board, index); // Finds the requested tile first.
    if (tile == nullptr || tile->tileType != TileType::WildEvoran)
    {
        return nullptr;
    }

    return &tile->wildEvoran;
}

const EvoSphere::Evoran* getEvoranOnTile(const Board* board, int index) // Returns read-only Wild Evoran data.
{
    const Tile* tile = getTileConst(board, index); // Finds the requested tile first.
    if (tile == nullptr || tile->tileType != TileType::WildEvoran)
    {
        return nullptr;
    }

    return &tile->wildEvoran;
}

bool updateEvoranOnTile(Board* board, int index, const EvoSphere::Evoran& evoran) // Updates a tile and the name map together.
{
    Tile* tile = getTile(board, index); // Finds the selected tile.
    if (tile == nullptr || tile->tileType != TileType::WildEvoran) return false; // Allows updates only on Wild Evoran tiles.
    tile->wildEvoran = evoran; // Updates the battle state stored on the tile.
    tile->linkedEvoranName = evoran.name; // Keeps the linked name current.
    tile->name = evoran.name; // Keeps the display name current.
    board->evoransByName[evoran.name] = evoran; // Keeps the board's lookup map current.
    return true; // Reports success.
}

void syncOwnedEvoransOnBoard(Board* board, const EvoSphere::Player& player) // Keeps a tile defender's displayed HP equal to its owner's Evoran HP.
{
    if (board == nullptr)
    {
        return;
    }

    for (Tile& tile : board->tiles)
    {
        if (tile.tileType != TileType::WildEvoran || tile.ownerId != player.playerId)
        {
            continue;
        }

        for (const EvoSphere::Evoran& evoran : player.ownedEvorans)
        {
            if (EvoSphere::getEvoranName(&evoran) == tile.linkedEvoranName)
            {
                tile.wildEvoran = evoran;
                board->evoransByName[evoran.name] = evoran;
                break;
            }
        }
    }
}

std::vector<int> getTerritoryTiles(const Board* board, const std::string& territoryName) // Finds all tiles in a named territory.
{
    std::vector<int> indexes; // Stores matching tile indexes.
    if (board == nullptr || territoryName.empty()) return indexes; // Rejects invalid searches safely.
    for (const Tile& tile : board->tiles) if (tile.territoryName == territoryName) indexes.push_back(tile.index); // Adds each matching tile.
    return indexes; // Returns all matching indexes.
}

bool doesPlayerOwnTerritory(const Board* board, int playerId, const std::string& territoryName) // Checks whether one player owns every ownable tile in a territory.
{
    const std::vector<int> indexes = getTerritoryTiles(board, territoryName); // Finds the requested territory first.
    if (playerId < 0 || indexes.empty()) return false; // Rejects invalid players and unknown territories.
    for (int index : indexes) if (!isOwnedBy(getTileConst(board, index), playerId)) return false; // Requires ownership of every territory tile.
    return true; // Reports full territory ownership.
}

bool isBoardValid(const Board* board) // Verifies the documented 40-tile distribution.
{
    if (board == nullptr || getBoardSize(board) != EvoSphere::BOARD_SIZE || static_cast<int>(getTeleportTileIndexes(board).size()) != EvoSphere::TELEPORT_TILE_COUNT) return false; // Verifies the required board and teleport sizes.

    int originGates = 0; // Counts Origin Gate tiles.
    int wildEvorans = 0; // Counts Wild Evoran tiles.
    int guardians = 0; // Counts Guardian tiles.
    int teleports = 0; // Counts Teleport Terminal tiles.
    int blessings = 0; // Counts Blessing Shrine tiles.
    int chaosRifts = 0; // Counts Chaos Rift tiles.
    int specialTiles = 0; // Counts Special Ownable tiles.

    for (int index = 0; index < getBoardSize(board); ++index) // Checks every board tile.
    {
        const Tile& tile = board->tiles[static_cast<std::size_t>(index)]; // Reads the current tile.
        if (tile.index != index) return false; // Requires the stored index to match the vector position.
        switch (tile.tileType) // Adds the tile to its type count.
        {
        case TileType::OriginGate: ++originGates; break;
        case TileType::WildEvoran: ++wildEvorans; break;
        case TileType::Guardian: ++guardians; break;
        case TileType::Teleport: ++teleports; break;
        case TileType::BlessingShrine: ++blessings; break;
        case TileType::ChaosRift: ++chaosRifts; break;
        case TileType::SpecialOwnable: ++specialTiles; break;
        }
    }

    return originGates == 1 && wildEvorans == EvoSphere::WILD_EVORAN_TILE_COUNT && guardians == EvoSphere::GUARDIAN_TILE_COUNT && teleports == EvoSphere::TELEPORT_TILE_COUNT && blessings == EvoSphere::BLESSING_SHRINE_TILE_COUNT && chaosRifts == EvoSphere::CHAOS_RIFT_TILE_COUNT && specialTiles == EvoSphere::SPECIAL_OWNABLE_TILE_COUNT; // Confirms every required tile count.
}
