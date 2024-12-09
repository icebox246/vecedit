cmake_minimum_required(VERSION 3.30)

find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED IMPORTED_TARGET raylib>=5.5)

project(VecEdit CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_compile_options(-Werror)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OPENGL_LIBRARY OpenGL)
    mark_as_advanced (IOKIT_LIBRARY
        COCOA_LIBRARY
        OPENGL_LIBRARY)
    set(EXTRA_MACOS_LIBS ${IOKIT_LIBRARY} ${COCOA_LIBRARY} ${OPENGL_LIBRARY})
endif()

set(SOURCE 
    src/main.cpp

    src/Document.cpp

    src/ui/AppUi.cpp
    src/ui/DocumentTabs.cpp
    src/ui/Toolbar.cpp
    src/ui/IconButton.cpp
    src/ui/Editor.cpp
    src/ui/FigurePropertiesPanel.cpp
    
    src/ui/strategy/NewDocumentStrategy.cpp
    src/ui/strategy/OpenDocumentStrategy.cpp
    src/ui/strategy/SetFigureInsertStrategy.cpp
    src/ui/strategy/SetSelectStrategy.cpp
    
    src/figure/RectFigure.cpp
    src/figure/CircleFigure.cpp
    
    src/figure/visitor/RendererVisitor.cpp
    src/figure/visitor/PointIntersectionVisitor.cpp
    
    src/figure/adapter/RectFigurePointEditor.cpp
    src/figure/adapter/CircleFigurePointEditor.cpp
)

set(THIRDPARYSOURCE
    thirdparty/raygui.cpp
)

add_executable(VecEdit
    ${SOURCE}
    ${THIRDPARYSOURCE}
)

target_include_directories(VecEdit PRIVATE ${PROJECT_SOURCE_DIR}/thirdparty)

target_link_libraries(VecEdit PkgConfig::RAYLIB)

target_link_libraries(VecEdit ${EXTRA_MACOS_LIBS})
