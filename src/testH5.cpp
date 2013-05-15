#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <H5Cpp.h>

#include "Prediction.h"
#include "PerformanceMeasure.h"
#include "Performance.h"
#include "misc.h"

using namespace std;
namespace PerfM = PerformanceMeasure;
using namespace H5;

int main(int argc, char *argv[]) {
    ifstream in("../test/data/rocr.xval.1cv.tsv");

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
    Performance<PerfM::None, PerfM::AUCROC> perf(pred);
    perf.compute();

    H5File file( "/tmp/test.h5", H5F_ACC_TRUNC );

}
