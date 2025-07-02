#=============================================
# Makefile for exe_TrigStudy (TrigNbTag/TriggerStudy)
#=============================================

# 1) Final executable name
PROGRAM := exe_TrigStudy

# 2) Compiler
CXX := $(shell which g++)
LD  := $(CXX)

# 3) ROOT flags
ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS   := $(shell root-config --libs)

# 4) Compilation and link flags
CXXFLAGS := -g -O2 -std=c++17 $(ROOTCFLAGS) -Iinclude 
LDFLAGS  := $(ROOTLIBS) -lBranchInterface

# 5) Source files
SRCS := main.cpp \
        src/EventLooper.cpp \
        src/HistogramManager.cpp

# 6) Object files under tmp/
OBJS := $(SRCS:%.cpp=tmp/%.o)

# 7) Default target
.PHONY: all clean run
all: $(PROGRAM)

# 8) Link step
$(PROGRAM): $(OBJS)
	$(LD) $^ -o $@ $(LDFLAGS)

# 9) Compile rule
tmp/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 10) Run target
run: all
	./$(PROGRAM) ttJets

# 11) Clean
clean:
	rm -rf tmp $(PROGRAM)
