.PHONY: all

CXX=g++
RM=rm
CXXFLAGS=-std=c++0x -O3 -fomit-frame-pointer -march=native
LDFLAGS=
LDLIBS=-lhdf5_cpp -lhdf5

DEPS=approx.h IPerformance.h misc.h Performance.h PerformanceMeasure.h Prediction.h H5IO.h
SRCS=Prediction.cpp misc.cpp approx.cpp H5IO.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: calc_auc calc_all_yaml calc_avg_yaml calc_avg_h5

calc_auc: $(OBJS) $(DEPS) calc_auc.o
	g++ $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

calc_all_yaml: $(OBJS) $(DEPS) calc_all_yaml.o
	g++ $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

calc_avg_yaml: $(OBJS) $(DEPS) calc_avg_yaml.o
	g++ $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

calc_avg_h5: $(OBJS) $(DEPS) calc_avg_h5.o
	g++ $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) -v *.o
