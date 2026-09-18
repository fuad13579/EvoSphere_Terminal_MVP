#include "data/EvoranDatabase.hpp"

namespace EvoSphere
{

    // makeEvoran creates and initializes a normal Evoran for the starter and wild databases.
    static Evoran makeEvoran(
        const char* name,
        const char* evolvedName,
        ElementType elementType,
        EvoranCategory category,
        int maxHp,
        int damage,
        int evolvedMaxHp,
        int evolvedDamage
    )
    {
        Evoran evoran;// Create an Evoran, in the file Evoran.cpp//

        initializeEvoran(&evoran, name, evolvedName, elementType, category, maxHp, damage, evolvedMaxHp, evolvedDamage);

        return evoran;
    }

    static Guardian makeGuardian(
        const char* name,
        const char* title,
        ElementType elementType,
        const char* specialPower,
        const std::array<std::string, 3>& blessings,
        const std::array<std::string, 3>& curses
    )
    {
        Guardian guardian;

        initializeGuardian( &guardian, name, title, elementType, specialPower, blessings, curses);//Gurdian.cpp//

        return guardian;
    }

    std::vector<Evoran> createStarterEvorans()
    {
        return {
            makeEvoran("Cindroki", "Cindrava", ElementType::Fire,EvoranCategory::Starter, 95, 24, 125, 36),
            makeEvoran("Leafari", "Floravyn", ElementType::Nature,EvoranCategory::Starter, 110, 19, 145, 30),
            makeEvoran("Aquillo", "Aquarion", ElementType::Water,EvoranCategory::Starter, 120, 17, 155, 28),
            makeEvoran("Voltrik", "Voltrion", ElementType::Electric,EvoranCategory::Starter, 90, 26, 120, 38)
        };
    }//

    std::vector<Evoran> createWildEvorans()
    {
        return {
            makeEvoran("Mossari", "Mossarion", ElementType::Nature,EvoranCategory::Wild, 115, 16, 150, 26),
            makeEvoran("Thorniva", "Thornivine", ElementType::Nature,EvoranCategory::Wild, 100, 21, 135, 32),
            makeEvoran("Florayn", "Floralith", ElementType::Nature,EvoranCategory::Wild, 105, 19, 140, 30),
            makeEvoran("Pebloru", "Peblorion", ElementType::Rock,EvoranCategory::Wild, 125, 15, 165, 25),
            makeEvoran("Cragorn", "Cragorak", ElementType::Rock,EvoranCategory::Wild, 135, 18, 175, 29),
            makeEvoran("Basaldrum", "Basaldrake", ElementType::Rock,EvoranCategory::Wild, 150, 16, 190, 28),
            makeEvoran("Sparqit", "Sparqion", ElementType::Electric,EvoranCategory::Wild, 85, 25, 115, 37),
            makeEvoran("Ionixu", "Ionivolt", ElementType::Electric,EvoranCategory::Wild, 95, 27, 125, 40),
            makeEvoran("Thundravo", "Thundravox", ElementType::Electric,EvoranCategory::Wild, 105, 30, 140, 44),
            makeEvoran("Emberu", "Emberion", ElementType::Fire,EvoranCategory::Wild, 90, 24, 120, 36),
            makeEvoran("Flarexon", "Flarexar", ElementType::Fire,EvoranCategory::Wild, 100, 28, 130, 42),
            makeEvoran("Pyroclast", "Pyroclaxon", ElementType::Fire,EvoranCategory::Wild, 110, 31, 145, 46),
            makeEvoran("Ripplin", "Ripplora", ElementType::Water,EvoranCategory::Wild, 105, 19, 140, 30),
            makeEvoran("Mistora", "Mistovyn", ElementType::Water,EvoranCategory::Wild, 115, 18, 150, 29),
            makeEvoran("Tidalux", "Tidalorian", ElementType::Water,EvoranCategory::Wild, 130, 22, 170, 34),
            makeEvoran("Galevi", "Galevyr", ElementType::Air,EvoranCategory::Wild, 90, 23, 120, 35),
            makeEvoran("Driftail", "Driftalon", ElementType::Air,EvoranCategory::Wild, 100, 22, 135, 34),
            makeEvoran("Zephyrox", "Zephyron", ElementType::Air,EvoranCategory::Wild, 105, 27, 140, 41),
            makeEvoran("Duskleaf", "Duskthorn", ElementType::Dark,EvoranCategory::Wild, 100, 24, 135, 36),
            makeEvoran("Umbraxo", "Umbraxor", ElementType::Dark,EvoranCategory::Wild, 95, 30, 125, 44),
            makeEvoran("Voidmar", "Voidmare", ElementType::Dark,EvoranCategory::Wild, 110, 33, 145, 49),
            makeEvoran("Auramind", "Auramage", ElementType::Mystic,EvoranCategory::Wild, 105, 26, 140, 39),
            makeEvoran("Runelith", "Runelorian", ElementType::Mystic,EvoranCategory::Wild, 125, 24, 165, 37)
        };
    }

    std::vector<Guardian> createGuardians()
    {
        return {
            makeGuardian(
                "Solvyrion",
                "Guardian of Radiance and Preservation",
                ElementType::Mystic,
                "Radiant Aegis",
                {"Heal 20 Avatar Points", "Gain 2 Evolution Gems", "Heal 10 Avatar Points and gain 1 Evolution Gem"},
                {"", "", ""}
            ),
            makeGuardian(
                "Noctharax",
                "Guardian of Ruin and Corruption",
                ElementType::Dark,
                "Abyssal Brand",
                {"", "", ""},
                {"Lose 35 Avatar Points", "Lose 1 Evolution Gem", "Lose 15 Avatar Points"}
            ),
            makeGuardian(
                "Aequorion",
                "Guardian of Balance and Fate",
                ElementType::Mystic,
                "Equinox Decree",
                {"Balance: gain 1 Evolution Gem and heal 10 Avatar Points", "Fate success: gain 2 Evolution Gems and heal 25 Avatar Points", ""},
                {"Fate failure: lose 25 Avatar Points", "", ""}
            )
        };
    }

    // findEvoranByName searches for an Evoran by name in the provided vector of Evorans.
    bool findEvoranByName(
        const std::vector<Evoran>& evorans,
        const std::string& name,
        Evoran* result
    )
    {
        for (const Evoran& evoran : evorans)
        {
            if (evoran.name == name)
            {
                if (result != nullptr)
                {
                    *result = evoran;
                }

                return true;
            }
        }

        return false;
    }
}
