cmake_minimum_required(VERSION 3.15)
project(AUv2Lab VERSION 1.0 LANGUAGES CXX OBJCXX)

set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13")

set(SRC_ROOT "${CMAKE_SOURCE_DIR}/src")

file(GLOB_RECURSE SOURCES
    ${SRC_ROOT}/*.c*
    ${SRC_ROOT}/*.h*
    ${SRC_ROOT}/*.m*
    ${SRC_ROOT}/*.exp
)

add_library(AUv2Lab MODULE ${SOURCES})

set_target_properties(AUv2Lab PROPERTIES
    BUNDLE TRUE
    BUNDLE_EXTENSION "component"
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
    XCODE_ATTRIBUTE_ENABLE_HARDENED_RUNTIME "YES"
    XCODE_ATTRIBUTE_OTHER_LDFLAGS "-framework AudioUnit -framework CoreAudio -framework AppKit"
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_include_directories(AUv2Lab PRIVATE ${SRC_ROOT})

target_compile_definitions(AUv2Lab PRIVATE
    AU_COMPILING_AUBASE=1
    TARGET_API_MAC_CARBON=1
    AUDIOUNIT_SDK=1
)

configure_file(
    ${CMAKE_SOURCE_DIR}/build-resources/Info.plist
    ${CMAKE_BINARY_DIR}/AUv2Lab.component/Contents/Info.plist
    COPYONLY
)

add_custom_command(TARGET AUv2Lab POST_BUILD
    COMMAND "/bin/cp" -R "${CMAKE_BINARY_DIR}/$<CONFIG>/AUv2Lab.component" "$ENV{HOME}/Library/Audio/Plug-Ins/Components/"
    COMMENT "Deploying AUv2Lab.component to ~/Library/Audio/Plug-Ins/Components"
)
