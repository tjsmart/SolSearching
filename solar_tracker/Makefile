# Makefile

# compilation rules
.SUFFIXES : .o .cpp
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< $(headers)

# c++ compiler
CXX = clang++

# flags
CXXFLAGS = \
    -std=c++17 \
    -Wall \
    -g

# libraries
LDFLAGS =

# objects to build
sub_obj = \
	solarTracker.o

# main target
testTracker.x: $(sub_obj) testTracker.o
	$(CXX) $(sub_obj) testTracker.o -o $@ $(CXXFLAGS) $(headers)

# clean
clean:
	rm -f *.o *.x *.a
