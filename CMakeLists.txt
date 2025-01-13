cmake_minimum_required(VERSION 3.29)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "5.5"
    GIT_PROGRESS TRUE
    GIT_SHALLOW 1
)

FetchContent_MakeAvailable(raylib)

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
    src/ui/FigureHierarchyPanel.cpp
    src/ui/DocumentPropertiesView.cpp
    
    src/ui/strategy/NewDocumentStrategy.cpp
    src/ui/strategy/SaveDocumentStrategy.cpp
    src/ui/strategy/OpenDocumentStrategy.cpp
    src/ui/strategy/SetFigureInsertStrategy.cpp
    src/ui/strategy/SetSelectStrategy.cpp
    
    src/figure/RectFigure.cpp
    src/figure/CircleFigure.cpp
    src/figure/FigureGroup.cpp
    
    src/figure/visitor/RendererVisitor.cpp
    src/figure/visitor/PointIntersectionVisitor.cpp
    src/figure/visitor/SvgSerializerVisitor.cpp
    
    src/figure/adapter/RectFigurePointEditor.cpp
    src/figure/adapter/CircleFigurePointEditor.cpp
    src/figure/adapter/PolyFigurePointEditor.cpp
    src/figure/adapter/FigureGroupPointEditor.cpp

    src/ui/command/CommandManager.cpp
)

set(THIRDPARYSOURCE
    thirdparty/raygui.cpp
)

add_executable(VecEdit
    ${SOURCE}
    ${THIRDPARYSOURCE}
)

target_include_directories(VecEdit PRIVATE ${PROJECT_SOURCE_DIR}/thirdparty)

target_link_libraries(${PROJECT_NAME} raylib)

target_link_libraries(VecEdit ${EXTRA_MACOS_LIBS})

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
