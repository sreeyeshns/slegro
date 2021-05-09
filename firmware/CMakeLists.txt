CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)

set(TARGET "slegro")
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/lpc2138.ld")

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
set(CPU "-mcpu=arm7tdmi-s")
set(CMAKE_C_FLAGS "-ggdb ${CPU} -Wall -Werror -gdwarf-2" CACHE STRING "" FORCE)
set(CMAKE_ASM_FLAGS "-ggdb ${CPU} -gdwarf-2" CACHE STRING "" FORCE)

# set linker flags
set(CMAKE_EXE_LINKER_FLAGS "-T ${LINKER_SCRIPT} -Wl,-Map,${TARGET}.map -nostartfiles" CACHE STRING "" FORCE)


project(Slegro)

enable_language(C ASM)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/include ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/external/include)

file(GLOB SLEGRO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.s ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB DRV_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/*.c)
file(GLOB EXT_DRV_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/external/*.c)

add_executable(${TARGET} ${SLEGRO_SRC} ${DRV_SRC} ${EXT_DRV_SRC})
add_custom_command(TARGET ${TARGET} POST_BUILD COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex ${TARGET} ${TARGET}.hex)