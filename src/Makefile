EXE = pivo_imgui
IMGUI_DIR = ../
API_DIR = ..
GLFW_DIR = ../GLFW

SOURCES = main.cpp
SOURCES += $(IMGUI_DIR)/imgui/imgui.cpp \
           $(IMGUI_DIR)/imgui/imgui_demo.cpp \
           $(IMGUI_DIR)/imgui/imgui_draw.cpp \
           $(IMGUI_DIR)/imgui/imgui_tables.cpp \
           $(IMGUI_DIR)/imgui/imgui_widgets.cpp \
           $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp \
           $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp \
           $(API_DIR)/Source/Private/AdditiomalMenu.cpp

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

ifeq ($(OS), Windows_NT)
    ECHO_MESSAGE = "Windows"
    CXX = g++
    CXXFLAGS += -I$(GLFW_DIR)/include -I$(GLFW_DIR)/include/GLFW -I$(IMGUI_DIR)/imgui -I$(IMGUI_DIR)/backends -I$(API_DIR)/Source/Private -I$(API_DIR)/Source/Public
    LIBS += -L$(GLFW_DIR)/lib -lglfw3 -lopengl32 -lstdc++ -lm -lgdi32 -luser32
else ifeq ($(OS), Linux)
    ECHO_MESSAGE = "Linux"
    LIBS += -lGL `pkg-config --static --libs glfw3`
    CXXFLAGS += `pkg-config --cflags glfw3`
else
    $(error Unsupported platform)
endif

CXXFLAGS += -std=c++11 -g -Wall -Wformat

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: $(IMGUI_DIR)/imgui/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: $(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: $(API_DIR)/Source/Private/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS) -static -mwindows

clean:
	del $(EXE) $(OBJS)