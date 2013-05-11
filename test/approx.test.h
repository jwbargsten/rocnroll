#include <cxxtest/TestSuite.h>
#include <vector>
#include <iostream>
#include <limits>
#include "../src/approx.h"

class MiscTest : public CxxTest::TestSuite
{
  public:
    void testTieMean1(void)
    {
      double x_[] = {0.7, 1.2, 1.2, 1.9, 3};
      vector<double> x (x_, x_ + sizeof(x_) / sizeof(double) );

      double y_[] = {1,2,3,4,5};
      vector<double> y (y_, y_ + sizeof(y_) / sizeof(double) );

      pair<vector<double>, vector<double> > res;

      res = tie_mean(x, y);
      double res_ref[] = { 1, 2.5, 4, 5};

      double x_ref_[] = {0.7, 1.2, 1.9, 3};
      vector<double> x_ref (x_ref_, x_ref_ + sizeof(x_ref_) / sizeof(double) );

      int i = 0;
      for(vector<double>::const_iterator it = res.second.begin(); it != res.second.end(); ++it, ++i)
      {
        TS_ASSERT_EQUALS(*it, res_ref[i]);
      }
      TS_ASSERT_EQUALS(i, 4);

      i = 0;
      for(vector<double>::const_iterator it = res.first.begin(); it != res.first.end(); ++it, ++i)
      {
        TS_ASSERT_EQUALS(*it, x_ref[i]);
      }
      TS_ASSERT_EQUALS(i, 4);
    }
    void testTieMean2(void)
    {
      double x_[] = {0.7, 1.2, 1.2, 1.9, 3, 3};
      vector<double> x (x_, x_ + sizeof(x_) / sizeof(double) );

      double y_[] = {1,2,3,4,5, 6};
      vector<double> y (y_, y_ + sizeof(y_) / sizeof(double) );

      pair<vector<double>, vector<double> > res;

      res = tie_mean(x, y);
      double res_ref[] = { 1, 2.5, 4, 5.5};

      int i = 0;
      for(vector<double>::const_iterator it = res.second.begin(); it != res.second.end(); ++it, ++i)
      {
        TS_ASSERT_EQUALS(*it, res_ref[i]);
      }
      TS_ASSERT_EQUALS(i, 4);
    }
    void testTieMean3(void)
    {
      double x_[] = {0.7, 1.2, std::numeric_limits<double>::infinity(), 1.9, 3, 3};
      vector<double> x (x_, x_ + sizeof(x_) / sizeof(double) );

      double y_[] = {1,2,3,4,5, 6};
      vector<double> y (y_, y_ + sizeof(y_) / sizeof(double) );

      pair<vector<double>, vector<double> > res;

      res = tie_mean(x, y);
      double res_ref[] = { 1, 2, 4, 5.5};

      int i = 0;
      for(vector<double>::const_iterator it = res.second.begin(); it != res.second.end(); ++it, ++i)
      {
        TS_ASSERT_EQUALS(*it, res_ref[i]);
      }
      TS_ASSERT_EQUALS(i, 4);
    }
    void testTieMean4(void)
    {
      double x_[] = {3, 1.2,0.7, 1.2, 1.9};
      vector<double> x (x_, x_ + sizeof(x_) / sizeof(double) );

      double y_[] = {5,3,1,2,4};
      vector<double> y (y_, y_ + sizeof(y_) / sizeof(double) );

      pair<vector<double>, vector<double> > res;

      res = tie_mean(x, y);
      double res_ref[] = { 1, 2.5, 4, 5};

      int i = 0;
      for(vector<double>::const_iterator it = res.second.begin(); it != res.second.end(); ++it, ++i)
      {
        TS_ASSERT_EQUALS(*it, res_ref[i]);
      }
      TS_ASSERT_EQUALS(i, 4);
    }
    void testInterpolate(void) {
      double x_[] = {3, 1.2,0.7, 1.2, 1.9};
      vector<double> x (x_, x_ + sizeof(x_) / sizeof(double) );

      double y_[] = {5,3,1,2,4};
      vector<double> y (y_, y_ + sizeof(y_) / sizeof(double) );

      SimpleInterpolation s(x, y, 0, make_pair(2,2), false);
      /* approxfun(c(3,1.2,0.7,1.2,1.9), c(5,3,1,2,4), rule = 2)(2.5) */
      TS_ASSERT_DELTA( s.interpolate(2.5), 4.545455, 0.00001);
      TS_ASSERT_DELTA( s.interpolate(0.1), 1, 0.00001);
      TS_ASSERT_DELTA( s.interpolate(10), 5, 0.00001);

    }
};
