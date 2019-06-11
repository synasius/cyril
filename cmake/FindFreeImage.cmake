find_path(FreeImage_INCLUDE_DIR NAMES FreeImage.h)
mark_as_advanced(FreeImage_INCLUDE_DIR)

if(NOT FreeImage_LIBRARY)
  # Look for the library
  find_library(FreeImage_LIBRARY_RELEASE NAMES
      freeimage
      libfreeimage
  )
  mark_as_advanced(FreeImage_LIBRARY_RELEASE)

  find_library(FreeImage_LIBRARY_DEBUG NAMES
      freeimaged
      libfreeimaged
  )
  mark_as_advanced(FreeImage_LIBRARY_DEBUG)

  include(SelectLibraryConfigurations)
  select_library_configurations(FreeImage)
endif()

if(FreeImage_INCLUDE_DIR AND EXISTS "${FreeImage_INCLUDE_DIR}/FreeImage.h")
  file(STRINGS "${FreeImage_INCLUDE_DIR}/FreeImage.h" freeimage_major_version_str REGEX "^#define[\t ]+FREEIMAGE_MAJOR_VERSION[\t ]+\".*\"")
  file(STRINGS "${FreeImage_INCLUDE_DIR}/FreeImage.h" freeimage_minor_version_str REGEX "^#define[\t ]+FREEIMAGE_MINOR_VERSION[\t ]+\".*\"")
  file(STRINGS "${FreeImage_INCLUDE_DIR}/FreeImage.h" freeimage_release_serial_str REGEX "^#define[\t ]+FREEIMAGE_RELEASE_SERIAL[\t ]+\".*\"")

  string(REGEX REPLACE "^#define[\t ]+FREEIMAGE_MAJOR_VERSION[\t ]+\"([^\"]*)\".*" "\\1" FreeImage_VERSION_MAJOR "${freeimage_major_version_str}")
  string(REGEX REPLACE "^#define[\t ]+FREEIMAGE_MINOR_VERSION[\t ]+\"([^\"]*)\".*" "\\1" FreeImage_VERSION_MINOR "${freeimage_minor_version_str}")
  string(REGEX REPLACE "^#define[\t ]+FREEIMAGE_RELEASE_SERIAL[\t ]+\"([^\"]*)\".*" "\\1" FreeImage_RELEASE_SERIAL "${freeimage_release_serial_str}")
  set(FreeImage_VERSION_STRING ${FreeImage_VERSION_MAJOR}.${FreeImage_VERSION_MINOR}.${FreeImage_RELEASE_SERIAL})

  unset(freeimage_major_version_str)
  unset(freeimage_minor_version_str)
  unset(freeimage_release_serial_str)
  unset(FreeImage_VERSION_MAJOR)
  unset(FreeImage_VERSION_MINOR)
  unset(FreeImage_RELEASE_SERIAL)
endif()

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
    FreeImage
    REQUIRED_VARS FreeImage_LIBRARY FreeImage_INCLUDE_DIR
    VERSION_VAR FreeImage_VERSION_STRING)

if(FreeImage_FOUND)
  set(FreeImage_LIBRARIES ${FreeImage_LIBRARY})
  set(FreeImage_INCLUDE_DIRS ${FreeImage_INCLUDE_DIR})

  if(NOT TARGET FreeImage::FreeImage)
    add_library(FreeImage::FreeImage UNKNOWN IMPORTED)
    set_target_properties(FreeImage::FreeImage PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${FreeImage_INCLUDE_DIRS}")

    if(EXISTS "${FreeImage_LIBRARY}")
      set_target_properties(FreeImage::FreeImage PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${FreeImage_LIBRARY}")
    endif()
    if(FreeImage_LIBRARY_RELEASE)
      set_property(TARGET FreeImage::FreeImage APPEND PROPERTY
        IMPORTED_CONFIGURATIONS RELEASE)
      set_target_properties(FreeImage::FreeImage PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION_RELEASE "${FreeImage_LIBRARY_RELEASE}")
    endif()
    if(FreeImage_LIBRARY_DEBUG)
      set_property(TARGET FreeImage::FreeImage APPEND PROPERTY
        IMPORTED_CONFIGURATIONS DEBUG)
      set_target_properties(FreeImage::FreeImage PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION_DEBUG "${FreeImage_LIBRARY_DEBUG}")
    endif()
  endif()
endif()
