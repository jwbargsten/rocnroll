#include <vector>
#include <utility>

using namespace std;

pair<vector<double>, vector<double> > tie_mean(const vector<double>& x_, const vector<double>& y_);

class SimpleInterpolation {
  //compared to R: constant = method 2, linear = method 1
  bool constant_interpolation;

  double ylow;
  double yhigh;
  double f1;
  double f2;
  /* f with constant :
   * If ‘y0’ and ‘y1’ are the values to the left
   * and right of the point then the value is ‘y0*(1-f)+y1*f’ so
   * that ‘f = 0’ is right-continuous and ‘f = 1’ is
   * left-continuous.
   */

  vector<double> x;
  vector<double> y;

  // rule = 1: NA, rule = 2: closest to extreme
  public:
    SimpleInterpolation(const vector<double>& x_, const vector<double>& y_, const double& f_, const pair<int, int>& rule_, const bool& constant_interpolation_);
    SimpleInterpolation() {}
    double interpolate(const double& v);
};
