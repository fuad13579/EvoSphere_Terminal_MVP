#ifndef BOARD_H // Prevents this header from being included more than once.
#define BOARD_H // Marks this header as already included.

#include <map> // Uses std::map to find Evorans by name.
#include <string> // Uses std::string as the map key and territory argument.
#include <vector> // Uses std::vector for board tiles and teleport positions.

#include "Core/Tile.h" // Uses Tile and Evoran data.

namespace EvoSphere
{
    struct Player;
}

struct Board // Stores all board state without classes or member functions.
{
    std::vector<Tile> tiles; // Stores exactly 40 tiles after initialization.
    std::map<std::string, EvoSphere::Evoran> evoransByName; // Stores wild Evorans by their names.
    std::vector<int> teleportTileIndexes; // Stores the four Teleport Terminal positions.
};

void initializeBoard(Board* board); // Builds the complete 40-tile board.
Tile* getTile(Board* board, int index); // Returns a mutable tile, or nullptr for an invalid index.
const Tile* getTileConst(const Board* board, int index); // Returns a read-only tile, or nullptr for an invalid index.
int getBoardSize(const Board* board); // Returns the number of tiles, or zero for a missing board.
bool setTileOwner(Board* board, int index, int playerId); // Updates ownership at one tile index.
const std::vector<int>& getTeleportTileIndexes(const Board* board); // Returns all Teleport Terminal indexes.
EvoSphere::Evoran* getEvoranOnTile(Board* board, int index); // Returns the Wild Evoran stored at one tile.
const EvoSphere::Evoran* getEvoranOnTile(const Board* board, int index); // Reads the Wild Evoran stored at one tile.
bool updateEvoranOnTile(Board* board, int index, const EvoSphere::Evoran& evoran); // Updates a tile's Wild Evoran data.
void syncOwnedEvoransOnBoard(Board* board, const EvoSphere::Player& player); // Copies an owner's current Evoran HP to the matching owned tiles.
std::vector<int> getTerritoryTiles(const Board* board, const std::string& territoryName); // Finds every tile in one territory.
bool doesPlayerOwnTerritory(const Board* board, int playerId, const std::string& territoryName); // Checks full territory ownership.
bool isBoardValid(const Board* board); // Checks indexes and the required tile counts.

#endif // BOARD_H
