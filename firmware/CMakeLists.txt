CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)

set(TARGET "slegro")
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/src/system/stm32f103rc.ld")

# set cross compilation information
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

#set(CMAKE_MAKE_PROGRAM make CACHE INTERNAL "")

# specify the toolchain
set(TOOLCHAIN_PREFIX arm-none-eabi-)

set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}as)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)

# Try to force the compiler
SET(CMAKE_C_COMPILER_WORKS 1 CACHE INTERNAL "")
SET(CMAKE_CXX_COMPILER_WORKS 1 CACHE INTERNAL "")

# set compiler flags
set(CPU "-mcpu=cortex-m3")
#set(CMAKE_ASM_FLAGS "-ggdb ${CPU} -gdwarf-2" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS "-ggdb ${CPU} -Wall -Werror -mthumb -gdwarf-2 -std=c99" CACHE STRING "" FORCE)

# set linker flags
set(CMAKE_EXE_LINKER_FLAGS "-T ${LINKER_SCRIPT} -Wl,-Map,${TARGET}.map -nostartfiles" CACHE STRING "" FORCE)


project(Slegro)

enable_language(C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/app/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/system/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/drivers_ext/include)

file(GLOB APP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/app/*.c)
file(GLOB SYSTEM_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/system/*.c)
file(GLOB DRIVER_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/*.c)
file(GLOB DRIVER_EXT_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers_ext/*.c)

add_executable(${TARGET}.elf ${APP_SRC} ${SYSTEM_SRC} ${DRIVER_SRC} ${DRIVER_EXT_SRC})
add_custom_command(TARGET ${TARGET}.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex ${TARGET}.elf ${TARGET}.hex)
add_custom_command(TARGET ${TARGET}.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${TARGET}.elf ${TARGET}.bin)
