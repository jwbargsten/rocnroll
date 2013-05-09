.PHONY: all test

test_measure:
	cxxtestgen --error-printer -o measure.test.cpp measure.test.h
	g++ -o t_measure measure.test.cpp ../src/misc.cpp
	./t

test_approx:
	cxxtestgen --error-printer -o approx.test.cpp approx.test.h 
	g++ -o t_approx approx.test.cpp ../src/approx.cpp
	./t_approx
