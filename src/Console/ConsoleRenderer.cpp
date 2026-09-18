#include "Console/ConsoleRenderer.hpp"

#include <iostream>

namespace ConsoleRenderer
{

void gameTitleIntroduction()
{
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "              E V O S P H E R E\n";
    std::cout << "========================================\n";
    std::cout << " Welcome to the World of Evorans!\n";
    std::cout << "========================================\n\n";
}

void gameRules()
{
    std::cout << "--------------- GAME RULES --------------\n";
    std::cout << "1. Players take turns.\n";
    std::cout << "2. Keep your avatar alive.\n";
    std::cout << "3. The last active player wins.\n";
    std::cout << "-----------------------------------------\n\n";
}

void playerStatus(const EvoSphere::Player& player)
{
    std::cout << "\n";
    std::cout << "------------- AVATAR STATUS -------------\n";
    std::cout << "Avatar Name:      " << player.avatarName << "\n";
    std::cout << "Avatar Points:    " << player.avatarPoints << "\n";
    std::cout << "Evolution Gems:   " << player.evolutionGems << "\n";
    std::cout << "Board Position:   " << player.currentPosition << "\n";
    std::cout << "Score:            " << player.score << "\n";
    std::cout << "Owned Evorans:\n";
    if (player.ownedEvorans.empty())
    {
        std::cout << "  None\n";
    }
    else
    {
        for (const EvoSphere::Evoran& evoran : player.ownedEvorans)
        {
            std::cout << "  - " << EvoSphere::getDisplayName(&evoran)
                << "  HP: " << EvoSphere::getCurrentHp(&evoran)
                << "/" << EvoSphere::getMaxHp(&evoran)
                << "  Damage: " << EvoSphere::getDamage(&evoran) << "\n";
        }
    }
    std::cout << "-----------------------------------------\n\n";
}

void playerTurnStart(
    const EvoSphere::Player& player,
    int round)
{
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "Round " << round << " | " << player.avatarName << "'s Turn\n";
    std::cout << "========================================\n";
}

void starterEvoranChoices(const std::vector<EvoSphere::Evoran>& starters)
{
    std::cout << "\n-------- CHOOSE YOUR STARTER EVORAN --------\n";

    for (std::size_t index = 0; index < starters.size(); index++)
    {
        std::cout << index + 1 << ". " << EvoSphere::getEvoranName(&starters[index]) << "\n";
    }

    std::cout << "-----------------------------------------\n";
}

void activeEvoranChoices(const EvoSphere::Player& player)
{
    std::cout << "\n--------- CHOOSE AN ACTIVE EVORAN ---------\n";

    int choice = 1;
    for (const EvoSphere::Evoran& evoran : player.ownedEvorans)
    {
        if (EvoSphere::isEvoranDefeated(&evoran))
        {
            continue;
        }

        std::cout << choice << ". " << EvoSphere::getDisplayName(&evoran)
            << "  HP: " << EvoSphere::getCurrentHp(&evoran)
            << "/" << EvoSphere::getMaxHp(&evoran)
            << "  Damage: " << EvoSphere::getDamage(&evoran) << "\n";
        ++choice;
    }

    std::cout << "-----------------------------------------\n";
}

void mainMenu(bool hasRolled)
{
    std::cout << "\n";
    std::cout << "--------------- MAIN MENU ---------------\n";
    if (hasRolled)
    {
        std::cout << "1. End Turn\n";
    }
    else
    {
        std::cout << "1. Roll the Orbs\n";
    }
    std::cout << "2. View Stats\n";
    std::cout << "3. Evolve an Evoran\n";
    std::cout << "4. Quit Game\n";
    std::cout << "-----------------------------------------\n";
}

void gameWinner(const EvoSphere::Player& player)
{
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "             GAME OVER\n";
    std::cout << "Winner: " << player.avatarName << "\n";
    std::cout << "========================================\n";
}

void gameMessage(const std::string& message)
{
    std::cout << "\n> " << message << "\n";
}

}
