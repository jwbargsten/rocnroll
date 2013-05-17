#ifndef ROCNROLL_PERFORMANCE_H
#define ROCNROLL_PERFORMANCE_H

#include <stdexcept>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <H5Cpp.h>

#include <cmath>

#include "Prediction.h"
#include "misc.h"
#include "approx.h"
#include "IPerformance.h"
#include "H5IO.h"


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

    void H5Add(H5File *file, const string& grp_name, const string& name);
    void H5Add(H5File* file, const string& grp_name);
    void H5Add(H5File* file);
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


template <class MX, class MY>
void
Performance<MX, MY>::H5Add(H5File* file, const string& grp_name, const string& name)
{
  std::ostringstream prefix;
  prefix << "/";
  if(!grp_name.empty()) {
    prefix << grp_name << "/";
    file->createGroup( "/" + grp_name );
  }

  if(!name.empty())
    write_hdf5(file, name, prefix.str() + "name");

  write_hdf5(file, y_values, prefix.str() + "y_values");
  write_hdf5(file, x_values, prefix.str() + "x_values");
  write_hdf5(file, alpha_values, prefix.str() + "alpha_values");
  write_hdf5(file, MX::name(), prefix.str() + "x_name");
  write_hdf5(file, MY::name(), prefix.str() + "y_name");

  return;
}

template <class MX, class MY>
void
Performance<MX, MY>::H5Add(H5File* file, const string& grp_name)
{
  return H5Add(file, grp_name, "unnamed");
}

template <class MX, class MY>
void
Performance<MX, MY>::H5Add(H5File* file)
{
  return H5Add(file, "", "unnamed");
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

  /* the idea is to find the maximum to substitute inf with ... */
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


  /* ... max + (mean of (differences between consecutive alpha_values)) ... */
  double max_inf = max + (diff_mean/num_finite_idcs);

  /* ... in all all alpha_values that are not finite */
  for(vector<int>::const_iterator it = inf_idcs.begin(); it != inf_idcs.end(); ++it)
    alpha_values[*it] = max_inf;

  vector<double> x_values_finite;
  vector<double> y_values_finite;
  vector<double> alpha_values_finite;

  vector<double>::const_iterator itx = x_values.begin();
  vector<double>::const_iterator ity = y_values.begin();
  vector<double>::const_iterator ita = alpha_values.begin();

  /* omit all tuples (x, y, alpha_value) where either x or y are not finite */
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

struct avgPerformanceResultInfo {
  int valid_groups;
  int skipped_groups;
  int total_groups;
};


template <class MX, class MY>
pair<Performance<MX, MY>,avgPerformanceResultInfo> averagePerformance(vector<Performance<MX, MY> > perfs)
{

  /* find the minimum, maximum and the longest sample of all alpha values */

  double max = -std::numeric_limits<double>::infinity();
  double min = std::numeric_limits<double>::infinity();
  int cnt_longest = 0;

  for(typename vector<Performance<MX, MY> >::iterator it = perfs.begin(); it != perfs.end(); ++it) {
    it->makeFinite();
    /* find minimum and maximum of alpha_values over all groups */
    double tmax = *max_element(it->alpha_values.begin(), it->alpha_values.end());
    double tmin = *min_element(it->alpha_values.begin(), it->alpha_values.end());
    if(tmax > max)
      max = tmax;
    if(tmin < min)
      min = tmin;
    /* also find the group with longest alpha_values vector (needed for interpolation) */
    if(it->alpha_values.size() > cnt_longest)
      cnt_longest = it->alpha_values.size();
  }

  /* create a equally spaced sequence of alpha_values to represent the average alpha_values */
  vector<double> alpha_values_avg = numseq(min, max, cnt_longest);
  reverse(alpha_values_avg.begin(), alpha_values_avg.end());

  /* initialize the average x and y values with 0 */
  vector<double> x_values_avg(cnt_longest, 0);
  vector<double> y_values_avg(cnt_longest, 0);

  /* keep track of valid (for avg calculation) missing (just for info) groups */
  avgPerformanceResultInfo info;
  info.total_groups = perfs.size();
  info.valid_groups = 0;
  info.skipped_groups = 0;

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

    SimpleInterpolation xapprox;
    SimpleInterpolation yapprox;

    /* only add to total avg, if SimpleInterpolation does not have any errors */
    try {
      xapprox = SimpleInterpolation(it->alpha_values, it->x_values, 0, make_pair(2,2), false);
      yapprox = SimpleInterpolation(it->alpha_values, it->y_values, 0, make_pair(2,2), false);

      /* and count the group */
      info.valid_groups++;

    } catch (std::runtime_error& e) {
      cerr << "Warning: " << e.what() << ", skipping group" << endl;

      /* or skip the complete group if we cannot interpolate,
       * a common problem is a vector of alpha values with (0, Inf)
       */
      info.skipped_groups++;
      continue;
    }

    /* add up interpolated x and y values */
    for(int i = 0; i < cnt_longest; i++) {
      x_values_avg[i] += xapprox.interpolate(alpha_values_avg[i]);
      y_values_avg[i] += yapprox.interpolate(alpha_values_avg[i]);
    }
  }

  /* calculate the mean/average */
  for(int i = 0; i< alpha_values_avg.size(); i++) {
    x_values_avg[i] /= info.total_groups;
    y_values_avg[i] /= info.total_groups;
  }

  /* create a performance object from the averages */
  Performance<MX, MY> avg_perf(x_values_avg, y_values_avg, alpha_values_avg, "avgcutoff");
  return make_pair(avg_perf, info);
}

#endif
