#include <limits>
#include <vector>
#include <utility>
#include "approx.h"

pair<vector<double>, vector<double> > tie_mean(const vector<double>& x, const vector<double>& y)
{

  vector<double> x_tie;
  vector<double> y_tie;

  if(x.size() != y.size())
    throw std::runtime_error("size of x and y values are not equal");

  double last_x;
  int current_tie_size = 0;

  vector<double>::const_iterator itx;
  vector<double>::const_iterator ity;

  for(itx = x.begin(), ity = y.begin(); itx != x.end() && ity != y.end(); ++itx, ++ity) {

    if(!is_finite<double>(*itx))
      continue;
    if(!is_finite<double>(*ity))
      continue;

    if(itx != x.begin() && last_x == *itx)
    {
      /* this value and the last are now in the tie-bin */
      if(current_tie_size = 0)
        current_tie_size++;
      current_tie_size++;
      y_tie.back() += *ity;
      continue;
    }
    if(current_tie_size > 0)
    {
      y_tie.back() /= current_tie_size;
      current_tie_size = 0;
    }

    x_tie.push_back(*itx);
    y_tie.push_back(*ity);

    last_x = *itx;
  }

  return make_pair(x_tie, y_tie);
}

