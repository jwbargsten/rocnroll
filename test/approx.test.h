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

      int i = 0;
      for(vector<double>::const_iterator it = res.second.begin(); it != res.second.end(); ++it, ++i)
      {
        TS_ASSERT_EQUALS(*it, res_ref[i]);
      }
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
    }
};
