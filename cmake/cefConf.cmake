include(${CMAKE_SOURCE_DIR}/cmake/detectArch.cmake)

if(WIN32)
    set(CEF_ROOT "${CMAKE_SOURCE_DIR}/third_party/cef_windows_${ARCH_LABEL}")
    include_directories(${CEF_ROOT}/include)
    link_directories(${CEF_ROOT}/Release)
    file(GLOB CEF_LIBS
        ${CEF_ROOT}/Release/libcef.lib
        ${CEF_ROOT}/Release/cef_sandbox.lib
    )
    set(CEF_BINARY_DIR ${CEF_ROOT}/Release)
elseif(APPLE)
    set(CEF_ROOT "${CMAKE_SOURCE_DIR}/third_party/cef_macos_${ARCH_LABEL}")
    include_directories(${CEF_ROOT}/include)
    link_directories(${CEF_ROOT}/Release)
    file(GLOB CEF_LIBS
        ${CEF_ROOT}/Release/Chromium\ Embedded\ Framework.framework
    )
    set(CEF_BINARY_DIR ${CEF_ROOT}/Release)
    
elseif(UNIX)
    set(CEF_ROOT "${CMAKE_SOURCE_DIR}/third_party/cef_linux_${ARCH_LABEL}")
    include_directories(${CEF_ROOT}/include)
    link_directories(${CEF_ROOT}/Release)
    file(GLOB CEF_LIBS
        ${CEF_ROOT}/Release/libcef.so
    )
    set(CEF_BINARY_DIR ${CEF_ROOT}/Release)
elseif(APPLE)
    set_target_properties(cameleo PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/Info.plist"
    )
endif()

include_directories(${CEF_DIR}/include)
link_directories(${CEF_DIR}/Release)
