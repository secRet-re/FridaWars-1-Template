cmake_minimum_required(VERSION 3.4.1)

set(can_use_assembler TRUE)
enable_language(ASM)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s")

#Set flags to detect arm32 bit or arm64 bit for switching between elf structures
if(${ANDROID_ABI} STREQUAL "armeabi-v7a" OR ${ANDROID_ABI} STREQUAL "x86")
    add_definitions("-D_32_BIT")
elseif(${ANDROID_ABI} STREQUAL "arm64-v8a" OR ${ANDROID_ABI} STREQUAL "x86_64")
    add_definitions("-D_64_BIT")
endif()

add_library( # Sets the name of the library.
        secret
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        secret.c)

find_library( # Sets the name of the path variable.
        log-lib
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log )

target_link_libraries( # Specifies the target library.
        secret
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib} )

add_custom_command( TARGET secret
        POST_BUILD
        COMMAND "${ANDROID_TOOLCHAIN_PREFIX}strip" -R .comment -g -S -d --strip-unneeded --strip-debug --verbose ${CMAKE_HOME_DIRECTORY}/../../../build/intermediates/cmake/debug/obj/${ANDROID_ABI}/libsecret.so
        COMMENT "Stripped native library")
