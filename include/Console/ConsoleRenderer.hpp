#pragma once

#include <string>
#include <vector>

#include "Core/Evoran.h"
#include "Core/Player.h"

namespace ConsoleRenderer
{
    void gameTitleIntroduction();
    void gameRules();

    void playerStatus(const EvoSphere::Player& player);
    void playerTurnStart(const EvoSphere::Player& player, int round);
    void starterEvoranChoices(const std::vector<EvoSphere::Evoran>& starters);
    void activeEvoranChoices(const EvoSphere::Player& player);

    void mainMenu(bool hasRolled);
    void gameWinner(const EvoSphere::Player& player);

    void gameMessage(const std::string& message);
}
