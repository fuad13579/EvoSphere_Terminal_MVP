#include "Console/ConsoleGame.hpp"
#include "Systems/MovementSystem.h"

#include <string>

#include "Console/ConsoleInput.hpp"
#include "Console/ConsoleRenderer.hpp"
#include "Systems/BattleSystem.h"
#include "Systems/EvolutionSystem.h"
#include "Systems/EventSystem.h"
#include "Systems/TeleportSystem.h"
#include "Core/Guardian.h"
#include "Core/Player.h"
#include "data/EvoranDatabase.hpp"

namespace
{
    const EvoSphere::Guardian* findGuardian(const std::vector<EvoSphere::Guardian>& guardians, const std::string& name)
    {
        for (const EvoSphere::Guardian& guardian : guardians)
        {
            if (guardian.name == name) return &guardian;
        }
        return nullptr;
    }

    std::string guardianMessage(EvoSphere::GuardianOutcome outcome)
    {
        using EvoSphere::GuardianOutcome;
        switch (outcome)
        {
        case GuardianOutcome::SolvyrionHealingBlessing: return "Solvyrion healed 20 Avatar Points.";
        case GuardianOutcome::SolvyrionGemBlessing: return "Solvyrion granted 2 Evolution Gems.";
        case GuardianOutcome::SolvyrionBalancedBlessing: return "Solvyrion healed 10 Avatar Points and granted 1 Evolution Gem.";
        case GuardianOutcome::NoctharaxMajorCurse: return "Noctharax removed 35 Avatar Points.";
        case GuardianOutcome::NoctharaxGemCurse: return "Noctharax removed 1 Evolution Gem.";
        case GuardianOutcome::NoctharaxMinorCurse: return "Noctharax removed 15 Avatar Points.";
        case GuardianOutcome::AequorionBalance: return "Aequorion's Balance healed 10 Avatar Points and granted 1 Evolution Gem.";
        case GuardianOutcome::AequorionFateBlessing: return "Aequorion's Fate healed 25 Avatar Points and granted 2 Evolution Gems.";
        case GuardianOutcome::AequorionFateCurse: return "Aequorion's Fate removed 25 Avatar Points.";
        default: return "The Guardian encounter could not be resolved.";
        }
    }
}

void setupGame(ConsoleGameState* consoleGame);
void createPlayers(ConsoleGameState* consoleGame, int playerCount);
void movementSystem(ConsoleGameState* consoleGame, EvoSphere::Player& currentPlayer, int playerIndex);
void evolveEvoran(EvoSphere::Player& currentPlayer);
void resolveLanding(ConsoleGameState* consoleGame, int playerIndex);
void runTurn(ConsoleGameState* consoleGame);

void runConsoleGame(ConsoleGameState* consoleGame)
{
    if (consoleGame == nullptr)
    {
        return;
    }

    GameState& gameState = consoleGame->gameState;
    std::vector<EvoSphere::Player>& players = consoleGame->players;
    bool& running = consoleGame->running;

    setupGame(consoleGame);

    while (running && !gameState.gameOver)
    {
        runTurn(consoleGame);
    }

    if (gameState.gameOver && gameState.winnerIndex >= 0 && gameState.winnerIndex < gameState.playerCount)
    {
        ConsoleRenderer::gameWinner(players[gameState.winnerIndex]);
    }
}

void setupGame(ConsoleGameState* consoleGame)
{
    GameState& gameState = consoleGame->gameState;
    std::vector<EvoSphere::Player>& players = consoleGame->players;

    ConsoleRenderer::gameTitleIntroduction();
    ConsoleRenderer::gameRules();

    const int playerCount = ConsoleInput::askPlayerCount();
    createPlayers(consoleGame, playerCount);

    initializeGameState(
        &gameState,
        players.data(),
        playerCount
    );

    ConsoleRenderer::gameMessage("Game setup is complete.");
    ConsoleInput::waitForEnter();
}

