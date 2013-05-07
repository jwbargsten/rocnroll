#ifndef ROCNROLL_MEASURE_H
#define ROCNROLL_MEASURE_H
#include <iostream>

class Cutoff {
public:
  static std::string name() { return "cutoff"; }

  inline double compute(const int& num_neg, const int& num_pos, const double& cutoff, const int& fp, const int& tp, const int& fn, const int& tn)
  {
    return cutoff;
  }
};

class TPR {
public:
  static std::string name() { return "tpr"; }
  inline double compute(const int& num_neg, const int& num_pos, const double& cutoff, const int& fp, const int& tp, const int& fn, const int& tn)
  {
    double tpr = (double)tp/num_pos;
    return(tpr);
  }
};

class PPV {
public:
  static std::string name() { return "ppv"; }
  inline double compute(const int& num_neg, const int& num_pos, const double& cutoff, const int& fp, const int& tp, const int& fn, const int& tn)
  {
    double ppv = (double)tp/(fp+tp);
    return(ppv);
  }
};

class FPR {
public:
  static std::string name() { return "fpr"; }
  inline double compute(const int& num_neg, const int& num_pos, const double& cutoff, const int& fp, const int& tp, const int& fn, const int& tn)
  {
    double fpr = (double)fp/num_neg;
    return(fpr);
  }
};

class AUC {
public:
  static std::string name() { return "auc"; }

};

#endif
