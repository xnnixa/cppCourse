# Variables
CXX = g++
CXXFLAGS = -Wall -g
OBJS = main.o intro.o RGB/rgbapixel.o RGB/png.o
EXE = intro

# Default target
all: $(EXE)

# Linking rule
$(EXE): $(OBJS)
	$(CXX) $(OBJS) -o $(EXE) -lpng

# Compilation rules
main.o: main.cpp intro.h RGB/rgbapixel.h
	$(CXX) $(CXXFLAGS) -c main.cpp

intro.o: intro.cpp intro.h RGB/rgbapixel.h
	$(CXX) $(CXXFLAGS) -c intro.cpp

RGB/rgbapixel.o: RGB/rgbapixel.cpp RGB/rgbapixel.h
	$(CXX) $(CXXFLAGS) -c RGB/rgbapixel.cpp -o RGB/rgbapixel.o

RGB/png.o: RGB/png.cpp RGB/png.h
	$(CXX) $(CXXFLAGS) -c RGB/png.cpp -o RGB/png.o

# Clean rule
clean:
	rm -f $(OBJS) $(EXE)