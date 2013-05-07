#ifndef ROCNROLL_MISC_H
#define ROCNROLL_MISC_H

#include <limits>
#include <iostream>
#include <sstream>
#include <string>

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

#endif
