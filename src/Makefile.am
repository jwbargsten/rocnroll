AM_CPPFLAGS=-fomit-frame-pointer -std=c++0x 
AM_LDFLAGS=-std=c++0x 
COMMON_SOURCES=approx.h IPerformance.h misc.h Performance.h PerformanceMeasure.h Prediction.h Prediction.cpp misc.cpp approx.cpp 
#LDADD=Performance.h 
LDADD=$(LIBH5)

bin_PROGRAMS=calc_auc calc_all_yaml calc_avg_yaml 

if USE_LIBH5
bin_PROGRAMS+=calc_avg_h5
COMMON_SOURCES+= H5IO.h H5IO.cpp

calc_avg_h5_SOURCES=$(COMMON_SOURCES) calc_avg_h5.cpp
endif

calc_auc_SOURCES=$(COMMON_SOURCES) calc_auc.cpp
calc_all_yaml_SOURCES=$(COMMON_SOURCES) calc_all_yaml.cpp
calc_avg_yaml_SOURCES=$(COMMON_SOURCES) calc_avg_yaml.cpp

