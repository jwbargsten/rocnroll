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


  cerr << "reading in " << argv[optind] << endl;
  cerr << "writing to " << argv[optind+1] << endl;
  string file(argv[optind]);
  string outfile(argv[optind+1]);
  unordered_map<string, pair<vector<double>, vector<int> > > data = readData(file);

  /* calc cutoff/fp/tp for every cv */

  /* computed measures (not necessary, output goes to stdout) */
  //unordered_map<string, Prediction> rocdata;

  vector<Performance<PerfM::FPR, PerfM::TPR> > perfs_roc;
  vector<Performance<PerfM::TPR, PerfM::PPV> > perfs_pr;
  /* iterate over x-validations */
  unordered_map<string, pair<vector<double>, vector<int>>>::iterator it;
  for(it = data.begin(); it != data.end(); ++it) {
    cerr << it->first << endl;
    /* first is the name of the group */
    /* second -> the label-prediction pair 2nd second -> the label */
    Prediction unroc(it->second.first, it->second.second);
    unroc.compute();

    Performance<PerfM::FPR, PerfM::TPR> perf_roc(unroc);
    perf_roc.compute();
    perfs_roc.push_back(perf_roc);

    Performance<PerfM::TPR, PerfM::PPV> perf_pr(unroc);
    perf_pr.compute();
    perfs_pr.push_back(perf_pr);

    cerr << endl;

  }

  H5File h5file( outfile, H5F_ACC_TRUNC );
  pair<Performance<PerfM::FPR, PerfM::TPR>, avgPerformanceResultInfo> perf_roc_avg = averagePerformance<PerfM::FPR, PerfM::TPR>(perfs_roc);
  perf_roc_avg.first.H5Add(&h5file, "perf_roc", "threshold_avg");
  write_hdf5(&h5file, perf_roc_avg.second.skipped_groups, "/perf_roc/skipped_groups");
  write_hdf5(&h5file, perf_roc_avg.second.total_groups, "/perf_roc/total_groups");
  write_hdf5(&h5file, perf_roc_avg.second.valid_groups, "/perf_roc/valid_groups");

  cerr << "pr avg" << endl;
  pair<Performance<PerfM::TPR, PerfM::PPV>, avgPerformanceResultInfo> perf_pr_avg = averagePerformance<PerfM::TPR, PerfM::PPV>(perfs_pr);
  perf_pr_avg.first.H5Add(&h5file, "perf_pr", "threshold_avg");
  write_hdf5(&h5file, perf_pr_avg.second.skipped_groups, "/perf_pr/skipped_groups");
  write_hdf5(&h5file, perf_pr_avg.second.total_groups, "/perf_pr/total_groups");
  write_hdf5(&h5file, perf_pr_avg.second.valid_groups, "/perf_pr/valid_groups");
}
