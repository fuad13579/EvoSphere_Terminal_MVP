#include "Core/TurnManager.h"

void initializeTurnManager(TurnManager* manager)
{
    if (manager == nullptr)
    {
        return;
    }

    manager->currentPlayerIndex = 0;
    manager->currentRound = 1;
}

int getCurrentPlayerIndex(const TurnManager* manager)
{
    if (manager == nullptr)
    {
        return 0;
    }

    return manager->currentPlayerIndex;
}

int getCurrentRound(const TurnManager* manager)
{
    if (manager == nullptr)
    {
        return 0;
    }

    return manager->currentRound;
}

void nextTurn(TurnManager* manager, int playerCount)
{
    if (manager == nullptr || playerCount <= 0)
    {
        return;
    }

    ++manager->currentPlayerIndex;
    if (manager->currentPlayerIndex >= playerCount)
    {
        ++manager->currentRound;
        manager->currentPlayerIndex = 0;
    }
}
