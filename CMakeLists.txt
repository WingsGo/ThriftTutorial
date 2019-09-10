# 参考Thrift官方tutorial,注释include(BoostMacros)并将LINK_AGAINST_THRIFT_LIBRARY替换为target_link_libraries

cmake_minimum_required(VERSION 3.12)
project(ThriftTutorial)

set(CMAKE_CXX_STANDARD 11)

# 指定thrift执行路径
set(Thrift_EXCUTABLE /usr/local/bin/thrift)

#Make sure gen-cpp files can be included
include_directories("${PROJECT_SOURCE_DIR}/gen-cpp")


set(THRIFT_GEN_FILES
        gen-cpp/Serv.cpp
        gen-cpp/student_types.cpp
        gen-cpp/student_constants.cpp)

# 将动态生成代码与thrift进行链接
add_library(thriftgenfiles SHARED ${THRIFT_GEN_FILES})
target_link_libraries(thriftgenfiles thrift)

add_custom_command(
        DEPENDS ${CMAKE_SOURCE_DIR}/student.thrift
        OUTPUT ${THRIFT_GEN_FILES}
        COMMAND ${Thrift_EXECUTABLE}
        ARGS -r -gen cpp ${CMAKE_SOURCE_DIR}/student.thrift)

add_executable(client main.cpp)
target_link_libraries(client thriftgenfiles)
target_link_libraries(client thrift)
