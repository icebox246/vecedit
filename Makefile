UNAME_S = $(shell uname -s)

OBJECTS += src/main.o
OBJECTS += src/Document.o

OBJECTS += src/ui/AppUi.o
OBJECTS += src/ui/DocumentTabs.o
OBJECTS += src/ui/Toolbar.o
OBJECTS += src/ui/IconButton.o
OBJECTS += src/ui/Editor.o
OBJECTS += src/ui/FigurePropertiesPanel.o

OBJECTS += src/ui/command/NewDocumentCommand.o
OBJECTS += src/ui/command/OpenDocumentCommand.o
OBJECTS += src/ui/command/SetFigureInsertCommand.o
OBJECTS += src/ui/command/SetSelectCommand.o

OBJECTS += src/figure/RectFigure.o
OBJECTS += src/figure/CircleFigure.o

OBJECTS += src/figure/visitor/RendererVisitor.o
OBJECTS += src/figure/visitor/PointIntersectionVisitor.o

OBJECTS += src/figure/adapter/RectFigurePointEditor.o
OBJECTS += src/figure/adapter/CircleFigurePointEditor.o

OBJECTS += thirdparty/raygui.o

CFLAGS += -std=c++20
CFLAGS += -Ithirdparty
CFLAGS += `pkg-config raylib --cflags`
CFLAGS += -Werror

LDFLAGS += `pkg-config raylib --libs`

ifeq (${UNAME_S},Darwin)
	LDFLAGS += -framework IOKit -framework Cocoa -framework OpenGL
endif

main: ${OBJECTS}
	${CXX} -o $@ ${OBJECTS} ${LDFLAGS}

%.o: %.cpp
	${CXX} -c -o $@ $^ ${CFLAGS}

compile_flags.txt: Makefile
	echo ${CFLAGS} | sed 's/ /\n/g' > $@
