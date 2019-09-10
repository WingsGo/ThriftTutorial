cmake_minimum_required(VERSION 3.0.2)
project(ThriftTutorial)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Thrift REQUIRED)
find_package(Boost REQUIRED)

message("Thrift_EXECUTABLE: " ${Thrift_EXECUTABLE})
message("Thrift_LIBRARIES: " ${Thrift_LIBRARIES})

set(THRIFT_GEN_FILES
        ${CMAKE_SOURCE_DIR}/gen-cpp/Serv.h
        ${CMAKE_SOURCE_DIR}/gen-cpp/Serv.cpp
        ${CMAKE_SOURCE_DIR}/gen-cpp/student_types.h
        ${CMAKE_SOURCE_DIR}/gen-cpp/student_types.cpp
        ${CMAKE_SOURCE_DIR}/gen-cpp/student_constants.h
        ${CMAKE_SOURCE_DIR}/gen-cpp/student_constants.cpp)

message(${THRIFT_GEN_FILES})

add_custom_command(
        DEPENDS ${CMAKE_SOURCE_DIR}/student.thrift
        OUTPUT ${THRIFT_GEN_FILES}
        COMMAND ${Thrift_EXECUTABLE}
        ARGS -r -gen cpp -o ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/student.thrift)

add_library(tutorialgencpp STATIC ${THRIFT_GEN_FILES})

add_executable(client main.cpp ${THRIFT_GEN_FILES})
target_link_libraries(client ${Thrift_LIBRARIES} thrift)
