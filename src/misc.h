#ifndef ROCNROLL_MISC_H
#define ROCNROLL_MISC_H

#include <limits>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> order(vector<double>& d);
vector<string> splitLine(string& line);

class BadNumber : public std::runtime_error {
public:
  BadNumber(std::string const& s)
    : std::runtime_error(s)
    { }
};

template<typename T>
inline bool is_finite(T value)
{
  return value == value && (value - value) == 0;
}

template <typename Iter>
std::string join(Iter begin, Iter end, std::string const& separator)
{
  std::ostringstream result;
  if (begin != end)
    result << *begin++;
  while (begin != end)
    result << separator << *begin++;
  return result.str();
}

class BadConversion : public std::runtime_error {
public:
  BadConversion(std::string const& s)
    : std::runtime_error(s)
    { }
};

inline double convertToDouble(std::string const& s)
{
  std::istringstream i(s);
  double x;
  if (!(i >> x))
    throw BadConversion("convertToDouble(\"" + s + "\")");
  return x;
}

inline int convertToInt(std::string const& s)
{
  std::istringstream i(s);
  int x;
  if (!(i >> x))
    throw BadConversion("convertToInt(\"" + s + "\")");
  return x;
}

inline bool pairSort(pair<int , vector<double>::const_iterator> a, pair<int, vector<double>::const_iterator> b)
{
  return(*(a.second) > *(b.second));
}

#endif
