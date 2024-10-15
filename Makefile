# Makefile for compiling knightMoves.cpp

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall

# Source file
SOURCES = knightMoves.cpp

# Output executable
OUTPUT = prog

# Default target
all: $(OUTPUT)

# Rule to create the executable
$(OUTPUT): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SOURCES)

# Clean target
clean:
	rm -f $(OUTPUT)