void createPlayers(ConsoleGameState* consoleGame, int playerCount)
{
    std::vector<EvoSphere::Player>& players = consoleGame->players;

    players.resize(playerCount);
    std::vector<EvoSphere::Evoran> availableStarters = EvoSphere::createStarterEvorans();

    for (int index = 0; index < playerCount; index++)
    {
        const std::string avatarName = ConsoleInput::askAvatarName(index + 1);

        EvoSphere::initializePlayer(&players[index], index, avatarName);
    }

    for (int index = 0; index < playerCount; index++)
    {
        const std::string& avatarName = players[index].avatarName;

        ConsoleRenderer::gameMessage(avatarName + ", choose your starter Evoran.");
        ConsoleRenderer::starterEvoranChoices(availableStarters);
        const int starterChoice = ConsoleInput::askMenuChoice(1, static_cast<int>(availableStarters.size()));

        EvoSphere::Evoran starter = availableStarters[starterChoice - 1];
        EvoSphere::setOwnerId(&starter, index);
        EvoSphere::addEvoran(&players[index], starter);

        ConsoleRenderer::gameMessage(
            avatarName + " chose " + EvoSphere::getEvoranName(&starter) +
            " as their starter Evoran."
        );

        availableStarters.erase(availableStarters.begin() + (starterChoice - 1));
    }
}

void movementSystem(ConsoleGameState* consoleGame, EvoSphere::Player& currentPlayer, int playerIndex)
{
    GameState& gameState = consoleGame->gameState;

    int rollTotal = EvoSphere::rollEnergyOrbs();

    const int round = getCurrentRound(&gameState.turnManager);
    if (doesPlayerOwnTerritory(&gameState.board, currentPlayer.playerId, "Electric") &&
        currentPlayer.electricBonusRound != round)
    {
        rollTotal += 3;
        currentPlayer.electricBonusRound = round;
        ConsoleRenderer::gameMessage("Electric territory adds +3 movement this round.");
    }

    if (useOrbForgeMovementBonus(&gameState, playerIndex))
    {
        ++rollTotal;
        ConsoleRenderer::gameMessage("Orb Forge grants +1 movement this round.");
    }
    const int oldPosition = currentPlayer.currentPosition;

    EvoSphere::movePlayer(currentPlayer, gameState.board, rollTotal);

    const int newPosition = currentPlayer.currentPosition;

    ConsoleRenderer::gameMessage("Rolled: " + std::to_string(rollTotal));
    ConsoleRenderer::gameMessage("Old position: " + std::to_string(oldPosition));
    ConsoleRenderer::gameMessage("New position: " + std::to_string(newPosition));

    if (EvoSphere::didPassOriginGate(oldPosition, newPosition, rollTotal))
    {
        ConsoleRenderer::gameMessage(
            "You passed Origin Gate: +1 Evolution Gem, and defeated Evorans revive at 50% HP."
        );
        if (doesPlayerOwnTerritory(&gameState.board, currentPlayer.playerId, "Water"))
        {
            EvoSphere::healAvatar(&currentPlayer, 5);
            ConsoleRenderer::gameMessage("Water territory restores 5 Avatar Points.");
        }
        const int specialTileGems = applySpecialTileOriginGateRewards(&gameState, currentPlayer.playerId);
        if (specialTileGems > 0)
        {
            ConsoleRenderer::gameMessage("Your owned special tiles gave you " + std::to_string(specialTileGems) + " extra Evolution Gem(s).");
        }
    }
}

void evolveEvoran(EvoSphere::Player& currentPlayer)
{
    std::vector<int> eligibleIndexes;
    for (int index = 0; index < static_cast<int>(currentPlayer.ownedEvorans.size()); ++index)
    {
        if (EvoSphere::canEvolve(currentPlayer, currentPlayer.ownedEvorans[index]))
        {
            eligibleIndexes.push_back(index);
        }
    }

    if (eligibleIndexes.empty())
    {
        ConsoleRenderer::gameMessage("No Evoran can evolve yet. You need 3 Evolution Gems and an unevolved Evoran.");
        return;
    }

    ConsoleRenderer::gameMessage("Choose an Evoran to evolve:");
    for (int choice = 0; choice < static_cast<int>(eligibleIndexes.size()); ++choice)
    {
        const EvoSphere::Evoran& evoran = currentPlayer.ownedEvorans[eligibleIndexes[choice]];
        ConsoleRenderer::gameMessage(
            std::to_string(choice + 1) + ". " + EvoSphere::getDisplayName(&evoran) +
            " -> " + EvoSphere::getEvolvedName(&evoran)
        );
    }

    const int choice = ConsoleInput::askMenuChoice(1, static_cast<int>(eligibleIndexes.size()));
    const int selectedIndex = eligibleIndexes[choice - 1];
    if (!EvoSphere::evolveSelectedEvoran(currentPlayer, selectedIndex))
    {
        ConsoleRenderer::gameMessage("Evolution failed.");
        return;
    }

    const EvoSphere::Evoran& evolvedEvoran = currentPlayer.ownedEvorans[selectedIndex];
    ConsoleRenderer::gameMessage(
        EvoSphere::getName(&evolvedEvoran) + " evolved into " +
        EvoSphere::getDisplayName(&evolvedEvoran) + "!"
    );
}

