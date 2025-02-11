cmake_minimum_required(VERSION 3.15)
project(AUv3Lab VERSION 1.0 LANGUAGES CXX OBJCXX)

set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13")

set(SRC_ROOT "${CMAKE_SOURCE_DIR}/src")

file(GLOB_RECURSE SOURCES
    ${SRC_ROOT}/*.c*
    ${SRC_ROOT}/*.h*
    ${SRC_ROOT}/*.m*
    ${SRC_ROOT}/*.exp
)

add_executable(AUv3Lab MODULE ${SOURCES})

target_sources(AUv3Lab PRIVATE ${CMAKE_SOURCE_DIR}/build-resources/Info.plist)

set_target_properties(AUv3Lab PROPERTIES
    BUNDLE TRUE
    BUNDLE_EXTENSION "appex"
    XCODE_ATTRIBUTE_WRAPPER_EXTENSION "appex"
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "nl.izmar.AUv3Lab"
    XCODE_PRODUCT_TYPE com.apple.product-type.app-extension
    #XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Apple Development"
    XCODE_ATTRIBUTE_CODE_SIGN_STYLE "Automatic"
    #XCODE_ATTRIBUTE_DEVELOPMENT_TEAM ""
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/build-resources/Info.plist
    XCODE_ATTRIBUTE_ENABLE_HARDENED_RUNTIME "YES"
    XCODE_ATTRIBUTE_APPLICATION_EXTENSION_API_ONLY NO
    CODE_ATTRIBUTE_OTHER_LDFLAGS "-framework AudioUnit -framework CoreAudio -framework AppKit"
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_include_directories(AUv3Lab PRIVATE ${SRC_ROOT})

target_compile_definitions(AUv3Lab PRIVATE
    AU_COMPILING_AUBASE=1
    TARGET_API_MAC_CARBON=1
    AUDIOUNIT_SDK=1
)

configure_file(
    ${CMAKE_SOURCE_DIR}/build-resources/Info.plist
    ${CMAKE_BINARY_DIR}/AUv3Lab.component/Contents/Info.plist
    COPYONLY
)

add_custom_command(TARGET AUv3Lab POST_BUILD
    COMMAND /bin/echo -n "BNDL????" > "${CMAKE_BINARY_DIR}/$<CONFIG>/AUv3Lab.component/Contents/PkgInfo"
    COMMAND /bin/cp -R "${CMAKE_BINARY_DIR}/$<CONFIG>/AUv3Lab.component" "$ENV{HOME}/Library/Audio/Plug-Ins/Components/"
    COMMENT "Deploying AUv3Lab.component to ~/Library/Audio/Plug-Ins/Components"
)

