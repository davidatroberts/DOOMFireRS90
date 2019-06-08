SET(CMAKE_SYSTEM_NAME Linux)

SET(CMAKE_C_COMPILER /opt/rs90tools/bin/mipsel-linux-gcc)
SET(CMAKE_CXX_COMPILER /opt/rs90tools/bin/mipsel-linux-g++)

SET(CMAKE_FIND_ROOT_PATH /opt/rs90tools/mipsel-rs90-linux-musl/sysroot)

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

add_compile_options(-fdata-sections -ffunction-sections -fno-PIC -flto)
add_compile_options(-fsingle-precision-constant -fno-stack-protector)
add_compile_options(-fomit-frame-pointer -falign-functions=1 -falign-jumps=1)
add_compile_options(-falign-loops=1 -fprofile-use)

add_compile_options(-DRS90_BUILD -Ofast -mips32 -mno-check-zero-division -mframe-header-opt)
add_compile_options(-DSCREEN_WIDTH=240 -DSCREEN_HEIGHT=160 -DBPP=16)
