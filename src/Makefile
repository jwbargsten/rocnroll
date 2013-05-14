.PHONY: all

CXX=g++
RM=rm
CXXFLAGS=-std=c++0x -O3 -fomit-frame-pointer -march=native 
LDFLAGS=
LDLIBS=

DEPS=approx.h IPerformance.h misc.h Performance.h PerformanceMeasure.h Prediction.h
SRCS=Prediction.cpp misc.cpp approx.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: calc_auc calc_all_yaml calc_avg_yaml

calc_auc: $(OBJS) $(DEPS) calc_auc.o
	g++ $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

calc_all_yaml: $(OBJS) $(DEPS) calc_all_yaml.o
	g++ $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

calc_avg_yaml: $(OBJS) $(DEPS) calc_avg_yaml.o 
	g++ $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) -v *.o
