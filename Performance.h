#ifndef ROCNROLL_PERFORMANCE_H
#define ROCNROLL_PERFORMANCE_H

#include <stdexcept>
#include "ROCCurveUnnormalized.h"

class BadNumber : public std::runtime_error {
public:
  BadNumber(std::string const& s)
    : std::runtime_error(s)
    { }
};

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
  Performance(const ROCCurveUnnormalized& prediction_) : measure_x(MX()), measure_y(MY()), prediction(prediction_) {}
  void compute();
  vector<pair<double, double>> result();

};


// calc measure
// combine by cutoff
// approx 
  //function(predictions, labels, cutoffs, fp, tp, fn, tn,
           //n.pos, n.neg, n.pos.pred, n.neg.pred, fpr.stop) {
#endif
