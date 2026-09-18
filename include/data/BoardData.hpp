#pragma once

#include <array>

#include "Core/Tile.h"
#include "Utils/Constants.h"

namespace EvoSphere
{
    std::array<Tile, BOARD_SIZE> createBoardTiles();//array of tiles that represent the game board, with a size defined by the constant BOARD_SIZE. Each tile is an instance of the Tile struct, which holds data for one board tile, including its index, type, related ID, and ownable status.
    //example usage std::array<Tile, BOARD_SIZE> board = createBoardTiles();Tile firstTile = board[0];

    const std::array<int, TELEPORT_TILE_COUNT>&getTeleportTerminalPositions();//returns a reference to a constant array of integers representing the positions of teleport terminal tiles on the game board. The size of the array is defined by the constant TELEPORT_TILE_COUNT, which indicates how many teleport terminal tiles are present on the board.
    //example usage const std::array<int, TELEPORT_TILE_COUNT>& teleportPositions = getTeleportTerminalPositions();int firstTeleportPosition = teleportPositions[0];
}