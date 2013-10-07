#ifndef ROCNROLL_PREDICTION_H
#define ROCNROLL_PREDICTION_H
#include <config.h>

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <algorithm>

using namespace std;

class Prediction {

  public:
    static bool verbose;

    vector<double> p;
    vector<int> l;

    vector<int> idcs;

    int num_pos;
    int num_neg;

    int num_pred;
    int num_uniq_pred;

    int num_pred_one;
    int num_pred_zero;

    vector<int> num_pos_pred;
    vector<int> num_neg_pred;

    vector<int> fp;
    vector<int> tp;
    vector<int> fn;
    vector<int> tn;

    vector<double> cutoffs;

    Prediction();
    Prediction(const vector<double>&, const vector<int>&);

    void compute();
    void printYAML(const string&, bool, const string&);
    void printYAML();
};

#endif
