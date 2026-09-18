#pragma once

#include <string>
#include <vector>

#include "Core/Evoran.h"
#include "Utils/Constants.h"

namespace EvoSphere
{
    struct Player
    {
        int playerId = 0;
        std::string avatarName;
        int avatarPoints = STARTING_AVATAR_POINTS;
        int evolutionGems = STARTING_EVOLUTION_GEMS;
        int currentPosition = STARTING_POSITION;
        std::vector<Evoran> ownedEvorans;
        bool defeated = false;
        bool noActiveEvoranPenaltyApplied = false;
        int orbForgeBonusRound = -1;// this is the round number when the player last received the Orb Forge bonus, and it is used to prevent multiple bonuses in the same round.//
        int mysticRerollRound = -1;
        int electricBonusRound = -1;
        int airProtectionRound = -1;
        int nextWildBattleDamageBonus = 0;// this is the bonus damage that will be applied to the next wild battle, and it is reset after the battle. It is set when a player lands on a Chaos Rift tile.//
        int score = 0;//Changed by Musfiq to merge Game.cpp and Player.cpp//
    };

    void initializePlayer(Player* player, int playerId, const std::string& avatarName);

    int getPlayerId(const Player* player);
    const std::string& getAvatarName(const Player* player);
    int getAvatarPoints(const Player* player);
    int getEvolutionGems(const Player* player);
    int getCurrentPosition(const Player* player);

    void movePlayerTo(Player* player, int position);

    void addEvolutionGems(Player* player, int amount);
    bool spendEvolutionGems(Player* player, int amount);

    void takeAvatarDamage(Player* player, int amount);
    void healAvatar(Player* player, int amount);

    void addEvoran(Player* player, const Evoran& evoran);

    const std::vector<Evoran>& getOwnedEvorans(const Player* player);
    bool hasOwnedEvorans(const Player* player);
    bool hasActiveEvorans(const Player* player);
    void updateNoActiveEvoranPenalty(Player* player);
    Evoran* getStrongestEvoran(Player* player);
    void reviveDefeatedEvorans(Player* player);

    bool isAvatarDefeated(const Player* player);
    bool isAlive(const Player* player);
}
