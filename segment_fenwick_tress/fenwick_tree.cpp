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
    int n;  // size

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

    // https://cp-algorithms.com/data_structures/fenwick.html#toc-tgt-10
    // void add(int idx, int val) {
    // for (++idx; idx < n; idx += idx & -idx)
    //     a[idx] += val;
    // }

    // void range_add(int l, int r, int val) {
    //     add(l, val);
    //     add(r + 1, -val);
    // }

    void print() {
        for (int i=1;i<=a.size();i++) {
            cout << i << "--->" << a[i] << endl;
        }
    }
};

int main() {
    // N = number in array, Q = number of operations
    int N = 0, Q = 0;
    cin >> N >> Q;
    FenwickTree myTree(N);

    int a, b, val;
    char operation;

    while (Q--) {
        cin >> operation;
        if (operation == '+') {
            //cin >> a >> b;
            scanf("%d %d", &a, &b);
            myTree.incr(a + 1, b);
            myTree.print();
        }
        // add a value to each element in the range
        // else if (operation == '-') {
        //     cin >> a >> b >> val;
        //     myTree.range_add(a, b, val);
        //     myTree.print();
        // }
        else {
            cin >> a >> b;
            printf("%lld\n", myTree.rsq(a, b));
        }

    }

    cin >> N >> Q;
}