cmake_minimum_required(VERSION 3.8)
project(RetroGame)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SDLIMAGE_AVIF OFF)
set(SDLIMAGE_JXL OFF)
set(SDLIMAGE_WEBP OFF)
set(SDLIMAGE_TIF OFF)

add_subdirectory(external/SDL3)
add_subdirectory(external/SDL_image)

add_executable(RetroGame src/main.c
                        src/core/game.c
                        src/rendering/renderer.c
                         src/rendering/sprites.c)

target_link_libraries(RetroGame SDL3::SDL3
                                SDL3_image::SDL3_image)