void resolveLanding(ConsoleGameState* consoleGame, int playerIndex)
{
    GameState& gameState = consoleGame->gameState;
    std::vector<EvoSphere::Player>& players = consoleGame->players;

    EvoSphere::Player& currentPlayer = players[playerIndex];
    Tile* tile = getTile(&gameState.board, currentPlayer.currentPosition);
    int selectedEvoranIndex = -1;
    EvoSphere::Evoran* attacker = nullptr;
    EvoSphere::Evoran* defender = nullptr;
    int attackerHpBefore = 0;
    int defenderHpBefore = 0;

    if (tile == nullptr)
    {
        ConsoleRenderer::gameMessage("The landing tile could not be found.");
        return;
    }

    if (tile->tileType == EvoSphere::TileType::Teleport)
    {
        const int oldPosition = currentPlayer.currentPosition;
        if (EvoSphere::teleportPlayer(currentPlayer, gameState.board))
        {
            ConsoleRenderer::gameMessage(
                "Teleport Terminal moved you from " + std::to_string(oldPosition) +
                " to " + std::to_string(currentPlayer.currentPosition) + "."
            );
        }
        return;
    }

    if (tile->tileType == EvoSphere::TileType::Guardian)
    {
        const std::vector<EvoSphere::Guardian> guardians = EvoSphere::createGuardians();
        const EvoSphere::Guardian* guardian = findGuardian(guardians, tile->linkedEvoranName);
        EvoSphere::AequorionChoice choice = EvoSphere::AequorionChoice::Balance;

        if (guardian != nullptr && guardian->name == "Aequorion")
        {
            ConsoleRenderer::gameMessage("Aequorion offers 1. Balance or 2. Fate.");
            if (ConsoleInput::askMenuChoice(1, 2) == 1)
            {
                choice = EvoSphere::AequorionChoice::Balance;
            }
            else
            {
                choice = EvoSphere::AequorionChoice::Fate;
            }
        }

        const EvoSphere::GuardianOutcome outcome = EvoSphere::applyGuardianEncounter(&currentPlayer, guardian, choice);
        ConsoleRenderer::gameMessage(guardianMessage(outcome));
        refreshGameState(&gameState);
        return;
    }

    if (tile->tileType == EvoSphere::TileType::BlessingShrine ||
        tile->tileType == EvoSphere::TileType::ChaosRift)
    {
        const bool isBlessing = tile->tileType == EvoSphere::TileType::BlessingShrine;
        EvoSphere::EventResult event;
        if (isBlessing)
        {
            event = EvoSphere::generateBlessingShrineEvent();
        }
        else
        {
            event = EvoSphere::generateChaosRiftEvent();
        }

        if (event.isMovementEvent)
        {
            if (isBlessing)
            {
                ConsoleRenderer::gameMessage(
                    "Blessing: move forward " +
                    std::to_string(event.movementAmount) + " tiles."
                );
            }
            else
            {
                ConsoleRenderer::gameMessage(
                    "Chaos: move backward " +
                    std::to_string(event.movementAmount) + " tiles."
                );
            }
        }
        else
        {
            ConsoleRenderer::gameMessage("Territory event selected.");
        }

        const int round = getCurrentRound(&gameState.turnManager);
        if (!isBlessing && event.isMovementEvent &&
            doesPlayerOwnTerritory(&gameState.board, currentPlayer.playerId, "Air") &&
            currentPlayer.airProtectionRound != round)
        {
            currentPlayer.airProtectionRound = round;
            ConsoleRenderer::gameMessage("Air territory ignored this backward movement event.");
            return;
        }
        if (EvoSphere::ownsFullTerritory(currentPlayer, gameState.board, EvoSphere::ElementType::Mystic) &&
            currentPlayer.mysticRerollRound != round)
        {
            ConsoleRenderer::gameMessage("Use your Mystic reroll? 1. Yes  2. No");
            if (ConsoleInput::askMenuChoice(1, 2) == 1)
            {
                if (isBlessing)
                {
                    event = EvoSphere::generateBlessingShrineEvent();
                }
                else
                {
                    event = EvoSphere::generateChaosRiftEvent();
                }
                currentPlayer.mysticRerollRound = round;
                ConsoleRenderer::gameMessage("Mystic reroll used.");
            }
        }

        EvoSphere::applyEventResult(currentPlayer, gameState.board, event);
        if (event.applied)
        {
            ConsoleRenderer::gameMessage("Event applied.");
        }
        else
        {
            ConsoleRenderer::gameMessage("The territory event faded away.");
        }
        return;
    }

    if (tile != nullptr && isOpponentOwnedEvoranTile(*tile, currentPlayer))
    {
        const int territoryBonus = EvoSphere::getTerritoryDefenseBonus(gameState.board, *tile, tile->ownerId);

        if (territoryBonus > 0)
        {
            ConsoleRenderer::gameMessage("The defender controls this territory and gains +" + std::to_string(territoryBonus) + " damage.");
        }

        defender = getDefendingEvoran(&gameState, *tile);

        if (defender == nullptr)
        {
            ConsoleRenderer::gameMessage("The tile defender could not be found.");
        }
        else if (!EvoSphere::canEvoranBattle(*defender))
        {
            ConsoleRenderer::gameMessage(
                EvoSphere::getDisplayName(defender) + " is defeated and cannot defend this tile."
            );
        }
        else
        {
            std::vector<int> activeIndexes;
            for (int index = 0; index < static_cast<int>(currentPlayer.ownedEvorans.size()); ++index)
            {
                if (EvoSphere::canEvoranBattle(currentPlayer.ownedEvorans[index]))
                {
                    activeIndexes.push_back(index);
                }
            }

            if (activeIndexes.empty())
            {
                ConsoleRenderer::gameMessage("You have no active Evoran available to battle.");
            }
            else
            {
                ConsoleRenderer::activeEvoranChoices(currentPlayer);
                const int choice = ConsoleInput::askMenuChoice(1, static_cast<int>(activeIndexes.size()));
                selectedEvoranIndex = activeIndexes[choice - 1];

                attacker = &currentPlayer.ownedEvorans[selectedEvoranIndex];
                attackerHpBefore = EvoSphere::getCurrentHp(attacker);
                defenderHpBefore = EvoSphere::getCurrentHp(defender);
                ConsoleRenderer::gameMessage(
                    EvoSphere::getDisplayName(attacker) + " battles " +
                    EvoSphere::getDisplayName(defender) + "."
                );
            }
        }
    }

    if (tile->tileType == EvoSphere::TileType::WildEvoran && tile->ownerId == -1)
    {
        std::vector<int> activeIndexes;
        for (int index = 0; index < static_cast<int>(currentPlayer.ownedEvorans.size()); ++index)
        {
            if (EvoSphere::canEvoranBattle(currentPlayer.ownedEvorans[index]))
            {
                activeIndexes.push_back(index);
            }
        }

        if (activeIndexes.empty())
        {
            ConsoleRenderer::gameMessage("You have no active Evoran available to capture this wild Evoran.");
        }
        else
        {
            ConsoleRenderer::gameMessage(
                "Wild " + EvoSphere::getDisplayName(&tile->wildEvoran) +
                " appears. HP: " + std::to_string(EvoSphere::getCurrentHp(&tile->wildEvoran)) +
                "/" + std::to_string(EvoSphere::getMaxHp(&tile->wildEvoran)) +
                ", Damage: " + std::to_string(EvoSphere::getDamage(&tile->wildEvoran)) +
                ". Choose an Evoran to battle."
            );
            ConsoleRenderer::activeEvoranChoices(currentPlayer);
            const int choice = ConsoleInput::askMenuChoice(1, static_cast<int>(activeIndexes.size()));
            selectedEvoranIndex = activeIndexes[choice - 1];
            attacker = &currentPlayer.ownedEvorans[selectedEvoranIndex];
            attackerHpBefore = EvoSphere::getCurrentHp(attacker);
            defenderHpBefore = EvoSphere::getCurrentHp(&tile->wildEvoran);
        }
    }

    const LandingResult result = resolvePlayerLanding(
        &gameState,
        playerIndex,
        selectedEvoranIndex
    );

    if (result == LandingResult::WildEvoranCaptured)
    {
        ConsoleRenderer::gameMessage(
            "You captured " + EvoSphere::getDisplayName(&tile->wildEvoran) +
            " and claimed its tile."
        );
    }
    else if (result == LandingResult::WildEvoranBattleFailed)
    {
        if (attacker != nullptr)
        {
            ConsoleRenderer::gameMessage(
                EvoSphere::getDisplayName(attacker) + " HP: " +
                std::to_string(EvoSphere::getCurrentHp(attacker)) + "/" +
                std::to_string(EvoSphere::getMaxHp(attacker)) + "."
            );
            ConsoleRenderer::gameMessage(
                EvoSphere::getDisplayName(&tile->wildEvoran) + " HP: " +
                std::to_string(EvoSphere::getCurrentHp(&tile->wildEvoran)) + "/" +
                std::to_string(EvoSphere::getMaxHp(&tile->wildEvoran)) + "."
            );
            ConsoleRenderer::gameMessage("The wild Evoran was not captured.");
        }
    }
    else if (result == LandingResult::OwnEvoranTile)
    {
        ConsoleRenderer::gameMessage("This Evoran tile belongs to you. You are safe.");
    }
    else if (result == LandingResult::OpponentEvoranTile)
    {
        if (attacker != nullptr && defender != nullptr)
        {
            const int defenderDamageTaken = defenderHpBefore - EvoSphere::getCurrentHp(defender);
            const int attackerDamageTaken = attackerHpBefore - EvoSphere::getCurrentHp(attacker);

            ConsoleRenderer::gameMessage(
                EvoSphere::getDisplayName(attacker) + " attacked " +
                EvoSphere::getDisplayName(defender) + " for " +
                std::to_string(defenderDamageTaken) + " damage."
            );
            ConsoleRenderer::gameMessage(
                EvoSphere::getDisplayName(defender) + " HP: " +
                std::to_string(EvoSphere::getCurrentHp(defender)) + "/" +
                std::to_string(EvoSphere::getMaxHp(defender))
            );

            if (attackerDamageTaken > 0)
            {
                ConsoleRenderer::gameMessage(
                    EvoSphere::getDisplayName(defender) + " counterattacked " +
                    EvoSphere::getDisplayName(attacker) + " for " +
                    std::to_string(attackerDamageTaken) + " damage."
                );
            }

            ConsoleRenderer::gameMessage(
                EvoSphere::getDisplayName(attacker) + " HP: " +
                std::to_string(EvoSphere::getCurrentHp(attacker)) + "/" +
                std::to_string(EvoSphere::getMaxHp(attacker))
            );

            if (EvoSphere::isEvoranDefeated(attacker))
            {
                ConsoleRenderer::gameMessage(EvoSphere::getDisplayName(attacker) + " has been defeated.");
            }

            if (EvoSphere::isEvoranDefeated(defender))
            {
                ConsoleRenderer::gameMessage(EvoSphere::getDisplayName(defender) + " has been defeated.");
            }

            if (EvoSphere::getElementType(attacker) == EvoSphere::ElementType::Fire &&
                doesPlayerOwnTerritory(&gameState.board, currentPlayer.playerId, "Fire"))
            {
                ConsoleRenderer::gameMessage("Fire territory increased the attacker's damage by 20%.");
            }

            if (EvoSphere::getElementType(defender) == EvoSphere::ElementType::Fire &&
                doesPlayerOwnTerritory(&gameState.board, tile->ownerId, "Fire"))
            {
                ConsoleRenderer::gameMessage("Fire territory increased the defender's damage by 20%.");
            }

            if (EvoSphere::getElementType(attacker) == EvoSphere::ElementType::Rock &&
                doesPlayerOwnTerritory(&gameState.board, currentPlayer.playerId, "Rock"))
            {
                ConsoleRenderer::gameMessage("Rock territory reduced incoming damage to the attacker by 5.");
            }

            if (EvoSphere::getElementType(defender) == EvoSphere::ElementType::Rock &&
                doesPlayerOwnTerritory(&gameState.board, tile->ownerId, "Rock"))
            {
                ConsoleRenderer::gameMessage("Rock territory reduced incoming damage to the defender by 5.");
            }

            if ((EvoSphere::getElementType(attacker) == EvoSphere::ElementType::Dark &&
                 doesPlayerOwnTerritory(&gameState.board, currentPlayer.playerId, "Dark")) ||
                (EvoSphere::getElementType(defender) == EvoSphere::ElementType::Dark &&
                 doesPlayerOwnTerritory(&gameState.board, tile->ownerId, "Dark")))
            {
                ConsoleRenderer::gameMessage("Dark territory gives its Dark Evoran a 40% chance to dodge incoming damage.");
            }

            if (doesPlayerOwnTerritory(&gameState.board, currentPlayer.playerId, "Nature") ||
                doesPlayerOwnTerritory(&gameState.board, tile->ownerId, "Nature"))
            {
                ConsoleRenderer::gameMessage("Nature territory healed its owner's Nature Evorans by 10 HP after battle.");
            }
        }

        ConsoleRenderer::gameMessage("The avatar whose Evoran lost this tile battle loses 5 Avatar Points."
);
    }
    else if (result == LandingResult::SpecialTileAttuned && tile != nullptr)
    {
        const int progress = tile->attunementProgress[currentPlayer.playerId];
        ConsoleRenderer::gameMessage(
            "You attuned to " + getName(tile) + ". Progress: " +
            std::to_string(progress) + "/" +
            std::to_string(tile->requiredAttunement) + "."
        );
    }
    else if (result == LandingResult::SpecialTileClaimed && tile != nullptr)
    {
        ConsoleRenderer::gameMessage(
            "You reached " + std::to_string(tile->requiredAttunement) + "/" +
            std::to_string(tile->requiredAttunement) + " attunement and claimed " +
            getName(tile) + "."
        );
    }
    else if (result == LandingResult::OwnSpecialTile && tile != nullptr)
    {
        if (tile->index == EvoSphere::ANCIENT_RELIC_SHRINE_INDEX)
        {
            ConsoleRenderer::gameMessage("Ancient Relic Shrine grants +5 damage for your next wild Evoran battle.");
        }
        else
        {
            ConsoleRenderer::gameMessage("This special tile belongs to you.");
        }
    }
    else if (result == LandingResult::OpponentSpecialTile && tile != nullptr)
    {
        if (tile->index == EvoSphere::GEMSTONE_MINE_INDEX)
        {
            ConsoleRenderer::gameMessage("Gemstone Mine belongs to an opponent. Its owner gained 1 Evolution Gem.");
        }
        else if (tile->index == EvoSphere::ORB_FORGE_INDEX)
        {
            ConsoleRenderer::gameMessage("Orb Forge moved you backward 2 tiles.");
        }
        else
        {
            ConsoleRenderer::gameMessage("Ancient Relic Shrine removed 1 Evolution Gem if you had one.");
        }
    }
}

