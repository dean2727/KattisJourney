#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int n;
  cin >> n;

  int num;
  map<string, int> co;
  vector<string> combos;
  while (n--) {
    vector<int> c;
    string combo = "";

    cin >> num;
    c.push_back(num);

    cin >> num;
    c.push_back(num);

    cin >> num;
    c.push_back(num);

    cin >> num;
    c.push_back(num);

    cin >> num;
    c.push_back(num);

    sort(c.begin(), c.end());

    for (int i=0;i<c.size();i++) {
      combo += to_string(c[i]);
    }

    co[combo]++;
    combos.push_back(combo);
  }

  // get most popular (max value of map)
  int mostPop = 0;
  for (map<string, int>::iterator it=co.begin();it!=co.end();it++){
    //cout << it->second << endl;
    if (it->second > mostPop) {
      mostPop = it->second;
    }
  }

  // get how many combos have most popular value
  int numMostPop = 0;
  for (int i =0;i<combos.size();i++){
    if (co[combos[i]] == mostPop) {
      numMostPop++;
    }
  }

  cout << numMostPop;
}
