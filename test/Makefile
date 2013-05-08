.PHONY: all test

test:
	cxxtestgen --error-printer -o approx.test.cpp approx.test.h 
	g++ -o t approx.test.cpp ../src/approx.cpp
	./t
