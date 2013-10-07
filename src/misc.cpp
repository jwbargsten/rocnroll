#include <config.h>
#include <sstream>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "misc.h"

vector<int>
order(const vector<double>& d)
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

inline
vector<string>
splitLine(string& line)
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

vector<double>
numseq(double min, double max, long length)
{
  double range = max - min;
  double step = range/(length-1);

  vector<double> seq;

  if(length < 2)
    throw std::runtime_error("sequence length too short");
  if(max == min)
    throw std::runtime_error("max & min are equal");

  seq.push_back(min);
  for(long i = 1; i< length-1; i++) {
    seq.push_back(min + i * step);

  }
  seq.push_back(max);
  return seq;
}

shared_ptr<unordered_map<string, pair<vector<double>, vector<int> > > >
readData(const string& file)
{
  ifstream in(file);

  if(!in || in.bad())
      throw std::runtime_error("Supply the right arguments, you idiot! " + file + " [FILENAME]");

  shared_ptr<unordered_map<string, pair<vector<double>, vector<int> > > > data(new unordered_map<string, pair<vector<double>, vector<int> > >());

  vector<string> row;
  string line;
  for (; getline(in, line, '\n');) {
    /* skip empty lines */
    if(line.length() == 0)
      continue;

    row = splitLine(line);

    (*data)[row[0]].first.push_back(convertToDouble(row[1]));
    (*data)[row[0]].second.push_back(convertToInt(row[2]));
  }
  return data;
}

std::string
joinDoubleYAML(vector<double>::const_iterator begin, vector<double>::const_iterator end, std::string const& separator)
{
  std::ostringstream result;
  result.precision(15);
  if (begin != end) {
    result << convertToYAMLString(*begin);
    begin++;
  }
  while (begin != end) {
    result << separator << convertToYAMLString(*begin);
    begin++;
  }
  return result.str();
}

