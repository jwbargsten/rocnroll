#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <memory>

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

unordered_map<string, pair<shared_ptr<vector<double>>, shared_ptr<vector<int> > > >
readData(const string& file)
{
  ifstream in(file);

  if(!in || in.bad())
      throw std::runtime_error("Supply the right arguments, you idiot! " + file + " [FILENAME]");

  unordered_map<string, pair<shared_ptr< vector<double> >, shared_ptr<vector<int> > > > data;

  vector<string> row;
  for (string line; getline(in, line, '\n');) {
    /* skip empty lines */
    if(line.length() == 0)
      continue;

    row = splitLine(line);

    if(!data[row[0]].first) {
      shared_ptr< vector<double> > v(new vector<double>);
      data[row[0]].first = v;
    }

    if(!data[row[0]].second) {
      shared_ptr<vector<int> > v(new vector<int>);
      data[row[0]].second = v;
    }

    data[row[0]].first->push_back(convertToDouble(row[1]));
    data[row[0]].second->push_back(convertToInt(row[2]));
  }
  return data;
}
