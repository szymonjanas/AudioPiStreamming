cmake_minimum_required(VERSION 3.7)

project(audio)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

find_package(Qt5 COMPONENTS Core Quick REQUIRED)
if ( NOT (Qt5_FOUND))
      message(FATAL_ERROR "Please Install Qt Dev: CMake will Exit")
endif()
#find_package(Boost 1.67)

# local cmake scripts
#list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

#find_package(ZMQ REQUIRED)
include_directories("${GST_INCLUDE_DIRS}")
link_libraries(${GST_LIBRARIES})
include_directories( ${Boost_INCLUDE_DIRS} )
#include_directories(${ZMQ_INCLUDE_DIRS})


set (CLIENT
        client/client-main.cpp

        client/client-audio.cpp
        client/client-audio-local-mp3.cpp
        client/client-audio-udp-file.cpp
        client/client-audio-udp-live.cpp

        client/client-audio-controller.cpp

        media/media.cpp
        media/messageBus.cpp

        client/client-communication-with-headquarters.cpp
        client/client-communication-controller-with-headquarters.cpp
        media/communication-state.cpp

        #client/client-qt-controller.cpp
       # qt/qml.qrc
        )


add_executable(${PROJECT_NAME}-client ${CLIENT} )
target_link_libraries(${PROJECT_NAME}-client ${GST_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-client zmq)
target_link_libraries(${PROJECT_NAME}-client Qt5::Core Qt5::Quick)



set (HEADQUARTERS
        headquarters/headquarters-main.cpp
        headquarters/headquarters-audio-processing.cpp
        headquarters/headquarters-controler.cpp
        media/media.cpp
        media/messageBus.cpp
        headquarters/headquarters-communication.cpp
        media/communication-state.cpp)
include_directories(media)
add_executable(${PROJECT_NAME}-headquarters ${HEADQUARTERS})
target_link_libraries(${PROJECT_NAME}-headquarters ${GST_LIBRARIES})
target_link_libraries(${PROJECT_NAME}-headquarters zmq)


set (TESTS_SRC_LISTS
     client-tests/test-main.cpp
     client-tests/test-communication-state.cpp

     media/communication-state.cpp
     )
add_executable(${PROJECT_NAME}-client-tests ${TESTS_SRC_LISTS})
target_link_libraries(${PROJECT_NAME}-client-tests zmq)



