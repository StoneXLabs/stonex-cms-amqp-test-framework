
cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-test-framework LANGUAGES CXX DESCRIPTION "stonex cms client test framework")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB sourceFiles
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/src/Configuration/*.cpp 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/src/*.cpp 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/src/MessageDecorator/*.cpp 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/src/MessageReceiver/*.cpp 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/src/MessageSender/*.cpp 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/src/MessageListener/*.cpp 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/src/VerifierFactory/*.cpp
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/src/VerifyingReceiverFactory/*.cpp 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/src/Metrics/*.cpp 
	)
file(GLOB headerFiles
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/include/Configuration/*.h 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/include/MessageDecorator/*.h 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/include/MessageReceiver/*.h 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/include/MessageSender/*.h 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/include/MessageListener/*.h 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/include/VerifierFactory/*.h 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/include/VerifyingReceiverFactory/*.h 
	${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/include/Metrics/*.h 
	)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles} )

add_library(stonex-cms-amqp-test-framework
	${sourceFiles}
	${headerFiles}
	)     


target_include_directories(stonex-cms-amqp-test-framework
	PUBLIC ${PROJECT_SOURCE_DIR}/stonex-cms-amqp-test-framework-lib/include
	)

target_link_libraries(stonex-cms-amqp-test-framework CONAN_PKG::stonex-cms-amqp-test-engine)


