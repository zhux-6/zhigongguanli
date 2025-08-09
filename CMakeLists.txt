cmake_minimum_required(VERSION 3.20)
project(program CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
elseif (MSVC)
    add_compile_options("/utf-8")
endif()


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(SRCS
    "src/main.cpp"
    "src/worker.cpp"
    "src/workermanager.cpp"
    "src/utils.cpp"

)

add_executable(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)