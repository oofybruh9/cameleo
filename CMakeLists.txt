# CMakeLists.txt for Cameleo Browser (SDL3 + CEF - Cross-Platform Light Mode)
cmake_minimum_required(VERSION 3.15)
project(CameleoBrowser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL3
find_package(SDL3 REQUIRED CONFIG)

# Platform-specific CEF config
if(WIN32)
    set(CEF_ROOT "${CMAKE_SOURCE_DIR}/third_party/cef")
    include_directories(${CEF_ROOT}/include)
    link_directories(${CEF_ROOT}/Release)
    file(GLOB CEF_LIBS
        ${CEF_ROOT}/Release/libcef.lib
        ${CEF_ROOT}/Release/cef_sandbox.lib
    )
    set(CEF_BINARY_DIR ${CEF_ROOT}/Release)
elseif(APPLE)
    set(CEF_ROOT "${CMAKE_SOURCE_DIR}/third_party/cef")
    include_directories(${CEF_ROOT}/include)
    link_directories(${CEF_ROOT}/Release)
    file(GLOB CEF_LIBS
        ${CEF_ROOT}/Release/Chromium\ Embedded\ Framework.framework
    )
    set(CEF_BINARY_DIR ${CEF_ROOT}/Release)
elseif(UNIX)
    set(CEF_ROOT "${CMAKE_SOURCE_DIR}/third_party/cef")
    include_directories(${CEF_ROOT}/include)
    link_directories(${CEF_ROOT}/Release)
    file(GLOB CEF_LIBS
        ${CEF_ROOT}/Release/libcef.so
    )
    set(CEF_BINARY_DIR ${CEF_ROOT}/Release)
endif()

# App Source
add_executable(cameleo src/main.cpp)

# Link libraries
target_link_libraries(cameleo PRIVATE SDL3::SDL3 ${CEF_LIBS})

# Install target with minimal CEF runtime
install(TARGETS cameleo RUNTIME DESTINATION .)

install(FILES
    ${CEF_BINARY_DIR}/libcef.dll
    ${CEF_BINARY_DIR}/cef.pak
    ${CEF_BINARY_DIR}/chrome_100.pak
    ${CEF_BINARY_DIR}/snapshot_blob.bin
    ${CEF_BINARY_DIR}/v8_context_snapshot.bin
    ${CEF_BINARY_DIR}/subprocess.exe
    DESTINATION .
    OPTIONAL
)

install(DIRECTORY ${CEF_BINARY_DIR}/locales/
    DESTINATION locales
    FILES_MATCHING PATTERN "en-US.pak"
    OPTIONAL
)

message(STATUS "Cameleo Browser is configured for light CEF runtime bundle.")
