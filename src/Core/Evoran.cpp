#include "Core/Evoran.h"

#include <algorithm>

namespace EvoSphere
{
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
    )
    {
        if (evoran == nullptr)
        {
            return;
        }

        evoran->name = name;
        evoran->evolvedName = evolvedName;
        evoran->elementType = elementType;
        evoran->category = category;

        evoran->maxHp = std::max(0, maxHp);
        evoran->currentHp = evoran->maxHp;
        evoran->damage = std::max(0, damage);

        evoran->evolvedMaxHp = std::max(0, evolvedMaxHp);
        evoran->evolvedDamage = std::max(0, evolvedDamage);

        evoran->isEvolved = false;
        evoran->ownerId = -1;
    }

    const std::string& getEvoranName(const Evoran* evoran)
    {
        static const std::string emptyName;//static is used to ensure that the emptyName variable is only created once and persists for the lifetime of the program. This avoids creating a new empty string every time the function is called, which would be inefficient. By using a static variable, we can return a reference to the same empty string whenever the evoran pointer is null, ensuring that we don't return a dangling reference to a temporary object.

        if (evoran == nullptr)
        {
            return emptyName;
        }

        return evoran->name;
    }

    const std::string& getEvolvedName(const Evoran* evoran)
    {
        static const std::string emptyName;

        if (evoran == nullptr)
        {
            return emptyName;
        }

        return evoran->evolvedName;
    }

    const std::string& getName(const Evoran* evoran)
{
    static const std::string emptyName;

    if (evoran == nullptr)
    {
        return emptyName;
    }

    return evoran->name;
}

const std::string& getDisplayName(const Evoran* evoran)
{
    static const std::string emptyName;

    if (evoran == nullptr)
    {
        return emptyName;
    }

    if (evoran->isEvolved)
    {
        return evoran->evolvedName;
    }

    return evoran->name;
}

    ElementType getElementType(const Evoran* evoran)
    {
        if (evoran == nullptr)
        {
            return ElementType::None;
        }

        return evoran->elementType;
    }

    EvoranCategory getEvoranCategory(const Evoran* evoran)
    {
        if (evoran == nullptr)
        {
            return EvoranCategory::None;
        }

        return evoran->category;
    }

    int getCurrentHp(const Evoran* evoran)
    {
        if (evoran == nullptr)
        {
            return 0;
        }

        return evoran->currentHp;
    }

    int getMaxHp(const Evoran* evoran)
    {
        if (evoran == nullptr)
        {
            return 0;
        }

        return evoran->maxHp;
    }

    int getDamage(const Evoran* evoran)
    {
        if (evoran == nullptr)
        {
            return 0;
        }

        return evoran->damage;
    }

    int getOwnerId(const Evoran* evoran)
    {
        if (evoran == nullptr)
        {
            return -1;
        }

        return evoran->ownerId;
    }

    void setOwnerId(Evoran* evoran, int ownerId)
    {
        if (evoran == nullptr)
        {
            return;
        }

        evoran->ownerId = ownerId;
    }

    void takeDamage(Evoran* evoran, int amount)
    {
        if (evoran == nullptr || amount <= 0)
        {
            return;
        }

        evoran->currentHp =
            std::max(0, evoran->currentHp - amount);
    }

    void heal(Evoran* evoran, int amount)
    {
        if (evoran == nullptr || amount <= 0)
        {
            return;
        }

        evoran->currentHp =
            std::min(evoran->maxHp,
                    evoran->currentHp + amount);
    }

    bool isEvoranDefeated(const Evoran* evoran)
    {
        return evoran == nullptr || evoran->currentHp <= 0;
    }

    bool canEvolve(const Evoran* evoran)
    {
        return evoran != nullptr &&!evoran->isEvolved &&!evoran->evolvedName.empty() &&evoran->evolvedMaxHp > 0 &&evoran->evolvedDamage > 0;
    }

    bool evolve(Evoran* evoran)
    {
        if (!canEvolve(evoran))
        {
            return false;
        }

        evoran->isEvolved = true;
        evoran->maxHp = evoran->evolvedMaxHp;
        evoran->currentHp = evoran->maxHp;
        evoran->damage = evoran->evolvedDamage;

        return true;
    }

    void resetHp(Evoran* evoran)
    {
        if (evoran == nullptr)
        {
            return;
        }

        evoran->currentHp = evoran->maxHp;
    }
}
