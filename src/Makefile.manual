.PHONY: all

CXX=g++
RM=rm
CXXFLAGS=-std=c++0x -O3 -fomit-frame-pointer -march=native
LDFLAGS=
LDLIBS=
DEPS=approx.h IPerformance.h misc.h Performance.h PerformanceMeasure.h Prediction.h
SRCS=Prediction.cpp misc.cpp approx.cpp 
OBJS=$(subst .cpp,.o,$(SRCS))

DEPSH5=$(DEPS) H5IO.h
SRCSH5=$(SRCS) H5IO.cpp
OBJSH5=$(subst .cpp,.o,$(SRCSH5))

all: calc_auc calc_all_yaml calc_avg_yaml 

allh5: all calc_avg_h5

calc_auc: $(OBJS) $(DEPS) calc_auc.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

calc_all_yaml: $(OBJS) $(DEPS) calc_all_yaml.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

calc_avg_yaml: $(OBJS) $(DEPS) calc_avg_yaml.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

calc_avg_h5: $(OBJSH5) $(DEPSH5) calc_avg_h5.o
	LD_LIBRARY_PATH=../hdf5-1.8.11-linux-x86_64-shared/lib \
	$(CXX) \
		-I../hdf5-1.8.11-linux-x86_64-shared/include \
		$(CXXFLAGS) \
		-L../hdf5-1.8.11-linux-x86_64-shared/lib \
		$(LDFLAGS) \
		-o $@ \
		$^ \
		-lhdf5_cpp -lhdf5 \
		$(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) -v *.o
