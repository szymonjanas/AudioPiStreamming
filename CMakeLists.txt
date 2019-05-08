cmake_minimum_required(VERSION 3.7)

set (CMAKE_CXX_STANDARD 11)
project(audioPi)

set(PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
find_package(PkgConfig REQUIRED)
if ( NOT (PKGCONFIG_FOUND))
      message(FATAL_ERROR "Please Install PPkgConfig: CMake will Exit")
endif()
pkg_check_modules(GST REQUIRED gstreamer-1.0>=1.2)
if ( NOT (GST_FOUND))
      message(FATAL_ERROR "Please Install Gstreamer Dev: CMake will Exit")
endif()
set(ENV{PKG_CONFIG_PATH})

find_package(Boost 1.67)

include_directories("${GST_INCLUDE_DIRS}")
link_libraries(${GST_LIBRARIES})
include_directories( ${Boost_INCLUDE_DIRS} )


set (SERVER
	server/server-main.cpp
        server/server-local.cpp
        server/server-udp.cpp
        server/server-controler.cpp
        media/media.cpp
	)
add_executable(${PROJECT_NAME}-server ${SERVER})
target_link_libraries(${PROJECT_NAME}-server ${GST_LIBRARIES})

set (CLIENT
        client/client-main.cpp
        client/client-audio-processing.cpp
        media/media.cpp
	)
include_directories(media)
add_executable(${PROJECT_NAME}-client ${CLIENT})
target_link_libraries(${PROJECT_NAME}-client ${GST_LIBRARIES})


