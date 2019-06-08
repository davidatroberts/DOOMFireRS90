cmake_minimum_required(VERSION 3.1)
project(fire)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(ZLIB REQUIRED)

set(SRC_FILES   src/main.cpp
                src/PixelBuffer.cpp
                src/Timer.cpp
                src/FireState.cpp
                src/Context.cpp
                src/Text.cpp)

add_executable(fire ${SRC_FILES})

target_link_libraries(fire ${SDL_LIBRARY})
target_link_libraries(fire ${SDL_TTF_LIBRARY})
target_link_libraries(fire ${ZLIB_LIBRARY})

target_compile_options(fire PUBLIC -lc)
target_compile_options(fire PUBLIC -lgcc)
target_compile_options(fire PUBLIC -no-pie)
target_compile_options(fire PUBLIC -Wl,--gc-sections)
target_compile_options(fire PUBLIC -flto)
target_compile_options(fire PUBLIC -s)

add_custom_target(
    opk
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/package_rs90.sh
    DEPENDS fire
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)