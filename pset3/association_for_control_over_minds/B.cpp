#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

const int maxIn = 500050;
int ingridients[maxIn];
int ncount[maxIn];

int findset(int i) {
    stack<int> s;
    while (i != ingridients[i]) {
        s.push(i);
        i = ingridients[i];
    }
    while (!s.empty()) {
        ingridients[s.top()] = i;
        s.pop();
    }
    return i;
}

void merge(int x, int y) {
    x = findset(x);
    y = findset(y);

    if (x != y) {
      ingridients[y] = ingridients[x];
      ncount[x] += ncount[y];
    }
}

int main () {
    int N = 0, M = 0, ingridient = 0, numConcoc = 0, sz, sz0;
    cin >> N;
    vector<int> v;

    // Keep sets of ingredients; each starts in its own set
    // For each set, keep track of total number in that set
    for(int i=0;i<maxIn;i++) {
      ingridients[i]=i;
      ncount[i]=1;
    }

    while (N--) {
      cin >> M;
      v.clear();
      
      // For a recipe, find which set each ingredient is currently in, keep a list of these,
      //then sort (to help count; or use hash table to assist counting)
      for (int i=0;i<M;i++) {
        cin >> ingridient;
        v.push_back(findset(ingridient));
      }
      sort(v.begin(), v.end());

      // erase duplicates
      v.erase(unique(v.begin(), v.end()), v.end());
      sz = v.size();

      // Count the number of times each set appears in the recipe; if that matches the size of that set,
      // then it is OK to use it
      int numTimes = 0;
      for (int i=0;i<sz;i++) {
        numTimes += ncount[v[i]];
      }

      if (numTimes == M) {
        numConcoc++;
        for (int j=0;j<sz;j++) {
          merge(v[j], v[0]);
        }
      }
    }
    cout << numConcoc;
}
