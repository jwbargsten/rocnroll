#ifndef ROCNROLL_MEASURE_H
#define ROCNROLL_MEASURE_H

class Cutoff {
public:
  inline double compute(const int& num_neg, const int& num_pos, const double& cutoff, const int& fp, const int& tp, const int& fn, const int& tn)
  {
    return cutoff;
  };
};

class TPR {
public:
  inline double compute(const int& num_neg, const int& num_pos, const double& cutoff, const int& fp, const int& tp, const int& fn, const int& tn)
  {
    double k = 3;
    double l = 0;
    double z = k/l;

    double tpr = tp/num_pos + 0.0;
    return(tpr);
  }
};

class PPV {
public:
  inline double compute(const int& num_neg, const int& num_pos, const double& cutoff, const int& fp, const int& tp, const int& fn, const int& tn)
  {
    double ppv = tp/(fp+tp) + 0.0;
    return(ppv);
  }
};

class FPR {
public:
  inline double compute(const int& num_neg, const int& num_pos, const double& cutoff, const int& fp, const int& tp, const int& fn, const int& tn)
  {
    double fpr = fp/num_neg + 0.0;
    return(fpr);
  }
};

class AUC {

};

#endif
