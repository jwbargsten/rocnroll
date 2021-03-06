#include <config.h>
#include <fstream>
#include <limits>
#include <string>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include <algorithm>

#include <getopt.h>

#include "PerformanceMeasure.h"
#include "Performance.h"
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

  int c;
  while((c =  getopt(argc, argv, "s")) != -1)
    switch (c) {
      case 's':
        isSlim = true;
        cerr << "slim output: no predictions and labels included" << endl;
        break;
      }


  std::cout.precision(15);

  shared_ptr<unordered_map<string, pair<vector<double>, vector<int> > > > data = readData(argv[optind]);

  /* calc cutoff/fp/tp for every cv */

  /* computed measures (not necessary, output goes to stdout) */
  //unordered_map<string, Prediction> rocdata;

  /* iterate over x-validations */
  unordered_map<string, pair<vector<double>, vector<int>>>::iterator it;
  for(it = data->begin(); it != data->end(); ++it) {
    cerr << it->first << endl;
    /* first is the name of the group */
    /* second -> the label-prediction pair 2nd second -> the label */
    Prediction unroc(it->second.first, it->second.second);
    unroc.compute();

    cout << "---" << endl;
    cout << "pred:" << endl;
    unroc.printYAML(it->first, isSlim, " ");

    Performance<PerfM::FPR, PerfM::TPR> perf_roc(unroc);
    perf_roc.compute();

    cout << "perf_roc:" << endl;
    perf_roc.printYAML(it->first, " ");

    Performance<PerfM::None, PerfM::AUCROC> perf_auc(unroc);
    perf_auc.compute();

    cout << "perf_auc:" << endl;
    perf_auc.printYAML(it->first, " ");

    Performance<PerfM::TPR, PerfM::PPV> perf_pr(unroc);
    perf_pr.compute();

    cout << "perf_pr:" << endl;
    perf_pr.printYAML(it->first, " ");

    cerr << endl;

  }

}
