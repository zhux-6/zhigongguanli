cmake_minimum_required(VERSION 3.20)
project(protect CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 跨平台设置源文件和执行文件编码为 UTF-8
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
elseif (MSVC)
    add_compile_options("/utf-8")
endif()

# 生成 compile_commands.json 以支持 clangd 等工具
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 建议：显式列出源文件，以避免 file(GLOB) 的问题。
# 当添加新文件时，构建系统能自动感知。
set(SRCS
    "src/main.cpp"
    "src/utils.cpp"
    "src/worker.cpp"
    "src/workermanager.cpp"
    
    # "src/another_file.cpp" # 在这里添加新的源文件
)

add_executable(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)