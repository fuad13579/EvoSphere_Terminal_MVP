#pragma once //pragma is a preprocessor directive that tells the compiler to include this header file only once in a single compilation, preventing duplicate definitions and improving compilation speed.

namespace EvoSphere //namespace is a declarative region that provides a scope to the identifiers (the names of types, functions, variables, etc) inside it. Namespaces are used to organize code into logical groups and to prevent name collisions that can occur especially when your code base includes multiple libraries. 
{
    //inline means that the variable is defined in a header file and can be included in multiple translation units without violating the One Definition Rule (ODR). It allows the variable to have internal linkage, meaning each translation unit gets its own copy of the variable. This is particularly useful for constants, as it avoids multiple definitions while still allowing the constant to be used across different source files.
    //constexpr means that the value of the variable is a constant expression, which is a compile-time constant. This means that the value of the variable can be evaluated at compile time, rather than at runtime. This can improve performance by allowing the compiler to optimize the code more effectively.

    inline constexpr int BOARD_SIZE = 40;
    inline constexpr int ORIGIN_GATE_INDEX = 0;
    inline constexpr int STARTING_POSITION = ORIGIN_GATE_INDEX;

    inline constexpr int WILD_EVORAN_TILE_COUNT = 23;
    inline constexpr int GUARDIAN_TILE_COUNT = 3;
    inline constexpr int TELEPORT_TILE_COUNT = 4;
    inline constexpr int BLESSING_SHRINE_TILE_COUNT = 3;
    inline constexpr int CHAOS_RIFT_TILE_COUNT = 3;
    inline constexpr int SPECIAL_OWNABLE_TILE_COUNT = 3;
    inline constexpr int SPECIAL_TILE_ATTUNEMENT_REQUIRED = 5;
    inline constexpr int GEMSTONE_MINE_INDEX = 12;
    inline constexpr int ORB_FORGE_INDEX = 27;
    inline constexpr int ANCIENT_RELIC_SHRINE_INDEX = 38;

    // Players
    inline constexpr int MIN_PLAYERS = 2;
    inline constexpr int MAX_PLAYERS = 3;

    inline constexpr int STARTING_AVATAR_POINTS = 100;
    inline constexpr int MAX_AVATAR_POINTS = 120;
    inline constexpr int STARTING_EVOLUTION_GEMS = 0;

    // Energy Orbs
    inline constexpr int ORB_MIN_VALUE = 1;
    inline constexpr int ORB_MAX_VALUE = 6;
    inline constexpr int NUMBER_OF_ORBS_PER_TURN = 2;

    // Evolution
    inline constexpr int EVOLUTION_GEM_COST = 3;
    inline constexpr int EVOLUTION_GEM_REWARD = 1;
    inline constexpr int ORIGIN_GATE_HEAL_AMOUNT = 10;
    inline constexpr int TERRITORY_DEFENSE_DAMAGE_BONUS = 5;

    // Capture
    inline constexpr int CAPTURE_HP_THRESHOLD_PERCENT = 30;
    inline constexpr int NO_ACTIVE_EVORAN_AVATAR_DAMAGE = 20;
    inline constexpr int OPPONENT_TILE_BATTLE_LOSS_AVATAR_DAMAGE = 5;

    // Events
    inline constexpr int BLESSING_GEM_REWARD = 1;
    inline constexpr int CHAOS_AVATAR_DAMAGE = 15;
    inline constexpr int BLESSING_DAMAGE_BOOST_PERCENT = 20;


    //enum class is a scoped enumeration that provides a way to define a set of named integral constants. The "class" keyword in enum class indicates that the enumerators are scoped within the enum, preventing them from being implicitly converted to integers and avoiding name clashes with other identifiers in the same scope. This enhances type safety and code clarity.
    
    enum class ElementType

    {
        None,
        Fire,
        Water,
        Nature,
        Electric,
        Rock,
        Air,
        Dark,
        Mystic
    };

    enum class TileType
    {
        OriginGate,
        WildEvoran,
        Guardian,
        Teleport,
        BlessingShrine,
        ChaosRift,
        SpecialOwnable
    };

    enum class EvoranCategory
    {
        None,
        Starter,
        Wild,
        Guardian
    };

    enum class EventType
    {
        Blessing,
        Chaos
    };

    enum class GamePhase
    {
        Setup,
        PlayerTurn,
        Battle,
        Capture,
        Event,
        GameOver
    };
}
