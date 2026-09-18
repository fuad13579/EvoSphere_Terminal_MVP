#include "Core/Game.h"

#include "Systems/BattleSystem.h"
#include "Systems/CaptureSystem.h"

namespace
{
    bool ownsSpecialTile(const GameState* game, int playerId, int tileIndex)
    {
        const Tile* tile = nullptr;
        if (game != nullptr)
        {
            tile = getTileConst(&game->board, tileIndex);
        }
        return tile != nullptr && isOwnedBy(tile, playerId);
    }

    EvoSphere::Player* findPlayerById(GameState* game, int playerId)
    {
        if (game == nullptr || game->players == nullptr)
        {
            return nullptr;
        }

        for (int index = 0; index < game->playerCount; ++index)
        {
            if (game->players[index].playerId == playerId)
            {
                return &game->players[index];
            }
        }

        return nullptr;
    }
}// this function searches for a player in the game state by their unique player ID. It takes a pointer to the GameState and an integer representing the player ID as parameters. The function first checks if the game or its players array is null, returning nullptr if so. It then iterates through the players array, comparing each player's ID with the provided playerId. If a match is found, it returns a pointer to that player. If no match is found after checking all players, it returns nullptr, indicating that the player was not found in the game state.    

void initializeGameState(GameState* game, EvoSphere::Player players[], int playerCount)
{
    if (game == nullptr)
    {
        return;
    }

    // The game points to the player array owned by the caller.
    game->players = players;//players=players means that the game struct's players pointer is set to point to the same memory location as the players array passed in as an argument. This allows the game struct to access and manipulate the player data directly.
    if (playerCount < 0)
    {
        game->playerCount = 0;
    }
    else
    {
        game->playerCount = playerCount;
    }
    initializeBoard(&game->board);
    game->gameOver = false;
    game->winnerIndex = -1;
    initializeTurnManager(&game->turnManager);
}

bool canPlayerTakeTurn(const EvoSphere::Player* player)
{
    return player != nullptr && !EvoSphere::isAvatarDefeated(player);
}

int countActivePlayers(const EvoSphere::Player players[], int playerCount)
{
    if (players == nullptr || playerCount <= 0)
    {
        return 0;
    }

    int activeCount = 0;
    for (int i = 0; i < playerCount; ++i)
    {
        if (canPlayerTakeTurn(&players[i]))
        {
            ++activeCount;
        }
    }

    return activeCount;
}

int findWinnerIndex(const EvoSphere::Player players[], int playerCount)
{
    if (players == nullptr || playerCount <= 0)
    {
        return -1;
    }

    int winnerIndex = -1;
    for (int i = 0; i < playerCount; ++i)
    {
        if (!canPlayerTakeTurn(&players[i]))
        {
            continue;
        }

        // If a second active player is found, there is no winner yet.
        if (winnerIndex != -1)
        {
            return -1;
        }

        winnerIndex = i;
    }

    return winnerIndex;
}

bool refreshGameState(GameState* game)
{
    if (game == nullptr || game->players == nullptr || game->playerCount <= 0)
    {
        return false;
    }

    const int activeCount = countActivePlayers(game->players, game->playerCount);//const is used to indicate that the value of activeCount will not be modified after its initialization//
    
    if (activeCount <= 1)
    {
        game->gameOver = true;
        game->winnerIndex = findWinnerIndex(game->players, game->playerCount);

        return true;
    }

    game->gameOver = false;
    game->winnerIndex = -1;
    return true;//Indicates that game state was updated successfully and the game is still ongoing.
}

bool updateGameState(GameState* game)
{
    if (!refreshGameState(game) || game->gameOver)
    {
        return game != nullptr && game->gameOver;
    }

    for (int attempts = 0; attempts < game->playerCount; ++attempts)
    {
        nextTurn(&game->turnManager, game->playerCount);

        if (canPlayerTakeTurn(&game->players[getCurrentPlayerIndex(&game->turnManager)]))
        {
            break;
        }
    }

    return true;
}

bool isOpponentOwnedEvoranTile(const Tile& tile, const EvoSphere::Player& player)
{
    return tile.tileType == EvoSphere::TileType::WildEvoran &&
        tile.ownerId != -1 &&
        tile.ownerId != player.playerId;
}

EvoSphere::Evoran* getDefendingEvoran(GameState* game, const Tile& tile)
{
    EvoSphere::Player* owner = findPlayerById(game, tile.ownerId);

    if (owner == nullptr)
    {
        return nullptr;
    }

    for (EvoSphere::Evoran& evoran : owner->ownedEvorans)
    {
        if (EvoSphere::getEvoranName(&evoran) == tile.linkedEvoranName)
        {
            return &evoran;
        }
    }

    return nullptr;
}

