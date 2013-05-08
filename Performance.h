#ifndef ROCNROLL_PERFORMANCE_H
#define ROCNROLL_PERFORMANCE_H

#include <stdexcept>
#include "Prediction.h"
#include "Measure.h"
#include <vector>
#include "Performance.h"
#include "misc.h"

using namespace std;
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

  Prediction prediction;

  vector<double> x_values;
  vector<double> y_values;

  vector<double> alpha_values;

  void combine();

public:
  Performance(const Prediction& prediction_) : measure_x(MX()), measure_y(MY()), prediction(prediction_) {}
  void printJSON(const string& name);
  void printJSON();
  void compute();
};



template <class MX, class MY>
void Performance<MX, MY>::combine()
{
}

template <class MX, class MY>
void Performance<MX, MY>::compute()
{
  y_values.clear();
  x_values.clear();
  alpha_values.clear();

  for(int i=0; i < prediction.num_uniq_pred; i++)
  { 
    double mx = measure_x.compute(
        prediction.num_neg,
        prediction.num_pos,
        prediction.cutoffs[i],
        prediction.fp[i],
        prediction.tp[i],
        prediction.fn[i],
        prediction.tn[i]
    );

    if(!is_finite<double>(mx))
      throw BadNumber("x-measure: non-finite number in element " + to_string(i) + ": " + to_string(mx));

    x_values.push_back(mx);

    double my = measure_y.compute(
        prediction.num_neg,
        prediction.num_pos,
        prediction.cutoffs[i],
        prediction.fp[i],
        prediction.tp[i],
        prediction.fn[i],
        prediction.tn[i]
    );

    if(!is_finite(my))
      throw BadNumber("y-measure: non-finite number in element " + to_string(i) + ": " + to_string(my));

    y_values.push_back(my);

    if(!is_finite(prediction.cutoffs[i]))
      throw BadNumber("cutoff: non-finite number in element " + to_string(i) + ": " + to_string(prediction.cutoffs[i]));

    alpha_values.push_back(prediction.cutoffs[i]);
  }
  return;
}

template <class MX, class MY>
void Performance<MX, MY>::printJSON(const string& name)
{
  cout.precision(15);
  cout << "{" << endl;
  if(!name.empty())
    cout << "  \"_name\":\"" << name << "\"," << endl;
  cout << "  \"x\":[" << join<vector<double>::const_iterator>(x_values.begin(), x_values.end(), ",") << "]," << endl;
  cout << "  \"y\":[" << join<vector<double>::const_iterator>(y_values.begin(), y_values.end(), ",") << "]," << endl;

  cout << "  \"x_measure\":\"" <<  MX::name() << "\"," << endl;
  cout << "  \"y_measure\":\"" << MY::name() << "\"," << endl;

  cout << "  \"alpha_values\":[" << join<vector<double>::const_iterator>(alpha_values.begin(), alpha_values.end(), ",") << "]" << endl;

  cout << "}";
}

template <class MX, class MY>
void Performance<MX, MY>::printJSON()
{
  printJSON(string());
}

#endif
