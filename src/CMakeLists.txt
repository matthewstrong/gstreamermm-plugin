set (CMAKE_CXX_STANDARD 11)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GSTREAMER_PLUGIN REQUIRED gstreamer-1.0>=1.14 gstreamer-base-1.0)
pkg_check_modules (GSTCPP REQUIRED gstreamermm-1.0)

## Throws linker error if unresolved symbols are found. This is required for a gstreamer plugin.
set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")
set (CMAKE_INSTALL_RPATH_USE_LINK_PATH true)

## Build static library
add_library (gstcpptest_static STATIC GstPlugin.cpp TestPlugin.cpp)
set_property (TARGET gstcpptest_static PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories (gstcpptest_static PUBLIC ${GSTREAMER_PLUGIN_INCLUDE_DIRS})
target_include_directories (gstcpptest_static PUBLIC ${GSTCPP_INCLUDE_DIRS})

target_link_libraries      (gstcpptest_static ${GSTCPP_LIBRARIES})

## Build shared library
add_library (gstcpptest SHARED GstPlugin.cpp TestPlugin.cpp)

target_include_directories (gstcpptest PUBLIC ${GSTREAMER_PLUGIN_INCLUDE_DIRS})
target_include_directories (gstcpptest PUBLIC ${GSTCPP_INCLUDE_DIRS})

target_link_libraries (gstcpptest ${GSTREAMER_PLUGIN_LIBRARIES})
target_link_libraries (gstcpptest ${GSTCPP_LIBRARIES})

install (TARGETS gstcpptest LIBRARY DESTINATION lib/gstreamer-1.0)
