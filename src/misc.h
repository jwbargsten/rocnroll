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

vector<string> splitLine(string& line);

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

vector<int> order(vector<double>& d)
{
  vector<pair<int, vector<double>::const_iterator> > idxPair(d.size());
  int n = 0;
  for(vector<double>::const_iterator it = d.begin(); it != d.end(); ++it, ++n)
  {
    idxPair[n] = make_pair(n, it);
  }
  sort(idxPair.begin(), idxPair.end(), pairSort);

  vector<int> idx;
  for(vector<pair<int, vector<double>::const_iterator> >::const_iterator it = idxPair.begin(); it != idxPair.end(); ++it)
  {
    idx.push_back(it->first);
  }

  return(idx);
}

#include "misc.cpp"

#endif
