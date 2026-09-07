cmake_minimum_required(VERSION 3.21)

project(Puzzle3D VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets OpenGL)

if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
endif()

add_executable(Puzzle3D MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    qoglwidget.cpp
    qoglwidget.h
    cube.cpp
    cube.h
    cylinder.cpp
    cylinder.h
    sphere.cpp
    sphere.h
    plane.cpp
    plane.h
)

target_link_libraries(Puzzle3D PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::OpenGL
)

if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    target_link_libraries(Puzzle3D PRIVATE Qt6::OpenGLWidgets)
endif()

set_target_properties(Puzzle3D PROPERTIES
    MACOSX_BUNDLE_BUNDLE_NAME "Puzzle 3D"
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.example.puzzle3d"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
    MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
)

install(TARGETS Puzzle3D
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin
)
