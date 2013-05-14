#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include <algorithm>

#include "Performance.h"
#include "PerformanceMeasure.h"
#include "misc.h"

namespace PerfM = PerformanceMeasure;

using namespace std;

/*
 * input data structure: group <tab> prediction <tab> label
 * lables are assumed to be 0 (negative) and 1 (positive)
 * all number are assumed to be finite
 *
 */
int main(int argc, char *argv[])
{

  bool isSlim = false;

  std::cout.precision(15);

  int optind = 1;
  cerr << "reading in " << argv[optind] << endl;
  string file(argv[optind]);

  unordered_map<string, pair<vector<double>, vector<int> > > data = readData(file);

  /* calc cutoff/fp/tp for every cv */

  /* computed measures (not necessary, output goes to stdout) */
  //unordered_map<string, Prediction> rocdata;

  /* set header */
  cout << "group\tn_pred\tn_uniq_pred\tn_neg\tn_pos\tn_pred_zero\tn_pred_one\taucroc\taucpr\tfmax" << endl;

  /* iterate over x-validations */
  unordered_map<string, pair<vector<double>, vector<int>>>::const_iterator it;
  for(it = data.begin(); it != data.end(); ++it) {
    cerr << it->first << ": ";
    /* first is the name of the group */
    /* second -> the label-prediction pair 2nd second -> the label */
    Prediction unroc(it->second.first, it->second.second);
    unroc.compute();

    Performance<PerfM::None, PerfM::AUCROC> perf_aucroc(unroc);
    perf_aucroc.compute();

    Performance<PerfM::None, PerfM::AUCPR> perf_aucpr(unroc);
    perf_aucpr.compute();

    Performance<PerfM::None, PerfM::FMAX> perf_fmax(unroc);
    perf_fmax.compute();

    cerr << endl;
    cout << it->first
      << "\t" 
      << unroc.num_pred
      << "\t" 
      << unroc.num_uniq_pred
      << "\t" 
      << unroc.num_neg
      << "\t" 
      << unroc.num_pos
      << "\t" 
      << unroc.num_pred_zero
      << "\t" 
      << unroc.num_pred_one
      << "\t" 
      << perf_aucroc.y_values.front() 
      << "\t" 
      << perf_aucpr.y_values.front()
      << "\t" 
      << perf_fmax.y_values.front()
      << endl;
  }

}
