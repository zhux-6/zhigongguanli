# 设置 CMake 的最低版本要求。建议使用较新的版本以获得更多功能和更好的兼容性。
# CMake 3.20 或更高版本提供了许多现代特性和更好的兼容性。
cmake_minimum_required(VERSION 3.20)

# 定义项目名称和支持的语言。
# 'protect' 将是你的可执行文件的名称。
project(protect CXX)

# 设置 C++ 标准。建议使用最新的稳定标准，如 C++17 或 C++20。
# C++17 提供了许多现代 C++ 特性。
set(CMAKE_CXX_STANDARD 17)
# 强制要求使用指定的 C++ 标准，如果编译器不支持则会报错。

set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 禁用 GNU 扩展，确保代码更具可移植性。
# 如果你依赖于 GNU 特有扩展，请注释掉此行。
set(CMAKE_CXX_EXTENSIONS OFF)
# 配置编译器以正确处理中文（UTF-8）编码。
# 对于 GCC 和 Clang 编译器，使用 -finput-charset 和 -fexec-charset。
# 对于 MSVC (Visual Studio) 编译器，使用 /utf-8 选项。
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-finput-charset=UTF-8)
    add_compile_options(-fexec-charset=UTF-8)
elseif (MSVC)
    add_compile_options("/utf-8")
endif()
configure_file(
    ${CMAKE_SOURCE_DIR}/.clang-format
    ${CMAKE_BINARY_DIR}/.clang-format
    COPYONLY
)#生成.clang-format

# 生成 compile_commands.json 文件，这是 Clangd 等语言服务器进行代码分析的关键。
# 它包含了每个源文件的编译命令。

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 查找源文件。
# file(GLOB SRCS "src/*.cpp") 是一种方便的写法，可以找到指定模式的所有源文件。
# 但请注意，如果添加或删除了源文件，可能需要手动重新配置 CMake。
# 对于大型项目，更推荐明确列出源文件或使用 add_subdirectory 组织子目录。
file(GLOB SRCS "src/*.cpp")

# 定义可执行文件。
# ${PROJECT_NAME} 会自动使用 project() 命令中定义的名称。
# ${SRCS} 包含了通过 file(GLOB) 找到的所有源文件。
add_executable(${PROJECT_NAME} ${SRCS})


# 添加头文件搜索路径。
# target_include_directories 是现代 CMake 的推荐做法，它将头文件路径与特定目标关联。
# PUBLIC 关键字表示这个 include 路径不仅对当前目标可见，
# 如果其他目标链接了当前目标，它们也能继承这个 include 路径。
# ${CMAKE_SOURCE_DIR}/include 是一个常见的做法，用于存放项目公共头文件。
# 此行已移动到 add_executable 之后，以确保目标 'protect' 已被定义。
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

# 可选：如果你使用了第三方库（例如通过 Vcpkg 安装的库），需要在这里链接它们。
# Vcpkg 集成后，你可以使用 find_package() 来查找库，然后 target_link_libraries() 来链接。
# 示例：查找并链接 fmt 库（假设你已经通过 Vcpkg 安装了 fmt:x64-windows-ucrt）
# find_package(fmt CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

# 示例：链接其他常见的系统库（例如数学库）
# target_link_libraries(${PROJECT_NAME} PRIVATE m)
# 以下是为 Qt 项目添加的配置

# 设置 CMAKE_PREFIX_PATH，帮助 CMake 找到 MSYS2 UCRT64 环境下的 Qt 安装

# 在 MSYS2 UCRT64 终端中，/ucrt64 路径对应 MSYS2 安装目录下的 ucrt64 文件夹

set(CMAKE_PREFIX_PATH "D:/Vscode/msys64/ucrt64")


# 启用 Qt 的自动元对象编译 (MOC)、资源编译 (RCC) 和 UI 文件编译 (UIC)

# 这些对于 Qt 项目是必需的，可以自动处理 Qt 特有的文件生成
set(CMAKE_AUTOMOC ON)

set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC ON)


# 查找 Qt6 包及其所需的组件

# REQUIRED 表示如果找不到 Qt6，CMake 配置会失败

# COMPONENTS 列出了你项目需要的 Qt 模块，例如 Core, Widgets, Gui 等

# 根据你的实际需求添加或移除模块

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)


# PRIVATE 关键字表示这些库只对当前目标可见，不会传递给其他链接此目标的目标

target_link_libraries(${PROJECT_NAME} PRIVATE

    Qt::Core

    Qt::Widgets

    Qt::Gui
    # 如果你在 find_package 中添加了其他 Qt 模块，也需要在这里链接对应的 Qt::模块名
    # 例如：Qt::Network, Qt::Svg, Qt::Sql 等
)