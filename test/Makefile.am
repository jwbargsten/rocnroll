AM_CPPFLAGS=-fomit-frame-pointer -std=c++0x 
AM_LDFLAGS=-std=c++0x 

COMMON_SOURCES=approx.h IPerformance.h misc.h Performance.h PerformanceMeasure.h Prediction.h Prediction.cpp misc.cpp approx.cpp 

if USE_LIBH5
bin_PROGRAMS+=calc_avg_h5
COMMON_SOURCES+= H5IO.h H5IO.cpp

endif

COMMON_SOURCES=$(addprefix $(top_builddir),$(COMMON_SOURCES))


