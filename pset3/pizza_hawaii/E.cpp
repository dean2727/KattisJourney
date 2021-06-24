#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
using namespace std;

int main() {
  int t, i, j, k, n, m;
  string pname, ing;
  cin >> t;

  for (i=0;i<t;i++) {
    vector<string> ftn;
    vector<string> atn;
    map<string, long long> ingToPiz;
    cin >> n;

    for (j=0;j<n;j++) {
      cin >> pname;

      // foregin toppings
      cin >> m;
      for (k=0;k<m;k++) {
        cin >> ing;
        ing += "f";

        // cant flip bits if the integer in the map isnt defined
        if (!ingToPiz.count(ing)) {
          ingToPiz[ing] = 0;
        }

        ingToPiz[ing] |= (1 << j);
        ftn.push_back(ing);
      }

      // american toppings
      cin >> m;
      for (k=0;k<m;k++) {
        cin >> ing;
        ing += "a";

        // cant flip bits if the integer in the map isnt defined
        if (!ingToPiz.count(ing)) {
          ingToPiz[ing] = 0;
        }

        ingToPiz[ing] |= (1 << j);
        atn.push_back(ing);
      }
    }

    // go through foreign tops, finding those in american tops in same set (same long long val)
    set<string> common;
    for (j=0;j<ftn.size();j++) {
      for (k=0;k<atn.size();k++) {
        if (int(ingToPiz[ftn[j]]) == int(ingToPiz[atn[k]])) {
          common.insert("("+ftn[j].substr(0, ftn[j].size()-1)+", "+atn[k].substr(0, atn[k].size()-1)+")");
        }
      }
    }

    set<string>::iterator it;
    for (auto& it: common) {
      cout << it << "\n";
    }

    if (i != t-1) cout << "\n";
  }
}
