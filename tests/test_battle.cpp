#include <cassert>

#include "Systems/BattleSystem.h"

using namespace EvoSphere;

int main()
{
    Evoran cindroki;
    initializeEvoran(
        &cindroki,
        "Cindroki",
        "Cindrava",
        ElementType::Fire,
        EvoranCategory::Starter,
        95,
        24,
        125,
        36
    );

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

    //A living Evoran can battle.
    assert(canEvoranBattle(cindroki));
    assert(canEvoranBattle(leafari));


    // Power is current HP plus damage.
    assert(calculatePower(cindroki) == 95 + 24);
    assert(calculatePower(leafari) == 110 + 19);

    // An attack reduces the defender's HP by the attacker's damage.
    const int leafariHpBeforeAttack = getCurrentHp(&leafari);

    attack(cindroki, leafari);

    assert(
    getCurrentHp(&leafari) == leafariHpBeforeAttack - getDamage(&cindroki)
    );

        // A defeated Evoran cannot battle or deal damage.
    takeDamage(&cindroki, 200);

    assert(isEvoranDefeated(&cindroki));
    assert(!canEvoranBattle(cindroki));

    const int leafariHpBeforeDefeatedAttack = getCurrentHp(&leafari);// Leafari's HP should not change after Cindroki is defeated.

    attack(cindroki, leafari);

    assert(
        getCurrentHp(&leafari) ==
        leafariHpBeforeDefeatedAttack
    );

        // A player can win a wild battle when the wild Evoran reaches 30% HP or less.
    Player fuad;
    initializePlayer(&fuad, 0, "Fuad");

    Board board;
    initializeBoard(&board);

    Evoran selectedEvoran;
    initializeEvoran(
        &selectedEvoran,
        "TestFire",
        "TestFireEvolved",
        ElementType::Fire,
        EvoranCategory::Starter,
        100,
        80,
        120,
        100
    );


    Evoran wildEvoran;
    initializeEvoran(
        &wildEvoran,
        "TestWild",
        "TestWildEvolved",
        ElementType::Nature,
        EvoranCategory::Wild,
        100,
        10,
        150,
        20
    );


    assert(runWildBattle(fuad, selectedEvoran, wildEvoran, board));
    assert(getCurrentHp(&wildEvoran) == 20);

        // A wild battle fails when the selected Evoran is defeated first.
    Evoran weakEvoran;
    initializeEvoran(
        &weakEvoran,
        "WeakTest",
        "",
        ElementType::Nature,
        EvoranCategory::Starter,
        20,
        1,
        20,
        1
    );

    Evoran strongWildEvoran;
    initializeEvoran(
        &strongWildEvoran,
        "StrongWild",
        "",
        ElementType::Fire,
        EvoranCategory::Wild,
        100,
        50,
        100,
        50
    );

    assert(!runWildBattle(fuad, weakEvoran, strongWildEvoran, board));
    assert(isEvoranDefeated(&weakEvoran));

        // Winning an opponent-owned tile battle defeats the defender and applies
    // the Avatar Point penalty to the defending avatar.
    Player attackingAvatar;
    initializePlayer(&attackingAvatar, 0, "Fuad");

    Player defendingAvatar;
    initializePlayer(&defendingAvatar, 1, "Siam");

    Evoran attackingEvoran;
    initializeEvoran(
        &attackingEvoran,
        "StrongAttacker",
        "",
        ElementType::Fire,
        EvoranCategory::Starter,
        100,
        80,
        100,
        80
    );

    Evoran defendingEvoran;
    initializeEvoran(
        &defendingEvoran,
        "WeakDefender",
        "",
        ElementType::Nature,
        EvoranCategory::Wild,
        60,
        10,
        60,
        10
    );

    Evoran reserveEvoran;
    initializeEvoran(
        &reserveEvoran,
        "ReserveDefender",
        "",
        ElementType::Water,
        EvoranCategory::Starter,
        100,
        10,
        100,
        10
    );

    // Add them so each avatar has an active owned Evoran.
    addEvoran(&attackingAvatar, attackingEvoran);
    addEvoran(&defendingAvatar, defendingEvoran);
    addEvoran(&defendingAvatar, reserveEvoran);

    Tile defendedTile = createTile(
        1,
        TileType::WildEvoran,
        ElementType::Nature,
        "",
        "WeakDefender",
        true
    );// it is required for runOpponentOwnedTileBattle to have a tile with the defending Evoran's name linked to it, and the tile must be ownable.//

    setOwnerId(&defendedTile, defendingAvatar.playerId);// it is required for runOpponentOwnedTileBattle to have a tile with the defending Evoran's name linked to it, and the tile must be ownable.//

    const int defendingAvatarPointsBefore = getAvatarPoints(&defendingAvatar);// this is used to verify that the defending avatar's points are reduced by the correct amount after losing the battle.//

    assert(
        runOpponentOwnedTileBattle(
            attackingAvatar,
            attackingAvatar.ownedEvorans[0],
            defendingAvatar,
            defendingAvatar.ownedEvorans[0],
            board,
            defendedTile
        )
    );

    assert(isEvoranDefeated(&defendingAvatar.ownedEvorans[0]));

    assert(
        getAvatarPoints(&defendingAvatar) ==
        defendingAvatarPointsBefore -
        OPPONENT_TILE_BATTLE_LOSS_AVATAR_DAMAGE
    );

        // A battle cannot begin against an already defeated defending Evoran.
    const int attackerHpBeforeInvalidBattle =
        getCurrentHp(&attackingAvatar.ownedEvorans[0]);

    assert(
        !runOpponentOwnedTileBattle(
            attackingAvatar,
            attackingAvatar.ownedEvorans[0],
            defendingAvatar,
            defendingAvatar.ownedEvorans[0],
            board,
            defendedTile
        )
    );// the defending Evoran is already defeated, so the battle should not proceed.

    assert(
        getCurrentHp(&attackingAvatar.ownedEvorans[0]) ==
        attackerHpBeforeInvalidBattle
    );


    return 0;
}
