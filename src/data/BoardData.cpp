#include "data/BoardData.hpp" // Uses the fixed board-data declarations.

namespace
{
    Tile makeTile(int index, EvoSphere::TileType tileType, EvoSphere::ElementType elementType, const char* territoryName, const char* linkedEvoranName, bool ownable) // Creates one data tile with all required Tile fields.
    {
        return createTile(index, tileType, elementType, territoryName, linkedEvoranName, ownable); // Reuses the procedural Tile factory.
    }
}

namespace EvoSphere
{
    std::array<Tile, BOARD_SIZE> createBoardTiles() // Creates the fixed 40-tile EvoSphere layout.
    {
        return {
            makeTile(0, TileType::OriginGate, ElementType::None, "", "", false),
            makeTile(1, TileType::WildEvoran, ElementType::Nature, "Nature", "Mossari", true),
            makeTile(2, TileType::BlessingShrine, ElementType::None, "", "", false),
            makeTile(3, TileType::WildEvoran, ElementType::Nature, "Nature", "Florayn", true),
            makeTile(4, TileType::WildEvoran, ElementType::Nature, "Nature", "Thorniva", true),
            makeTile(5, TileType::Teleport, ElementType::None, "", "", false),
            makeTile(6, TileType::WildEvoran, ElementType::Rock, "Rock", "Basaldrum", true),
            makeTile(7, TileType::ChaosRift, ElementType::None, "", "", false),
            makeTile(8, TileType::WildEvoran, ElementType::Electric, "Electric", "Sparqit", true),
            makeTile(9, TileType::WildEvoran, ElementType::Electric, "Electric", "Ionixu", true),
            makeTile(10, TileType::Guardian, ElementType::Mystic, "Guardian", "Solvyrion", false),
            makeTile(11, TileType::WildEvoran, ElementType::Electric, "Electric", "Thundravo", true),
            makeTile(12, TileType::SpecialOwnable, ElementType::None, "Relic", "Gemstone Mine", true),
            makeTile(13, TileType::WildEvoran, ElementType::Fire, "Fire", "Flarexon", true),
            makeTile(14, TileType::WildEvoran, ElementType::Fire, "Fire", "Pyroclast", true),
            makeTile(15, TileType::Teleport, ElementType::None, "", "", false),
            makeTile(16, TileType::WildEvoran, ElementType::Water, "Water", "Ripplin", true),
            makeTile(17, TileType::BlessingShrine, ElementType::None, "", "", false),
            makeTile(18, TileType::WildEvoran, ElementType::Water, "Water", "Tidalux", true),
            makeTile(19, TileType::WildEvoran, ElementType::Water, "Water", "Mistora", true),
            makeTile(20, TileType::Guardian, ElementType::Mystic, "Guardian", "Aequorion", false),
            makeTile(21, TileType::WildEvoran, ElementType::Air, "Air", "Driftail", true),
            makeTile(22, TileType::ChaosRift, ElementType::None, "", "", false),
            makeTile(23, TileType::WildEvoran, ElementType::Air, "Air", "Zephyrox", true),
            makeTile(24, TileType::WildEvoran, ElementType::Dark, "Dark", "Duskleaf", true),
            makeTile(25, TileType::Teleport, ElementType::None, "", "", false),
            makeTile(26, TileType::WildEvoran, ElementType::Dark, "Dark", "Voidmar", true),
            makeTile(27, TileType::SpecialOwnable, ElementType::None, "Relic", "Orb Forge", true),
            makeTile(28, TileType::WildEvoran, ElementType::Mystic, "Mystic", "Auramind", true),
            makeTile(29, TileType::WildEvoran, ElementType::Mystic, "Mystic", "Runelith", true),
            makeTile(30, TileType::Guardian, ElementType::Dark, "Guardian", "Noctharax", false),
            makeTile(31, TileType::WildEvoran, ElementType::Dark, "Dark", "Umbraxo", true),
            makeTile(32, TileType::BlessingShrine, ElementType::None, "", "", false),
            makeTile(33, TileType::WildEvoran, ElementType::Rock, "Rock", "Pebloru", true),
            makeTile(34, TileType::WildEvoran, ElementType::Rock, "Rock", "Cragorn", true),
            makeTile(35, TileType::Teleport, ElementType::None, "", "", false),
            makeTile(36, TileType::ChaosRift, ElementType::None, "", "", false),
            makeTile(37, TileType::WildEvoran, ElementType::Fire, "Fire", "Emberu", true),
            makeTile(38, TileType::SpecialOwnable, ElementType::None, "Relic", "Ancient Relic Shrine", true),
            makeTile(39, TileType::WildEvoran, ElementType::Air, "Air", "Galevi", true)
        };
    }

    const std::array<int, TELEPORT_TILE_COUNT>& getTeleportTerminalPositions() // Returns the fixed Teleport Terminal indexes.
    {
        static const std::array<int, TELEPORT_TILE_COUNT> terminals{5, 15, 25, 35}; // Stores the four terminal positions.
        return terminals; // Returns the shared read-only terminal list.
    }
}
