#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <algorithm>

using namespace std;

class ROCCurveUnnormalized {


  static bool inline pairSort(pair<int , vector<double>::const_iterator> a, pair<int, vector<double>::const_iterator> b)
  {
    return(*(a.second) > *(b.second));
  }
  vector<int> order(vector<double>& d);

public:
  vector<double> p;
  vector<int> l;

  vector<int> idcs;

  int num_pos;
  int num_neg;
  int num_pred;
  vector<int> num_pos_pred;
  vector<int> num_neg_pred;

  vector<int> fp;
  vector<int> tp;
  vector<int> fn;
  vector<int> tn;

  vector<double> cutoffs;

  ROCCurveUnnormalized();
  ROCCurveUnnormalized(vector<double>&, vector<int>&);
  //ROCCurveUnnormalized& operator=(const ROCCurveUnnormalized&);
  //ROCCurveUnnormalized(ROCCurveUnnormalized&);

  void compute();
  void printJSON(const string&, bool);
  void printJSON();
};
