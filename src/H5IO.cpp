#include <vector>
#include <string>
#include <H5Cpp.h>

#include "H5IO.h"

using namespace std;
using namespace H5;

void
write_hdf5(H5File *file, vector<double> const& v, string const& name)
{
  if(v.size() == 0) {
    DataSpace dspace(H5S_NULL);
    DataSet dset = file->createDataSet( name, PredType::NATIVE_DOUBLE, dspace );
  } else {
    hsize_t dim[1];
    dim[0] = v.size();
    DataSpace dspace(1, dim); // create new dspace
    FloatType dtype( PredType::NATIVE_DOUBLE );
    DataSet dset = file->createDataSet( name, dtype, dspace );
    dset.write(v.data(), dtype);
  }
  return;
}

void
write_hdf5(H5File *file, const int v, string const& name)
{
  hsize_t dim[1];
  dim[0] = 1;
  int data[1];
  data[0] = v;
  
  DataSpace dspace(1, dim); // create new dspace
  IntType dtype( PredType::NATIVE_INT );
  DataSet dset = file->createDataSet( name, dtype, dspace );
  dset.write(data, dtype);
  return;
}

void
write_hdf5(H5File *file, const double v, string const& name)
{
  vector<double> d(1,v);
  write_hdf5(file, d, name);
  return;
}

void
write_hdf5(H5File *file, string const& v, string const& name)
{
  hsize_t dim[1];
  dim[0] = 1;
  const char *t[1] = { v.c_str() };

  DataSpace dspace(1, dim); // create new dspace
  StrType dtype(0, H5T_VARIABLE);
  DataSet dset = file->createDataSet( name, dtype, dspace );
  dset.write(t, dtype);
  return;
}
