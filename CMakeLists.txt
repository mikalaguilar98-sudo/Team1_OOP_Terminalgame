cmake_minimum_required(VERSION 3.14)
project(TerminalGame)

# Use C++20 for threads and modern FTXUI features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_Required ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# makes sure vs applies C++20 to everything
if(MSVC)
    add_compile_options(/std:c++20 /permissive-)
endif()

# 1. Fetch FTXUI Library from Github
include(FetchContent)
FetchContent_Declare(ftxui 
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui 
    GIT_TAG v5.0.0) #use specific version so compiler will know how to run C++ 20 strings
FetchContent_MakeAvailable(ftxui)

#finding threading support
find_package(Threads REQUIRED)

# 2. Tell Cmake where to find the project files
# since theyre in the same folder as cmake, we can use (.)
include_directories(.)

# 3. List source files for the project
set(SOURCES
    main.cpp
    Entity.cpp
    Player.cpp
    Enemies.cpp
    GameWorld.cpp
    Render.cpp
)

# 4. Create the executable and link FTXUI
add_executable(my_game ${SOURCES})
target_link_libraries(my_game PRIVATE 
    ftxui::screen 
    ftxui::dom 
    ftxui::component
    Threads::Threads
)