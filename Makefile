.PHONY: all

all:
	g++ -std=c++0x -O3 -fomit-frame-pointer -march=native -o calc_curves calc_curves.cpp misc.cpp ROCCurveUnnormalized.cpp 
