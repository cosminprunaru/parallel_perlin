CPPFLAGS=-std=c++11
LDLIBS=-lpthread
CXX=g++

all: sky wood

sky: demo1.o noise.o ppm.o
	$(CXX) -o sky demo1.o noise.o ppm.o $(LDLIBS)

wood: demo0.o noise.o ppm.o
	$(CXX) -o wood demo0.o noise.o ppm.o $(LDLIBS)

demo1.o: PerlinRandom.cpp
	$(CXX) $(CPPFLAGS) -c PerlinRandom.cpp -o demo1.o $(LDLIBS)

demo0.o: PerlinWood.cpp
	$(CXX) $(CPPFLAGS) -c PerlinWood.cpp -o demo0.o $(LDLIBS)

noise.o: PerlinNoise.cpp PerlinNoise.h
	$(CXX) $(CPPFLAGS) -c PerlinNoise.cpp -o noise.o

ppm.o: ppm.cpp ppm.h
	$(CXX) $(CPPFLAGS) -c ppm.cpp -o ppm.o

clean:
	rm -f *.o *.ppm wood sky
