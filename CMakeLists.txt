﻿cmake_minimum_required(VERSION 3.5)

project(BunnyHole VERSION 0.0.2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# define diffren arch for intel and arm mac
if(APPLE)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
        set(CMAKE_OSX_ARCHITECTURES "arm64")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        set(CMAKE_OSX_ARCHITECTURES "x86_64")
    endif()
endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network WebSockets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network WebSockets REQUIRED)
string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%d %H:%M:%S")
message("Build timestamp is ${BUILD_TIMESTAMP}")
# get git hash
macro(get_git_hash _git_hash)   # 宏的开始
    find_package(Git QUIET)     # 查找Git，QUIET静默方式不报错
    if(GIT_FOUND)
      execute_process(          # 执行一个子进程
        COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%h # 命令
        OUTPUT_VARIABLE ${_git_hash}        # 输出字符串存入变量
        OUTPUT_STRIP_TRAILING_WHITESPACE    # 删除字符串尾的换行符
        ERROR_QUIET                         # 对执行错误静默
        WORKING_DIRECTORY                   # 执行路径
          ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif()
endmacro()                      # 宏的结束

# get git branch
macro(get_git_branch _git_branch)   # 宏的开始
    find_package(Git QUIET)     # 查找Git，QUIET静默方式不报错
    if(GIT_FOUND)
      execute_process(          # 执行一个子进程
        COMMAND ${GIT_EXECUTABLE} symbolic-ref --short -q HEAD
        OUTPUT_VARIABLE ${_git_branch}        # 输出字符串存入变量
        OUTPUT_STRIP_TRAILING_WHITESPACE    # 删除字符串尾的换行符
        ERROR_QUIET                         # 对执行错误静默
        WORKING_DIRECTORY                   # 执行路径
          ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif()
endmacro()                      # 宏的结束
set(GIT_HASH "")
get_git_hash(GIT_HASH)
message("Git hash is ${GIT_HASH}")

set(GIT_BRANCH "")
get_git_branch(GIT_BRANCH)
message("Git branch is ${GIT_BRANCH}")

configure_file (
    "${PROJECT_SOURCE_DIR}/version.h.in"
    "${PROJECT_SOURCE_DIR}/include/version.h"
)
include_directories("include/")
set(PROJECT_SOURCES
        include/version.h
        main.cpp
        src/kernel/carrot.h
        src/kernel/carrot.cpp
        src/kernel/carrotleaf.h
        src/kernel/carrotleaf.cpp
        src/kernel/bunny.h
        src/kernel/bunny.cpp
        src/kernel/bunnychild.h
        src/kernel/bunnychild.cpp
        src/kernel/bunnyhole.h
        src/kernel/bunnyhole.cpp
        src/kernel/bunnyholeprotocol.h
        src/kernel/bunnyholeprotocol.cpp
        src/kernel/bunnyholeprotocolbuilder.h
        src/kernel/bunnyholeprotocolbuilder.cpp
        src/kernel/configuration.h
        src/kernel/configuration.cpp
        src/ui/model/clientmodel.h
        src/ui/model/clientmodel.cpp
        src/ui/mainwindow.cpp
        src/ui/mainwindow.h
        src/ui/mainwindow.ui
        src/ui/transferdialog.h
        src/ui/transferdialog.cpp
        src/ui/transferdialog.ui
        src/ui/listitem.h
        src/ui/listitem.cpp
        src/ui/listitem.ui
        src/ui/filedialog.h
        src/ui/filedialog.cpp
        src/ui/resource.qrc
        src/kernel/file/bunnydir.h
        src/kernel/file/bunnydir.cpp
        src/kernel/file/bunnyfile.h
        src/kernel/file/bunnyfile.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BunnyHole
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(BunnyHole SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(BunnyHole
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BunnyHole PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::WebSockets
    )

set_target_properties(BunnyHole PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BunnyHole)
endif()
