#include <limits>
#include <vector>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include "misc.h"
#include "approx.h"


SimpleInterpolation::SimpleInterpolation(const vector<double>& x_, const vector<double>& y_, const double& f_, const pair<int, int>& rule_, const bool& constant_interpolation_)
  : constant_interpolation(constant_interpolation_)
{

  if(x_.size() != y_.size())
    throw std::runtime_error("size of x and y values are not equal");

  pair<vector<double>, vector<double> > tied = tie_mean(x_, y_);

  x = tied.first;
  y = tied.second;

  if(x.size() < 2)
    throw std::runtime_error("need at least two unique finite values to interpolate");

  f1 = f_;
  f2 = 1-f_;

  if(rule_.first == 1)
    ylow = - std::numeric_limits<double>::infinity();
  else
    ylow = y.front();

  if(rule_.second == 1)
    yhigh = std::numeric_limits<double>::infinity();
  else
    yhigh = y.back();

}

double SimpleInterpolation::interpolate(const double& v)
{
  if(!is_finite(v))
    return v;

  int n = x.size();

  /* Approximate  y(v),  given (x,y)[i], i = 0,..,n-1 */
  int i, j, ij;

  i = 0;
  j = n - 1;

  /* handle out-of-domain points */
  if(v < x.front()) return ylow;
  if(v > x.back()) return yhigh;

  /* find the correct interval by bisection */
  while(i < j - 1) { /* x[i] <= v <= x[j] */
    ij = (i + j)/2; /* i+1 <= ij <= j-1 */
    if(v < x[ij]) j = ij; else i = ij;
    /* still i < j */
  }
  /* provably have i == j-1 */

  /* interpolation */

  if(v == x[j]) return y[j];
  if(v == x[i]) return y[i];
  /* impossible: if(x[j] == x[i]) return y[i]; */

  if(!constant_interpolation) /* linear */
    return y[i] + (y[j] - y[i]) * ((v - x[i])/(x[j] - x[i]));
  else /* 2 : constant */
    return y[i] * f1 + y[j] * f2;
}/* approx1() */

pair<vector<double>, vector<double> >
tie_mean(const vector<double>& x_, const vector<double>& y_)
{
  vector<double> x;
  vector<double> y;

  vector<int> idcs = order(x_);


  for(vector<int>::const_reverse_iterator it = idcs.rbegin(); it != idcs.rend(); ++it) {
    x.push_back(x_[*it]);
    y.push_back(y_[*it]);
  }


  vector<double> x_tie;
  vector<double> y_tie;

  if(x.size() != y.size())
    throw std::runtime_error("size of x and y values are not equal");

  double last_x = std::numeric_limits<double>::infinity();
  int current_tie_size = 0;

  vector<double>::const_iterator itx;
  vector<double>::const_iterator ity;

  for(itx = x.begin(), ity = y.begin(); itx != x.end() && ity != y.end(); ++itx, ++ity) {
    if(!is_finite<double>(*itx))
      continue;
    if(!is_finite<double>(*ity))
      continue;

    if(itx != x.begin() && last_x == *itx) {
      /* this value and the last are now in the tie-bin */
      if(0 == current_tie_size)
        current_tie_size++;
      current_tie_size++;
      y_tie.back() += *ity;
      continue;
    }
    if(current_tie_size > 0) {
      y_tie.back() /= current_tie_size;
      current_tie_size = 0;
    }

    x_tie.push_back(*itx);
    y_tie.push_back(*ity);

    last_x = *itx;
  }

  /* the last x element could be a duplicate, too */
  if(current_tie_size > 0)
    y_tie.back() /= current_tie_size;

  return make_pair(x_tie, y_tie);
}
