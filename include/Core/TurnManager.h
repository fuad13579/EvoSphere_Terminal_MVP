#ifndef TURNMANAGER_H
#define TURNMANAGER_H

struct TurnManager
{
    int currentPlayerIndex = 0;
    int currentRound = 1;
};

void initializeTurnManager(TurnManager* manager);
int getCurrentPlayerIndex(const TurnManager* manager);
int getCurrentRound(const TurnManager* manager);
void nextTurn(TurnManager* manager, int playerCount);

#endif
