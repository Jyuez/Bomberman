cmake_minimum_required(VERSION 3.7)
project(BomberClient)
set(CMAKE_C_STANDARD 11)

INCLUDE_DIRECTORIES(include/)
INCLUDE_DIRECTORIES(include/SDL2)
INCLUDE_DIRECTORIES(include/game)
INCLUDE_DIRECTORIES(include/network)
INCLUDE_DIRECTORIES(include/menuTree)
LINK_DIRECTORIES(lib/)

set(SOURCE_FILES
        src/globals.c

        src/game/player.c
        src/game/mainLoop.c
        src/game/actionsMenu.c
        src/game/EventHandler.c
        src/game/menuTree/menu.c

        src/network/server.c
        src/network/client.c
        src/network/network.c
        main.c
        )

add_executable(BomberClient ${SOURCE_FILES})
target_link_libraries(BomberClient -lmingw32 -lpthread -lws2_32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf)