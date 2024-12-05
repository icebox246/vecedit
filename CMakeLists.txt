cmake_minimum_required(VERSION 3.30)

find_package(PkgConfig)
pkg_check_modules(RAYLIB REQUIRED raylib)

project(VecEdit CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_compile_options(-Werror)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_link_options(-framework IOKit -framework Cocoa -framework OpenGL)
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
    
    src/ui/command/NewDocumentCommand.cpp
    src/ui/command/OpenDocumentCommand.cpp
    src/ui/command/SetFigureInsertCommand.cpp
    src/ui/command/SetSelectCommand.cpp
    
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

target_link_libraries(VecEdit ${RAYLIB_LIBRARIES})
target_include_directories(VecEdit PUBLIC ${RAYLIB_INCLUDE_DIRS})
target_compile_options(VecEdit PUBLIC ${RAYLIB_CFLAGS_OTHER})
