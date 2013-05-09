.PHONY: all

CXX=g++
RM=rm
CXXFLAGS=-std=c++0x -O3 -fomit-frame-pointer -march=native 
LDFLAGS=
LDLIBS=

SRCS= Prediction.cpp misc.cpp approx.cpp

OBJS=$(subst .cpp,.o,$(SRCS))

all: calc_auc calc_all_json

calc_auc: $(OBJS) calc_auc.o
	g++ $(LDFLAGS) -o calc_auc $^ $(LDLIBS)

calc_all_json: $(OBJS) calc_all_json.o
	g++ $(LDFLAGS) -o calc_all_json $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) -v *.o


#calc_aucz:
	#g++ -std=c++0x -o calc_auc calc_auc.cpp Prediction.cpp misc.cpp
#calc_curves:
	#g++ -std=c++0x -O3 -fomit-frame-pointer -march=native -o calc_curves calc_curves.cpp Prediction.cpp misc.cpp
