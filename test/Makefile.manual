.PHONY: all test

INCLUDE=-I$(HOME)/usr/include
CXX=g++
CXXTEST=cxxtestgen
CXXTESTFLAGS=--error-printer
RM=rm
CXXFLAGS=-std=c++0x -O3 -fomit-frame-pointer -march=native $(INCLUDE)
LDFLAGS=
LDLIBS=-lhdf5_cpp -lhdf5

DEPS=$(addprefix ../src/,approx.h IPerformance.h misc.h Performance.h PerformanceMeasure.h Prediction.h H5IO.h)
SRCS=$(addprefix ../src/,Prediction.cpp misc.cpp approx.cpp H5IO.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))


all: test_measure test_approx

%.test.cpp: %.test.h
	$(CXXTEST) $(CXXTESTFLAGS) -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< $(LDLIBS)

test_measure: $(OBJS) measure.test.o $(DEPS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	./$@

test_approx: $(OBJS) approx.test.o $(DEPS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	./$@

test_misc: $(OBJS) misc.test.o $(DEPS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	./$@

clean:
	$(RM) -v *.o *.cpp
