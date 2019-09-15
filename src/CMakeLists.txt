# 参考Thrift官方tutorial,注释include(BoostMacros)并将LINK_AGAINST_THRIFT_LIBRARY替换为target_link_libraries

cmake_minimum_required(VERSION 3.12)
project(ThriftTutorial)

set(CMAKE_CXX_STANDARD 11)

# 指定thrift执行路径
set(THRIFT_EXCUTABLE /usr/local/bin/thrift)

#Make sure gen-cpp files can be included
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/gen-cpp")
include_directories("${PROJECT_SOURCE_DIR}/lib/cpp/src")

set(THRIFT_GEN_FILES
        gen-cpp/Calculator.cpp
        gen-cpp/shared_constants.cpp
        gen-cpp/shared_types.cpp
        gen-cpp/SharedService.cpp
        gen-cpp/tutorial_constants.cpp
        gen-cpp/tutorial_types.cpp)

# 将动态生成代码与thrift进行链接
add_library(thriftgenfiles STATIC ${THRIFT_GEN_FILES})
target_link_libraries(thriftgenfiles thrift)

add_custom_command(
        DEPENDS ${CMAKE_SOURCE_DIR}/tutorial.thrift
        OUTPUT ${THRIFT_GEN_FILES}
        COMMAND ${THRIFT_EXCUTABLE}
        ARGS --gen cpp -r ${PROJECT_SOURCE_DIR}/tutorial.thrift)

add_executable(client client.cpp)
target_link_libraries(client thriftgenfiles)
target_link_libraries(client thrift)

add_executable(server server.cpp)
target_link_libraries(server thriftgenfiles)
target_link_libraries(server thrift)
