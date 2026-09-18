#pragma once

#include "Core/Board.h"
#include "Core/Player.h"

namespace EvoSphere
{

struct EventResult
{
    bool isBlessing = false;//this boolean indicates whether the event is a blessing or not. If true, it means the event is a blessing, and if false, it means the event is a curse or negative effect.
    bool isMovementEvent = false;// this boolean indicates whether the event affects movement.
    ElementType selectedElement = ElementType::None;//this variable represents the element type associated with the event. It can be one of the predefined element types (e.g., Fire, Water, Nature, etc.) or None if no specific element is selected.
    int movementAmount = 0;//this integer represents the amount of movement affected by the event. It can be positive (indicating forward movement) or negative (indicating backward movement). The value is typically determined by the event's effect on the player's position on the game board.
    bool applied = false;
};//this struct represents the result of an event in the game. It contains information about whether the event is a blessing, whether it affects movement, the selected element type for the event, the amount of movement affected, and whether the event was successfully applied.

struct ActiveTerritoryEffect
{
    bool active = false;
    int playerId = -1;//this integer represents the ID of the player who owns the territory associated with the effect. It is used to identify which player is affected by the territory effect.
    ElementType element = ElementType::None;
    int remainingRounds = 0;//this integer represents the number of rounds remaining for which the territory effect will be active. It is decremented after each round, and when it reaches zero, the effect is no longer active.
    int damageModifier = 0;//this integer represents the modifier for the player's damage stat while the effect is active. It can be positive (indicating increased damage) or negative (indicating decreased damage). The value is typically determined by the specific territory effect applied to the player.
    int defenseModifier = 0;//this integer represents the modifier for the player's defense stat while the effect is active.
    bool movementProtection = false;//this boolean indicates whether the player is granted protection from movement-related effects while the territory effect is active. If true, it means the player is protected from movement penalties or restrictions, and if false, it means the player is not protected.
};//this struct represents an active territory effect in the game. It contains information about whether the effect is currently active, the ID of the player who owns the territory, the element type associated with the effect, the number of remaining rounds for which the effect will be active, any damage or defense modifiers applied by the effect, and whether movement protection is granted by the effect.

bool ownsFullTerritory(
    const Player& player,
    const Board& board,
    ElementType element
);//this function checks if a player owns the full territory of a specific element type on the game board. It takes a reference to the player, the game board, and the element type as parameters. The function iterates through all tiles on the board and counts how many tiles of the specified element type are owned by the player. If the count matches the total number of tiles of that element type on the board, it returns true, indicating that the player owns the full territory. Otherwise, it returns false.

EventResult resolveBlessingShrine(Player& player, Board& board);//this function resolves the effects of a blessing shrine event for a player on the game board. It takes a reference to the player and the game board as parameters. The function checks if the player owns the full territory of a specific element type associated with the blessing shrine. If the player does own the full territory, it applies the blessing effects, such as granting bonuses or advantages to the player. The function returns an EventResult struct that contains information about whether the event was a blessing, whether it affected movement, the selected element type, and whether the event was successfully applied.

EventResult resolveChaosRift(Player& player, Board& board);//this function resolves the effects of a chaos rift event for a player on the game board. It takes a reference to the player and the game board as parameters. The function checks if the player owns the full territory of a specific element type associated with the chaos rift. If the player does own the full territory, it applies the curse effects, such as imposing penalties or disadvantages on the player. The function returns an EventResult struct that contains information about whether the event was a blessing, whether it affected movement, the selected element type, and whether the event was successfully applied.

EventResult generateBlessingShrineEvent();
EventResult generateChaosRiftEvent();
void applyEventResult(Player& player, Board& board, EventResult& result);

bool applyTerritoryBlessing(
    Player& player,
    Board& board,
    ElementType element
);//this function applies the effects of a territory blessing to a player on the game board. It takes a reference to the player, the game board, and the element type associated with the blessing as parameters. The function checks if the player owns the full territory of the specified element type. If the player does own the full territory, it applies the blessing effects, such as granting bonuses or advantages to the player. The function returns true if the blessing was successfully applied, and false otherwise.

bool applyTerritoryCurse(
    Player& player,
    Board& board,
    ElementType element
);// this function applies the effects of a territory curse to a player on the game board. It takes a reference to the player, the game board, and the element type associated with the curse as parameters. The function checks if the player owns the full territory of the specified element type. If the player does own the full territory, it applies the curse effects, such as imposing penalties or disadvantages on the player. The function returns true if the curse was successfully applied, and false otherwise.


//the difference applyTerritoryBlessing and resolveBlessingShrine is that the first one applies the blessing effects to the player, while the second one resolves the event and determines whether the blessing was successfully applied or not. The same applies to applyTerritoryCurse and resolveChaosRift.
}
