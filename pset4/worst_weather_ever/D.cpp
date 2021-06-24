#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
using namespace std;

typedef vector<int> vi;

#define trav(a, x) for(auto& a : x)

class SegmentTree {
private:
    int n;
    // A holds our actual values (rain amounts)
    vector<long long> A;
    // index of st = where in the tree we are (e.g. root is 1, its left child is 2, right child is 3, etc),
    // which also represents a range (e.g. root is [0, 6])
    // value of st = the index of A for the maximmum value in the range
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
            st[p] = (A[p1] >= A[p2]) ? p1 : p2;
        }
    }

    // find index of the maximum element in the range [i..j], runtime: O(log n)
    int rmq(int p, int L, int R, int i, int j) {
        // current segment is outside the query range [i, j]
        if (i > R || j < L) return -1;
        // [L, R] inside the range [i, j]
        if (L >= i && R <= j) return st[p];

        // compute max position in the left and right part of the interval
        int p1 = rmq(left(p), L, (L + R) / 2, i, j);
        int p2 = rmq(right(p), (L + R) / 2 + 1, R, i, j);

        // if we try to access segment outside query
        if (p1 == -1) return p2;
        if (p2 == -1) return p1;

        // gets us the index in A of the max value of the range
        return (A[p1] >= A[p2]) ? p1 : p2;
    }

public:
    SegmentTree(const vector<long long> &_A) {
        A = _A; n = (int)A.size();
        // vector will consist of 4n zeroes (which is large enough)
        st.assign(4 * n, 0);
        // recursive build
        build(1, 0, n - 1);
    }

    int rmq(int i, int j) {
      return rmq(1, 0, n - 1, i, j);
    }
};

int main() {
  int n, y, m, y1, y2;
  long long r;
  string newline;

  // end input on 0
  cin >> n;
  while (n != 0) {
    int years[n];
    vector<long long> amounts;
    int y, nn = n, idx;
    long long r;

    // keep track of year and index. this tells us whether the years in between were recorded
    map<int, int> yearIdx;

    // if a query has a year thats not in this set, output "maybe"
    set<int> recordedYears;

    // map rain amounts to latest year idx (for checking the X < Z < Y inequality)
    map<int, int> latestAmts;

    scanf("%d %lld", &y, &r);
    years[0] = y;
    amounts.push_back(r);
    yearIdx.insert(make_pair(y, 0));
    recordedYears.insert(y);
    int init = y;

    n--;
    int i = 1;
    while (n--) {
      scanf("%d %lld", &y, &r);
      years[i] = y;
      amounts.push_back(r);
      latestAmts[r] = i;
      yearIdx.insert(make_pair(y, i));
      recordedYears.insert(y);
      i++;
    }

    SegmentTree st(amounts);

    int stret;
    scanf("%d\n", &m);
    while (m--) {
      scanf("%d %d", &y1, &y2);

      int similar = 1;
      if (amounts[yearIdx[y1]] == amounts[yearIdx[y2]]) similar++;

      // year data missing if the difference in years is not equal to difference in indexes
      bool nonexistYear = false;
      bool outOfBounds = false;
      if (y2 - y1 != yearIdx[y2] - yearIdx[y1]) {
        nonexistYear = true;
      }
      if (!recordedYears.count(y1) || !recordedYears.count(y2)) {
        outOfBounds = true;
      }

      // find the max amount of rain in the range. if the year with highest amount is y1,
      // and we know all the amounts in between the 2 years, print true
      // if we know all the amounts but y1 isnt max, print false
      // print maybe otherwise
      stret = st.rmq(yearIdx[y1], yearIdx[y2]);
      //cout << "similar = " << similar << endl;
      //cout << stret << endl;
      //cout << amounts[yearIdx[y1]] << endl;

      // cant claim anything if the given range is out of bounds of our recorded years
      if (outOfBounds) {
        printf("maybe\n");
      }
      else {
        // if y1 had the most
        idx = yearIdx[y1];
        if (idx == stret) {
          // if this truly was the last time we've seen this amount (no later year with same amount)
          if (idx != latestAmts[amounts[idx]] && latestAmts[amounts[idx]] <= yearIdx[y2]) printf("false\n");
          else if (nonexistYear) printf("maybe\n");
          else printf("true\n");
        }

        // else, print "false" no matter what
        else {
          printf("false\n");
        }
      }
    }

    getline(cin, newline);
    cin >> n;
    if (n != 0) printf("\n");
  }
  cin >> n;
}
