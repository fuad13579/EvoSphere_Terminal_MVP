#pragma once // Prevents multiple inclusions of this header file in a single compilation unit.

#include <string>

#include "Utils/Constants.h"

namespace EvoSphere
{
    struct Evoran
    {
        std::string name;
        std::string evolvedName;

        ElementType elementType = ElementType::None;
        EvoranCategory category = EvoranCategory::Wild;

        int maxHp = 0;
        int currentHp = 0;
        int damage = 0;

        int evolvedMaxHp = 0;
        int evolvedDamage = 0;

        bool isEvolved = false;
        int ownerId = -1;
    };

    void initializeEvoran(
        Evoran* evoran,
        const std::string& name,
        const std::string& evolvedName,
        ElementType elementType,
        EvoranCategory category,
        int maxHp,
        int damage,
        int evolvedMaxHp,
        int evolvedDamage
    );// this function is used to initialize an evoran
    //we use const for the name and evolvedName because we don't want to change them
    const std::string& getEvoranName(const Evoran* evoran);
    const std::string& getEvolvedName(const Evoran* evoran);

    ElementType getElementType(const Evoran* evoran);
    EvoranCategory getEvoranCategory(const Evoran* evoran);

    int getCurrentHp(const Evoran* evoran);
    int getMaxHp(const Evoran* evoran);
    int getDamage(const Evoran* evoran);
    int getOwnerId(const Evoran* evoran);

    void setOwnerId(Evoran* evoran, int ownerId);

    void takeDamage(Evoran* evoran, int amount);
    void heal(Evoran* evoran, int amount);

    bool isEvoranDefeated(const Evoran* evoran);
    bool canEvolve(const Evoran* evoran);
    bool evolve(Evoran* evoran);
    void resetHp(Evoran* evoran);
    const std::string& getName(const Evoran* evoran);
    const std::string& getDisplayName(const Evoran* evoran);
}
