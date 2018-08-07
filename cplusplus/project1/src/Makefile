CXX = g++
SOPTS = -std=c++11 -O3 -march=native -fopenmp
OPTS = -std=c++11 -O2 -g -fopenmp
all: main

main: main.cpp bmp.o geometry.o render.o
	$(CXX) $(SOPTS) main.cpp bmp.o geometry.o render.o -o main

render.o: render.cpp render.h
	$(CXX) $(SOPTS) render.cpp -c

bmp.o: bmp.cpp bmp.h
	$(CXX) $(SOPTS) bmp.cpp -c

geometry.o: geometry.cpp geometry.h
	$(CXX) $(SOPTS) geometry.cpp -c

clean:
	rm *.o main
