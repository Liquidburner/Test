CXX = g++
CXXFLAGS = -Wall -O3 -std=c++11 -march=native

# comment the following flags if you do not want to use OpenMP
#DFLAG += -DUSEOMP
#CXXFLAGS += -fopenmp

all: run-clustering

run-clustering: main.cpp datapoint.o optics_datapoint.o dataheap.o optics.o minioptics.o
	$(CXX) $(CXXFLAGS) -o $@ $^

datapoint.o: datapoint.cpp datapoint.h
	$(CXX) $(CXXFLAGS) $(DFLAG) -c -o $@ $<

optics_datapoint.o: optics_datapoint.cpp optics_datapoint.h
	$(CXX) $(CXXFLAGS) $(DFLAG) -c -o $@ $<

dataheap.o: dataheap.cpp dataheap.h
	$(CXX) $(CXXFLAGS) $(DFLAG) -c -o $@ $<

optics.o: optics.cpp optics.h
	$(CXX) $(CXXFLAGS) $(DFLAG) -c -o $@ $<

minioptics.o: minioptics.cpp minioptics.h
	$(CXX) $(CXXFLAGS) $(DFLAG) -c -o $@ $<

clean:
	rm -f run-clustering minioptics.o optics.o dataheap.o optics_datapoint.o datapoint.o main.o
