#include <iostream>
#include <vector>
using namespace std;

//#define LSOne(x) ((x) & (-(x)))  macro is similar to inline function
inline int LSOne(const int x) {
    return x & (-x);  // -x is 2's complement
}

// bit more efficient then a segment tree
class FenwickTree {
    vector<long long> a;
    int n;

public:
    FenwickTree(int x) {
        n = x;
        a.resize(x + 1, 0);
    }
    
    // must change everything along the line
    // elem = number to increase, val = amount to increase by
    void incr(int elem, long long val) {
        while (elem <= n) {
            a[elem] += val;
            elem = elem + LSOne(elem);
        }
    }

    // ranged sum from 1 to x
    long long rsq(int elem) {
        long long summation = 0;
        while (elem > 0) {
            summation += a[elem];
            elem -= LSOne(elem);
        }
        return summation;
    }

    // ranged sum from i to j
    long long rsq(int i, int j) {
        return rsq(j) - rsq(i - 1);
    }

    void print() {
        for (int i=1;i<=a.size();i++) {
            cout << i << "--->" << a[i] << endl;
        }
    }
};

// query an individual height, and it returns the amount of things at that height
// H elements, query each height
// 1 fenwick tree for stalagmites, 1 for stalagtites
int main() {
    int N, H;
    cin >> N >> H;

    FenwickTree ftBottom(H+1);
    FenwickTree ftTop(H+1);

    int st;
    for (int i=0;i<N;i++) {
        cin >> st;

        // bottom (stalagmite)
        if (i % 2 == 0) {
            ftBottom.incr(st, 1);
        }

        // top (stalagtite)
        else {
            ftTop.incr(st, 1);
        }
    }

    int minObst = 1000000, tot, minLevel = 0;
    for (int i=1;i<=H;i++) {
        tot = ftBottom.rsq(i) + ftTop.rsq(i, H);
        if (tot < minObst) {
            minObst = tot;
            minLevel = i;
        }
    }

    cout << minLevel << " " << minObst;
}