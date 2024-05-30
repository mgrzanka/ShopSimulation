cmake_minimum_required(VERSION 3.25.1)
set(CMAKE_CXX_STANDARD 20)

project(Projekt)
include(FetchContent)

file(GLOB_RECURSE client CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Client/*")
file(GLOB_RECURSE employee CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Employee/*")
file(GLOB_RECURSE eventgenerator CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/EventsGenerator/*")
file(GLOB_RECURSE filehandler CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/EventHandler/*")
file(GLOB_RECURSE product CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Product/*")
file(GLOB_RECURSE randomevent CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/RandomEvent/*")
file(GLOB_RECURSE simulation CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Simulation/*")
file(GLOB_RECURSE store CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Store/*")
file(GLOB_RECURSE userinterface CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/UserInterface/*")
file(GLOB_RECURSE structures CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Structures.*")

add_library(Projekt ${client} ${employee} ${eventgenerator} ${filehandler}
${product} ${randomevent} ${simulation} ${store} ${userinterface} ${structures})

add_executable("main" "main.cpp")
target_link_libraries("main" PUBLIC Projekt)

add_subdirectory("Tests")
add_subdirectory("google_tests")
enable_testing()