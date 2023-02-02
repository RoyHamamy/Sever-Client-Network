cmake_minimum_required(VERSION 3.20)
project(SPL3new)

set(CMAKE_CXX_STANDARD 14)

add_executable(SPL3new include/encoderDecoder.h include/Task.h src/Task.cpp src/encoderDecoder.cpp src/bidiProtocol.cpp src/bidiClient.cpp src/connectionHandler.cpp)
set(BOOST_ROOT "C:Boost")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME off)
find_package(Boost REQUIRED COMPONENTS system)

target_include_directories(SPL3new PUBLIC ${Boost_INCLUDE_DIRD})
target_link_libraries(SPL3new ${Boost_LIBRARIES})

SET(LDFLAGS "-lboost_system -lboost_thread -pthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LDFLAGS}")