#include <iostream>
#include <vector>
using namespace std;

inline int LSOne(const int x) {
    return x & (-x);  // -x is 2's complement
}

class FenwickTree {
    vector<int> bits;
    vector<int> sums;
    int n;

public:
    FenwickTree(int x) {
        n = x;
        bits.resize(x + 1, 0);
        sums.resize(x + 1, 0);
    }

    // if a bit is set, increment everything along the line by 1, else decrement by 1
    void incr(int elem, int val) {
        while (elem <= n) {
            sums[elem] += val;
            elem = elem + LSOne(elem);
        }
    }

    void flip(int i) {
        if (bits[i]) {
            bits[i] = 0;
            incr(i, -1);
        }
        else {
            bits[i] = 1;
            incr(i, 1);
        }
    }

    // ranged sum from 1 to x
    int rsq(int elem) {
        int summation = 0;
        while (elem > 0) {
            summation += sums[elem];
            elem -= LSOne(elem);
        }
        return summation;
    }

    // ranged sum from i to j
    long long rsq(int i, int j) {
        return rsq(j) - rsq(i - 1);
    }
};

int main() {
  int N, K;
  cin >> N >> K;

  FenwickTree ft(N);

  char x;
  int i, l, r;
  while (K--) {
    cin >> x;
    if (x == 'F') {
      // flip the bit
      cin >> i;
      ft.flip(i);
    }
    // count number of set bits in range
    else {
      cin >> l >> r;
      cout << ft.rsq(l, r) << "\n";
    }
  }
}
