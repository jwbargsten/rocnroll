#include <sstream>
#include <string>
#include <vector>

using namespace std;
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
