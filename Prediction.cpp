#include <limits>

#include "ROCCurveUnnormalized.h"
#include "misc.h"
#include <stdexcept>

ROCCurveUnnormalized::ROCCurveUnnormalized(vector<double>& pp, vector<int>& ll) :
  p(pp), l(ll)
{}

ROCCurveUnnormalized::ROCCurveUnnormalized()
{
}

void ROCCurveUnnormalized::compute()
{
    num_pos = 0;
    num_neg = 0;

    for(vector<int>::const_iterator it = l.begin(); it != l.end(); ++it) {
      if(*it > 0)
        num_pos++;
      else
        num_neg++;
    }

    idcs = order(p);

    if(idcs.size() != p.size()) {
      cerr << "not equal " << idcs.size() << " - " << p.size() << endl;
      exit(1);
    }

    fp.clear();
    tp.clear();
    fn.clear();
    tn.clear();

    cutoffs.clear();

    fp.push_back(0);
    tp.push_back(0);

    fn.push_back(num_pos);
    tn.push_back(num_neg);

    num_pos_pred.push_back(tp.back() + fp.back());
    num_neg_pred.push_back(tn.back() + fn.back());

    cutoffs.push_back(std::numeric_limits<double>::max());

    num_pred = 0;

    /* start with one prediction since we pushed std values above on the arrays */
    num_uniq_pred = 1;

    /* variables for cumulative sum */
    int fp_tmp = 0;
    int tp_tmp = 0;
    for(vector<int>::const_iterator it = idcs.begin(); it != idcs.end(); ++it)
    {
      num_pred++;
      /* skip duplicates */

      fp_tmp += -1 * (l[*it] - 1);
      tp_tmp += l[*it];
      if(it + 1 != idcs.end() && p[*it] == p[*(it+1)]) {
        cerr << ".";
        continue;
      }

      num_uniq_pred++;
      cutoffs.push_back(p[*it]);

      /* invert: 0 -> 1, 1 -> 0 */
      fp.push_back(fp.back() + fp_tmp);
      tp.push_back(tp.back() + tp_tmp);

      fp_tmp = 0;
      tp_tmp = 0;

      fn.push_back(num_pos - tp.back());
      tn.push_back(num_neg - fp.back());

      num_pos_pred.push_back(tp.back() + fp.back());
      num_neg_pred.push_back(tn.back() + fn.back());

    }
    cerr << " " << num_uniq_pred << "/" << num_pred;
    if(num_pred != p.size())
      throw std::runtime_error("ERROR number of total predictions do not fit");
    if(num_uniq_pred != cutoffs.size() ||  num_uniq_pred != fp.size())
      throw std::runtime_error("ERROR number of unique predictions do not fit");

    return;
}

vector<int> ROCCurveUnnormalized::order(vector<double>& d)
{
  vector<pair<int, vector<double>::const_iterator>> idxPair(d.size());
  int n = 0;
  for(vector<double>::const_iterator it = d.begin(); it != d.end(); ++it, ++n)
  {
    idxPair[n] = make_pair(n, it);
  }
  sort(idxPair.begin(), idxPair.end(), pairSort);

  vector<int> idx;
  for(vector<pair<int, vector<double>::const_iterator>>::const_iterator it = idxPair.begin(); it != idxPair.end(); ++it)
  {
    idx.push_back(it->first);
  }

  return(idx);
}

void ROCCurveUnnormalized::printJSON(const string& name, bool slim)
{
  cout.precision(15);
  cout << "{" << endl;
  if(!name.empty())
    cout << "  \"_name\":\"" << name << "\"," << endl;
  if(!slim) {
    cout << "  \"l\":[" << join<vector<int>::const_iterator>(l.begin(), l.end(), ",") << "]," << endl;
    cout << "  \"p\":[" << join<vector<double>::const_iterator>(p.begin(), p.end(), ",") << "]," << endl;
    //not necessary
    //cout << "  \"idx\":[" << join<vector<int>::const_iterator>(idcs.begin(), idcs.end(), ",") << "]," << endl;
  }
  cout << "  \"num_pos\":" << num_pos << "," << endl;
  cout << "  \"num_neg\":" << num_neg << "," << endl;
  cout << "  \"num_pred\":" << num_pred << "," << endl;
  cout << "  \"num_uniq_pred\":" << num_uniq_pred << "," << endl;
  cout << "  \"num_pos_pred\":[" << join<vector<int>::const_iterator>(num_pos_pred.begin(), num_pos_pred.end(), ",") << "]," << endl;
  cout << "  \"num_neg_pred\":[" << join<vector<int>::const_iterator>(num_neg_pred.begin(), num_neg_pred.end(), ",") << "]," << endl;

  cout << "  \"fp\":[" << join<vector<int>::const_iterator>(fp.begin(), fp.end(), ",") << "]," << endl;
  cout << "  \"tp\":[" << join<vector<int>::const_iterator>(tp.begin(), tp.end(), ",") << "]," << endl;
  cout << "  \"fn\":[" << join<vector<int>::const_iterator>(fn.begin(), fn.end(), ",") << "]," << endl;
  cout << "  \"tn\":[" << join<vector<int>::const_iterator>(tn.begin(), tn.end(), ",") << "]," << endl;

  cout << "  \"cutoffs\":[" << join<vector<double>::const_iterator>(cutoffs.begin(), cutoffs.end(), ",") << "]" << endl;
  cout << "}";
}

void ROCCurveUnnormalized::printJSON()
{
  printJSON(string(), true);
}

