#ifndef ROCNROLL_PERFORMANCE_H
#define ROCNROLL_PERFORMANCE_H

#include <stdexcept>
#include <algorithm>
#include <vector>
#include <H5Cpp.h>

#include <cmath>

#include "Prediction.h"
#include "misc.h"
#include "approx.h"
#include "IPerformance.h"


using namespace std;
using namespace H5;

template <class MX, class MY>
class Performance : public IPerformance {
    Prediction prediction;
    MX measure_x;
    MY measure_y;

  public:
    vector<double> x_values;
    vector<double> y_values;

    vector<double> alpha_values;
    string alpha_name;

    Performance(const Prediction& prediction_) : measure_x(MX()), measure_y(MY()), prediction(prediction_) {}

    Performance() : measure_x(MX()), measure_y(MY()) {}

    Performance(const vector<double>& x_values_, const vector<double>& y_values_, const vector<double>& alpha_values_, const string& alpha_name_)
      : measure_x(MX()), measure_y(MY()), x_values(x_values_), y_values(y_values_), alpha_values(alpha_values_), alpha_name(alpha_name_)
    {}

    virtual void compute();
    virtual void makeFinite();
    virtual void printYAML();
    virtual void printYAML(const string& name, const string& indent);

    void H5Add(H5File& file, const string& grp_name, const string& name);
};



template <class MX, class MY>
void
Performance<MX, MY>::compute()
{
  y_values.clear();
  x_values.clear();
  alpha_values.clear();

  x_values = measure_x.compute(
      prediction.num_uniq_pred,
      prediction.num_neg,
      prediction.num_pos,
      prediction.cutoffs,
      prediction.fp,
      prediction.tp,
      prediction.fn,
      prediction.tn
    );

  y_values = measure_y.compute(
      prediction.num_uniq_pred,
      prediction.num_neg,
      prediction.num_pos,
      prediction.cutoffs,
      prediction.fp,
      prediction.tp,
      prediction.fn,
      prediction.tn
    );

  /* set alpha values to cutoff if we have fitting measures */
  if(x_values.size() == y_values.size() && x_values.size() == prediction.num_uniq_pred) {
    alpha_values = prediction.cutoffs;
    alpha_name = "cutoff";
  } else {
    alpha_name = "none";
  }

  return;
}

template <class MX, class MY>
void
Performance<MX, MY>::printYAML(const string& name, const string& indent)
{
  cout.precision(15);

  if(!name.empty())
    cout << indent << "name: \"" << name << "\"" << endl;
  cout << indent << "x_values: [" << joinDoubleYAML(x_values.begin(), x_values.end(), ", ") << "]" << endl;

  cout << indent << "y_values: [" << joinDoubleYAML(y_values.begin(), y_values.end(), ", ") << "]" << endl;

  cout << indent << "x_name: " << MX::name() << endl;
  cout << indent << "y_name: " << MY::name() << endl;

  cout << indent << "alpha_values: [" << joinDoubleYAML(alpha_values.begin(), alpha_values.end(), ", ") << "]" << endl;
}

inline void
write_hdf5(H5File& file, vector<double> const& v, string const& name)
{
  if(v.size() == 0) {
    DataSpace dspace(H5S_NULL);
    DataSet dset = file.createDataSet( name, PredType::NATIVE_DOUBLE, dspace );
  } else {
    hsize_t dim[1];
    dim[0] = v.size();
    DataSpace dspace(1, dim); // create new dspace
    FloatType dtype( PredType::NATIVE_DOUBLE );
    DataSet dset = file.createDataSet( name, dtype, dspace );
    dset.write(v.data(), dtype);
  }
  return;
}

inline void
write_hdf5(H5File& file, string const& v, string const& name)
{
  hsize_t dim[1];
  dim[0] = 1;
  const char *t[1] = { v.c_str() };

  DataSpace dspace(1, dim); // create new dspace
  StrType dtype(0, H5T_VARIABLE);
  DataSet dset = file.createDataSet( name, dtype, dspace );
  dset.write(t, dtype);
  return;
}

template <class MX, class MY>
void
Performance<MX, MY>::H5Add(H5File& file, const string& grp_name, const string& name = "unnamed")
{
  file.createGroup( "/" + grp_name );

  if(!name.empty())
    write_hdf5(file, name, "/" + grp_name + "/name");

  write_hdf5(file, y_values, "/" + grp_name + "/y_values");
  write_hdf5(file, x_values, "/" + grp_name + "/x_values");
  write_hdf5(file, alpha_values, "/" + grp_name + "/alpha_values");
  write_hdf5(file, MX::name(), "/" + grp_name + "/x_name");
  write_hdf5(file, MY::name(), "/" + grp_name + "/y_name");

  return;
}

