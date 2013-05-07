#include "ROCCurveUnnormalized.h"

template <class MX, class MY>
class Performance {
  MX measure_x;
  MY measure_y;

  ROCCurveUnnormalized prediction;

  vector<double> x_values;
  vector<double> y_values;

  vector<double> alpha_values;

  void combine();

public:
  vector<pair<double, double>> compute();
  vector<pair<double, double>> result();


};

// calc measure
// combine by cutoff
// approx 
  //function(predictions, labels, cutoffs, fp, tp, fn, tn,
           //n.pos, n.neg, n.pos.pred, n.neg.pred, fpr.stop) {
