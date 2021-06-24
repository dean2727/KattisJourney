// from pg. 57 in the book

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;

class SegmentTree {
private:
    int n;
    // A holds our actual values
    vi A;
    // index of st = where in the tree we are (e.g. root is 1, its left child is 2, right child is 3, etc),
    // which also represents a range (e.g. root is [0, 6])
    // value of st = the index of A for the minimum value in the range
    vi st;

    // left child is 2i, right is 2i + 1. this is same as binary heap operations
    int left (int p) { return p << 1; }
    int right (int p) { return (p << 1) + 1; }

    // recursively build the tree, runtime: O(n)
    void build(int p, int L, int R) {
        if (L == R) {
            st[p] = L;
        }
        else {
            build(left(p), L, (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R);
            int p1 = st[left(p)], p2 = st[right(p)];
            st[p] = (A[p1] <= A[p2]) ? p1 : p2;
        }
    }

    // find index of the minimum element in the range [i..j], runtime: O(log n)
    int rmq(int p, int L, int R, int i, int j) {
        // current segment is outside the query range [i, j]
        if (i > R || j < L) return -1;
        // [L, R] inside the range [i, j]
        if (L >= i && R <= j)

        // compute min position in the left and right part of the interval
        int p1 = rmq(left(p), L, (L + R) / 2, i, j);
        int p2 = rmq(right(p), (L + R) / 2 + 1, R, i, j);

        // if we try to access segment outside query
        if (p1 == -1) return p2;
        if (p2 == -1) return p1;

        // gets us the index in A of the min value of the range
        return (A[p1] <= A[p2]) ? p1 : p2;
    }

public:
    SegmentTree(const vi &_A) {
        A = _A; n = (int)A.size();
        // vector will consist of 4n zeroes (which is large enough)
        st.assign(4 * n, 0);
        // recursive build
        build(1, 0, n - 1);
    }
    
    int rmq(int i, int j) {
      return rmq(1, 0, n - 1, i, j);
    }
}