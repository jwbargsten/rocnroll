#ifndef ROCNROLL_MEASURE_H
#define ROCNROLL_MEASURE_H
#include <iostream>
#include <string>
#include <cmath>
#include "misc.h"

using namespace std;

class None {
  public:
    static std::string name() { return "none"; }
    inline vector<double> compute(
       const int& n,
       const int& num_neg, 
       const int& num_pos,
       const vector<double>& cutoffs,
       const vector<int>& fp,
       const vector<int>& tp,
       const vector<int>& fn,
       const vector<int>& tn)
    {
      return vector<double>();
    }

};

class Cutoff {
  public:
    static std::string name() { return "cutoff"; }
    inline vector<double> compute(
       const int& n,
       const int& num_neg, 
       const int& num_pos,
       const vector<double>& cutoffs,
       const vector<int>& fp,
       const vector<int>& tp,
       const vector<int>& fn,
       const vector<int>& tn)
    {
      vector<double> res;
      for(vector<double>::const_iterator it = cutoffs.begin(); it != cutoffs.end(); ++it) {

        //if(!is_finite<double>(*it))
          //throw BadNumber(name() + "-measure: non-finite number: " + std::to_string(*it) );
        res.push_back(*it);
      }
      return res;
    }
};

class TPR {
  public:
    static std::string name() { return "tpr"; }
    inline vector<double> compute(
       const int& n,
       const int& num_neg, 
       const int& num_pos,
       const vector<double>& cutoffs,
       const vector<int>& fp,
       const vector<int>& tp,
       const vector<int>& fn,
       const vector<int>& tn)
    {
      vector<double> res;

      for(int i=0; i < n; i++) { 
        double tpr = (double)tp[i]/num_pos;
        //if(!is_finite<double>(tpr))
          //throw BadNumber(name() + "-measure: non-finite number: " + std::to_string(tpr) );
        res.push_back(tpr);
      }

      return res;
    }
};

class PPV {
  public:
    static std::string name() { return "ppv"; }
    inline vector<double> compute(
       const int& n,
       const int& num_neg, 
       const int& num_pos,
       const vector<double>& cutoffs,
       const vector<int>& fp,
       const vector<int>& tp,
       const vector<int>& fn,
       const vector<int>& tn)
    {
      vector<double> res;

      for(int i=0; i < n; i++) { 
        double ppv = (double)tp[i]/(fp[i]+tp[i]);
        //if(!is_finite<double>(ppv))
          //throw BadNumber(name() + "-measure: non-finite number: " + std::to_string(ppv) );
        res.push_back(ppv);
      }

      return res;
    }
};

class FPR {
  public:
    static std::string name() { return "fpr"; }
    inline vector<double> compute(
       const int& n,
       const int& num_neg, 
       const int& num_pos,
       const vector<double>& cutoffs,
       const vector<int>& fp,
       const vector<int>& tp,
       const vector<int>& fn,
       const vector<int>& tn)
    {
      vector<double> res;

      for(int i=0; i < n; i++) { 
        double fpr = (double)fp[i]/num_neg;
        //if(!is_finite<double>(fpr))
          //throw BadNumber(name() + "-measure: non-finite number: " + std::to_string(fpr) );
        res.push_back(fpr);
      }

      return res;
    }
};

class AUCPR {
  public:
    static std::string name() { return "auc"; }
    inline vector<double> compute(
       const int& n,
       const int& num_neg, 
       const int& num_pos,
       const vector<double>& cutoffs,
       const vector<int>& fp,
       const vector<int>& tp,
       const vector<int>& fn,
       const vector<int>& tn)
    {
      vector<double> res;

      if(n < 2)
        throw std::runtime_error("Not enough distinct predictions for AUC calculation");

      double auc = 0;

      double last_y = (double) tp[0]/(fp[0]+tp[0]);
      double last_x = (double) tp[0]/num_pos;

      if(std::isnan(last_x))
        last_x = 0;
      if(std::isnan(last_y))
        last_y = 0;

      for(int i=1; i < n; i++) { 
        double x = (double) fp[i]/num_neg;

        if(std::isnan(x))
          x = 0;
        if(!is_finite<double>(x))
          continue;

        double y = (double) tp[i]/num_pos;

        if(std::isnan(y))
          y = 0;
        if(!is_finite<double>(y))
          continue;


        auc += 0.5 * (x - last_x) * (y + last_y);

        last_y = y;
        last_x = x;
      }
      //if(!is_finite<double>(auc))
        //throw BadNumber(name() + "-measure: non-finite number: " + std::to_string(auc) );
      res.push_back(auc);

      return res;
    }
};

class AUCROC {
  public:
    static std::string name() { return "auc"; }
    inline vector<double> compute(
       const int& n,
       const int& num_neg, 
       const int& num_pos,
       const vector<double>& cutoffs,
       const vector<int>& fp,
       const vector<int>& tp,
       const vector<int>& fn,
       const vector<int>& tn)
    {
      vector<double> res;

      if(n < 2)
        throw std::runtime_error("Not enough distinct predictions for AUC calculation");

      double auc = 0;

      double last_x = (double) fp[0]/num_neg;
      double last_y = (double) tp[0]/num_pos;

      if(std::isnan(last_x))
        last_x = 0;
      if(std::isnan(last_y))
        last_y = 0;

      for(int i=1; i < n; i++) { 
        double x = (double) fp[i]/num_neg;
        if(!is_finite<double>(x))
          continue;

        double y = (double) tp[i]/num_pos;
        if(!is_finite<double>(y))
          continue;

        auc += 0.5 * (x - last_x) * (y + last_y);

        last_y = y;
        last_x = x;
      }
      //if(!is_finite<double>(auc))
        //throw BadNumber(name() + "-measure: non-finite number: " + std::to_string(auc) );
      res.push_back(auc);

      return res;
    }
};

#endif
