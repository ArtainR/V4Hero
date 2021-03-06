cmake_minimum_required(VERSION 3.19)
project(V4Hero VERSION 1.2)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DPATAFOUR_VERSION="${CMAKE_PROJECT_VERSION}")

include(FetchContent)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(DiscordSDK 2.5.6 COMPONENTS x86_64 REQUIRED)

FetchContent_Declare(nlohmann_json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.9.1)

FetchContent_GetProperties(nlohmann_json)
if(NOT nlohmann_json_POPULATED)
    FetchContent_Populate(nlohmann_json)
    add_subdirectory(${nlohmann_json_SOURCE_DIR} ${nlohmann_json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_Declare(spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG v1.8.5)
FetchContent_MakeAvailable(spdlog)

set(ENGINE_FILES
        Engine/Func.cpp
        Engine/V4Core.cpp
        Engine/Item/Item.cpp
        Engine/Item/InventoryData.cpp
        Engine/Item/Equipment.cpp
        Engine/Item/ItemRegistry.cpp
        Engine/Dialog/ControlTips.cpp
        Engine/Dialog/RoundedRect.cpp
        Engine/Dialog/MessageCloud.cpp
        Engine/Dialog/DialogBox.cpp
        Engine/Binary.cpp
        Engine/Menu/MainMenu.cpp
        Engine/Menu/ButtonList.cpp
        Engine/Menu/Barracks.cpp
        Engine/Menu/IntroductionMenu.cpp
        Engine/Menu/Altar.cpp
        Engine/Menu/Patapolis.cpp
        Engine/Menu/MenuButton.cpp
        Engine/Menu/Credits.cpp
        Engine/Menu/NewGameNameEntryMenu.cpp
        Engine/Menu/Obelisk.cpp
        Engine/Menu/NewGameMenu.cpp
        Engine/Menu/ButtonLists/NameEntryButtonList.cpp
        Engine/Menu/ButtonLists/SaveFileCreatedMenuButtonList.cpp
        Engine/Menu/ButtonLists/NewGameMenuButtonList.cpp
        Engine/Menu/SaveFileCreated.cpp
        Engine/Menu/OptionsMenu.cpp
        Engine/Graphics/PSpritesheet.cpp
        Engine/Graphics/Scene.cpp
        Engine/Graphics/PSprite.cpp
        Engine/Graphics/Menu.cpp
        Engine/Graphics/PText.cpp
        Engine/Graphics/ScreenFade.cpp
        Engine/Math/PVector.cpp
        Engine/SaveReader.cpp
        Engine/Input/InputController.cpp
        Engine/Rhythm/RhythmGUI.cpp
        Engine/Rhythm/RhythmController.cpp
        Engine/Rhythm/SongController.cpp
        Engine/Rhythm/Drum.cpp
        Engine/Rhythm/Rhythm.cpp
        Engine/Rhythm/Song.cpp
        Engine/Pon/Pon.cpp
        Engine/Pon/PonRegistry.cpp
        Engine/StringRepository.cpp
        Engine/Config.cpp
        Engine/TipsUtil.cpp
        Engine/P4A.cpp
        Engine/Mission/Background.cpp
        Engine/Mission/Camera.cpp
        Engine/Mission/MissionController.cpp
        Engine/Mission/Weather.cpp
        Engine/Mission/Units/CollidableObject.cpp
        Engine/Mission/Units/AnimatedObject.cpp
        Engine/Mission/Units/Hitbox.cpp
        Engine/Mission/Units/Object.cpp
        Engine/Mission/Units/Projectile.cpp
        Engine/Mission/Units/Entity.cpp
        Engine/Mission/Units/Entities/Kirajin/Kirajin_Yari_2.cpp
        Engine/Mission/Units/Entities/Kirajin/Kirajin_Yari_1.cpp
        Engine/Mission/Units/Entities/Animals/Rappata.cpp
        Engine/Mission/Units/Entities/Animals/Kacheek.cpp
        Engine/Mission/Units/Entities/Misc/DroppedItem.cpp
        Engine/Mission/Units/Entities/Misc/EndFlag.cpp
        Engine/Mission/Units/Entities/Misc/FeverWorm.cpp
        Engine/Mission/Units/Entities/Obstacles/WoodenSpikes.cpp
        Engine/Mission/Units/Entities/Obstacles/RockBig.cpp
        Engine/Mission/Units/Entities/Obstacles/RockPile.cpp
        Engine/Mission/Units/Entities/Obstacles/TreasureChest.cpp
        Engine/Mission/Units/Entities/Obstacles/Wall.cpp
        Engine/Mission/Units/Entities/Obstacles/RockSmall.cpp
        Engine/Mission/Units/Entities/Buildings/KirajinPoweredTowerSmall.cpp
        Engine/Mission/Units/Entities/Buildings/KirajinPoweredTowerBig.cpp
        Engine/Mission/Units/Entities/Buildings/KirajinHut.cpp
        Engine/Mission/Units/Entities/Buildings/KirajinGuardTower.cpp
        Engine/Mission/Units/Entities/Nature/Grass2.cpp
        Engine/Mission/Units/Entities/Nature/Grass1.cpp
        Engine/Mission/Units/PlayableUnit.cpp
        Engine/Mission/Units/HitboxFrame.cpp
        Engine/Mission/Units/Units/Tatepon.cpp
        Engine/Mission/Units/Units/Hatapon.cpp
        Engine/Mission/Units/Units/Yaripon.cpp
        Engine/Mission/Units/Projectiles/Spear.cpp
        Engine/Mission/Mission.cpp
        Engine/Utils.h)

add_executable(V4Hero ${ENGINE_FILES} main.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Enabling Unity build for Release build")
    set_target_properties(V4Hero PROPERTIES
            UNITY_BUILD ON
            UNITY_BUILD_BATCH_SIZE 5)
endif()

if(MSVC)
    target_compile_options(V4Hero PRIVATE /W4)
else()
    target_compile_options(V4Hero PRIVATE -Wall -Wextra)
endif()

target_include_directories(V4Hero PRIVATE Engine/)
target_include_directories(V4Hero PRIVATE DiscordSDK)

target_link_libraries(V4Hero PRIVATE
        sfml-graphics
        sfml-audio
        DiscordSDK
        nlohmann_json::nlohmann_json
        spdlog::spdlog)

if (OS STREQUAL "Linux")
    find_package(X11 REQUIRED)
    target_link_libraries(V4Hero PRIVATE X11::X11)
endif (OS STREQUAL "Linux")

add_custom_command(
        TARGET V4Hero POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_SOURCE_DIR}/resources ${PROJECT_BINARY_DIR}/resources
        DEPENDS "${PROJECT_BINARY_DIR}/resources"
)
