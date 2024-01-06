cmake_minimum_required(VERSION 3.22)
project(astroid_collision_game)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(astroid_collision_game
    src/main.cpp
    src/game.cpp
    include/game.h
)

target_include_directories(astroid_collision_game PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(astroid_collision_game PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})