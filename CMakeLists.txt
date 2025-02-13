cmake_minimum_required(VERSION 3.15)
project(AUv3Lab VERSION 1.0 LANGUAGES CXX OBJCXX)

set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13")

set(SRC_ROOT_APP "${CMAKE_SOURCE_DIR}/src/app")
set(SRC_ROOT_EXT "${CMAKE_SOURCE_DIR}/src/extension")

set(AUv3Lab_SOURCES
    ${SRC_ROOT_EXT}/AudioUnitViewController.h
    ${SRC_ROOT_EXT}/AudioUnitViewController.m
    ${SRC_ROOT_EXT}/Base.lproj/AudioUnitViewController.xib
    ${SRC_ROOT_EXT}/MyAudioUnit.h
    ${SRC_ROOT_EXT}/MyAudioUnit.m
)

source_group("src" FILES ${AUv3Lab_SOURCES})

add_library(AUv3Lab MODULE ${AUv3Lab_SOURCES})

set_source_files_properties(${SRC_ROOT_EXT}/Base.lproj/AudioUnitViewController.xib MACOSX_PACKAGE_LOCATION "Resources")

set_target_properties(AUv3Lab PROPERTIES
    XCODE_ATTRIBUTE_ORGANIZE_IN_GROUPS "NO"
    XCODE_FILE_GROUP "src"
)

set(AUv3LabApp_SOURCES
    ${SRC_ROOT_APP}/AppDelegate.h
    ${SRC_ROOT_APP}/AppDelegate.m
    ${SRC_ROOT_APP}/Base.lproj/MainMenu.xib
    ${SRC_ROOT_APP}/main.m
)

source_group("src" FILES ${AUv3LabApp_SOURCES})

add_executable(AUv3LabApp MACOSX_BUNDLE ${AUv3LabApp_SOURCES})

set_source_files_properties(${SRC_ROOT_APP}/Base.lproj/MainMenu.xib MACOSX_PACKAGE_LOCATION "Resources")

target_sources(AUv3Lab PRIVATE ${SRC_ROOT_EXT}/Info.plist)

target_sources(AUv3LabApp PRIVATE ${SRC_ROOT_APP}/Info.plist)

set_target_properties(AUv3Lab PROPERTIES
    BUNDLE TRUE
    BUNDLE_EXTENSION "appex"
    XCODE_ATTRIBUTE_WRAPPER_EXTENSION "appex"
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "nl.izmar.AUv3Lab"
    XCODE_PRODUCT_TYPE com.apple.product-type.app-extension
    XCODE_ATTRIBUTE_CODE_SIGN_STYLE "Automatic"
    MACOSX_BUNDLE_INFO_PLIST ${SRC_ROOT_EXT}/Info.plist
    XCODE_ATTRIBUTE_APPLICATION_EXTENSION_API_ONLY "YES"
    XCODE_ATTRIBUTE_OTHER_LDFLAGS "-framework AudioToolbox -framework AVFoundation -framework CoreAudio -framework AppKit -framework CoreAudioKit"
    XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS "${SRC_ROOT_EXT}/extension.entitlements"
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

set_target_properties(AUv3LabApp PROPERTIES
    BUNDLE TRUE
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "nl.izmar.AUv3LabApp"
    XCODE_ATTRIBUTE_CODE_SIGN_STYLE "Automatic"
    XCODE_ATTRIBUTE_OTHER_CODE_SIGN_FLAGS "--deep"
    XCODE_ATTRIBUTE_OTHER_LDFLAGS "-framework AudioToolbox -framework AVFoundation -framework CoreAudio -framework AppKit -framework CoreAudioKit"
    CXX_STANDARD 17
    XCODE_ATTRIBUTE_APPLICATION_EXTENSION_API_ONLY "YES"
    XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC "YES"
    XCODE_PRODUCT_TYPE com.apple.product-type.application
    MACOSX_BUNDLE_INFO_PLIST ${SRC_ROOT_APP}/Info.plist
)

target_include_directories(AUv3Lab PRIVATE ${SRC_ROOT})
target_include_directories(AUv3LabApp PRIVATE ${SRC_ROOT})

add_dependencies(AUv3LabApp AUv3Lab)

target_compile_definitions(AUv3Lab PRIVATE
    AU_COMPILING_AUBASE=1
    TARGET_API_MAC_CARBON=1
    AUDIOUNIT_SDK=1
)

target_compile_definitions(AUv3LabApp PRIVATE
    AU_COMPILING_AUBASE=1
    TARGET_API_MAC_CARBON=1
    AUDIOUNIT_SDK=1
)

add_custom_command(TARGET AUv3LabApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/$<CONFIG>/AUv3LabApp.app/Contents/PlugIns
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_BINARY_DIR}/$<CONFIG>/AUv3Lab.appex
        ${CMAKE_BINARY_DIR}/$<CONFIG>/AUv3LabApp.app/Contents/PlugIns/AUv3Lab.appex
)

