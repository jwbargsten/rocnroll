#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <cxxtest/TestSuite.h>
#include "../src/misc.h"

class MeasureTest : public CxxTest::TestSuite
{
  public:
    void testAUC(void)
    {
      /* write.table(cbind(ROCR.xval$predictions[[1]], ROCR.xval$labels[[1]]), "rocr.xval.1cv.tsv", row.names=F, col.names=F, quote=F) */
      ifstream in("rocr.xval.1cv.tsv");
      TS_ASSERT(!in || in.bad());

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

  }
};
