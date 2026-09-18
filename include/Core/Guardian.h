#pragma once

#include <array>
#include <string>

#include "Core/Player.h"
#include "Utils/Constants.h"

namespace EvoSphere
{
    struct Guardian
    {
        std::string name;
        std::string title;
        ElementType elementType = ElementType::None;
        std::string specialPower;
        std::array<std::string, 3> blessings;
        std::array<std::string, 3> curses;
    };

    enum class AequorionChoice
    {
        Balance,
        Fate
    };

    enum class GuardianOutcome
    {
        Invalid,
        SolvyrionHealingBlessing,
        SolvyrionGemBlessing,
        SolvyrionBalancedBlessing,
        NoctharaxMajorCurse,
        NoctharaxGemCurse,
        NoctharaxMinorCurse,
        AequorionBalance,
        AequorionFateBlessing,
        AequorionFateCurse
    };

    void initializeGuardian(
        Guardian* guardian,
        const std::string& name,
        const std::string& title,
        ElementType elementType,
        const std::string& specialPower,
        const std::array<std::string, 3>& blessings,
        const std::array<std::string, 3>& curses
    );

    GuardianOutcome applyGuardianEncounter(
        Player* player,
        const Guardian* guardian,
        AequorionChoice aequorionChoice
    );
}
