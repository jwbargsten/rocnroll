#include <vector>
#include "Performance.h"

using namespace std;

template <class MX, class MY>
void Performance<MX, MY>::combine()
{
}

template <class MX, class MY>
vector<pair<double, double>> Performance<MX, MY>::compute()
{
  for(int i=0; i < prediction.num_pred; i++)
  { 
    double mx = measure_x.compute(
        prediction.num_neg,
        prediction.num_pos,
        prediction.fp[i],
        prediction.tp[i],
        prediction.fn[i],
        prediction.tn[i]
    );
  }

}

template <class MX, class MY>
vector<pair<double, double>> Performance<MX, MY>::result()
{
}
