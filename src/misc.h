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
#include <unordered_map>
#include <memory>
#include <H5Cpp.h>

using namespace std;
using namespace H5;

vector<int>
order(const vector<double>& d);

inline
vector<string>
splitLine(string& line);

vector<double>
numseq(double min, double max, long length);

shared_ptr<unordered_map<string, pair<vector<double>, vector<int> > > >
readData(const string& file);

std::string
joinDoubleYAML(vector<double>::const_iterator begin, vector<double>::const_iterator end, std::string const& separator);

class BadNumber : public std::runtime_error {
  public:
    BadNumber(std::string const& s)
      : std::runtime_error(s)
      { }
};

class BadConversion : public std::runtime_error {
public:
  BadConversion(std::string const& s)
    : std::runtime_error(s)
    { }
};

template<typename T>
inline bool
is_finite(T value)
{
  return value == value && (value - value) == 0;
}

template <typename Iter>
std::string
join(Iter begin, Iter end, std::string const& separator)
{
  std::ostringstream result;
  result.precision(15);
  if (begin != end)
    result << fixed << *begin++;
  while (begin != end)
    result << separator << fixed << *begin++;
  return result.str();
}


inline double
convertToDouble(std::string const& s)
{
  if(s == "Inf")
    return std::numeric_limits<double>::infinity();
  if(s == "-Inf")
    return -std::numeric_limits<double>::infinity();
  std::istringstream i(s);
  double x;
  if (!(i >> x))
    throw BadConversion("convertToDouble(\"" + s + "\")");
  return x;
}

inline std::string
convertToYAMLString(double const& d)
{
  std::ostringstream s;
  s.precision(15);

  if(d == std::numeric_limits<double>::infinity())
    s << ".inf";
  else if(d == -std::numeric_limits<double>::infinity())
    s << "-.inf";
  else if(d != d)
    s << ".NaN";
  else s << fixed << d;

  return s.str();
}

inline int
convertToInt(std::string const& s)
{
  std::istringstream i(s);
  int x;
  if (!(i >> x))
    throw BadConversion("convertToInt(\"" + s + "\")");
  return x;
}

inline bool
pairSort(pair<int , vector<double>::const_iterator> a, pair<int, vector<double>::const_iterator> b)
{
  return(*(a.second) > *(b.second));
}

#endif
