#include "SortIndex.h"
#include <algorithm>    // std::sort

vector<double> SortIndex::order()
{
  vector<double> o;
  for(int i = 0; i < data.size(); i++)
  {
    o.push_back(i);
  }
  sort(o.begin(), o.end(), this.compare);

  return(o);
}
