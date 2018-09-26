cmake_minimum_required(VERSION 3.5)

project (q)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create the executable
FILE(GLOB SRC_C_FILES src/*.c)
ADD_EXECUTABLE(q ${SRC_C_FILES})
