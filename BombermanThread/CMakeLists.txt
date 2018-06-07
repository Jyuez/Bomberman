cmake_minimum_required(VERSION 3.7)
project(Bomberman)

set(CMAKE_C_STANDARD 11)

INCLUDE_DIRECTORIES(include/)
INCLUDE_DIRECTORIES(include/SDL2)
INCLUDE_DIRECTORIES(include/launcher)
INCLUDE_DIRECTORIES(include/GameEngine)
INCLUDE_DIRECTORIES(include/network)
INCLUDE_DIRECTORIES(include/host)
INCLUDE_DIRECTORIES(include/client)
INCLUDE_DIRECTORIES(include/lobby)

LINK_DIRECTORIES(lib/)

set(SOURCE_FILES main.c
        )

set(GAME_ENGINE
        src/GameEngine/engine.c
        src/GameEngine/menu.c
        src/GameEngine/player.c
        src/GameEngine/map.c
        src/GameEngine/GameEvent.c
        src/GameEngine/Game.c
        )

set(LAUNCHER
        src/launcher/launcher.c
        src/launcher/EventLauncher.c
        src/launcher/InterfaceLauncher.c
        src/launcher/ActionLauncher.c
        )

set(NETWORK
        src/network/network.c
        )

set(HOST
        src/host/server.c
        src/host/HostEvent.c
        src/host/ActionHost.c
        src/host/InterfaceHost.c
        src/host/host.c
        )

set(LOBBY
        src/lobby/ActionLobby.c
        src/lobby/EventLobby.c
        )

set(CLIENT
        src/client/guest.c
        src/client/InterfaceGuest.c
        src/client/guestEvent.c
        src/client/ActionGuest.c
        src/client/client.c
        )


add_executable(Bomberman
        ${SOURCE_FILES}
        ${GAME_ENGINE}
        ${LAUNCHER}
        ${HOST}
        ${NETWORK}
        ${CLIENT})

target_link_libraries(Bomberman -lmingw32 -lpthread -lws2_32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf)