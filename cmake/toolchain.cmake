set(CMAKE_SYSTEM_NAME Linux)

if(WIN32)
    set(EXE_EXTENSION ".exe")
else()
    set(EXE_EXTENSION "")
endif()

set(C_COMPILER gcc)
set(CXX_COMPILER g++)
set(PREFIX "")

if("${TOOLCHAIN}" STREQUAL "clang")
    message("Clang toolchain specified")
    set(C_COMPILER clang)
    set(CXX_COMPILER clang++)
    set(PREFIX "llvm-")
endif()

set(CMAKE_ASM_COMPILER              /usr/bin/${C_COMPILER}${EXE_EXTENSION})
set(CMAKE_C_COMPILER                /usr/bin/${C_COMPILER}${EXE_EXTENSION})
set(CMAKE_CXX_COMPILER              /usr/bin/${CXX_COMPILER}${EXE_EXTENSION})
set(CMAKE_AR                        /usr/bin/${PREFIX}ar${EXE_EXTENSION})
set(CMAKE_OBJCOPY                   /usr/bin/${PREFIX}objcopy${EXE_EXTENSION} CACHE INTERNAL "")
set(CMAKE_RANLIB                    /usr/bin/${PREFIX}ranlib${EXE_EXTENSION} CACHE INTERNAL "")
set(CMAKE_SIZE_UTIL                 /usr/bin/${PREFIX}size${EXE_EXTENSION} CACHE INTERNAL "")
set(CMAKE_STRIP                     /usr/bin/${PREFIX}strip${EXE_EXTENSION} CACHE INTERNAL "")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)