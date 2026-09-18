#include <cassert>// Uses assert to stop the test when a condition is false.

#include "Core/Evoran.h"

using namespace EvoSphere;

int main(){
        Evoran leafari;

    initializeEvoran(&leafari,"Leafari","Floravyn",ElementType::Nature,EvoranCategory::Starter,110,19,145,30);

    assert(getName(&leafari) == "Leafari");
    assert(getEvolvedName(&leafari) == "Floravyn");
    assert(getElementType(&leafari) == EvoSphere::ElementType::Nature);
    assert(getEvoranCategory(&leafari) == EvoSphere::EvoranCategory::Starter);

    assert(getMaxHp(&leafari) == 110);
    assert(getCurrentHp(&leafari) == 110);
    assert(getDamage(&leafari) == 19);

    assert(!isEvoranDefeated(&leafari));
    assert(!leafari.isEvolved);
    assert(getOwnerId(&leafari) == -1);

        // Damage reduces current HP.
    takeDamage(&leafari, 30);
    assert(getCurrentHp(&leafari) == 80);
    assert(!isEvoranDefeated(&leafari));// HP is not zero, so the Evoran is not defeated.

    // Healing restores HP.
    heal(&leafari, 20);
    assert(getCurrentHp(&leafari) == 100);

    // Healing cannot exceed max HP.
    heal(&leafari, 100);
    assert(getCurrentHp(&leafari) == 110);

    // Damage cannot reduce HP below zero.
    takeDamage(&leafari, 200);
    assert(getCurrentHp(&leafari) == 0);
    assert(isEvoranDefeated(&leafari));

    // The current heal() function can restore an Evoran from 0 HP.
    heal(&leafari, 25);
    assert(getCurrentHp(&leafari) == 25);
    assert(!isEvoranDefeated(&leafari));

    // Invalid damage and healing amounts do not change HP.
    takeDamage(&leafari, -10);
    assert(getCurrentHp(&leafari) == 25);

    heal(&leafari, 0);
    assert(getCurrentHp(&leafari) == 25);

        // Leafari has an evolved form, valid evolved HP, and evolved damage.
    assert(canEvolve(&leafari));

    // Evolution succeeds once.
    assert(evolve(&leafari));
    assert(leafari.isEvolved);

    // The displayed name, HP, and damage change to the evolved values.
    assert(getDisplayName(&leafari) == "Floravyn");
    assert(getMaxHp(&leafari) == 145);
    assert(getCurrentHp(&leafari) == 145);
    assert(getDamage(&leafari) == 30);

    // An Evoran cannot evolve a second time.
    assert(!canEvolve(&leafari));
    assert(!evolve(&leafari));

        // Owner ID can be assigned and read.
    setOwnerId(&leafari, 2);
    assert(getOwnerId(&leafari) == 2);

    // resetHp restores full HP for the current form.
    takeDamage(&leafari, 70);
    assert(getCurrentHp(&leafari) == 75);

    resetHp(&leafari);
    assert(getCurrentHp(&leafari) == 145);

    // Getter functions safely handle a null pointer.
    assert(getName(nullptr).empty());
    assert(getEvolvedName(nullptr).empty());
    assert(getElementType(nullptr) == ElementType::None);
    assert(getEvoranCategory(nullptr) == EvoranCategory::None);
    assert(getCurrentHp(nullptr) == 0);
    assert(getMaxHp(nullptr) == 0);
    assert(getDamage(nullptr) == 0);
    assert(getOwnerId(nullptr) == -1);
    assert(isEvoranDefeated(nullptr));
    assert(!canEvolve(nullptr));
    return 0;
}
