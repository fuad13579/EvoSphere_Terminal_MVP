#include "Core/Player.h"

#include <algorithm>

namespace EvoSphere
{
    void initializePlayer(Player* player, int playerId, const std::string& avatarName)
    {
        if (player == nullptr)
        {
            return;
        }

        player->playerId = playerId;
        player->avatarName = avatarName;
        player->avatarPoints = STARTING_AVATAR_POINTS;
        player->evolutionGems = STARTING_EVOLUTION_GEMS;
        player->currentPosition = STARTING_POSITION;
        player->ownedEvorans.clear();//clear all evorans
        player->defeated = false;//reset defeated status
        player->noActiveEvoranPenaltyApplied = false;
        player->orbForgeBonusRound = -1;
        player->mysticRerollRound = -1;
        player->electricBonusRound = -1;
        player->airProtectionRound = -1;
        player->nextWildBattleDamageBonus = 0;
        player->score = 0;
    }

    int getPlayerId(const Player* player)
    {
        if (player == nullptr)
        {
            return -1;
        }

        return player->playerId;
    }

    const std::string& getAvatarName(const Player* player)
    {
        static const std::string emptyName;

        if (player == nullptr)
        {
            return emptyName;
        }

        return player->avatarName;
    }

    int getAvatarPoints(const Player* player)
    {
        if (player == nullptr)
        {
            return 0;
        }

        return player->avatarPoints;
    }

    int getEvolutionGems(const Player* player)
    {
        if (player == nullptr)
        {
            return 0;
        }

        return player->evolutionGems;
    }

    int getCurrentPosition(const Player* player)
    {
        if (player == nullptr)
        {
            return -1;
        }

        return player->currentPosition;
    }

    void movePlayerTo(Player* player, int position)
    {
        if (player == nullptr)
        {
            return;
        }

        player->currentPosition = position % BOARD_SIZE;//

        if (player->currentPosition < 0)
        {
            player->currentPosition += BOARD_SIZE;
        }
    }

    void addEvolutionGems(Player* player, int amount)
    {
        if (player == nullptr || amount <= 0)
        {
            return;
        }

        player->evolutionGems += amount;
    }

    bool spendEvolutionGems(Player* player, int amount)
    {
        if (player == nullptr ||
            amount <= 0 ||
            player->evolutionGems < amount)
        {
            return false;
        }

        player->evolutionGems -= amount;
        return true;
    }

    void takeAvatarDamage(Player* player, int amount)
    {
        if (player == nullptr || amount <= 0)
        {
            return;
        }

        player->avatarPoints =
            std::max(0, player->avatarPoints - amount);

        player->defeated = player->avatarPoints <= 0;// this line checks if the player's avatar points have dropped to zero or below after taking damage. If so, it sets the player's defeated status to true, indicating that the player has been defeated in the game.
    }

    void healAvatar(Player* player, int amount)
    {
        if (player == nullptr || amount <= 0)
        {
            return;
        }

        player->avatarPoints =
            std::min(MAX_AVATAR_POINTS,player->avatarPoints + amount);// this line increases the player's avatar points by the specified amount, ensuring that the total does not exceed the maximum allowed avatar points (MAX_AVATAR_POINTS). It uses the std::min function to compare the new total with MAX_AVATAR_POINTS and assigns the smaller value to player->avatarPoints, effectively capping the avatar points at the maximum limit.

        player->defeated = player->avatarPoints <= 0;
    }

    void addEvoran(Player* player, const Evoran& evoran)
    {
        if (player == nullptr)
        {
            return;
        }

        player->ownedEvorans.push_back(evoran);
        updateNoActiveEvoranPenalty(player);
    }

    const std::vector<Evoran>& getOwnedEvorans(const Player* player)
    {
        static const std::vector<Evoran> emptyEvorans;

        if (player == nullptr)
        {
            return emptyEvorans;
        }

        return player->ownedEvorans;
    }

    bool hasOwnedEvorans(const Player* player)
    {
        return player != nullptr && !player->ownedEvorans.empty();
    }

    bool hasActiveEvorans(const Player* player)
    {
        if (!hasOwnedEvorans(player))
        {
            return false;
        }

        for (const Evoran& evoran : player->ownedEvorans)
        {
            if (!isEvoranDefeated(&evoran))
            {
                return true;
            }
        }

        return false;
    }

    void updateNoActiveEvoranPenalty(Player* player)
    {
        if (player == nullptr)
        {
            return;
        }

        if (hasActiveEvorans(player))
        {
            player->noActiveEvoranPenaltyApplied = false;
            return;
        }

        if (!player->noActiveEvoranPenaltyApplied)
        {
            takeAvatarDamage(player, NO_ACTIVE_EVORAN_AVATAR_DAMAGE);
            player->noActiveEvoranPenaltyApplied = true;
        }
    }// this function checks if the player has any active Evorans. If the player has no active Evorans and the penalty has not been applied yet, it applies a penalty by reducing the player's avatar points by a predefined amount (NO_ACTIVE_EVORAN_AVATAR_DAMAGE) and sets the noActiveEvoranPenaltyApplied flag to true. If the player has active Evorans, it resets the penalty flag to false, allowing for future penalties if the player loses all active Evorans again.

    Evoran* getStrongestEvoran(Player* player)
    {
        if (!hasOwnedEvorans(player))
        {
            return nullptr;
        }

        Evoran* strongest = &player->ownedEvorans[0];//this line initializes a pointer to the first Evoran in the player's ownedEvorans vector, assuming that the player has at least one Evoran. It serves as the starting point for finding the strongest Evoran based on their damage values.

        for (Evoran& evoran : player->ownedEvorans)
        {
            if (getDamage(&evoran) > getDamage(strongest))
            {
                strongest = &evoran;
            }
        }

        return strongest;
    }

    bool isAvatarDefeated(const Player* player)
    {
        return player == nullptr ||player->defeated ||player->avatarPoints <= 0;
    }

    void reviveDefeatedEvorans(Player* player)
{
    if (player == nullptr)
    {
        return;
    }

    for (Evoran& evoran : player->ownedEvorans)
    {
        if (isEvoranDefeated(&evoran))
        {
            // A revived Evoran returns weakened, so losing a battle still matters.
            // max(1, ...) also makes a one-HP Evoran revive as an active Evoran.
            evoran.currentHp = std::max(1, evoran.maxHp / 2);
        }
    }

    updateNoActiveEvoranPenalty(player);
}// Revives every defeated owned Evoran at 50% maximum HP and then clears the no-active-team penalty state.

    bool isAlive(const Player* player)
    {
        return !isAvatarDefeated(player);
    }
}
