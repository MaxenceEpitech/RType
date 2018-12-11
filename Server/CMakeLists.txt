cmake_minimum_required(VERSION 2.8.12)
project(server C CXX)

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W0" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra ")#-Werror")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -g3 -Wno-unused-function")

## --- CONAN SETUP ---

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

## --- !CONAN SETUP ---

## --- ADD EXECUTABLE ---

set(PROJECT_SOURCE_DIR .)
set(SHARED_DIR ../Shared)

## --- ECS ---

set(ECS_DIR ${PROJECT_SOURCE_DIR}/GameEngine/ECS)

set(ECS_COMPONENTS_INCLUDE ${ECS_DIR}/Components/Include)
set(ECS_INTERFACE ${ECS_DIR}/Interface)
set(ECS_UTILS ${ECS_DIR}/Utils)
set(ECS_WORLD ${ECS_DIR}/World)
set(ECS_ENTITIES ${ECS_DIR}/Entities)
set(ECS_SYSTEMS ${ECS_DIR}/Systems)

### --- !ECS ---


include_directories(    ${SHARED_DIR}/Inc
                        ${PROJECT_DIR}/Inc
                        ${PROJECT_SOURCE_DIR}/Inc

                        ${ECS_COMPONENTS_INCLUDE}
                        ${ECS_INTERFACE}
                        ${ECS_UTILS}
                        ${ECS_WORLD}
                        ${ECS_ENTITIES}
                        ${ECS_SYSTEMS}
                        )

FILE(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/Src/*.cpp)
FILE(GLOB SHARED_SRC_FILES ./Shared/Src/*.cpp)

file(GLOB COMPONENTS_FILES ${ECS_DIR}/Components/Src/*.cpp)
file(GLOB ENTITIES_FILES ${ECS_DIR}/Entities/*.cpp)
file(GLOB SYSTEM_FILES ${ECS_DIR}/Systems/*.cpp)
file(GLOB UTILS_FILES ${ECS_DIR}/Utils/*.cpp)
file(GLOB WORLD_FILES ${ECS_DIR}/World/*.cpp)

add_executable( ${PROJECT_NAME}
                ${SRC_FILES}
                ${SHARED_SRC_FILES}

                ${COMPONENTS_FILES}
                ${ENTITIES_FILES}
                ${SYSTEM_FILES}
                ${UTILS_FILES}
                ${WORLD_FILES}
        GameEngine/ECS/Systems/SPlayerConnection.cpp GameEngine/ECS/Systems/SPlayerConnection.hpp GameEngine/ECS/Components/Src/CPlayer.cpp GameEngine/ECS/Components/Include/CPlayer.hpp GameEngine/ECS/Components/Src/CDirection.cpp GameEngine/ECS/Components/Include/CDirection.hpp GameEngine/ECS/Components/Src/CSpeed.cpp GameEngine/ECS/Components/Include/CSpeed.hpp GameEngine/ECS/Components/Src/CLevel.cpp GameEngine/ECS/Components/Include/CLevel.hpp GameEngine/ECS/Systems/SMapBorder.cpp GameEngine/ECS/Systems/SMapBorder.hpp GameEngine/ECS/Components/Src/CTeam.cpp GameEngine/ECS/Components/Include/CTeam.hpp GameEngine/ECS/Systems/SMove.cpp GameEngine/ECS/Systems/SMove.hpp GameEngine/ECS/Components/Src/CTimer.cpp GameEngine/ECS/Components/Include/CTimer.hpp GameEngine/ECS/Systems/SShot.cpp GameEngine/ECS/Systems/SShot.hpp GameEngine/ECS/Components/Src/CShoot.cpp GameEngine/ECS/Components/Include/CShoot.hpp GameEngine/ECS/Systems/SLevel.cpp GameEngine/ECS/Systems/SLevel.hpp GameEngine/ECS/Utils/RandomInt.hpp GameEngine/ECS/Components/Src/CDamage.cpp GameEngine/ECS/Components/Include/CDamage.hpp)

## --- !ADD EXECUTABLE ---

## --- LINK ---

target_link_libraries(  ${PROJECT_NAME}
                        ${CONAN_LIBS}
                        )
## --- !LINK ---
