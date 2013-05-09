#ifndef ROCNROLL_PERFORMANCE_H
#define ROCNROLL_PERFORMANCE_H

#include <stdexcept>
#include "Prediction.h"
#include "Measure.h"
#include <vector>
#include "misc.h"

using namespace std;

template <class MX, class MY>
class Performance {
  MX measure_x;
  MY measure_y;

  Prediction prediction;


public:
  vector<double> x_values;
  vector<double> y_values;

  vector<double> alpha_values;
  string alpha_name;

  Performance(const Prediction& prediction_) : measure_x(MX()), measure_y(MY()), prediction(prediction_) {}
  void printYAML(const string& name, const string& indent);
  void printYAML();
  void compute();
};



template <class MX, class MY>
void Performance<MX, MY>::compute()
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
void Performance<MX, MY>::printYAML(const string& name, const string& indent)
{
  cout.precision(15);
  if(!name.empty())
    cout << indent << "_name: " << name << endl;
  cout << indent << "x_values:" << endl;
  cout << indent << " - " << join<vector<double>::const_iterator>(x_values.begin(), x_values.end(), "\n" + indent + " - ") << endl;

  cout << indent << "y_values:" << endl;
  cout << indent << " - " << join<vector<double>::const_iterator>(y_values.begin(), y_values.end(), "\n" + indent + " - ") << endl;

  cout << indent << "x_name: " << MX::name() << endl;
  cout << indent << "y_name: " << MY::name() << endl;

  cout << indent << "alpha_values:" << endl;
  cout << indent << " - " << join<vector<double>::const_iterator>(alpha_values.begin(), alpha_values.end(), "\n" + indent + " - ") << endl;

}

template <class MX, class MY>
void Performance<MX, MY>::printYAML()
{
  printYAML(string(), "");
}

#endif
