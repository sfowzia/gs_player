cmake_minimum_required(VERSION 3.0)

project(gstreamer_player)

set(CMAKE_CXX_STANDARD 11)

# Add GStreamer libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

# Add the executable
add_executable(gs_player main.cpp)

# Link against GStreamer libraries
target_link_libraries(gs_player ${GSTREAMER_LIBRARIES})
target_include_directories(gs_player PUBLIC ${GSTREAMER_INCLUDE_DIRS})