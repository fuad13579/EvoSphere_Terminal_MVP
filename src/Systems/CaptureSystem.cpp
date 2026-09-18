#include "Systems/CaptureSystem.h"

#include "Systems/BattleSystem.h"

namespace EvoSphere
{
    bool canCapture(const Evoran& wildEvoran)
    {
        const int maxHp = getMaxHp(&wildEvoran);

        return getEvoranCategory(&wildEvoran) == EvoranCategory::Wild && maxHp > 0 &&
               getCurrentHp(&wildEvoran) * 100 <=
                   maxHp * CAPTURE_HP_THRESHOLD_PERCENT;// This line checks if the wild Evoran's current HP is less than or equal to a certain percentage (defined by CAPTURE_HP_THRESHOLD_PERCENT) of its maximum HP. If the wild Evoran's current HP is below this threshold, it indicates that the wild Evoran is weakened and can be captured by the player.
    }

    bool captureEvoran(Player& player, Board& board, int tileIndex)
    {
        if (tileIndex < 0 || tileIndex >= BOARD_SIZE || isAvatarDefeated(&player))
        {
            return false;
        }

        Tile& tile = board.tiles[tileIndex];//this line retrieves a reference to the tile at the specified index (tileIndex) from the board's tiles array. The reference is stored in the variable tile, allowing the function to access and modify the properties of that specific tile on the game board.

        if (tile.tileType != TileType::WildEvoran ||
            tile.ownerId != -1 ||
            !canCapture(tile.wildEvoran))
        {
            return false;
        }

        setOwnerId(&tile.wildEvoran, getPlayerId(&player));
        setTileOwner(&board, tileIndex, getPlayerId(&player));
        addEvoran(&player, tile.wildEvoran);

        return true;
    }// This function attempts to capture a wild Evoran on the specified tile (tileIndex) of the game board. It first checks if the tile index is valid and if the player is not defeated. Then, it retrieves the tile at the specified index and checks if it contains a wild Evoran that can be captured (i.e., it is of type WildEvoran, has no owner, and meets the capture conditions). If all conditions are met, the function sets the owner ID of the wild Evoran to the player's ID, updates the tile's owner ID, and adds the captured Evoran to the player's collection. The function returns true if the capture is successful; otherwise, it returns false.

    bool handleWildEvoranEncounter(
        Player& player,
        Board& board,
        int tileIndex,
        int selectedEvoranIndex
    )// This function handles the encounter between a player and a wild Evoran on the game board. It takes references to the player, the game board, the index of the tile where the encounter occurs (tileIndex), and the index of the player's selected Evoran (selectedEvoranIndex) as parameters. The function first checks if the tile index and selected Evoran index are valid, if the player is not defeated, and if the player has active Evorans. If any of these conditions are not met, it returns false. Then, it retrieves the tile at the specified index and checks if it contains a wild Evoran that can be battled. If so, it retrieves the player's selected Evoran and initiates a battle using the runWildBattle function. If the battle is successful and the wild Evoran can be captured, it calls captureEvoran to capture the wild Evoran. The function returns true if the capture is successful; otherwise, it returns false.
    {
        if (tileIndex < 0 || tileIndex >= BOARD_SIZE ||
            selectedEvoranIndex < 0 ||
            selectedEvoranIndex >= static_cast<int>(player.ownedEvorans.size()) ||
            isAvatarDefeated(&player) ||
            !hasActiveEvorans(&player))//static_cast<int>(player.ownedEvorans.size()) is used to convert the size of the player's owned Evorans vector (which is of type size_t) to an int for comparison with selectedEvoranIndex. This ensures that the comparison is valid and avoids potential issues with signed/unsigned integer comparisons.For example if the player has 3 owned Evorans, player.ownedEvorans.size() would return 3 (of type size_t). If selectedEvoranIndex is 2, the comparison would be valid. However, if selectedEvoranIndex is 3 or greater, it would be out of bounds, and the function would return false to indicate that the selected Evoran index is invalid.
        {
            return false;
        }

        Tile& tile = board.tiles[tileIndex];

        if (tile.tileType != TileType::WildEvoran || tile.ownerId != -1)
        {
            return false;
        }

        Evoran& selectedEvoran = player.ownedEvorans[selectedEvoranIndex];

        if (isEvoranDefeated(&selectedEvoran) ||
            !runWildBattle(player, selectedEvoran, tile.wildEvoran, board))
        {
            return false;
        }

        return captureEvoran(player, board, tileIndex);// This line attempts to capture the wild Evoran on the specified tile (tileIndex) of the game board after a successful battle. It calls the captureEvoran function, passing in the player, the game board, and the tile index as arguments. If the capture is successful, it returns true; otherwise, it returns false.
    }
}
