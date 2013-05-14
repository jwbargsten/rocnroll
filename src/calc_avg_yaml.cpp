#include <fstream>
#include <limits>
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <memory>

#include <getopt.h>

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

  int c;
  while((c =  getopt(argc, argv, "s")) != -1)
    switch (c) {
      case 's':
        isSlim = true;
        cerr << "slim output: no predictions and labels included" << endl;
        break;
      }


  std::cout.precision(15);

  cerr << "reading in " << argv[optind] << endl;
  string file(argv[optind]);
  unordered_map<string, pair<shared_ptr<vector<double>>, shared_ptr<vector<int> > > > data = readData(file);

  /* calc cutoff/fp/tp for every cv */

  /* computed measures (not necessary, output goes to stdout) */
  //unordered_map<string, Prediction> rocdata;

  vector<Performance<PerfM::FPR, PerfM::TPR> > perfs_roc;
  vector<Performance<PerfM::TPR, PerfM::PPV> > perfs_pr;
  /* iterate over x-validations */
  unordered_map<string, pair<shared_ptr<vector<double>>, shared_ptr<vector<int> > > >::const_iterator it;
  for(it = data.begin(); it != data.end(); ++it) {
    cerr << it->first << endl;
    /* first is the name of the group */
    /* second -> the label-prediction pair 2nd second -> the label */
    shared_ptr<Prediction> unroc(new Prediction(it->second.first, it->second.second));
    unroc->compute();

    Performance<PerfM::FPR, PerfM::TPR> perf_roc(unroc);
    perf_roc.compute();
    perfs_roc.push_back(perf_roc);

    Performance<PerfM::TPR, PerfM::PPV> perf_pr(unroc);
    perf_pr.compute();
    perfs_pr.push_back(perf_pr);

    cerr << endl;

  }
  cerr << "roc avg" << endl;
  Performance<PerfM::FPR, PerfM::TPR> perf_roc_avg = averagePerformance<PerfM::FPR, PerfM::TPR>(perfs_roc);
    cout << "---" << endl;
    cout << "perf_roc:" << endl;
    perf_roc_avg.printYAML("threshold_avg", " ");

  cerr << "pr avg" << endl;
  Performance<PerfM::TPR, PerfM::PPV> perf_pr_avg = averagePerformance<PerfM::TPR, PerfM::PPV>(perfs_pr);
    cout << "perf_pr:" << endl;
    perf_pr_avg.printYAML("theshold_avg", " ");
    cerr << endl;
}

 

