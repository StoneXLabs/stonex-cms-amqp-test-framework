
cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-test-framework LANGUAGES CXX DESCRIPTION "stonex cms client test framework")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(protobuf-messages)

file(GLOB sourceFiles
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/src/Metrics/*.cpp 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/src/MessageSender/*.cpp 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/src/Messages/*.cpp 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/src/messages/*.cpp 
	)
file(GLOB headerFiles
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/include/Metrics/*.h 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/include/MessageSender/*.h 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/include/Messages/*.h 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/src/messages/*.h 
	)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles} )


add_library(stonex-cms-amqp-test-framework
	${sourceFiles}
	${headerFiles}
	)     


target_include_directories(stonex-cms-amqp-test-framework
	PUBLIC ${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/include
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/src
	)

target_link_libraries(stonex-cms-amqp-test-framework CONAN_PKG::stonex-cms-amqp-test-engine CONAN_PKG::protobuf protobuf-messages)

add_subdirectory(Test)
  