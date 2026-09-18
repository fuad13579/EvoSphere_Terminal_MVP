#include "Systems/EvolutionSystem.h"

namespace EvoSphere
{
    bool canEvolve(const Player& player, const Evoran& evoran)
    {
        return !isAvatarDefeated(&player) &&
            getEvolutionGems(&player) >= EVOLUTION_GEM_COST &&
            canEvolve(&evoran);// this is from the Evoran.h file, which checks if the Evoran meets the criteria for evolution, such as having an evolved form and not already being evolved.
    }// This function checks if a player can evolve a specific Evoran. It takes a constant reference to a Player object and a constant reference to an Evoran object as parameters. The function first checks if the player is not defeated using the isDefeated function. Then, it checks if the player has enough evolution gems (at least EVOLUTION_GEM_COST) using the getEvolutionGems function. Finally, it checks if the Evoran can evolve using the canEvolve function. If all three conditions are met, the function returns true, indicating that the player can evolve the specified Evoran; otherwise, it returns false.

    bool evolveSelectedEvoran(Player& player, int evoranIndex)
    {
        if (evoranIndex < 0 ||
            evoranIndex >= static_cast<int>(player.ownedEvorans.size()))//static cast to convert the size of the ownedEvorans vector to an integer. because the size() function returns a value of type size_t, which is an unsigned integer type. By casting it to int, we ensure that the comparison with evoranIndex (which is of type int) is valid and avoids potential issues with signed/unsigned integer comparisons.
        {
            return false;
        }

        Evoran& selectedEvoran = player.ownedEvorans[evoranIndex];

        if (!canEvolve(player, selectedEvoran) ||
            !evolve(&selectedEvoran))
        {
            return false;
        }

        spendEvolutionGems(&player, EVOLUTION_GEM_COST);

        return true;
    }


}
