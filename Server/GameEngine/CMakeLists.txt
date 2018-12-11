cmake_minimum_required (VERSION 3.1.0)

project(GameEngine)

set(PROJECT_SOURCE_DIR .)
set(ECS_COMPONENTS_INCLUDE ./ECS/Components/Include)
set(ECS_INTERFACE ./ECS/Interface)
set(ECS_UTILS ./ECS/Utils)
set(ECS_WORLD ./ECS/World)
set(ECS_ENTITIES ./ECS/Entities)
set(ECS_SYSTEMS ./ECS/Systems)

include_directories(
        ${ECS_COMPONENTS_INCLUDE}
        ${ECS_INTERFACE}
        ${ECS_UTILS}
        ${ECS_WORLD}
        ${ECS_ENTITIES}
        ${ECS_SYSTEMS}
        )

file(GLOB COMPONENTS_FILES ${PROJECT_SOURCE_DIR}/ECS/Components/Src/*.cpp)
file(GLOB ENTITIES_FILES ${PROJECT_SOURCE_DIR}/ECS/Entities/*.cpp)
file(GLOB SYSTEM_FILES ${PROJECT_SOURCE_DIR}/ECS/Systems/*.cpp)
file(GLOB UTILS_FILES ${PROJECT_SOURCE_DIR}/ECS/Utils/*.cpp)
file(GLOB WORLD_FILES ${PROJECT_SOURCE_DIR}/ECS/World/*.cpp)
file(GLOB MAIN_FILE ${PROJECT_SOURCE_DIR}/Engine.cpp)

add_executable(${PROJECT_NAME} ${COMPONENTS_FILES} ${SYSTEM_FILES} ${ENTITIES_FILES} ${UTILS_FILES} ${WORLD_FILES} ${MAIN_FILE} ECS/Systems/ASystem.cpp ECS/Systems/ASystem.hpp ECS/Components/Src/CSprite.cpp ECS/Components/Include/CSprite.hpp)
