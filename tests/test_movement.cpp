#include <cassert>

#include "Systems/MovementSystem.h"

using namespace EvoSphere;

int main()
{
    Board board;
    initializeBoard(&board);

    Player fuad;
    initializePlayer(&fuad, 0, "Fuad");

    // Two Energy Orbs always produce a total from 2 to 12.
    for (int attempt = 0; attempt < 46; ++attempt)
    {
        const int rollTotal = rollEnergyOrbs();

        assert(rollTotal >= 2);
        assert(rollTotal <= 12);
    }

    // Normal movement updates the avatar's board position.
    movePlayer(fuad, board, 6);

    assert(getCurrentPosition(&fuad) == 6);

        // Movement wraps around the 40-tile board after tile 39.
    movePlayerTo(&fuad, 38);

    const int gemsBeforeOriginGate = getEvolutionGems(&fuad);

    movePlayer(fuad, board, 5);

    assert(getCurrentPosition(&fuad) == 3);
    assert(
        getEvolutionGems(&fuad) ==
        gemsBeforeOriginGate + EVOLUTION_GEM_REWARD
    );
    
        // Origin Gate detection works for wrapping, landing on tile 0, and normal moves.
    assert(didPassOriginGate(38, 3, 5));
    assert(didPassOriginGate(35, 0, 5));
    assert(!didPassOriginGate(10, 12, 2));

    // Invalid movement does not change the avatar's position.
    const int positionBeforeInvalidMove = getCurrentPosition(&fuad);

    movePlayer(fuad, board, 0);
    assert(getCurrentPosition(&fuad) == positionBeforeInvalidMove);

    movePlayer(fuad, board, -3);
    assert(getCurrentPosition(&fuad) == positionBeforeInvalidMove);
    
        // Origin Gate revives defeated owned Evorans at 50% HP and updates their tile.
    Player revivalOwner;
    initializePlayer(&revivalOwner, 1, "Siam");

    Evoran defeatedMossari = *getEvoranOnTile(&board, 1);

    setOwnerId(&defeatedMossari, revivalOwner.playerId);
    takeDamage(&defeatedMossari, getMaxHp(&defeatedMossari));

    addEvoran(&revivalOwner, defeatedMossari);
    assert(setTileOwner(&board, 1, revivalOwner.playerId));

    applyOriginGateReward(revivalOwner, board);

    const int expectedRevivalHp =
        getMaxHp(&revivalOwner.ownedEvorans[0]) / 2;

    assert(
        getCurrentHp(&revivalOwner.ownedEvorans[0]) ==
        expectedRevivalHp
    );

    assert(
        getCurrentHp(getEvoranOnTile(&board, 1)) ==
        expectedRevivalHp
    );
    
    
    return 0;
}