#include <cassert> // Uses assert to stop the test when a condition is false.

#include "Core/Board.h" // Uses the Board functions being tested.
#include "Core/Game.h" // Uses special-tile landing and Origin Gate reward logic.
#include "Systems/BattleSystem.h" // Uses the territory defense-bonus function.
#include "Systems/MovementSystem.h" // Uses Origin Gate revival logic.

using namespace EvoSphere; // Uses the EvoSphere namespace to avoid prefixing every function with EvoSphere::.
int main() // Runs the Board logic checks.
{
    Tile origin = createTile(0, TileType::OriginGate, ElementType::None, "", "", false); // Creates an Origin Gate tile.
    Tile wild = createTile(1, TileType::WildEvoran, ElementType::Nature, "Nature", "Mossari", true); // Creates a Wild Evoran tile.
    Tile guardian = createTile(10, TileType::Guardian, ElementType::Mystic, "Guardian", "Solvyrion", false); // Creates a Guardian tile.
    Tile teleport = createTile(5, TileType::Teleport, ElementType::None, "", "", false); // Creates a Teleport tile.
    assert(getIndex(&origin) == 0 && getName(&origin) == "Origin Gate"); // Checks Origin Gate creation and getters.
    assert(getTileType(&wild) == TileType::WildEvoran && getElementType(&wild) == ElementType::Nature); // Checks Wild Evoran data.
    assert(getLinkedEvoranName(&guardian) == "Solvyrion" && getTileType(&teleport) == TileType::Teleport); // Checks Guardian and Teleport creation.
    assert(setOwnerId(&wild, 1) && isOwned(&wild) && isOwnedBy(&wild, 1) && isOwnedByOpponent(&wild, 0)); // Checks Tile ownership functions.
    assert(setLinkedEvoranName(&wild, "Florayn") && getLinkedEvoranName(&wild) == "Florayn" && getTerritoryName(&wild) == "Nature"); // Checks linked-name and territory functions.

    Board board; // Creates one board for the test.
    initializeBoard(&board); // Loads the documented 40-tile layout.

    assert(isBoardValid(&board)); // Confirms every tile index and type count is correct.
    assert(getBoardSize(&board) == BOARD_SIZE); // Confirms that the Board stores exactly 40 tiles.
    assert(getTile(&board, 0)->tileType == TileType::OriginGate); // Confirms tile zero is Origin Gate.
    assert(getTile(&board, 1)->tileType == TileType::WildEvoran); // Confirms the first normal tile is wild.
    assert(getTile(&board, -1) == nullptr); // Rejects a negative index safely.
    assert(getTileConst(&board, BOARD_SIZE) == nullptr); // Rejects an index after tile 39 safely.
    assert(getTeleportTileIndexes(&board).size() == TELEPORT_TILE_COUNT); // Confirms all four Teleport Terminal positions are stored.
    assert(getEvoranOnTile(&board, 1) != nullptr && getEvoranOnTile(&board, 1)->name == "Mossari"); // Confirms Wild Evoran data is connected to its tile.

    assert(setTileOwner(&board, 1, 0)); // Lets player zero own a wild Evoran tile.
    assert(isOwnedBy(getTileConst(&board, 1), 0)); // Confirms that ownership was stored.
    assert(!setTileOwner(&board, 0, 0)); // Prevents players from owning Origin Gate.
    assert(setTileOwner(&board, 3, 0) && setTileOwner(&board, 4, 0)); // Gives player zero every Nature territory tile.
    assert(doesPlayerOwnTerritory(&board, 0, "Nature")); // Confirms complete Nature territory ownership.
    assert(getTerritoryTiles(&board, "Nature").size() == 3); // Confirms all Nature territory tile indexes are returned.
    assert(getTerritoryDefenseBonus(board, *getTile(&board, 1), 0) == TERRITORY_DEFENSE_DAMAGE_BONUS); // Confirms a complete territory gives the defender +5 damage.
    assert(getTerritoryDefenseBonus(board, *getTile(&board, 1), 1) == 0); // Confirms other players do not receive the bonus.

    Player territoryOwner; // Creates the player who owns the Nature territory.
    Player landingPlayer; // Creates the player landing on that territory.
    initializePlayer(&territoryOwner, 0, "Owner"); // Gives the defender the correct player ID.
    initializePlayer(&landingPlayer, 1, "Visitor"); // Gives the attacker a different player ID.
    Evoran attacker; // Creates an Evoran for the landing player.
    Evoran defender; // Creates an Evoran for the territory owner.
    initializeEvoran(&attacker, "Attacker", "", ElementType::Fire, EvoranCategory::Wild, 100, 10, 100, 10); // Creates a 100-HP attacker.
    initializeEvoran(&defender, "Defender", "", ElementType::Nature, EvoranCategory::Wild, 100, 10, 100, 10); // Creates a 100-HP defender.
    
    runOpponentOwnedTileBattle(landingPlayer, attacker, territoryOwner, defender, board, *getTile(&board, 1)); // Runs a battle on the completed Nature territory.
    assert(attacker.currentHp == 0 && defender.currentHp == 30); // Confirms battle continues until defeat and the defender's +5 territory bonus affects every counterattack.

    Evoran updatedEvoran = *getEvoranOnTile(&board, 1); // Copies the Wild Evoran before updating it.
    updatedEvoran.currentHp = 1; // Changes its battle state for the update test.
    assert(updateEvoranOnTile(&board, 1, updatedEvoran)); // Updates the Wild Evoran through the Board API.
    assert(getEvoranOnTile(&board, 1)->currentHp == 1); // Confirms the updated battle state was stored.

    Board revivalBoard; // Uses a fresh board to test Origin Gate revival and tile synchronization.
    initializeBoard(&revivalBoard);
    Player revivalOwner;
    initializePlayer(&revivalOwner, 2, "Revival Owner");
    Evoran defeatedDefender = *getEvoranOnTile(&revivalBoard, 1);
    setOwnerId(&defeatedDefender, revivalOwner.playerId);
    takeDamage(&defeatedDefender, getMaxHp(&defeatedDefender));
    addEvoran(&revivalOwner, defeatedDefender);
    assert(setTileOwner(&revivalBoard, 1, revivalOwner.playerId));
    applyOriginGateReward(revivalOwner, revivalBoard);
    const int expectedRevivalHp = getMaxHp(&revivalOwner.ownedEvorans[0]) / 2;
    assert(getCurrentHp(&revivalOwner.ownedEvorans[0]) == expectedRevivalHp); // Confirms every defeated owned Evoran revives at 50% HP.
    assert(getEvoranOnTile(&revivalBoard, 1)->currentHp == expectedRevivalHp); // Confirms the owned tile displays the revived defender HP.

    Player players[2]; // Creates two players for the special-tile test.
    initializePlayer(&players[0], 0, "Player 1"); // Initializes the first player.
    initializePlayer(&players[1], 1, "Player 2"); // Initializes the second player.
    GameState game; // Creates one complete game state.
    initializeGameState(&game, players, 2); // Creates a board and connects the players.
    movePlayerTo(&players[0], 12); // Moves player zero onto Gemstone Mine.
    for (int attempt = 1; attempt < SPECIAL_TILE_ATTUNEMENT_REQUIRED; ++attempt)
    {
        assert(resolvePlayerLanding(&game, 0) == LandingResult::SpecialTileAttuned); // Confirms the first four visits add attunement instead of immediate ownership.
    }
    assert(resolvePlayerLanding(&game, 0) == LandingResult::SpecialTileClaimed); // Confirms an unowned special tile is claimed.
    assert(getOwnerId(getTileConst(&game.board, 12)) == 0); // Confirms the new owner is stored.
    assert(resolvePlayerLanding(&game, 0) == LandingResult::OwnSpecialTile); // Confirms the owner can land on their claimed special tile.
    assert(players[0].evolutionGems == 0); // Gemstone Mine rewards occur on opponent landings and at Origin Gate.
    movePlayerTo(&players[1], 12); // Moves player one onto player zero's special tile.
    assert(resolvePlayerLanding(&game, 1) == LandingResult::OpponentSpecialTile); // Confirms an opponent can trigger the owner's reward.
    assert(players[0].evolutionGems == 1); // Confirms the owner gained the opponent-landing reward.
    assert(setTileOwner(&game.board, 27, 0) && setTileOwner(&game.board, 38, 0)); // Gives player zero the other two special tiles.
    assert(applySpecialTileOriginGateRewards(&game, 0) == 1); // Confirms the owned Gemstone Mine grants one Origin Gate gem.
    assert(players[0].evolutionGems == 2); // Confirms the Gemstone Mine Origin Gate reward was added.

    return 0; // Reports success when every assertion passes.
}
