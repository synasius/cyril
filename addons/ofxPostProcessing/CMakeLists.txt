cmake_minimum_required(VERSION 3.1...3.14)

project(ofxPostProcessing VERSION 1.0
                          DESCRIPTION "Cyril Live Visuals"
                          LANGUAGES CXX)

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

add_library(ofxPostProcessing STATIC
    src/BleachBypassPass.cpp
    src/BleachBypassPass.h
    src/BloomPass.cpp
    src/BloomPass.h
    src/ContrastPass.cpp
    src/ContrastPass.h
    src/ConvolutionPass.cpp
    src/ConvolutionPass.h
    src/DofAltPass.cpp
    src/DofAltPass.h
    src/DofPass.cpp
    src/DofPass.h
    src/EdgePass.cpp
    src/EdgePass.h
    src/FakeSSSPass.cpp
    src/FakeSSSPass.h
    src/FxaaPass.cpp
    src/FxaaPass.h
    src/GodRaysPass.cpp
    src/GodRaysPass.h
    src/HorizontalTiltShifPass.cpp
    src/HorizontalTiltShifPass.h
    src/HsbShiftPass.cpp
    src/HsbShiftPass.h
    src/KaleidoscopePass.cpp
    src/KaleidoscopePass.h
    src/LimbDarkeningPass.cpp
    src/LimbDarkeningPass.h
    src/LUTPass.cpp
    src/LUTPass.h
    src/NoiseWarpPass.cpp
    src/NoiseWarpPass.h
    src/ofxPostProcessing.h
    src/PixelatePass.cpp
    src/PixelatePass.h
    src/PostProcessing.cpp
    src/PostProcessing.h
    src/RenderPass.cpp
    src/RenderPass.h
    src/RGBShiftPass.cpp
    src/RGBShiftPass.h
    src/RimHighlightingPass.cpp
    src/RimHighlightingPass.h
    src/SSAOPass.cpp
    src/SSAOPass.h
    src/ToonPass.cpp
    src/ToonPass.h
    src/VerticalTiltShifPass.cpp
    src/VerticalTiltShifPass.h
    src/ZoomBlurPass.cpp
    src/ZoomBlurPass.h
)

target_include_directories(ofxPostProcessing PUBLIC src)

