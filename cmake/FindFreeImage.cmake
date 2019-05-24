find_path(FreeImage_INCLUDE_DIR FreeImage.h)

set(freeimage_names ${FreeImage_NAMES} freeimage libfreeimage)
#foreach(name ${freeimage_names})
  #list(APPEND jpeg_names_debug "${name}d")
#endforeach()

if(NOT FreeImage_LIBRARY)
    find_library(FreeImage_LIBRARY_RELEASE NAMES ${freeimage_names})
  include(${CMAKE_CURRENT_LIST_DIR}/SelectLibraryConfigurations.cmake)
  select_library_configurations(JPEG)
  mark_as_advanced(JPEG_LIBRARY_RELEASE JPEG_LIBRARY_DEBUG)
endif()
unset(jpeg_names)
unset(jpeg_names_debug)

if(JPEG_INCLUDE_DIR AND EXISTS "${JPEG_INCLUDE_DIR}/jpeglib.h")
  file(STRINGS "${JPEG_INCLUDE_DIR}/jpeglib.h"
    jpeg_lib_version REGEX "^#define[\t ]+JPEG_LIB_VERSION[\t ]+.*")

  if (NOT jpeg_lib_version)
    # libjpeg-turbo sticks JPEG_LIB_VERSION in jconfig.h
    find_path(jconfig_dir jconfig.h)
    if (jconfig_dir)
      file(STRINGS "${jconfig_dir}/jconfig.h"
        jpeg_lib_version REGEX "^#define[\t ]+JPEG_LIB_VERSION[\t ]+.*")
    endif()
    unset(jconfig_dir)
  endif()

  string(REGEX REPLACE "^#define[\t ]+JPEG_LIB_VERSION[\t ]+([0-9]+).*"
    "\\1" JPEG_VERSION "${jpeg_lib_version}")
  unset(jpeg_lib_version)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(JPEG
  REQUIRED_VARS JPEG_LIBRARY JPEG_INCLUDE_DIR
  VERSION_VAR JPEG_VERSION)

if(JPEG_FOUND)
  set(JPEG_LIBRARIES ${JPEG_LIBRARY})
  set(JPEG_INCLUDE_DIRS "${JPEG_INCLUDE_DIR}")

  if(NOT TARGET JPEG::JPEG)
    add_library(JPEG::JPEG UNKNOWN IMPORTED)
    if(JPEG_INCLUDE_DIRS)
      set_target_properties(JPEG::JPEG PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${JPEG_INCLUDE_DIRS}")
    endif()
    if(EXISTS "${JPEG_LIBRARY}")
      set_target_properties(JPEG::JPEG PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${JPEG_LIBRARY}")
    endif()
    if(EXISTS "${JPEG_LIBRARY_RELEASE}")
      set_property(TARGET JPEG::JPEG APPEND PROPERTY
        IMPORTED_CONFIGURATIONS RELEASE)
      set_target_properties(JPEG::JPEG PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
        IMPORTED_LOCATION_RELEASE "${JPEG_LIBRARY_RELEASE}")
    endif()
    if(EXISTS "${JPEG_LIBRARY_DEBUG}")
      set_property(TARGET JPEG::JPEG APPEND PROPERTY
        IMPORTED_CONFIGURATIONS DEBUG)
      set_target_properties(JPEG::JPEG PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
        IMPORTED_LOCATION_DEBUG "${JPEG_LIBRARY_DEBUG}")
    endif()
  endif()
endif()

mark_as_advanced(JPEG_LIBRARY JPEG_INCLUDE_DIR)
