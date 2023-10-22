cmake_minimum_required(VERSION 3.5)

project(Indigo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#list(APPEND CMAKE_CXX_FLAGS "‐std=c++17 ${CMAKE_CXX_FLAGS}")

link_libraries(SDL2 SDL2_image SDL2_ttf SDL2_mixer)
include_directories(/usr/include/SDL2)

add_executable(Indigo Main.cpp
    CameraFollower.h CameraFollower.cpp Camera.h Camera.cpp Vec2.h Vec2.cpp   Timer.h Timer.cpp TileSet.h TileSet.cpp TileMap.h TileMap.cpp Text.h Text.cpp State.h State.cpp   Sprite.h Sprite.cpp Sound.h Sound.cpp SDL_include.h Resources.h Resources.cpp Rect.h Rect.cpp Music.h Music.cpp InputManager.h InputManager.cpp GameObject.h GameObject.cpp GameData.h GameData.cpp Game.h Game.cpp Component.h Component.cpp Collision.h Collision.cpp Collider.h Collider.cpp
    States/TitleState.h States/TitleState.cpp
    Components/Indigo.h Components/Indigo.cpp)

include(GNUInstallDirs)
install(TARGETS Indigo
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
