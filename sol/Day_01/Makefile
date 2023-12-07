BASENAME = $(shell basename $(CURDIR))
CXX = g++
CXXFLAGS = -I. -Wall -Wextra -O0 -g3
.MAIN: output

output : $(BASENAME).cc $(BASENAME).hh
	$(CXX) $(CXXFLAGS) $(BASENAME).cc -o run -lgtest

.PHONY: clean

clean:
	rm *.o run *.out