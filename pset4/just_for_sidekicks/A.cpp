#include <iostream>
#include <vector>

using namespace std;

inline int LSOne(const int x) {
    return x & (-x);
}

// for this problem, store how many of a type of gem there is in 6 different vectors
// then, when getting ranged sum, get how many there are and then multiply by this by the value of that type
class FenwickTree {
    vector<long long> types;
    vector<int> gems;
    vector<int> type1;
    vector<int> type2;
    vector<int> type3;
    vector<int> type4;
    vector<int> type5;
    vector<int> type6;
    int n;
public:
    FenwickTree(int x, string s, const vector<long long> gtypes) {
      n = x;
      type1.resize(x + 1, 0);
      type2.resize(x + 1, 0);
      type3.resize(x + 1, 0);
      type4.resize(x + 1, 0);
      type5.resize(x + 1, 0);
      type6.resize(x + 1, 0);
      gems.resize(x + 1, 0);
      types = gtypes;

      for (int i=1;i<=s.length();i++) {
        int t = int(s.at(i-1))-48;
        gems[i] = t;
        if (t == 1) {
          incr(type1, i, 1);
        }
        else if (t == 2) {
          incr(type2, i, 1);
        }
        else if (t == 3) {
          incr(type3, i, 1);
        }
        else if (t == 4) {
          incr(type4, i, 1);
        }
        else if (t == 5) {
          incr(type5, i, 1);
        }
        else {
          incr(type6, i, 1);
        }
      }
    }

    // increase or decrease by 1 at an index of a gem type vector
    void incr(vector<int>& typev, int idx, int val) {
      while (idx <= n) {
        typev[idx] += val;
        idx += LSOne(idx);
      }
    }


    // replace the elem gem to have type val
    void replace(int elem, int val) {
      int orig = gems[elem];
      // decrement original
      if (orig == 1) {
        incr(type1, elem, -1);
      }
      else if (orig == 2) {
        incr(type2, elem, -1);
      }
      else if (orig == 3) {
        incr(type3, elem, -1);
      }
      else if (orig == 4) {
        incr(type4, elem, -1);
      }
      else if (orig == 5) {
        incr(type5, elem, -1);
      }
      else {
        incr(type6, elem, -1);
      }
      gems[elem] = val;

      // increment new
      if (val == 1) {
        incr(type1, elem, 1);
      }
      else if (val == 2) {
        incr(type2, elem, 1);
      }
      else if (val == 3) {
        incr(type3, elem, 1);
      }
      else if (val == 4) {
        incr(type4, elem, 1);
      }
      else if (val == 5) {
        incr(type5, elem, 1);
      }
      else {
        incr(type6, elem, 1);
      }
      gems[elem] = val;
    }

    // ranged sum from 1 to x
    long long rsq(int elem) {
        //cout << "rsq of " << elem << endl;
        long long numGemsType1 = 0;
        long long numGemsType2 = 0;
        long long numGemsType3 = 0;
        long long numGemsType4 = 0;
        long long numGemsType5 = 0;
        long long numGemsType6 = 0;
        while (elem > 0) {
            //cout << "elem = " << elem << endl;
            numGemsType1 += type1[elem];
            numGemsType2 += type2[elem];
            numGemsType3 += type3[elem];
            numGemsType4 += type4[elem];
            numGemsType5 += type5[elem];
            numGemsType6 += type6[elem];

            elem -= LSOne(elem);
        }
        long long summation = numGemsType1 * types[0] +
          numGemsType2 * types[1] + 
          numGemsType3 * types[2] +
          numGemsType4 * types[3] + 
          numGemsType5 * types[4] + 
          numGemsType6 * types[5];
        
        return summation;
    }

    // ranged sum from i to j
    long long rsq(int i, int j) {
        //cout << "doing rsq of " << j << " - rsq of " << i-1 << endl;
        //cout << rsq(j) << " and " << rsq(i - 1) << endl;
        return rsq(j) - rsq(i - 1);
    }

    // revalue gem of type P_idx with value newVal
    void revalue(int idx, int newVal) {
      types[idx - 1] = newVal;
    }
};

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<long long> typeValues(6);
  long long val;
  for (int i=0;i<6;i++) {
    cin >> val;
    typeValues.at(i) = val;
  }

  //long long gems[N];
  string s;
  cin >> s;
  FenwickTree ft(N, s, typeValues);

  int a,b,c;
  while (Q--) {
    cin >> a >> b >> c;

    // replace K_i^th gem with a gem of type P_i
    if (a == 1) {
      ft.replace(b, c);
    }

    // change gem type value
    else if (a == 2) {
      ft.revalue(b, c);
    }

    // ranged sum from b to c
    else {
      cout << ft.rsq(b, c) << "\n";
    }
  }
}
