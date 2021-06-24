#include <iostream>
#include <vector>
using namespace std;

inline int LSOne(const int x) {
    return x & (-x);  // -x is 2's complement
}

// bit more efficient then a segment tree
class FenwickTree {
    vector<int> a;
    int n;

public:
    FenwickTree(int x) {
        n = x;
        a.resize(x + 1, 0);
    }
    
    // must change everything along the line
    // elem = number to increase, val = amount to increase by
    void incr(int elem, int val) {
        while (elem <= n) {
            a[elem] += val;
            elem = elem + LSOne(elem);
        }
    }

    // ranged sum from 1 to x
    int rsq(int elem) {
        long long summation = 0;
        while (elem > 0) {
            summation += a[elem];
            elem -= LSOne(elem);
        }
        return summation;
    }

    // ranged sum from i to j
    int rsq(int i, int j) {
        return rsq(j) - rsq(i - 1);
    }

    void print() {
        for (int i=1;i<=a.size();i++) {
            cout << i << "--->" << a[i] << endl;
        }
    }
};

int main() {
    int N, num;
    cin >> N;
    vector<int> positions(N+1);
    FenwickTree ft(N);

    for (int i = 1; i <= N; i++) {
        cin >> num;
        positions[num] = i;
        ft.incr(i, 1);
    }

    int l = 1, r = N;
    for (int i = 1; i <= N; i++) {
        if (i % 2 == 1) {
            ft.incr(positions[l], -1);
            cout << ft.rsq(1, positions[l]) << endl;
            l++;
        }
        else {
            ft.incr(positions[r], -1);
            cout << ft.rsq(positions[r], N) << endl;
            r--;
        }
    }
}