.PHONY: all test

CXX=g++
CXXTEST=cxxtestgen
CXXTESTFLAGS=--error-printer 
RM=rm
CXXFLAGS=-std=c++0x -O3 -fomit-frame-pointer -march=native 

SRCS=$(addprefix ../src/,Prediction.cpp misc.cpp approx.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))
 
LDFLAGS=
LDLIBS=

all: test_measure test_approx

%.test.cpp: %.test.h
	$(CXXTEST) $(CXXTESTFLAGS) -o $@ $< 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

test_measure: $(OBJS) measure.test.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	./$@

test_approx: $(OBJS) approx.test.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	./$@

clean:
	$(RM) -v *.o *.cpp