LandingResult resolvePlayerLanding(GameState* game, int playerIndex, int selectedEvoranIndex)
{
    if (game == nullptr || game->players == nullptr || playerIndex < 0 || playerIndex >= game->playerCount)
    {
        return LandingResult::Invalid;
    }

    EvoSphere::Player& currentPlayer = game->players[playerIndex];
    Tile* tile = getTile(&game->board, currentPlayer.currentPosition);

    if (tile == nullptr || EvoSphere::isAvatarDefeated(&currentPlayer))
    {
        return LandingResult::Invalid;
    }

    if (tile->tileType == EvoSphere::TileType::SpecialOwnable)
    {
        if (!isOwned(tile))
        {
            const int playerId = currentPlayer.playerId;
            if (playerId < 0 || playerId >= EvoSphere::MAX_PLAYERS)
            {
                return LandingResult::Invalid;
            }

            int& progress = tile->attunementProgress[playerId];
            if (progress < tile->requiredAttunement)
            {
                ++progress;
            }

            if (progress >= tile->requiredAttunement)
            {
                setTileOwner(&game->board, tile->index, playerId);
                return LandingResult::SpecialTileClaimed;
            }

            return LandingResult::SpecialTileAttuned;
        }

        if (isOwnedBy(tile, currentPlayer.playerId))
        {
            if (tile->index == EvoSphere::ANCIENT_RELIC_SHRINE_INDEX)
            {
                currentPlayer.nextWildBattleDamageBonus = 5;
            }
            return LandingResult::OwnSpecialTile;
        }

        EvoSphere::Player* owner = findPlayerById(game, tile->ownerId);
        if (tile->index == EvoSphere::GEMSTONE_MINE_INDEX && owner != nullptr)
        {
            EvoSphere::addEvolutionGems(owner, EvoSphere::EVOLUTION_GEM_REWARD);
        }
        else if (tile->index == EvoSphere::ORB_FORGE_INDEX)
        {
            EvoSphere::movePlayerTo(&currentPlayer, currentPlayer.currentPosition - 2);
        }
        else if (tile->index == EvoSphere::ANCIENT_RELIC_SHRINE_INDEX &&
            currentPlayer.evolutionGems > 0)
        {
            EvoSphere::spendEvolutionGems(&currentPlayer, EvoSphere::EVOLUTION_GEM_REWARD);
        }

        return LandingResult::OpponentSpecialTile;
    }

    if (tile->tileType != EvoSphere::TileType::WildEvoran)
    {
        return LandingResult::NoEffect;
    }

    if (tile->ownerId == -1)
    {
        if (selectedEvoranIndex >= 0)
        {
            const bool captured = EvoSphere::handleWildEvoranEncounter(
                currentPlayer,
                game->board,
                tile->index,
                selectedEvoranIndex
            );
            refreshGameState(game);
            if (captured)
            {
                return LandingResult::WildEvoranCaptured;
            }

            return LandingResult::WildEvoranBattleFailed;
        }

        return LandingResult::WildEvoranEncounter;
    }

    if (tile->ownerId == currentPlayer.playerId)
    {
        return LandingResult::OwnEvoranTile;
    }

    EvoSphere::Player* defendingPlayer = findPlayerById(game, tile->ownerId);
    EvoSphere::Evoran* defendingEvoran = getDefendingEvoran(game, *tile);

    if (defendingPlayer == nullptr ||
        defendingEvoran == nullptr ||
        selectedEvoranIndex < 0 ||
        selectedEvoranIndex >= static_cast<int>(currentPlayer.ownedEvorans.size()))
    {
        return LandingResult::OpponentEvoranTile;
    }

    EvoSphere::Evoran& attackingEvoran = currentPlayer.ownedEvorans[selectedEvoranIndex];

    EvoSphere::runOpponentOwnedTileBattle(
        currentPlayer,
        attackingEvoran,
        *defendingPlayer,
        *defendingEvoran,
        game->board,
        *tile
    );

    // Keep the board's tile copy synchronized for board displays.
    tile->wildEvoran = *defendingEvoran;
    refreshGameState(game);
    return LandingResult::OpponentEvoranTile;
}

int applySpecialTileOriginGateRewards(GameState* game, int playerIndex)
{
    if (game == nullptr || game->players == nullptr || playerIndex < 0 || playerIndex >= game->playerCount)
    {
        return 0;
    }

    EvoSphere::Player& player = game->players[playerIndex];
    int rewardCount = 0;

    for (const Tile& tile : game->board.tiles)
    {
        if (tile.index == EvoSphere::GEMSTONE_MINE_INDEX &&
            isOwnedBy(&tile, player.playerId))
        {
            ++rewardCount;
        }
    }

    EvoSphere::addEvolutionGems(&player, rewardCount * EvoSphere::EVOLUTION_GEM_REWARD);
    return rewardCount * EvoSphere::EVOLUTION_GEM_REWARD;
}

bool useOrbForgeMovementBonus(GameState* game, int playerIndex)
{
    if (game == nullptr || game->players == nullptr ||
        playerIndex < 0 || playerIndex >= game->playerCount)
    {
        return false;
    }

    EvoSphere::Player& player = game->players[playerIndex];
    const int round = getCurrentRound(&game->turnManager);

    if (!ownsSpecialTile(game, player.playerId, EvoSphere::ORB_FORGE_INDEX) ||
        player.orbForgeBonusRound == round)
    {
        return false;
    }

    player.orbForgeBonusRound = round;
    return true;
}
