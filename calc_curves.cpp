#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include "convert.h"
#include <algorithm>
#include "ROCCurveUnnormalized.h"

using namespace std;

vector<string> splitLine(string&);
bool pairSort(pair<int , vector<double>::const_iterator>, pair<int, vector<double>::const_iterator>);
vector<int> order(vector<double>& d);

/*
 * input data structure: group <tab> prediction <tab> label
 * lables are assumed to be 0 (negative) and 1 (positive)
 * all number are assumed to be finite
 *
 */
int main(int argc, char *argv[])
{
  unordered_map<string, pair<vector<double>, vector<int>>> data;

  ifstream in(argv[1]);

  if(!in || in.bad()) {
      cerr << "Supply the right arguments, you idiot! " << argv[0]  << " [FILENAME]" << endl;
      exit(1);
  }

  bool isSlim = false;
  if(argv[2] && string(argv[2]) == "slim") {
    isSlim = true;
    cerr << "slim output: no predictions and labels included" << endl;
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
  //unordered_map<string, ROCCurveUnnormalized> rocdata;

  /* iterate over x-validations */
  unordered_map<string, pair<vector<double>, vector<int>>>::iterator it;
  for(it = data.begin(); it != data.end(); ++it) {
    cerr << it->first << endl;
    /* first is the name of the group */
    /* second -> the label-prediction pair 2nd second -> the label */
    ROCCurveUnnormalized unroc(it->second.first, it->second.second);
    unroc.compute();
    cout << "----" << endl;
    unroc.printJSON(it->first, isSlim);
    cerr << endl;
  }

}

vector<string> splitLine(string& line)
{
  vector<string>   result;

  stringstream          lineStream(line);
  string                cell;

  while(getline(lineStream,cell,'\t'))
  {
      result.push_back(cell);
  }
  return result;
}
