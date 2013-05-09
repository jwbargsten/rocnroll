#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <cxxtest/TestSuite.h>
#include "../src/misc.h"
#include "../src/Prediction.h"
#include "../src/Performance.h"

#define DELTA 0.000001
class MeasureTest : public CxxTest::TestSuite
{
  public:
    void testAUC(void)
    {
      /* 
       library(ROCR)
       data(ROCR.xval)
       write.table(cbind(ROCR.xval$predictions[[1]], ROCR.xval$labels[[1]]), "rocr.xval.1cv.tsv", row.names=F, col.names=F, quote=F,sep="\t")
       p <- prediction(ROCR.xval$predictions[[1]], ROCR.xval$labels[[1]])
       perf <- performance(p, "auc")
       perf@y.values
       */
      ifstream in("data/rocr.xval.1cv.tsv");
      TS_ASSERT(in && !in.bad());

      vector<double> p;
      vector<int> l;
      for (string line; getline(in, line, '\n');) {
        /* skip empty lines */
        if(line.length() == 0)
          continue;

        vector<string> row = splitLine(line);
        p.push_back(convertToDouble(row[0]));
        l.push_back(convertToInt(row[1]));
      }

      Prediction pred(p, l);
      pred.compute();
      Performance<None, AUCROC> perf(pred);
      perf.compute();
      TS_ASSERT_DELTA(perf.y_values.front(), 0.9534701, DELTA);
  }
  void testTPRFPR(void)
  {
    /* 
     library(ROCR)
     data(ROCR.xval)
     write.table(cbind(ROCR.xval$predictions[[1]], ROCR.xval$labels[[1]]), "rocr.xval.1cv.tsv", row.names=F, col.names=F, quote=F,sep="\t")
     p <- prediction(ROCR.xval$predictions[[1]], ROCR.xval$labels[[1]])
     perf <- performance(p, "tpr", "fpr")
     write.table(cbind(perf@x.values[[1]], perf@y.values[[1]], perf@alpha.values[[1]]), "rocr.xval.1cv.ref.tsv", row.names=F, col.names=F, quote=F,sep="\t")
     perf@y.values
     */
    ifstream in("data/rocr.xval.1cv.tsv");
    TS_ASSERT(in && !in.bad());

    vector<double> p;
    vector<int> l;
    for (string line; getline(in, line, '\n');) {
      /* skip empty lines */
      if(line.length() == 0)
        continue;

      vector<string> row = splitLine(line);
      p.push_back(convertToDouble(row[0]));
      l.push_back(convertToInt(row[1]));
    }

    Prediction pred(p, l);
    pred.compute();
    Performance<TPR, FPR> perf(pred);
    perf.compute();

    ifstream in_ref("data/rocr.xval.1cv.ref.tsv");
    TS_ASSERT(in_ref && !in_ref.bad());

    vector<double> x_values;
    vector<double> y_values;
    vector<double> alpha_values;

    for (string line; getline(in_ref, line, '\n');) {
      /* skip empty lines */
      if(line.length() == 0)
        continue;

      vector<string> row = splitLine(line);
      x_values.push_back(convertToDouble(row[0]));
      y_values.push_back(convertToDouble(row[1]));
      alpha_values.push_back(convertToDouble(row[2]));
    }

    TS_ASSERT(x_values.size() == perf.x_values.size());
    TS_ASSERT(y_values.size() == perf.y_values.size());
    TS_ASSERT(alpha_values.size() == perf.alpha_values.size());

    for(int i = 0; i< x_values.size(); i++) {
      // ROCR has swapped axes
      TS_ASSERT_DELTA(perf.y_values[i],x_values[i], DELTA);
      TS_ASSERT_DELTA(perf.x_values[i],y_values[i], DELTA);
      TS_ASSERT_DELTA(perf.alpha_values[i],alpha_values[i], DELTA);
    }
  }
};
