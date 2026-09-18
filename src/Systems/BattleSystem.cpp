#include "Systems/BattleSystem.h"

#include "Utils/Random.h"

namespace EvoSphere
{
    namespace
    {
        const char* territoryName(ElementType element)
        {
            switch (element)
            {
            case ElementType::Nature: return "Nature";
            case ElementType::Fire: return "Fire";
            case ElementType::Rock: return "Rock";
            case ElementType::Dark: return "Dark";
            default: return "";
            }
        }

        bool ownsElement(const Board& board, const Player& player, ElementType element)
        {
            return doesPlayerOwnTerritory(&board, player.playerId, territoryName(element));
        }

        int outgoingDamage(const Board& board, const Player& player, const Evoran& evoran)
        {
            const int damage = getDamage(&evoran);
            if (getElementType(&evoran) == ElementType::Fire &&
                ownsElement(board, player, ElementType::Fire))
            {
                return damage + damage / 5;
            }

            return damage;
        }

        int incomingDamage(const Board& board, const Player& player, const Evoran& evoran, int damage)
        {
            if (getElementType(&evoran) == ElementType::Dark && ownsElement(board, player, ElementType::Dark) && randomInt(1, 100) <= 40) return 0;
            if (getElementType(&evoran) == ElementType::Rock && ownsElement(board, player, ElementType::Rock)) return std::max(0, damage - 5);
            return damage;
        }

        void applyNatureHeal(const Board& board, Player& player)
        {
            if (!ownsElement(board, player, ElementType::Nature)) return;
            for (Evoran& evoran : player.ownedEvorans) if (getElementType(&evoran) == ElementType::Nature) heal(&evoran, 10);
        }
    }
    void attack(Evoran& attacker, Evoran& defender)// this function simulates an attack from one Evoran to another. It takes references to the attacker and defender Evorans as parameters. The function first checks if either the attacker or defender is defeated (i.e., has 0 or less HP). If either is defeated, the function returns early without performing any attack. If both Evorans are still active, the function calculates the damage dealt by the attacker and applies it to the defender's current HP using the takeDamage function.
    {
        if (isEvoranDefeated(&attacker) || isEvoranDefeated(&defender))
        {
            return;
        }

        takeDamage(&defender, getDamage(&attacker));//this line calls the takeDamage function, passing in a pointer to the defender Evoran and the damage value obtained from the getDamage function for the attacker Evoran. The takeDamage function reduces the defender's current HP by the specified damage amount, simulating the effect of the attack.
    }

    bool runWildBattle(
        Player& player,
        Evoran& selectedEvoran,
        Evoran& wildEvoran,
        const Board& board
    )// This function simulates a battle between a player's selected Evoran and a wild Evoran. It takes references to the player, the  selected Evoran, and the wild Evoran as parameters. The function first checks if the player's selected Evoran, or wild Evoran is defeated. If any of them are defeated, the function returns false, indicating that the battle cannot proceed. If all participants are active, the function enters a loop where the selected Evoran attacks the wild Evoran, and then the wild Evoran attacks back. The loop continues until either the selected Evoran or the wild Evoran is defeated. If the wild Evoran's current HP drops below a certain threshold (defined by CAPTURE_HP_THRESHOLD_PERCENT), the function returns true, indicating that the player has a chance to capture the wild Evoran. If the selected Evoran is defeated first, the function returns false.
    {
        if (isAvatarDefeated(&player) ||
            isEvoranDefeated(&selectedEvoran) ||
            isEvoranDefeated(&wildEvoran))
        {
            return false;
        }

        while (!isEvoranDefeated(&selectedEvoran) &&
            !isEvoranDefeated(&wildEvoran))
        {
            takeDamage(&wildEvoran, outgoingDamage(board, player, selectedEvoran) + player.nextWildBattleDamageBonus);

            if (getCurrentHp(&wildEvoran) * 100 <=
                getMaxHp(&wildEvoran) * CAPTURE_HP_THRESHOLD_PERCENT)
            {
                player.nextWildBattleDamageBonus = 0;
                return true;
            }

            takeDamage(&selectedEvoran, incomingDamage(board, player, selectedEvoran, getDamage(&wildEvoran)));
        }

        updateNoActiveEvoranPenalty(&player);
        applyNatureHeal(board, player);
        player.nextWildBattleDamageBonus = 0;

        return false;
    }

    int calculatePower(const Evoran& evoran)
    {
        return getCurrentHp(&evoran) + getDamage(&evoran);
    }

    bool canEvoranBattle(const Evoran& evoran)
    {
        return !isEvoranDefeated(&evoran);
    }

    int getTerritoryDefenseBonus(const Board& board, const Tile& tile, int defendingPlayerId)
    {
        if (tile.tileType != TileType::WildEvoran ||
            tile.territoryName.empty() ||
            defendingPlayerId < 0 ||
            !doesPlayerOwnTerritory(&board, defendingPlayerId, tile.territoryName))
        {
            return 0;
        }

        return TERRITORY_DEFENSE_DAMAGE_BONUS;
    }

    bool runOpponentOwnedTileBattle(
        Player& landingPlayer,
        Evoran& attackingEvoran,
        Player& defendingPlayer,
        Evoran& defendingEvoran,
        const Board& board,
        const Tile& defendedTile
    )//Returns true if the battle was won.
    {
        if (isAvatarDefeated(&landingPlayer) ||
            isAvatarDefeated(&defendingPlayer) ||
            !canEvoranBattle(attackingEvoran) ||
            !canEvoranBattle(defendingEvoran))
        {
            return false;
        }

        while (canEvoranBattle(attackingEvoran) &&
            canEvoranBattle(defendingEvoran))
        {
            takeDamage(
                &defendingEvoran,
                incomingDamage(
                    board,
                    defendingPlayer,
                    defendingEvoran,
                    outgoingDamage(board, landingPlayer, attackingEvoran)
                )
            );

            if (canEvoranBattle(defendingEvoran))
            {
                takeDamage(
                    &attackingEvoran,
                    incomingDamage(
                        board,
                        landingPlayer,
                        attackingEvoran,
                        outgoingDamage(board, defendingPlayer, defendingEvoran) +
                            getTerritoryDefenseBonus(board, defendedTile, defendingPlayer.playerId)
                    )
                );
            }
        }

        if (isEvoranDefeated(&attackingEvoran))
        {
            takeAvatarDamage(&landingPlayer, OPPONENT_TILE_BATTLE_LOSS_AVATAR_DAMAGE);
        }

        if (isEvoranDefeated(&defendingEvoran))
        {
            takeAvatarDamage(&defendingPlayer, OPPONENT_TILE_BATTLE_LOSS_AVATAR_DAMAGE);
        }

        updateNoActiveEvoranPenalty(&landingPlayer);
        updateNoActiveEvoranPenalty(&defendingPlayer);
        applyNatureHeal(board, landingPlayer);
        applyNatureHeal(board, defendingPlayer);

        return true;
    }
}
