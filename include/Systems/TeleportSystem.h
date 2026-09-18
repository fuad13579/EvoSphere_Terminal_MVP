#pragma once

#include <array>

#include "Core/Board.h"
#include "Core/Player.h"
#include "Utils/Constants.h"

namespace EvoSphere
{
    bool isTeleportTile(const Tile& tile);

    int chooseDestination(
        int currentTeleportIndex,
        const std::array<int, TELEPORT_TILE_COUNT>& teleportIndexes
    );

    bool teleportPlayer(Player& player, Board& board);
}
