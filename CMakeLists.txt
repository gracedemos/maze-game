project(maze-game)

if(APPLE)
    include_directories(/usr/local/include/SDL2)
    add_executable(${PROJECT_NAME} src/main.cpp)
    target_link_libraries(${PROJECT_NAME} /usr/local/lib/libSDL2.dylib)
endif()

if(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/include)
    add_executable(${PROJECT_NAME} WIN32 src/main.cpp)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/SDL2.lib)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Maze Game")
endif()