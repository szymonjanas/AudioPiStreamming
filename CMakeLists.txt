cmake_minimum_required(VERSION 3.8)

project(audioPi)

set(PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
find_package(PkgConfig REQUIRED)
if ( NOT (PKGCONFIG_FOUND))
      message(FATAL_ERROR "Please Install PPkgConfig: CMake will Exit")
endif()
pkg_check_modules(GST REQUIRED gstreamer-1.0>=1.8)
if ( NOT (GST_FOUND))
      message(FATAL_ERROR "Please Install Gstreamer Dev: CMake will Exit")
endif()
set(ENV{PKG_CONFIG_PATH})

include_directories("${GST_INCLUDE_DIRS}")
link_libraries(${GST_LIBRARIES})

set (SERVER
	server/server-main.cpp
	server/server-audio-processing.cpp
	)
add_executable(${PROJECT_NAME}-server ${SERVER})
target_link_libraries(${PROJECT_NAME}-server ${GST_LIBRARIES})
set (CLIENT
	client/client-main.cpp
        client/client-audio-processing.cpp
	)
add_executable(${PROJECT_NAME}-client ${CLIENT})
target_link_libraries(${PROJECT_NAME}-client ${GST_LIBRARIES})


