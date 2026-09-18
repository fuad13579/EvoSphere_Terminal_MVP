#include "Core/Guardian.h"

#include "Utils/Random.h"

namespace EvoSphere
{
    void initializeGuardian(
        Guardian* guardian,
        const std::string& name,
        const std::string& title,
        ElementType elementType,
        const std::string& specialPower,
        const std::array<std::string, 3>& blessings,
        const std::array<std::string, 3>& curses
    )
    {
        if (guardian == nullptr)
        {
            return;
        }

        guardian->name = name;
        guardian->title = title;
        guardian->elementType = elementType;
        guardian->specialPower = specialPower;
        guardian->blessings = blessings;
        guardian->curses = curses;
    }

    GuardianOutcome applyGuardianEncounter(
        Player* player,
        const Guardian* guardian,
        AequorionChoice aequorionChoice
    )
    {
        if (player == nullptr || guardian == nullptr || isAvatarDefeated(player))
        {
            return GuardianOutcome::Invalid;
        }

        if (guardian->name == "Solvyrion")
        {
            switch (randomIndex(3))
            {
            case 0:
                healAvatar(player, 20);
                return GuardianOutcome::SolvyrionHealingBlessing;
            case 1:
                addEvolutionGems(player, 2);
                return GuardianOutcome::SolvyrionGemBlessing;
            default:
                healAvatar(player, 10);
                addEvolutionGems(player, 1);
                return GuardianOutcome::SolvyrionBalancedBlessing;
            }
        }

        if (guardian->name == "Noctharax")
        {
            switch (randomIndex(3))
            {
            case 0:
                takeAvatarDamage(player, 35);
                return GuardianOutcome::NoctharaxMajorCurse;
            case 1:
                spendEvolutionGems(player, 1);
                return GuardianOutcome::NoctharaxGemCurse;
            default:
                takeAvatarDamage(player, 15);
                return GuardianOutcome::NoctharaxMinorCurse;
            }
        }

        if (guardian->name != "Aequorion")
        {
            return GuardianOutcome::Invalid;
        }

        if (aequorionChoice == AequorionChoice::Balance)
        {
            healAvatar(player, 10);
            addEvolutionGems(player, 1);
            return GuardianOutcome::AequorionBalance;
        }

        if (randomInt(0, 1) == 0)
        {
            healAvatar(player, 25);
            addEvolutionGems(player, 2);
            return GuardianOutcome::AequorionFateBlessing;
        }

        takeAvatarDamage(player, 25);
        return GuardianOutcome::AequorionFateCurse;
    }
}
