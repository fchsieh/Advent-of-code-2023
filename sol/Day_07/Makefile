PROJECT_ROOT=../../
BASENAME = $(shell basename $(CURDIR))
CXX = g++
CXXFLAGS = -I. -Wall -Wextra -Ofast -g3 -std=c++23
HELPER=$(PROJECT_ROOT)lib/helper
.MAIN: output

output : $(BASENAME).cc $(BASENAME).hh
	$(CXX) $(CXXFLAGS) $(BASENAME).cc $(HELPER).cc -o run -lgtest

.PHONY: clean

clean:
	rm *.o run *.out