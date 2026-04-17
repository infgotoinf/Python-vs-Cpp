cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_GENERATOR "Ninja")

project(BulletHand)

add_executable(game)

target_sources(game
  PRIVATE
    main/main.cpp

  PUBLIC
    FILE_SET headers
    TYPE HEADERS
    BASE_DIRS
      external/raylib
      external/raygui
      main/include
    FILES
      external/raylib/raylib.h
      external/raygui/raygui.h
)

target_link_libraries(game
  PRIVATE
    raylib
    GL
    m
    pthread
    dl
    rt
    X11
)
