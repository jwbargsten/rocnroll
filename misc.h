#ifndef ROCNROLL_MISC_H
#define ROCNROLL_MISC_H

#include <limits>
template<typename T>
inline bool is_finite(T value)
{
  return value >= std::numeric_limits<T>::min() &&
         value <= std::numeric_limits<T>::max() &&
         value == value;
}

#endif
