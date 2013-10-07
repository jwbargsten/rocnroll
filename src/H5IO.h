#ifndef H5IO_H
#define H5IO_H

#include <config.h>
#include <vector>
#include <string>
#include <H5Cpp.h>

using namespace std;
using namespace H5;

void
write_hdf5(H5File* file, vector<double> const& v, string const& name);

void
write_hdf5(H5File* file, string const& v, string const& name);

void
write_hdf5(H5File *file, const double v, string const& name);

void
write_hdf5(H5File *file, const int v, string const& name);

#endif
