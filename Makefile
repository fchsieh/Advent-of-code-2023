CXX = g++
CXXFLAGS = -Wall -Wextra -Ofast -g3 -std=c++23

# Set the source directory
SRC_DIR := sol
SOURCES := $(wildcard $(SRC_DIR)/**/*.cc)
OBJECTS := $(SOURCES:.cc=.o)

all: main

main: $(OBJECTS)
	@echo "Building main..."
	@$(CXX) $(CXXFLAGS) $(OBJECTS) main.cc -o run -lgtest

# Compile each day's source file
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS)
