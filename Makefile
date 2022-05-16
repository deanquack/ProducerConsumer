# CXX Make variable for compiler
CXX=g++
# Make variable for compiler options
#	-std=c++11  C/C++ variant to use, e.g. C++ 2011
#	-g          include information for symbolic debugger e.g. gdb 
CXXFLAGS=-std=c++11 -g -lpthread

# Rules format:
# target : dependency1 dependency2 ... dependencyN
#     Command to make target, uses default rules if not specified

# First target is the one executed if you just type make
# make target specifies a specific target
# $^ is an example of a special variable.  It substitutes all dependencies
rideshare : io.o main.o producer.o consumer.o sharedData.o io.o
	$(CXX) $(CXXFLAGS) -o rideshare $^ -lpthread

producer.o : producer.h producer.cpp 
	$(CXX) $(CXXFLAGS) -c producer.cpp
sharedData.o: sharedData.h sharedData.cpp
	$(CXX) $(CXXFLAGS) -c sharedData.cpp
consumer.o: consumer.h consumer.cpp 
	$(CXX) $(CXXFLAGS) -c consumer.cpp	

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

io.o : io.h io.cpp ridesharing.h
	$(CXX) $(CXXFLAGS) -c io.cpp
	

clean :
	rm *.o
