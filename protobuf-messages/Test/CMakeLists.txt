
cmake_minimum_required(VERSION 3.16)
project(protobuf-messages-test LANGUAGES CXX DESCRIPTION "protobuf messages test")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


add_executable(protobuf-messages-test ${PROJECT_SOURCE_DIR}/main.cpp)

if(UNIX)
	target_link_libraries(protobuf-messages-test
	protobuf-messages
	CONAN_PKG::protobuf
	)
else(UNIX)
	target_link_libraries(protobuf-messages-test
	protobuf-messages
	CONAN_PKG::protobuf
	secur32 
	crypt32 
	Ws2_32
	)
endif()


