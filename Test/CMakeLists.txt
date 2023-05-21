cmake_minimum_required(VERSION 3.16)
project(framework-test LANGUAGES CXX DESCRIPTION "framework tests")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB sourceFiles ${PROJECT_SOURCE_DIR}/*.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles})

add_executable(framework-test main.cpp)              

target_include_directories(framework-test PUBLIC ${PROJECT_SOURCE_DIR}/main.cpp )

target_link_libraries(framework-test
	stonex-cms-amqp-test-framework
	CONAN_PKG::protobuf
	secur32 
	crypt32 
	Ws2_32
	)
	
configure_file(${PROJECT_SOURCE_DIR}/test_case_all.config ${CMAKE_CURRENT_BINARY_DIR}/test_case_all.config COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_case_all_senders.config ${CMAKE_CURRENT_BINARY_DIR}/test_case_all_senders.config COPYONLY)    
#configure_file(${PROJECT_SOURCE_DIR}/test_case_all_receivers.config ${CMAKE_CURRENT_BINARY_DIR}/test_case_all_receivers.config COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_message_file1.txt ${CMAKE_CURRENT_BINARY_DIR}/test_message_file1.txt COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_message_file2.txt ${CMAKE_CURRENT_BINARY_DIR}/test_message_file2.txt COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_message_file3.txt ${CMAKE_CURRENT_BINARY_DIR}/test_message_file3.txt COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_message_file4.txt ${CMAKE_CURRENT_BINARY_DIR}/test_message_file4.txt COPYONLY)  