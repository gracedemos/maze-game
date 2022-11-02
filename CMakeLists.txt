project(maze-game)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(${PROJECT_NAME} WIN32 src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/SDL2.lib ${CMAKE_SOURCE_DIR}/lib/SDL2main.lib)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Maze Game")