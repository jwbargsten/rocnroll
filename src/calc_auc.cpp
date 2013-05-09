#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include <algorithm>

#include "Measure.h"
#include "Performance.h"


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
  unordered_map<string, pair<vector<double>, vector<int>>> data;

  int optind = 1;
  cerr << "reading in " << argv[optind] << endl;
  ifstream in(argv[optind]);

  if(!in || in.bad()) {
      cerr << "Supply the right arguments, you idiot! " << argv[0]  << " [FILENAME]" << endl;
      exit(1);
  }

  vector<string> row;
  for (string line; getline(in, line, '\n');) {
    /* skip empty lines */
    if(line.length() == 0)
      continue;

    row = splitLine(line);
    data[row[0]].first.push_back(convertToDouble(row[1]));
    data[row[0]].second.push_back(convertToInt(row[2]));
  }

  /* calc cutoff/fp/tp for every cv */

  /* computed measures (not necessary, output goes to stdout) */
  //unordered_map<string, Prediction> rocdata;

  /* iterate over x-validations */
  unordered_map<string, pair<vector<double>, vector<int>>>::iterator it;
  for(it = data.begin(); it != data.end(); ++it) {
    cerr << it->first << ":";
    /* first is the name of the group */
    /* second -> the label-prediction pair 2nd second -> the label */
    Prediction unroc(it->second.first, it->second.second);
    unroc.compute();

    Performance<None, AUCROC> perf_auc(unroc);
    perf_auc.compute();
    cerr << endl;
    cout << it->first << "\t" << perf_auc.y_values.front() << endl;
  }

}

