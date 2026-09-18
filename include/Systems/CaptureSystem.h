#pragma once

#include "Core/Board.h"
#include "Core/Player.h"

namespace EvoSphere
{
    bool canCapture(const Evoran& wildEvoran);// This function checks if a wild Evoran can be captured. It takes a reference to the wild Evoran as a parameter and returns true if the wild Evoran is eligible for capture, based on its properties such as current HP, max HP, and other relevant criteria. If the wild Evoran cannot be captured, the function returns false.

    bool captureEvoran(Player& player, Board& board, int tileIndex);// This function attempts to capture a wild Evoran for a player. It takes references to the player, the game board, and the index of the tile where the wild Evoran is located. The function checks if the wild Evoran can be captured using the canCapture function and, if so, adds the wild Evoran to the player's owned Evorans and updates the game board accordingly. The function returns true if the capture is successful and false otherwise.

    bool handleWildEvoranEncounter(
        Player& player,// the player who has landed on the wild Evoran tile. This reference allows the function to access and modify the player's properties, such as their owned Evorans and evolution gems, during the encounter.
        Board& board,// the game board that contains the wild Evoran tile and its properties. This reference allows the function to access and modify the board's tiles, including the wild Evoran tile, during the encounter.
        int tileIndex,// the index of the tile where the wild Evoran is located. This index is used to retrieve the corresponding tile from the board's tiles array, which contains information about the wild Evoran and its properties.
        int selectedEvoranIndex// the index of the player's Evoran that will be used to battle the wild Evoran. This index is used to retrieve the corresponding Evoran from the player's ownedEvorans vector, which is then used in the battle against the wild Evoran on the specified tile.
    );// This function handles the encounter between a player and a wild Evoran on the game board. It takes references to the player, board, tile index, and selected Evoran index as parameters. The function manages the battle between the player's selected Evoran and the wild Evoran, determining the outcome of the encounter based on their stats and abilities. It also updates the player's owned Evorans and evolution gems accordingly, depending on whether they successfully capture the wild Evoran or lose the battle.
}