#include <cxxtest/TestSuite.h>
#include <vector>
#include <iostream>
#include <limits>
#include "../src/misc.h"

class MiscTest : public CxxTest::TestSuite
{
  public:
    void testNumseq1(void)
    {
      double x_[] = {1.0, 1.6666666, 2.3333333,3.0};
      vector<double> x (x_, x_ + sizeof(x_) / sizeof(double) );


      vector<double> res = numseq(1, 3, 4);
      int i = 0;
      for(vector<double>::const_iterator it = res.begin(); it != res.end(); ++it, ++i)
      {
        TS_ASSERT_DELTA(*it, x[i], 0.000001);
      }
      TS_ASSERT_EQUALS(i, 4);

    }
};
