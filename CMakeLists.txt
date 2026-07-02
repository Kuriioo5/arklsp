cmake_minimum_required(VERSION 3.28)

project(ArkScriptLSP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)

FetchContent_MakeAvailable(nlohmann_json)

add_executable(arkscript-lsp)

target_sources(arkscript-lsp
    PRIVATE
        src/main.cpp
        src/json.cpp
        src/Server.cpp
        src/Diagnostic.cpp
)

target_sources(arkscript-lsp
    PRIVATE
        FILE_SET CXX_MODULES
        BASE_DIRS src
        FILES
            src/json.cppm
            src/Server.cppm
            src/Diagnostic.cppm
)

target_link_libraries(arkscript-lsp
    PRIVATE
        nlohmann_json::nlohmann_json
)
