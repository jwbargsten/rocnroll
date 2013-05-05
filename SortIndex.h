#include <vector>
using namespace std;

class SortIndex {
  vector<double>& data;

  static inline bool compare(int i, int j) {
    return(data[i] < data[j]);
  }

public:
  SortIndex(vector<double>& ddata) : data(ddata) {};
  vector<double> order();
};
