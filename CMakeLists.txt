cmake_minimum_required(VERSION 3.8)
project(RType)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
set(RUNTIME_OUTPUT_DIRECTORY build)
set(CMAKE_CXX_STANDARD 17)

if(UNIX)
    add_definitions("-fPIC -g -isystem")
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

include(build/conanbuildinfo.cmake)
include(build/conan_paths.cmake)
conan_basic_setup(KEEP_RPATHS)
include_directories(${CMAKE_INCLUDE_PATH})

find_package(Boost REQUIRED)
find_package(sfml 2.5.1 REQUIRED graphics window system audio)

find_package(PkgConfig)

find_path(CRITERION_INCLUDE_DIR criterion/criterion.h
          PATH_SUFFIXES criterion)

find_library(CRITERION_LIBRARY NAMES criterion libcriterion)

set(CRITERION_LIBRARIES ${CRITERION_LIBRARY})
set(CRITERION_INCLUDE_DIRS ${CRITERION_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Criterion DEFAULT_MSG
                                  CRITERION_LIBRARY CRITERION_INCLUDE_DIR)

mark_as_advanced(CRITERION_INCLUDE_DIR CRITERION_LIBRARY)

include_directories(
    CRITERION_INCLUDE_DIRS 

    client/src/game/include/
    client/src/network/include/

    server/clients/include/
    server/server/include/
    server/room/include/
    server/room/src/game/include/
    server/room/src/game/systems/

    monsters/
    monsters/

    common/
    common/protocol/
    common/client/
    common/gameSrc/gameEngine/core/
    common/gameSrc/gameEngine/components/
    common/gameSrc/gameEngine/systems/
    common/gameSrc/gameEngine/math/
    common/gameSrc/gameEngine/sfml/
    common/gameSrc/gameEngine/utils/
    common/gameSrc/game/button/
    common/gameSrc/game/background/
    common/gameSrc/game/music/
    common/gameSrc/game/player/
    common/gameSrc/game/monster/
    common/gameSrc/game/parallax/
    common/gameSrc/game/projectiles/
    common/gameSrc/game/powerUp/
    common/gameSrc/game/spawn/
    common/gameSrc/game/text/
)
include_directories(CRITERION_INCLUDE_DIRS client/src/gameEngine/core/SystemManager.hpp)
include_directories(CRITERION_INCLUDE_DIRS)
include_directories(client/src/gameEngine/core/)
include_directories(client/src/gameEngine/components/)
include_directories(client/src/gameEngine/systems/)
include_directories(client/src/gameEngine/math/)
include_directories(client/src/gameEngine/sfml/)
include_directories(client/src/gameEngine/utils/)
include_directories(client/src/network/include/)
include_directories(monsters/)

set(SRCS_SERVER
    server/API/directory/src/DirectoryLoader.cpp
    server/clients/src/ServerClient.cpp
    server/clients/src/UdpClient.cpp
    server/server/src/Server.cpp
    server/server/src/TcpConnection.cpp
    server/server/src/TcpServer.cpp
    server/server/src/UdpServer.cpp
    server/server/src/RoomManager.cpp
    server/server/src/SignalHandler.cpp
    server/room/src/Room.cpp
    server/room/src/RoomIPC.cpp
    server/room/src/game/MainGame.cpp
)

include_directories(
    server/API/directory/include/
    server/clients/include/
    server/clients/network/include/
    server/server/include/
    server/room/include/
)

set(MAIN_SERVER
    server/src/main.cpp
)

set(MAIN_CLIENT
    client/src/main.cpp    
)

set(SRCS_CLIENT
    client/src/game/MainGame.cpp
    client/src/game/MainLoop.cpp
    client/src/game/MainMenu.cpp
    client/src/game/MainEnd.cpp
    client/src/network/src/TcpClient.cpp
    client/src/network/src/UdpClient.cpp
)

set(SRCS_COMMON
    common/client/AUser.cpp
    common/protocol/AProtocol.cpp
    common/JsonUtility.cpp
    common/gameSrc/gameEngine/core/Types.cpp
   
)

set(SRCS_TEST
    tests/unit_tests.cpp
)

add_executable(r-type_client ${SRCS_CLIENT} ${MAIN_CLIENT} ${SRCS_COMMON} )
add_executable(r-type_server ${SRCS_SERVER} ${MAIN_SERVER} ${SRCS_COMMON} )

if(UNIX)
    add_executable(unit_test ${SRCS_TEST} ${SRCS_SERVER} ${SRCS_CLIENT} ${SRCS_COMMON} )
endif()

target_link_libraries(r-type_client sfml-graphics sfml-window sfml-audio sfml-system)

if(WIN32)
	target_link_libraries(r-type_server libboost_system libboost_chrono libboost_serialization
        Threads::Threads)
    target_link_libraries(r-type_client libboost_system libboost_chrono libboost_serialization Threads::Threads)
elseif (UNIX)
	target_link_libraries(r-type_server boost_system boost_chrono boost_serialization sfml-system sfml-window sfml-graphics sfml-audio
        Threads::Threads dl uuid)
	target_link_libraries(unit_test boost_system boost_chrono boost_serialization sfml-system sfml-window sfml-graphics sfml-audio
        Threads::Threads  dl criterion gcov uuid)
	target_compile_options(unit_test PRIVATE -fprofile-arcs -ftest-coverage)
    target_link_libraries(r-type_client boost_system boost_chrono Threads::Threads boost_serialization uuid ${CMAKE_DL_LIBS})
endif()