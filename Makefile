.PHONY: all

all:
	#normal
	g++ -std=c++0x -O3 -fomit-frame-pointer -march=native -o calc_curves calc_curves.cpp
	#debug version
	#g++ -O3 -pg -march=native -o kmer_gp kmer.cpp

