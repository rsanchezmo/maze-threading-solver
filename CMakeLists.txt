cmake_minimum_required(VERSION 3.5)
project(maze_solver)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


include_directories(include)
include_directories(mazes)

# CREATE A BASIC PROGRAM
set(MY_PROGRAM_REQUIRED_FILES
    src/solver.cpp
    src/maze_utils.cpp
)
add_executable(maze ${MY_PROGRAM_REQUIRED_FILES})

target_link_libraries(maze pthread)

install(DIRECTORY include/
  DESTINATION include/
)

install(DIRECTORY mazes/
  DESTINATION mazes/
)