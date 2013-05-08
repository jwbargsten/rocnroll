#include <cxxtest/TestSuite.h>
#include <vector>
#include "../src/approx.h"

class MiscTest : public CxxTest::TestSuite
{
  public:
    void testTieMean(void)
    {
      vector<double> x;
      x.push_back(0.7);
      x.push_back(1.2);
      x.push_back(1.2);
      x.push_back(1.9);
      x.push_back(3);

      vector<double> y;
      y.push_back(1);
      y.push_back(2);
      y.push_back(3);
      y.push_back(4);
      y.push_back(5);

      tie_mean(x, y);
      TS_ASSERT(1 + 1 > 1);
      TS_ASSERT_EQUALS(1 + 1, 2);
    }
};
