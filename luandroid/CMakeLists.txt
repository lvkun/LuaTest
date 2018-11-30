# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
set(CMAKE_CXX_FLAGS "-fPIC")
set(CMAKE_C_FLAGS "-fPIC")

if("${ANDROID_ABI}" MATCHES "armeabi-v7a")
    include_directories("${ANDROID_SYSROOT}/usr/include/arm-linux-androideabi")
else()
    include_directories("${ANDROID_SYSROOT}/usr/include/x86_64-linux-android")
endif()

SET(LIB_SRC
    src/main/cpp/lua/src/lcorolib.c
    src/main/cpp/lua/src/lutf8lib.c
    src/main/cpp/lua/src/lapi.c
    src/main/cpp/lua/src/lcode.c
    src/main/cpp/lua/src/lctype.c
    src/main/cpp/lua/src/ldebug.c
    src/main/cpp/lua/src/ldo.c
    src/main/cpp/lua/src/ldump.c
    src/main/cpp/lua/src/lfunc.c
    src/main/cpp/lua/src/lgc.c
    src/main/cpp/lua/src/llex.c
    src/main/cpp/lua/src/lmem.c
    src/main/cpp/lua/src/lobject.c
    src/main/cpp/lua/src/lopcodes.c
    src/main/cpp/lua/src/lparser.c
    src/main/cpp/lua/src/lstate.c
    src/main/cpp/lua/src/lstring.c
    src/main/cpp/lua/src/ltable.c
    src/main/cpp/lua/src/ltm.c
    src/main/cpp/lua/src/lundump.c
    src/main/cpp/lua/src/lvm.c
    src/main/cpp/lua/src/lzio.c
    src/main/cpp/lua/src/lauxlib.c
    src/main/cpp/lua/src/lbaselib.c
    src/main/cpp/lua/src/ldblib.c
    src/main/cpp/lua/src/liolib.c
    src/main/cpp/lua/src/lmathlib.c
    src/main/cpp/lua/src/loslib.c
    src/main/cpp/lua/src/ltablib.c
    src/main/cpp/lua/src/lstrlib.c
    src/main/cpp/lua/src/loadlib.c
    src/main/cpp/lua/src/linit.c)

include_directories( src/main/cpp/lua/src/ )

add_library( # Sets the name of the library.
             luandroid

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/LuaState.cpp
             src/main/cpp/Utils.cpp

             ${LIB_SRC})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       luandroid

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib})