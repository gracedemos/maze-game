project(maze-game)

if(APPLE)
    include_directories(/usr/local/include ${CMAKE_SOURCE_DIR}/include)
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE src/main.cpp src/game.cpp src/map.cpp)
    target_link_libraries(${PROJECT_NAME} /usr/local/lib/libSDL2.dylib)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Maze Game")
    
    add_custom_target(levels ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources "${CMAKE_BINARY_DIR}/Maze Game.app/Contents/MacOS/resources")
endif()

if(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/include)
    add_executable(${PROJECT_NAME} WIN32 src/main.cpp src/game.cpp src/map.cpp)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/SDL2.lib ${CMAKE_SOURCE_DIR}/lib/SDL2main.lib)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Maze Game")

    add_custom_target(levels ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/Debug/resources)
    add_custom_target(dll ALL COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/lib/SDL2.dll ${CMAKE_BINARY_DIR}/Debug)
endif()