#pragma once

#include "Core/Board.h"
#include "Core/Player.h"

namespace EvoSphere
{
    int rollEnergyOrbs();

    void movePlayer(Player& player, Board& board, int rollTotal);

    bool didPassOriginGate(int oldPosition, int newPosition, int rollTotal);

    void applyOriginGateReward(Player& player, Board& board);
}
