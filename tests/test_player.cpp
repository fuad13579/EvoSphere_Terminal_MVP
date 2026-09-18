#include <cassert>

#include "Core/Player.h"

using namespace EvoSphere;

int main()
{
    Player fuad;

    initializePlayer(&fuad, 0, "Fuad");

    // Basic identity data.
    assert(getPlayerId(&fuad) == 0);
    assert(getAvatarName(&fuad) == "Fuad");

    // Starting game state.
    assert(getAvatarPoints(&fuad) == STARTING_AVATAR_POINTS);
    assert(getEvolutionGems(&fuad) == STARTING_EVOLUTION_GEMS);
    assert(getCurrentPosition(&fuad) == STARTING_POSITION);

    // A new player has no Evorans yet.
    assert(!hasOwnedEvorans(&fuad));
    assert(!hasActiveEvorans(&fuad));
    assert(getOwnedEvorans(&fuad).empty());

    // The player is still alive at the start.
    assert(!isAvatarDefeated(&fuad));
    assert(isAlive(&fuad));

        // Avatar damage reduces Avatar Points.
    takeAvatarDamage(&fuad, 30);
    assert(getAvatarPoints(&fuad) == STARTING_AVATAR_POINTS - 30);
    assert(!isAvatarDefeated(&fuad));

    // Healing restores Avatar Points.
    healAvatar(&fuad, 20);
    assert(getAvatarPoints(&fuad) == STARTING_AVATAR_POINTS - 10);

    // Healing cannot exceed the maximum Avatar Points.
    healAvatar(&fuad, MAX_AVATAR_POINTS);
    assert(getAvatarPoints(&fuad) == MAX_AVATAR_POINTS);

    // Damage cannot reduce Avatar Points below zero.
    takeAvatarDamage(&fuad, MAX_AVATAR_POINTS + 50);
    assert(getAvatarPoints(&fuad) == 0);
    assert(isAvatarDefeated(&fuad));
    assert(!isAlive(&fuad));

    // The current healAvatar() function can restore a defeated avatar.
    healAvatar(&fuad, 25);
    assert(getAvatarPoints(&fuad) == 25);
    assert(!isAvatarDefeated(&fuad));
    assert(isAlive(&fuad));

    // Invalid values do not change Avatar Points.
    takeAvatarDamage(&fuad, -10);
    assert(getAvatarPoints(&fuad) == 25);

    healAvatar(&fuad, 0);
    assert(getAvatarPoints(&fuad) == 25);

        // Adding gems increases the avatar's total.
    addEvolutionGems(&fuad, 3);
    assert(getEvolutionGems(&fuad) == STARTING_EVOLUTION_GEMS + 3);

    // Spending enough gems succeeds.
    assert(spendEvolutionGems(&fuad, 2));
    assert(getEvolutionGems(&fuad) == STARTING_EVOLUTION_GEMS + 1);

    // Spending more gems than available fails.
    assert(!spendEvolutionGems(&fuad, 2));
    assert(getEvolutionGems(&fuad) == STARTING_EVOLUTION_GEMS + 1);

    // Invalid gem amounts do not change the total.
    addEvolutionGems(&fuad, -1);
    assert(getEvolutionGems(&fuad) == STARTING_EVOLUTION_GEMS + 1);

    assert(!spendEvolutionGems(&fuad, 0));
    assert(getEvolutionGems(&fuad) == STARTING_EVOLUTION_GEMS + 1);

        // Player position wraps around the 40-tile board.
    movePlayerTo(&fuad, 12);
    assert(getCurrentPosition(&fuad) == 12);

    movePlayerTo(&fuad, BOARD_SIZE + 4);
    assert(getCurrentPosition(&fuad) == 4);

    movePlayerTo(&fuad, -1);
    assert(getCurrentPosition(&fuad) == BOARD_SIZE - 1);

    // Create two Evorans for the avatar's team.
    Evoran leafari;
    initializeEvoran(
        &leafari,
        "Leafari",
        "Floravyn",
        ElementType::Nature,
        EvoranCategory::Starter,
        110,
        19,
        145,
        30
    );

    Evoran voltrik;
    initializeEvoran(
        &voltrik,
        "Voltrik",
        "Voltrion",
        ElementType::Electric,
        EvoranCategory::Starter,
        90,
        26,
        120,
        38
    );

    // Adding Evorans creates an owned active team.
    addEvoran(&fuad, leafari);
    addEvoran(&fuad, voltrik);

    assert(hasOwnedEvorans(&fuad));
    assert(hasActiveEvorans(&fuad));
    assert(getOwnedEvorans(&fuad).size() == 2);

    // The Evoran with the largest damage value is strongest.
    Evoran* strongest = getStrongestEvoran(&fuad);
    assert(strongest != nullptr);
    assert(getName(strongest) == "Voltrik");
    assert(getDamage(strongest) == 26);

    // Defeat both owned Evorans.
    takeDamage(&fuad.ownedEvorans[0], 200);
    takeDamage(&fuad.ownedEvorans[1], 200);

    assert(!hasActiveEvorans(&fuad));

    // Losing all active Evorans applies the Avatar Point penalty once.
    const int avatarPointsBeforePenalty = getAvatarPoints(&fuad);

    updateNoActiveEvoranPenalty(&fuad);
    assert(
        getAvatarPoints(&fuad) ==
        avatarPointsBeforePenalty - NO_ACTIVE_EVORAN_AVATAR_DAMAGE
    );
    assert(fuad.noActiveEvoranPenaltyApplied);

    // Calling the function again does not apply the penalty twice.
    updateNoActiveEvoranPenalty(&fuad);
    assert(
        getAvatarPoints(&fuad) ==
        avatarPointsBeforePenalty - NO_ACTIVE_EVORAN_AVATAR_DAMAGE
    );

    // Passing Origin Gate later uses this function to revive defeated Evorans.
    reviveDefeatedEvorans(&fuad);

    assert(getCurrentHp(&fuad.ownedEvorans[0]) == 55);
    assert(getCurrentHp(&fuad.ownedEvorans[1]) == 45);
    assert(hasActiveEvorans(&fuad));
    assert(!fuad.noActiveEvoranPenaltyApplied);

    // Player functions safely handle a null pointer.
    assert(getPlayerId(nullptr) == -1);
    assert(getAvatarName(nullptr).empty());
    assert(getAvatarPoints(nullptr) == 0);
    assert(getEvolutionGems(nullptr) == 0);
    assert(getCurrentPosition(nullptr) == -1);
    assert(getOwnedEvorans(nullptr).empty());
    assert(!hasOwnedEvorans(nullptr));
    assert(!hasActiveEvorans(nullptr));
    assert(getStrongestEvoran(nullptr) == nullptr);
    assert(isAvatarDefeated(nullptr));
    assert(!isAlive(nullptr));
    assert(!spendEvolutionGems(nullptr, 1));

    
    return 0;
}
