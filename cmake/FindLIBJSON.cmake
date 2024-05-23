# See:
# https://github.com/json-c/json-c/wiki
# $ sudo apt-get install libjson0-dev
# in sid:
# $ sudo apt-get install libjson-c-dev

find_path(LIBJSON_INCLUDE_DIR NAMES json/json.h json-c/json.h PATH_SUFFIXES "include")
find_library(LIBJSON_LIBRARY NAMES json json-c libjson-c PATH_SUFFIXES "lib" "lib32" "lib64")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBJSON DEFAULT_MSG
 LIBJSON_LIBRARY
 LIBJSON_INCLUDE_DIR
)

if(LIBJSON_FOUND)
  set(LIBJSON_LIBRARIES ${LIBJSON_LIBRARY})
  # hack to get old and new layout working:
  set(LIBJSON_INCLUDE_DIRS ${LIBJSON_INCLUDE_DIR}/json-c
    ${LIBJSON_INCLUDE_DIR}/json)
endif()

mark_as_advanced(
    LIBJSON_LIBRARY
    LIBJSON_INCLUDE_DIR
)