#pragma once

#include <vector>

#include "Core/Game.h"

struct ConsoleGameState
{
    GameState gameState;
    std::vector<EvoSphere::Player> players;
    bool running = true;
};

void runConsoleGame(ConsoleGameState* console);
