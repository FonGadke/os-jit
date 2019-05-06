CXX = g++
CXX_STANDARD = -std=c++14

all: jit

run: jit
	./jit

jit: jit.cpp
	$(CXX) $(CXX_STANDARD) -o $@ $^

.PHONY: clean
clean:
	rm jit