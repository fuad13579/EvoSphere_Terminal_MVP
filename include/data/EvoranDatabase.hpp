#pragma once

#include <string>
#include <vector>

#include "Core/Evoran.h"
#include "Core/Guardian.h"

namespace EvoSphere
{
    std::vector<Evoran> createStarterEvorans();
    std::vector<Evoran> createWildEvorans();
    std::vector<Guardian> createGuardians();

    bool findEvoranByName(const std::vector<Evoran>& evorans,const std::string& name,Evoran* result);
}
