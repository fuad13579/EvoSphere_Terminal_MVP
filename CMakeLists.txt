cmake_minimum_required(VERSION 3.16)

project(EvoSphere VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EVOSPHERE_CORE_SOURCES
    src/Core/Board.cpp
    src/Core/Evoran.cpp
    src/Core/Game.cpp
    src/Core/Guardian.cpp
    src/Core/Player.cpp
    src/Core/Tile.cpp
    src/Core/TurnManager.cpp

    src/Systems/BattleSystem.cpp
    src/Systems/CaptureSystem.cpp
    src/Systems/EventSystem.cpp
    src/Systems/EvolutionSystem.cpp
    src/Systems/MovementSystem.cpp
    src/Systems/TeleportSystem.cpp

    src/data/BoardData.cpp
    src/data/EventDatabase.cpp
    src/data/EvoranDatabase.cpp
)

function(configure_evosphere_target target)
    target_include_directories(${target}
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include
    )

    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()

add_library(EvoSphereCore STATIC ${EVOSPHERE_CORE_SOURCES})
configure_evosphere_target(EvoSphereCore)

add_executable(EvoSphere
    src/main.cpp
    src/Console/ConsoleGame.cpp
    src/Console/ConsoleInput.cpp
    src/Console/ConsoleRenderer.cpp
)
target_link_libraries(EvoSphere PRIVATE EvoSphereCore)
configure_evosphere_target(EvoSphere)

include(CTest)
if(BUILD_TESTING)
    add_executable(EvoSphereBoardTests tests/test_board.cpp)
    target_link_libraries(EvoSphereBoardTests PRIVATE EvoSphereCore)
    configure_evosphere_target(EvoSphereBoardTests)

    add_test(NAME EvoSphereBoardTests COMMAND EvoSphereBoardTests)

    add_executable(EvoSphereBattleTests tests/test_battle.cpp)
    target_link_libraries(EvoSphereBattleTests PRIVATE EvoSphereCore)
    configure_evosphere_target(EvoSphereBattleTests)

    add_test(NAME EvoSphereBattleTests COMMAND EvoSphereBattleTests)

    add_executable(EvoSphereEvoranTests tests/test_evoran.cpp)
    target_link_libraries(EvoSphereEvoranTests PRIVATE EvoSphereCore)
    configure_evosphere_target(EvoSphereEvoranTests)

    add_test(NAME EvoSphereEvoranTests COMMAND EvoSphereEvoranTests)

    add_executable(EvoSpherePlayerTests tests/test_player.cpp)
    target_link_libraries(EvoSpherePlayerTests PRIVATE EvoSphereCore)
    configure_evosphere_target(EvoSpherePlayerTests)

    add_test(NAME EvoSpherePlayerTests COMMAND EvoSpherePlayerTests)

    add_executable(EvoSphereMovementTests tests/test_movement.cpp)
    target_link_libraries(EvoSphereMovementTests PRIVATE EvoSphereCore)
    configure_evosphere_target(EvoSphereMovementTests)

    add_test(NAME EvoSphereMovementTests COMMAND EvoSphereMovementTests)

    add_executable(EvoSphereEvolutionTests tests/test_evolution.cpp)
    target_link_libraries(EvoSphereEvolutionTests PRIVATE EvoSphereCore)
    configure_evosphere_target(EvoSphereEvolutionTests)

    add_test(NAME EvoSphereEvolutionTests COMMAND EvoSphereEvolutionTests)
endif()
