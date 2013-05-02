#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include "convert.h"

using namespace std;

vector<string> splitLine(string&);

/*
 * input data structure: group <tab> prediction <tab> label
 * lables are assumed to be 0 and 1
 *
 */
int main(int argc, char *argv[])
{
  std::unordered_map<std::string, vector<double>> pred;
  std::unordered_map<std::string, vector<int>> labels;

  //ifstream in(argv[1]);
  ifstream in("../2013-04-26/prediction.cv.go.ag2bmrf.tsv");

  if(!in || in.bad()) {
      cerr << "Supply the right arguments, you idiot! " << argv[0]  << " [FILENAME]" << endl;
  }

  //unique 
  //sort( vec.begin(), vec.end() );
  //vec.erase( unique( vec.begin(), vec.end() ), vec.end() );
  vector<string> r;
  for (string line; getline(in, line, '\n');) {
    r = splitLine(line);
    pred[r[0]].push_back(convertToDouble(r[1]));
    labels[r[0]].push_back(convertToInt(r[2]));
  }

  for(vector<double>::iterator iit = pred["cv44"].begin(); iit != pred["cv44"].end(); ++iit)
  {
    for (vector<string>::iterator it = (*iit).begin() ; it != (*iit).end(); ++it)
    {
      std::cout << ' ' << *it;
    }
    std::cout << '\n';
  }
}

vector<string> splitLine(string& line)
{
  std::vector<std::string>   result;

  std::stringstream          lineStream(line);
  std::string                cell;

  while(std::getline(lineStream,cell,'\t'))
  {
      result.push_back(cell);
  }
  return result;
}