void runTurn(ConsoleGameState* consoleGame)
{
    GameState& gameState = consoleGame->gameState;
    std::vector<EvoSphere::Player>& players = consoleGame->players;
    bool& running = consoleGame->running;

    const int currentPlayerIndex = getCurrentPlayerIndex(&gameState.turnManager);
    EvoSphere::Player& currentPlayer = players[currentPlayerIndex];
    bool turnEnded = false;
    bool hasRolled = false;

    ConsoleRenderer::playerTurnStart(currentPlayer, getCurrentRound(&gameState.turnManager));

    while (running && !turnEnded)
    {
        ConsoleRenderer::mainMenu(hasRolled);

        const int choice = ConsoleInput::askMenuChoice(1, 4);

        if (choice == 1)
        {
            if (!hasRolled)
            {
                movementSystem(consoleGame, currentPlayer, currentPlayerIndex);
                resolveLanding(consoleGame, currentPlayerIndex);
                hasRolled = true;
                refreshGameState(&gameState);

                if (gameState.gameOver)
                {
                    turnEnded = true;
                }
            }
            else
            {
                turnEnded = true;
                ConsoleRenderer::gameMessage("Turn ended.");
                updateGameState(&gameState);
            }
        }
        else if (choice == 2)
        {
            ConsoleRenderer::playerStatus(currentPlayer);
            ConsoleInput::waitForEnter();
        }
        else if (choice == 3)
        {
            evolveEvoran(currentPlayer);
        }
        else
        {
            running = false;
            ConsoleRenderer::gameMessage("Game closed.");
        }
    }
}
