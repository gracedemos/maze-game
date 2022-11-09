project(maze-game)

if(APPLE)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

    add_executable(${PROJECT_NAME} MACOSX_BUNDLE src/main.cpp src/game.cpp src/map.cpp)
    add_custom_target(levels ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources "${CMAKE_BINARY_DIR}/Maze Game.app/Contents/MacOS/resources")

    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Maze Game")
endif()

if(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/include)

    add_executable(${PROJECT_NAME} WIN32 src/main.cpp src/game.cpp src/map.cpp)
    add_custom_target(levels ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/Debug/resources)
    add_custom_target(sdl2 ALL COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/lib/SDL2.dll ${CMAKE_BINARY_DIR}/Debug)

    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/SDL2.lib ${CMAKE_SOURCE_DIR}/lib/SDL2main.lib)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Maze Game")
endif()

if(UNIX AND NOT APPLE)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

    add_executable(${PROJECT_NAME} src/main.cpp src/game.cpp src/map.cpp)
    add_custom_target(levels ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources)

    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
endif()