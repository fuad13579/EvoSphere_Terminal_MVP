#pragma once

#include <string>

namespace ConsoleInput
{
    int askPlayerCount();
    std::string askAvatarName(int playerNumber);
    int askMenuChoice(int minimum, int maximum);
    void waitForEnter();
}
