cmake_minimum_required(VERSION 3.10)
project(CMakeHello VERSION 1.0.0 LANGUAGES C)

# 设置 C 标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 源文件
set(SOURCES
    src/main.c
    src/math_utils.c
    src/string_utils.c
)

# 创建可执行文件
add_executable(cmake_hello ${SOURCES})

# 设置编译选项
target_compile_options(cmake_hello PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# 生成 compile_commands.json（用于代码补全和静态分析）
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 安装目标
install(TARGETS cmake_hello
    RUNTIME DESTINATION bin
)
