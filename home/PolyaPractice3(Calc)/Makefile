# Initializing variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g -O2
LDFLAGS = -lm -lSDL2

all: Calc.o Combinatoric.o Fraction.o Functional.o Jwfunc.o Math_probability.o Matrix.o
	$(CXX) $(CXXFLAGS) Calc.o Combinatoric.o Fraction.o Functional.o Jwfunc.o Math_probability.o Matrix.o -o PolyaCalc $(LDFLAGS)

Calc.o: Calc.cpp
	$(CXX) $(CXXFLAGS) -c Calc.cpp

Combinatoric.o: Combinatoric.cpp
	$(CXX) $(CXXFLAGS) -c Combinatoric.cpp

Fraction.o: Fraction.cpp
	$(CXX) $(CXXFLAGS) -c Fraction.cpp

Functional.o: Functional.cpp
	$(CXX) $(CXXFLAGS) -c Functional.cpp

Jwfunc.o: Jwfunc.cpp
	$(CXX) $(CXXFLAGS) -c Jwfunc.cpp

Math_probability.o: Math_probability.cpp
	$(CXX) $(CXXFLAGS) -c Math_probability.cpp

Matrix.o: Matrix.cpp
	$(CXX) $(CXXFLAGS) -c Matrix.cpp

clean:
	rm -f *.o PolyaCalc
