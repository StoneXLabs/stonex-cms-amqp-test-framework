
cmake_minimum_required(VERSION 3.16)
project(protobuf-messages LANGUAGES CXX DESCRIPTION "stonex cms client test framework")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_FIND_DEBUG_MODE TRUE)
if(UNIX)
	find_package(Protobuf REQUIRED)
else(UNIX)
	find_package(protobuf REQUIRED)
endif()

include_directories(${Protobuf_INCLUDE_DIRS} )

EXECUTE_PROCESS(COMMAND ${Protobuf_PROTOC_EXECUTABLE}  --proto_path ${Protobuf_INCLUDE_DIRS} --proto_path ${PROJECT_SOURCE_DIR}/schemas  --cpp_out ${PROJECT_SOURCE_DIR}/messages ${PROJECT_SOURCE_DIR}/schemas/*.proto)

file(GLOB sourceFiles
	${PROJECT_SOURCE_DIR}/messages/*.pb.cc
	)
file(GLOB headerFiles
	${PROJECT_SOURCE_DIR}/messages/*.pb.h 
	)

add_library(protobuf-messages STATIC ${sourceFiles} ${headerFiles})

target_include_directories(protobuf-messages PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(protobuf-messages
	PUBLIC CONAN_PKG::protobuf
	)
