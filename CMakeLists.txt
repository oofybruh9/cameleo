# CMakeLists.txt for Cameleo Browser (SDL3 + CEF - Cross-Platform Light Mode)
cmake_minimum_required(VERSION 3.15)
project(CameleoBrowser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_SOURCE_DIR}/cmake/cefConf.cmake)

# SDL3
find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/src/)

# App Source
add_executable(cameleo ${SRC_FILES})

# Link libraries


# Install target with minimal CEF runtime
install(TARGETS cameleo RUNTIME DESTINATION .)

install(FILES
    ${CEF_BINARY_DIR}/libcef.so
    ${CEF_BINARY_DIR}/cef.pak
    ${CEF_BINARY_DIR}/chrome_100.pak
    ${CEF_BINARY_DIR}/snapshot_blob.bin
    ${CEF_BINARY_DIR}/v8_context_snapshot.bin
    ${CEF_BINARY_DIR}/subprocess
    DESTINATION .
    OPTIONAL
)

install(DIRECTORY ${CEF_BINARY_DIR}/locales/
    DESTINATION locales
    FILES_MATCHING PATTERN "en-US.pak"
)

# Link SDL3, TTF, and CEF
target_link_libraries(cameleo
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    ${CEF_LIBS}
)
