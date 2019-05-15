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

#find_package(Boost 1.67)

# local cmake scripts
#list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

#find_package(ZMQ REQUIRED)
include_directories("${GST_INCLUDE_DIRS}")
link_libraries(${GST_LIBRARIES})
include_directories( ${Boost_INCLUDE_DIRS} )
#include_directories(${ZMQ_INCLUDE_DIRS})


set (DEVICE
        device/device-main.cpp
        device/device-local.cpp
        device/device-udp.cpp
        device/device-controler.cpp
        media/media.cpp
        device/device-communication.cpp)
add_executable(${PROJECT_NAME}-device ${DEVICE})
target_link_libraries(${PROJECT_NAME}-device ${GST_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-device zmq)


set (BASE
        basePi/base-main.cpp
        basePi/base-audio-processing.cpp
        basePi/base-controler.cpp
        media/media.cpp
        basePi/base-communication.cpp)
include_directories(media)
add_executable(${PROJECT_NAME}-base ${BASE})
target_link_libraries(${PROJECT_NAME}-base ${GST_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-base zmq)



