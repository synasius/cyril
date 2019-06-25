cmake_minimum_required(VERSION 3.1...3.14)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

project(Cyril VERSION 1.0
              DESCRIPTION "Cyril Live Visuals"
              LANGUAGES CXX)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/install-root" CACHE PATH "..." FORCE)
endif()

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(OF_DIRECTORY "openFrameworks" CACHE STRING "OpenFrameworks")

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
BISON_TARGET(CyrilParser ${CMAKE_SOURCE_DIR}/src/Cyril/cyril.ypp ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
        COMPILE_FLAGS --defines=${CMAKE_CURRENT_BINARY_DIR}/y.tab.h)
FLEX_TARGET(CyrilScanner ${CMAKE_SOURCE_DIR}/src/Cyril/cyril.lpp  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(CyrilScanner CyrilParser)

# cyril executable
add_executable(cyril
    src/main.cpp
    src/cyrilApp.h
    src/cyrilApp.cpp
    src/Cyril/CyrilBloom.cpp
    src/Cyril/CyrilBloom.h
    src/Cyril/Cyril.cpp
    src/Cyril/Cyril.h
    src/Cyril/CyrilOp.cpp
    src/Cyril/CyrilOp.h
    src/Cyril/CyrilParser.cpp
    src/Cyril/CyrilParser.h
    src/Cyril/CyrilPixelate.cpp
    src/Cyril/CyrilPixelate.h
    src/Cyril/CyrilState.cpp
    src/Cyril/CyrilState.h
    src/Cyril/Funs/CyrilCosFun.cpp
    src/Cyril/Funs/CyrilCosFun.h
    src/Cyril/Funs/CyrilFftFun.cpp
    src/Cyril/Funs/CyrilFftFun.h
    src/Cyril/Funs/CyrilFun.cpp
    src/Cyril/Funs/CyrilFun.h
    src/Cyril/Funs/CyrilHsbFun.cpp
    src/Cyril/Funs/CyrilHsbFun.h
    src/Cyril/Funs/CyrilLerpFun.cpp
    src/Cyril/Funs/CyrilLerpFun.h
    src/Cyril/Funs/CyrilMapFun.cpp
    src/Cyril/Funs/CyrilMapFun.h
    src/Cyril/Funs/CyrilNoiseFun.cpp
    src/Cyril/Funs/CyrilNoiseFun.h
    src/Cyril/Funs/CyrilPaletteFun.cpp
    src/Cyril/Funs/CyrilPaletteFun.h
    src/Cyril/Funs/CyrilRandFun.cpp
    src/Cyril/Funs/CyrilRandFun.h
    src/Cyril/Funs/CyrilSinFun.cpp
    src/Cyril/Funs/CyrilSinFun.h
    src/Cyril/Funs/CyrilTanFun.cpp
    src/Cyril/Funs/CyrilTanFun.h
    src/Cyril/Funs/CyrilWaveFun.cpp
    src/Cyril/Funs/CyrilWaveFun.h
    src/Cyril/Lang/CyrilAssign.h
    src/Cyril/Lang/CyrilColorLoad.cpp
    src/Cyril/Lang/CyrilColorLoad.h
    src/Cyril/Lang/CyrilDebugOp.cpp
    src/Cyril/Lang/CyrilDebugOp.h
    src/Cyril/Lang/CyrilDo.h
    src/Cyril/Lang/CyrilFor.cpp
    src/Cyril/Lang/CyrilFor.h
    src/Cyril/Lang/CyrilHexColor.h
    src/Cyril/Lang/CyrilIf.h
    src/Cyril/Lang/CyrilList.h
    src/Cyril/Lang/CyrilLoad.h
    src/Cyril/Lang/CyrilLoad.cpp
    src/Cyril/Lang/CyrilNamedColor.h
    src/Cyril/Lang/CyrilPush.h
    src/Cyril/Lang/CyrilUnaryOp.h
    src/Cyril/Lang/CyrilWhile.h
    src/Cyril/Ops/CyrilAnimation.cpp
    src/Cyril/Ops/CyrilAnimation.h
    src/Cyril/Ops/CyrilAnimStep.cpp
    src/Cyril/Ops/CyrilAnimStep.h
    src/Cyril/Ops/CyrilBackgroundOp.cpp
    src/Cyril/Ops/CyrilBackgroundOp.h
    src/Cyril/Ops/CyrilBallDetailOp.cpp
    src/Cyril/Ops/CyrilBallDetailOp.h
    src/Cyril/Ops/CyrilBallOp.cpp
    src/Cyril/Ops/CyrilBallOp.h
    src/Cyril/Ops/CyrilBinaryOp.h
    src/Cyril/Ops/CyrilBlink.cpp
    src/Cyril/Ops/CyrilBlink.h
    src/Cyril/Ops/CyrilBoxOp.cpp
    src/Cyril/Ops/CyrilBoxOp.h
    src/Cyril/Ops/CyrilColorOp.cpp
    src/Cyril/Ops/CyrilColorOp.h
    src/Cyril/Ops/CyrilConeOp.cpp
    src/Cyril/Ops/CyrilConeOp.h
    src/Cyril/Ops/CyrilDie.h
    src/Cyril/Ops/CyrilFillOp.cpp
    src/Cyril/Ops/CyrilFillOp.h
    src/Cyril/Ops/CyrilGridOp.cpp
    src/Cyril/Ops/CyrilGridOp.h
    src/Cyril/Ops/CyrilImgOp.cpp
    src/Cyril/Ops/CyrilImgOp.h
    src/Cyril/Ops/CyrilInitOp.cpp
    src/Cyril/Ops/CyrilInitOp.h
    src/Cyril/Ops/CyrilKaleidoscope.cpp
    src/Cyril/Ops/CyrilKaleidoscope.h
    src/Cyril/Ops/CyrilLightOp.cpp
    src/Cyril/Ops/CyrilLightOp.h
    src/Cyril/Ops/CyrilLineOp.cpp
    src/Cyril/Ops/CyrilLineOp.h
    src/Cyril/Ops/CyrilMoveOp.cpp
    src/Cyril/Ops/CyrilMoveOp.h
    src/Cyril/Ops/CyrilNoFillOp.cpp
    src/Cyril/Ops/CyrilNoFillOp.h
    src/Cyril/Ops/CyrilNoiseWarp.cpp
    src/Cyril/Ops/CyrilNoiseWarp.h
    src/Cyril/Ops/CyrilPalette.cpp
    src/Cyril/Ops/CyrilPalette.h
    src/Cyril/Ops/CyrilPaletteItem.cpp
    src/Cyril/Ops/CyrilPaletteItem.h
    src/Cyril/Ops/CyrilParticle.cpp
    src/Cyril/Ops/CyrilParticle.h
    src/Cyril/Ops/CyrilPegOp.cpp
    src/Cyril/Ops/CyrilPegOp.h
    src/Cyril/Ops/CyrilPopMatrixOp.cpp
    src/Cyril/Ops/CyrilPopMatrixOp.h
    src/Cyril/Ops/CyrilPushMatrixOp.cpp
    src/Cyril/Ops/CyrilPushMatrixOp.h
    src/Cyril/Ops/CyrilRectOp.cpp
    src/Cyril/Ops/CyrilRectOp.h
    src/Cyril/Ops/CyrilRotateOp.cpp
    src/Cyril/Ops/CyrilRotateOp.h
    src/Cyril/Ops/CyrilScaleOp.cpp
    src/Cyril/Ops/CyrilScaleOp.h
    src/Cyril/Ops/CyrilShape.cpp
    src/Cyril/Ops/CyrilShape.h
    src/Cyril/Ops/CyrilShapeList.cpp
    src/Cyril/Ops/CyrilShapeList.h
    src/Cyril/Ops/CyrilSphereDetailOp.cpp
    src/Cyril/Ops/CyrilSphereDetailOp.h
    src/Cyril/Ops/CyrilSphereOp.cpp
    src/Cyril/Ops/CyrilSphereOp.h
    src/Cyril/Ops/CyrilTile.cpp
    src/Cyril/Ops/CyrilTile.h
    src/Engine/Palette.cpp
    src/Engine/Palette.h
    src/Engine/Particle.cpp
    src/Engine/Particle.h
    ${BISON_CyrilParser_OUTPUTS} ${FLEX_CyrilScanner_OUTPUTS}
    # ofxPostProcessing
    addons/ofxPostProcessing/src/BleachBypassPass.cpp
    addons/ofxPostProcessing/src/BleachBypassPass.h
    addons/ofxPostProcessing/src/BloomPass.cpp
    addons/ofxPostProcessing/src/BloomPass.h
    addons/ofxPostProcessing/src/ContrastPass.cpp
    addons/ofxPostProcessing/src/ContrastPass.h
    addons/ofxPostProcessing/src/ConvolutionPass.cpp
    addons/ofxPostProcessing/src/ConvolutionPass.h
    addons/ofxPostProcessing/src/DofAltPass.cpp
    addons/ofxPostProcessing/src/DofAltPass.h
    addons/ofxPostProcessing/src/DofPass.cpp
    addons/ofxPostProcessing/src/DofPass.h
    addons/ofxPostProcessing/src/EdgePass.cpp
    addons/ofxPostProcessing/src/EdgePass.h
    addons/ofxPostProcessing/src/FakeSSSPass.cpp
    addons/ofxPostProcessing/src/FakeSSSPass.h
    addons/ofxPostProcessing/src/FxaaPass.cpp
    addons/ofxPostProcessing/src/FxaaPass.h
    addons/ofxPostProcessing/src/GodRaysPass.cpp
    addons/ofxPostProcessing/src/GodRaysPass.h
    addons/ofxPostProcessing/src/HorizontalTiltShifPass.cpp
    addons/ofxPostProcessing/src/HorizontalTiltShifPass.h
    addons/ofxPostProcessing/src/HsbShiftPass.cpp
    addons/ofxPostProcessing/src/HsbShiftPass.h
    addons/ofxPostProcessing/src/KaleidoscopePass.cpp
    addons/ofxPostProcessing/src/KaleidoscopePass.h
    addons/ofxPostProcessing/src/LimbDarkeningPass.cpp
    addons/ofxPostProcessing/src/LimbDarkeningPass.h
    addons/ofxPostProcessing/src/LUTPass.cpp
    addons/ofxPostProcessing/src/LUTPass.h
    addons/ofxPostProcessing/src/NoiseWarpPass.cpp
    addons/ofxPostProcessing/src/NoiseWarpPass.h
    addons/ofxPostProcessing/src/ofxPostProcessing.h
    addons/ofxPostProcessing/src/PixelatePass.cpp
    addons/ofxPostProcessing/src/PixelatePass.h
    addons/ofxPostProcessing/src/PostProcessing.cpp
    addons/ofxPostProcessing/src/PostProcessing.h
    addons/ofxPostProcessing/src/RenderPass.cpp
    addons/ofxPostProcessing/src/RenderPass.h
    addons/ofxPostProcessing/src/RGBShiftPass.cpp
    addons/ofxPostProcessing/src/RGBShiftPass.h
    addons/ofxPostProcessing/src/RimHighlightingPass.cpp
    addons/ofxPostProcessing/src/RimHighlightingPass.h
    addons/ofxPostProcessing/src/SSAOPass.cpp
    addons/ofxPostProcessing/src/SSAOPass.h
    addons/ofxPostProcessing/src/ToonPass.cpp
    addons/ofxPostProcessing/src/ToonPass.h
    addons/ofxPostProcessing/src/VerticalTiltShifPass.cpp
    addons/ofxPostProcessing/src/VerticalTiltShifPass.h
    addons/ofxPostProcessing/src/ZoomBlurPass.cpp
    addons/ofxPostProcessing/src/ZoomBlurPass.h
    # ofxBeat
    addons/ofxBeat/src/fft.cpp
    addons/ofxBeat/src/fft.h
    addons/ofxBeat/src/ofxBeat.cpp
    addons/ofxBeat/src/ofxBeat.h
    # ofxEditor
    addons/ofxEditor/src/ClipBoard.cpp
    addons/ofxEditor/src/ClipBoard.h
    addons/ofxEditor/src/EditorBuffer.cpp
    addons/ofxEditor/src/EditorBuffer.h
    addons/ofxEditor/src/ofxEditor.cpp
    addons/ofxEditor/src/ofxEditor.h
)

target_compile_features(cyril PRIVATE cxx_std_17)
target_compile_options(cyril PRIVATE -Wall)
target_compile_options(cyril PRIVATE -Wextra)
target_compile_options(cyril PRIVATE -Wzero-as-null-pointer-constant)
target_compile_options(cyril PRIVATE -Wsuggest-override)

target_include_directories(cyril PUBLIC include)
target_include_directories(cyril PRIVATE src/Cyril)
target_include_directories(cyril PRIVATE src/Cyril/Funs)
target_include_directories(cyril PRIVATE src/Cyril/Ops)
target_include_directories(cyril PRIVATE src/Cyril/Lang)
target_include_directories(cyril PRIVATE src/Engine)

# Addons
# TODO: move to separate targets
target_include_directories(cyril PRIVATE addons/ofxBeat/src)
target_include_directories(cyril PRIVATE addons/ofxEditor/src)
target_include_directories(cyril PRIVATE addons/ofxPostProcessing/src)

# this include is necessary because of bison
target_include_directories(cyril PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# TODO: move to separate target
target_link_libraries(cyril PRIVATE ${OF_DIRECTORY}/libs/openFrameworksCompiled/lib/linux64/libopenFrameworks.a)
target_include_directories(cyril SYSTEM PRIVATE ${OF_DIRECTORY}/libs/openFrameworks/)
target_include_directories(cyril SYSTEM PRIVATE ${OF_DIRECTORY}/libs/openFrameworks/3d)
target_include_directories(cyril SYSTEM PRIVATE ${OF_DIRECTORY}/libs/openFrameworks/app)
target_include_directories(cyril SYSTEM PRIVATE ${OF_DIRECTORY}/libs/openFrameworks/communication)
target_include_directories(cyril SYSTEM PRIVATE ${OF_DIRECTORY}/libs/openFrameworks/events)
target_include_directories(cyril SYSTEM PRIVATE ${OF_DIRECTORY}/libs/openFrameworks/gl)
target_include_directories(cyril SYSTEM PRIVATE ${OF_DIRECTORY}/libs/openFrameworks/graphics)
target_include_directories(cyril SYSTEM PRIVATE ${OF_DIRECTORY}/libs/openFrameworks/math)
target_include_directories(cyril SYSTEM PRIVATE ${OF_DIRECTORY}/libs/openFrameworks/sound)
target_include_directories(cyril SYSTEM PRIVATE ${OF_DIRECTORY}/libs/openFrameworks/types)
target_include_directories(cyril SYSTEM PRIVATE ${OF_DIRECTORY}/libs/openFrameworks/utils)
target_include_directories(cyril SYSTEM PRIVATE ${OF_DIRECTORY}/libs/openFrameworks/video)

find_package(PkgConfig REQUIRED)

# cairo library
pkg_check_modules(Cairo REQUIRED IMPORTED_TARGET cairo)
target_include_directories(cyril PRIVATE PkgConfig::Cairo)
target_link_libraries(cyril PRIVATE PkgConfig::Cairo)

# GStreamer
pkg_check_modules(GST REQUIRED IMPORTED_TARGET gstreamer-1.0 gstreamer-app-1.0 gstreamer-video-1.0)
target_include_directories(cyril PRIVATE PkgConfig::GST)
target_link_libraries(cyril PRIVATE PkgConfig::GST)

# Threading libs
find_package(Threads REQUIRED)
target_link_libraries(cyril PRIVATE Threads::Threads)

# FontConfig
pkg_check_modules(FontConfig REQUIRED IMPORTED_TARGET fontconfig)
target_include_directories(cyril PRIVATE PkgConfig::FontConfig)
target_link_libraries(cyril PRIVATE PkgConfig::FontConfig)

# X11 libs
find_package(X11 REQUIRED)
target_link_libraries(cyril PRIVATE ${X11_LIBRARIES})

# OpenAL
pkg_check_modules(OpenAL REQUIRED IMPORTED_TARGET openal)
target_link_libraries(cyril PRIVATE PkgConfig::OpenAL)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(cyril PRIVATE OpenGL::OpenGL)

# GLEW
find_package(GLEW REQUIRED)
target_link_libraries(cyril PRIVATE GLEW::GLEW)

# Curl
find_package(CURL REQUIRED)
target_link_libraries(cyril PRIVATE CURL::libcurl)

# Boost
find_package(Boost REQUIRED COMPONENTS filesystem)
target_link_libraries(cyril PRIVATE Boost::filesystem)

# uriparser
pkg_check_modules(UriParser REQUIRED IMPORTED_TARGET liburiparser)
target_link_libraries(cyril PRIVATE PkgConfig::UriParser)

# FreeImage
find_package(FreeImage REQUIRED)
target_link_libraries(cyril PRIVATE FreeImage::FreeImage)

# GLFW
pkg_check_modules(GLFW REQUIRED IMPORTED_TARGET glfw3)
target_link_libraries(cyril PRIVATE PkgConfig::GLFW)

# Freetype
# TODO: maybe this lib is not necessary
find_package(Freetype REQUIRED)
target_link_libraries(cyril PRIVATE Freetype::Freetype)

# Poco
find_package(Poco REQUIRED COMPONENTS Foundation)
target_link_libraries(cyril PRIVATE Poco::Foundation)

# libsndfile
pkg_check_modules(SndFile REQUIRED IMPORTED_TARGET sndfile)
target_link_libraries(cyril PRIVATE PkgConfig::SndFile)

# RtAudio
pkg_check_modules(RtAudio REQUIRED IMPORTED_TARGET rtaudio)
target_link_libraries(cyril PRIVATE PkgConfig::RtAudio)

# Lib mpg123
pkg_check_modules(mpg123 REQUIRED IMPORTED_TARGET libmpg123)
target_link_libraries(cyril PRIVATE PkgConfig::mpg123)

# TODO: these are from OF  should use Find*.cmake

# tess2
target_include_directories(cyril PRIVATE ${OF_DIRECTORY}/libs/tess2/include)
target_link_libraries(cyril PRIVATE ${OF_DIRECTORY}/libs/tess2/lib/linux64/libtess2.a)

target_include_directories(cyril PRIVATE ${OF_DIRECTORY}/libs/utf8/include)
target_include_directories(cyril PRIVATE ${OF_DIRECTORY}/libs/glm/include)
target_include_directories(cyril PRIVATE ${OF_DIRECTORY}/libs/json/include)

# kiss
target_include_directories(cyril PRIVATE ${OF_DIRECTORY}/libs/kiss/include)
target_link_libraries(cyril PRIVATE ${OF_DIRECTORY}/libs/kiss/lib/linux64/libkiss.a)

install(TARGETS cyril RUNTIME DESTINATION .)
install(FILES DroidSansMono.ttf DESTINATION resources)
install(FILES SourceCodePro.ttf DESTINATION resources)
