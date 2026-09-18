#include <cassert>

#include "Systems/EvolutionSystem.h"

using namespace EvoSphere;

int main()
{
    Player fuad;
    initializePlayer(&fuad, 0, "Fuad");

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

    addEvoran(&fuad, leafari);

    // An avatar cannot evolve an Evoran without 3 Evolution Gems.
    assert(getEvolutionGems(&fuad) == 0);
    assert(!canEvolve(fuad, fuad.ownedEvorans[0]));
    assert(!evolveSelectedEvoran(fuad, 0));

        // Three Evolution Gems allow one owned Evoran to evolve.
    addEvolutionGems(&fuad, EVOLUTION_GEM_COST);

    assert(getEvolutionGems(&fuad) == EVOLUTION_GEM_COST);
    assert(canEvolve(fuad, fuad.ownedEvorans[0]));
    assert(evolveSelectedEvoran(fuad, 0));

    // Evolution changes the Evoran's form, HP, and damage.
    assert(fuad.ownedEvorans[0].isEvolved);
    assert(getDisplayName(&fuad.ownedEvorans[0]) == "Floravyn");
    assert(getMaxHp(&fuad.ownedEvorans[0]) == 145);
    assert(getCurrentHp(&fuad.ownedEvorans[0]) == 145);
    assert(getDamage(&fuad.ownedEvorans[0]) == 30);

    // The three gems are spent after successful evolution.
    assert(getEvolutionGems(&fuad) == 0);

        // An Evoran cannot evolve a second time, even when the avatar has enough gems.
    addEvolutionGems(&fuad, EVOLUTION_GEM_COST);

    const int gemsBeforeSecondEvolutionAttempt =
        getEvolutionGems(&fuad);

    assert(!canEvolve(fuad, fuad.ownedEvorans[0]));
    assert(!evolveSelectedEvoran(fuad, 0));

    assert(
        getEvolutionGems(&fuad) ==
        gemsBeforeSecondEvolutionAttempt

    );

    // Invalid Evoran indexes cannot be evolved.
    assert(!evolveSelectedEvoran(fuad, -1));
    assert(!evolveSelectedEvoran(fuad, 1));

        // A defeated avatar cannot evolve an otherwise eligible Evoran.
    Evoran aquillo;
    initializeEvoran(
        &aquillo,
        "Aquillo",
        "Aquarion",
        ElementType::Water,
        EvoranCategory::Starter,
        120,
        17,
        155,
        28
    );

    addEvoran(&fuad, aquillo);

    takeAvatarDamage(&fuad, MAX_AVATAR_POINTS);

    assert(isAvatarDefeated(&fuad));
    assert(!canEvolve(fuad, fuad.ownedEvorans[1]));
    assert(!evolveSelectedEvoran(fuad, 1));

    // Failed evolution does not spend the avatar's gems.
    assert(getEvolutionGems(&fuad) == gemsBeforeSecondEvolutionAttempt);

        return 0;
}