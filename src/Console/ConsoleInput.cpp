#include "Console/ConsoleInput.hpp"

#include <iostream>
#include <limits> // For std::numeric_limits.

namespace ConsoleInput
{

int askPlayerCount()
{
    int playerCount;

    while (1)
    {
        std::cout << "Number of players [2-3]: ";
        std::cin >> playerCount;

        if (std::cin.good() && playerCount >= 2 && playerCount <= 3)
        {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            return playerCount;
        }

        std::cout << "Invalid input.Need 2 to 3 Players\n";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }
}

std::string askAvatarName(int playerNumber)
{
    std::string avatarName;

    std::cout << "Avatar " << playerNumber << "\n";
    std::cout << "Enter Avatar name: ";

    std::getline(std::cin, avatarName);

    return avatarName;
}

int askMenuChoice(int minimum, int maximum)
{
    int playerChoice;

    while (1)
    {
        std::cout << "Choose an option: ";

        std::cin >> playerChoice;

        if (std::cin.good() && playerChoice >= minimum && playerChoice <= maximum)
        {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            return playerChoice;
        }

        std::cout << "Invalid choice.\n";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }
}

void waitForEnter()
{
    std::string lastChoice;

    std::cout << "Press Enter to continue...";
    std::getline(std::cin, lastChoice);
}

}