template <class MX, class MY>
void
Performance<MX, MY>::printYAML()
{
  printYAML(string(), "");
}

template <class MX, class MY>
void
Performance<MX, MY>::makeFinite()
{

  double max = -std::numeric_limits<double>::infinity();
  double diff_mean = 0;

  vector<int> inf_idcs;

  int num_finite_idcs = 0;
  int last_finite_idx = -1;

  for(int i = 0; i< alpha_values.size(); i++) {
    if(is_finite(alpha_values[i])) {

      if(last_finite_idx >= 0) {
        diff_mean += abs(alpha_values[i] - alpha_values[i-1]);
        num_finite_idcs++;
      }

      last_finite_idx = i;

      if(alpha_values[i] > max)
        max = alpha_values[i];
    } else {
      inf_idcs.push_back(i);
    }
  }


  double max_inf = max + (diff_mean/num_finite_idcs);

  for(vector<int>::const_iterator it = inf_idcs.begin(); it != inf_idcs.end(); ++it)
    alpha_values[*it] = max_inf;

  vector<double> x_values_finite;
  vector<double> y_values_finite;
  vector<double> alpha_values_finite;

  vector<double>::const_iterator itx = x_values.begin();
  vector<double>::const_iterator ity = y_values.begin();
  vector<double>::const_iterator ita = alpha_values.begin();

  for(; itx != x_values.end(); ++itx, ++ity, ++ita) {
    if(is_finite(*itx) && is_finite(*ity)) {
      x_values_finite.push_back(*itx);
      y_values_finite.push_back(*ity);
      alpha_values_finite.push_back(*ita);
    }
  }

  alpha_values = alpha_values_finite;
  x_values = x_values_finite;
  y_values = y_values_finite;

  return;
}

template <class MX, class MY>
Performance<MX, MY> averagePerformance(vector<Performance<MX, MY> > perfs)
{

  /* find the minimum, maximum and the longest sample of all alpha values */

  double max = -std::numeric_limits<double>::infinity();
  double min = std::numeric_limits<double>::infinity();
  int cnt_longest = 0;

  for(typename vector<Performance<MX, MY> >::iterator it = perfs.begin(); it != perfs.end(); ++it) {
    it->makeFinite();
    double tmax = *max_element(it->alpha_values.begin(), it->alpha_values.end());
    double tmin = *min_element(it->alpha_values.begin(), it->alpha_values.end());
    if(tmax > max)
      max = tmax;
    if(tmin < min)
      min = tmin;
    if(it->alpha_values.size() > cnt_longest)
      cnt_longest = it->alpha_values.size();
  }

  vector<double> alpha_values_avg = numseq(min, max, cnt_longest);
  reverse(alpha_values_avg.begin(), alpha_values_avg.end());

  vector<double> x_values_avg(cnt_longest, 0);
  vector<double> y_values_avg(cnt_longest, 0);

  int cnt_valid_perfs = 0;
  for(typename vector<Performance<MX, MY> >::iterator it = perfs.begin(); it != perfs.end(); ++it) {
    /* interpolate new adjusted x-values with average alpha values */
    /* SimpleInterpolation(
     *  const vector<double>& x_,
     *  const vector<double>& y_,
     *  const double& f_,
     *  const pair<int, int>& rule_,
     *  const bool& constant_interpolation_
     * )
     */
    if(it->alpha_values.size() < 2)
      continue;

    try {
      SimpleInterpolation xapprox = SimpleInterpolation(it->alpha_values, it->x_values, 0, make_pair(2,2), false);
      SimpleInterpolation yapprox = SimpleInterpolation(it->alpha_values, it->y_values, 0, make_pair(2,2), false);

      for(int i = 0; i < cnt_longest; i++) {
        x_values_avg[i] += xapprox.interpolate(alpha_values_avg[i]);
        y_values_avg[i] += yapprox.interpolate(alpha_values_avg[i]);
      }
      cnt_valid_perfs++;
    } catch (std::runtime_error& e) {
      cerr << "Warning: " << e.what() << ", skipping group" << endl;
      continue;
    }
  }

  for(int i = 0; i< alpha_values_avg.size(); i++) {
    x_values_avg[i] /= cnt_valid_perfs;
    y_values_avg[i] /= cnt_valid_perfs;
  }

  Performance<MX, MY> avg_perf(x_values_avg, y_values_avg, alpha_values_avg, "avgcutoff");
  return avg_perf;
}

#endif
