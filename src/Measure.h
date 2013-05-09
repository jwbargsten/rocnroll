#ifndef ROCNROLL_MEASURE_H
#define ROCNROLL_MEASURE_H
#include <iostream>

class None {
  public:
    static std::string name() { return "none"; }
    inline vector<double> compute(const int& num_neg, 
       const int& num_pos,
       const vector<double>& cutoffs,
       const vector<int>& fp,
       const vector<int>& tp,
       const vector<int>& fn,
       const vector<int>& tn)
    {
      return vector<double>();
    }

}

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

        if(!is_finite<double>(*it))
          throw BadNumber("measure: non-finite number: " + to_string(*it) );
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
        if(!is_finite<double>(tpr))
          throw BadNumber("measure: non-finite number: " + to_string(tpr) );
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
        if(!is_finite<double>(ppv))
          throw BadNumber("measure: non-finite number: " + to_string(ppv) );
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
        if(!is_finite<double>(fpr))
          throw BadNumber("measure: non-finite number: " + to_string(fpr) );
        res.push_back(fpr);
      }

      return res;
    }
};

class AUC {
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

      if(x.size() < 2)
        throw std::runtime_error("Not enough distinct predictions for AUC calculation");

      double auc = 0;

      for(int i=1; i < n; i++) { 
        double x = (double) fp[i]/num_neg;
        if(!is_finite<double>(x))
          continue;

        double y = (double) tp[i]/num_pos;
        if(!is_finite<double>(y))
          continue;

        auc += 0.5 * (x[i] - x[i-1]) * (y[i] + y[i-1]);
      }
      if(!is_finite<double>(auc))
        throw BadNumber("measure: non-finite number: " + to_string(auc) );
      res.push_back(auc);

      return res;
    }
};

#endif
