cmake_minimum_required(VERSION 3.5)

project (q)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create the executable
add_executable(q
  src/main.c
  src/exe.c
  src/token.c
)
