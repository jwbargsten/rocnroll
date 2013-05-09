#include <vector>
#include <utility>

using namespace std;
pair<vector<double>, vector<double> > tie_mean(const vector<double>& x, const vector<double>& y);

class SimpleInterpolation {
  bool constant_interpolation;
  //constant = method 2, linear = method 1
  // rule = 1: NA, rule = 2: closest to extreme

  double ylow;
  double yhigh;
  double f1;
  double f2;

  vector<double> x;
  vector<double> y;

  public:
    SimpleInterpolation(const vector<double>& x_, const vector<double>& y_, const double& f_, const pair<int, int>& rule_, const bool& constant_interpolation_);
    double interpolate(const double& v);
};
