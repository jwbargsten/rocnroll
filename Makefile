.PHONY: all


all:
	#normal
	g++ -std=c++0x -O3 -fomit-frame-pointer -march=native -o calc_curves calc_curves.cpp ROCCurveUnnormalized.cpp Performance.cpp
	#debug version
	#g++ -O3 -pg -march=native -o kmer_gp kmer.cpp
performance_test:
	g++ -std=c++0x -O3 -fomit-frame-pointer -march=native -o ptest ptest.cpp Performance.cpp ROCCurveUnnormalized.cpp

