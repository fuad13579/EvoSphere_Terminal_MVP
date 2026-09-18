#include "Systems/TeleportSystem.h"

#include "data/BoardData.hpp"
#include "Utils/Random.h"

namespace EvoSphere
{
    bool isTeleportTile(const Tile& tile)
    {
        return tile.tileType == TileType::Teleport;
    }// This function checks if the given tile is a teleport tile by comparing its type to the Teleport tile type defined in the TileType enumeration. If the tile's type matches Teleport, the function returns true; otherwise, it returns false.

    int chooseDestination(
        int currentTeleportIndex,
        const std::array<int, TELEPORT_TILE_COUNT>& teleportIndexes
    )// Chooses a random Teleport Terminal destination.
// The current terminal is excluded, so the player moves to one of the other three terminals.
    {
        int destinations[TELEPORT_TILE_COUNT - 1];// This line declares an array named destinations with a size of TELEPORT_TILE_COUNT - 1. The purpose of this array is to store the indexes of the available teleport terminal tiles that the player can choose as a destination, excluding the current teleport terminal index. Since there are TELEPORT_TILE_COUNT teleport terminals in total, and the current terminal is excluded, the size of the destinations array is set to TELEPORT_TILE_COUNT - 1.
        int destinationCount = 0;// This line declares an integer variable named destinationCount and initializes it to 0. The purpose of this variable is to keep track of the number of valid destination teleport terminal indexes that have been added to the destinations array. As the function iterates through the teleportIndexes array, it increments destinationCount each time a valid destination index (i.e., one that is not the current teleport terminal index) is added to the destinations array. This count will be used later to randomly select one of the available destination indexes for teleportation.
        bool foundCurrentTerminal = false;// This line declares a boolean variable named foundCurrentTerminal and initializes it to false. The purpose of this variable is to track whether the current teleport terminal index (currentTeleportIndex) has been found in the teleportIndexes array during the iteration. If the current terminal index is found, foundCurrentTerminal will be set to true, indicating that the current terminal is present in the list of teleport terminals. This information is used later to determine if a valid destination can be chosen for teleportation.

        for (int position : teleportIndexes)
        {
            if (position == currentTeleportIndex)
            {
                foundCurrentTerminal = true;
                continue;
            }// This line checks if the current position in the teleportIndexes array is equal to the currentTeleportIndex. If they are equal, it means that the current position is the same as the player's current teleport terminal, and it should not be included in the list of possible destinations. In this case, foundCurrentTerminal is set to true to indicate that the current terminal has been found, and the continue statement is used to skip the rest of the loop iteration and move on to the next position in the teleportIndexes array.

            destinations[destinationCount] = position;
            ++destinationCount;
        }

        if (!foundCurrentTerminal || destinationCount == 0)
        {
            return -1;
        }// This line checks if the current teleport terminal index was not found in the teleportIndexes array (foundCurrentTerminal is false) or if there are no valid destination indexes available (destinationCount is 0). If either of these conditions is true, it means that a valid destination cannot be chosen for teleportation. In this case, the function returns -1 to indicate that no valid destination is available.

        return destinations[randomIndex(destinationCount)];// This line returns a randomly selected destination index from the destinations array. The randomIndex function is called with destinationCount as the argument, which generates a random index between 0 and destinationCount - 1. This random index is then used to access the corresponding element in the destinations array, which represents one of the valid teleport terminal indexes that the player can choose as a destination. The selected destination index is returned by the function.
    }

    bool teleportPlayer(Player& player, Board& board)
    {
        if (isAvatarDefeated(&player) ||player.currentPosition < 0 ||player.currentPosition >= BOARD_SIZE)
        {
            return false;
        }

        Tile& currentTile = board.tiles[player.currentPosition];

        if (!isTeleportTile(currentTile))
        {
            return false;
        }

        const int destination = chooseDestination(
            player.currentPosition,
            getTeleportTerminalPositions()
        );//const is used to indicate that the destination variable is a constant and cannot be modified after its initial assignment. This ensures that the value of destination remains unchanged throughout the scope of the teleportPlayer function, providing clarity and preventing accidental modifications to the chosen destination index.

        if (destination == -1)
        {
            return false;
        }

        movePlayerTo(&player, destination);// This line calls the movePlayerTo function, passing in a pointer to the player and the destination index as arguments. The purpose of this function call is to update the player's current position on the game board to the chosen teleport terminal destination. The movePlayerTo function is responsible for handling the actual movement of the player to the specified tile index, ensuring that the player's position is updated correctly within the game state.

        return true;
    }
}
