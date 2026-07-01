cmake_minimum_required(VERSION 3.20)

project(ArkScriptLSP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(arkscript-lsp
    src/main.cpp
    src/server.cpp
)

target_include_directories(arkscript-lsp PRIVATE include)
