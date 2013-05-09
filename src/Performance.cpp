#include <vector>
#include "Performance.h"
#include "misc.h"
#include "Measure.h"

using namespace std;

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

    if(!is_finite(mx))
      throw BadNumber("x-measure: non-finite number in element " + i);

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

    if(!is_finite(mx))
      throw BadNumber("y-measure: non-finite number in element " + i);

    y_values.push_back(my);

    if(!is_finite(prediction.cutoffs[i]))
      throw BadNumber("cutoff: non-finite number in element " + i);

    alpha_values.push_back(prediction.cutoffs[i]);
  }
  return;
}
