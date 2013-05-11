#include <sstream>
#include <string>
#include <vector>

#include "misc.h"

vector<int> order(const vector<double>& d)
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

vector<string> splitLine(string& line)
{
  vector<string>   result;

  stringstream          lineStream(line);
  string                cell;

  while(getline(lineStream,cell,'\t'))
  {
      result.push_back(cell);
  }
  return result;
}

vector<double> numseq(double min, double max, long length)
{
  double range = max - min;
  double step = range/length;

  vector<double> seq;

  if(length < 2)
    throw std::runtime_error("sequence length too short");
  if(max == min)
    throw std::runtime_error("max & min are equal");

  for(long i = 0; i< length-1; i++) {
    seq.push_back(min + i * step);

  }
  seq.push_back(max);
  return seq;
}
