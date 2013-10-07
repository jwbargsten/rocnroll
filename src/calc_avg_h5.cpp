#include <config.h>
#include <fstream>
#include <memory>
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
#include <H5Cpp.h>

#include "H5IO.h"

#include "Performance.h"
#include "PerformanceMeasure.h"
#include "misc.h"

#include <ctime>

namespace PerfM = PerformanceMeasure;

using namespace std;
using namespace H5;

/*
 * input data structure: group <tab> prediction <tab> label
 * lables are assumed to be 0 (negative) and 1 (positive)
 * all number are assumed to be finite
 *
 */
int main(int argc, char *argv[])
{

  bool isSlim = false;
  clock_t begin;
  clock_t end;
  double elapsed_secs;

  bool verbose = false;

  Prediction::verbose = verbose;

  int c;
  while((c =  getopt(argc, argv, "s")) != -1)
    switch (c) {
      case 's':
        isSlim = true;
        cerr << "slim output: no predictions and labels included" << endl;
        break;
      }




  double pred_time = 0;
  double roc_time = 0;
  double pr_time = 0;

  clock_t begin_loop;
  clock_t end_loop;

  string file(argv[optind]);
  string outfile(argv[optind+1]);

  cerr << "reading in " << argv[optind] << " ... ";
  begin = clock();

  shared_ptr<unordered_map<string, pair<vector<double>, vector<int> > > > data = readData(file);

  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cerr << elapsed_secs << "s" << endl;

  /* calc cutoff/fp/tp for every cv */

  /* computed measures (not necessary, output goes to stdout) */
  //unordered_map<string, Prediction> rocdata;

  vector<Performance<PerfM::FPR, PerfM::TPR> > perfs_roc;
  vector<Performance<PerfM::TPR, PerfM::PPV> > perfs_pr;
  /* iterate over x-validations */
  cerr << "calculating prediction and performance per cv ... ";
  unordered_map<string, pair<vector<double>, vector<int>>>::iterator it;
  for(it = data->begin(); it != data->end(); ++it) {
    if(verbose)
      cerr << it->first << endl;
    /* first is the name of the group */
    /* second -> the label-prediction pair 2nd second -> the label */
    begin_loop = clock();
    Prediction unroc(it->second.first, it->second.second);
    unroc.compute();
    end_loop = clock();
    pred_time += double(end_loop - begin_loop) / CLOCKS_PER_SEC;

    begin_loop = clock();
    Performance<PerfM::FPR, PerfM::TPR> perf_roc(unroc);
    perf_roc.compute();
    perfs_roc.push_back(perf_roc);
    end_loop = clock();
    roc_time += double(end_loop - begin_loop) / CLOCKS_PER_SEC;

    begin_loop = clock();
    Performance<PerfM::TPR, PerfM::PPV> perf_pr(unroc);
    perf_pr.compute();
    perfs_pr.push_back(perf_pr);
    end_loop = clock();
    pr_time += double(end_loop - begin_loop) / CLOCKS_PER_SEC;

    if(verbose)
      cerr << endl;
  }

  cerr << "pred: " << pred_time << "s, pr: " << pr_time << "s, roc: " << roc_time << "s"<< endl;

  cerr << "writing to " << argv[optind+1] << endl;

  cerr << "averaging roc ... ";
  begin = clock();

  H5File h5file( outfile, H5F_ACC_TRUNC );
  pair<Performance<PerfM::FPR, PerfM::TPR>, avgPerformanceResultInfo> perf_roc_avg = averagePerformance<PerfM::FPR, PerfM::TPR>(perfs_roc);
  perf_roc_avg.first.H5Add(&h5file, "perf_roc", "threshold_avg");
  write_hdf5(&h5file, perf_roc_avg.second.skipped_groups, "/perf_roc/skipped_groups");
  write_hdf5(&h5file, perf_roc_avg.second.total_groups, "/perf_roc/total_groups");
  write_hdf5(&h5file, perf_roc_avg.second.valid_groups, "/perf_roc/valid_groups");

  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cerr << elapsed_secs << "s" << endl;

  cerr << "averaging precision/recall ... ";
  begin = clock();

  pair<Performance<PerfM::TPR, PerfM::PPV>, avgPerformanceResultInfo> perf_pr_avg = averagePerformance<PerfM::TPR, PerfM::PPV>(perfs_pr);
  perf_pr_avg.first.H5Add(&h5file, "perf_pr", "threshold_avg");
  write_hdf5(&h5file, perf_pr_avg.second.skipped_groups, "/perf_pr/skipped_groups");
  write_hdf5(&h5file, perf_pr_avg.second.total_groups, "/perf_pr/total_groups");
  write_hdf5(&h5file, perf_pr_avg.second.valid_groups, "/perf_pr/valid_groups");

  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cerr << elapsed_secs << "s" << endl;
}
