#include <iostream>
#include <vector>
#include <map>
#include <tuple>
using namespace std;

const int NEG_INF = -10000000;

#define loop(i, a, b) for(i = (a); i < (b); i++)
typedef tuple<int, int, int> t;
int i;
vector<vector<int> > v;

/*
DP[i][j][k] = maximum obtained at row i, for k remaining rooms to block off, where j indicates whether row
above has left (j=0), right (j=1), or both (j=2) open (j is a state that determines what our options are)

Base cases:
1. DP[i][j][anything > i] = negative value. e.g. if you have to block off 10 rooms but youre 9 from the bottom, youre stuck
2. DP[0][j][k] = negative value. have to use up your last room before you get to the bottom
3. DP[i > 0][j][k < 0] = negative value
4. DP[0][j][]

DP[i][j][k] = max {
    // Use both rooms on this level (don’t use any “blocks” up)
    DP[i-1][2][k] + v[i][0] + v[i][1],
    // level above has left room open, so OK to block right room (j != 1)
    DP[i-1][0][k-1] + v[i][0],
    // level above has right room open, so OK to block left room (j != 0)
    DP[i-1][1][k-1] + v[i][1]
}

Run DP with DP[n][2][# to block], which says that we are starting at the top, we need to block off k rooms,
and there are technically 2 open rooms above the first row
*/

int NAGTopDown(int i, int j, int k) {
    if (k > i) return NEG_INF;
    if (i == -1 && k > 0) return NEG_INF;
    if (i >= 0 && k < 0) return NEG_INF;
    if (i < 0) return 0;

    static map<t, int> seen;
    if (seen.count(make_tuple(i,j,k))) return seen[make_tuple(i,j,k)];

    int ret;
    int o1;
    if (j == 2) {
        o1 = max(NAGTopDown(i-1, 0, k-1) + v[i][0], NAGTopDown(i-1, 1, k-1) + v[i][1]);
    }
    // j isnt 1, so right room isnt open, and so its closed, and so the left room must be open on next go
    else if (j != 1) {
        o1 = NAGTopDown(i-1, 0, k-1) + v[i][0];
    }
    // j isnt 0, so left room isnt open, and so its closed, and so the right room must be open on next go
    else {
        o1 = NAGTopDown(i-1, 1, k-1) + v[i][1];
    }

    ret = max(o1, NAGTopDown(i-1, 2, k) + v[i][0] + v[i][1]);
    //cout << "ret = " << ret << " for " << i << "," << j << "," << k << endl;
    seen[make_tuple(i,j,k)] = ret;
    return ret;
}

// int NAGBottomUp(int k, const vector<int>& left, const vector<int>& right) {
//     map<t, int> m;
//     int a, numRows = left.size(), minVal;

//     // compute values for all possible configurations where all k rooms are blocked off
    
//     // compute for blocking 1 room (both spots, all rows), then 
//     for (int roomsLeft = k - 1; roomsLeft >= 0; roomsLeft--) {
//         for (int r = 0; i < numRows; i++) {
//             m[make_tuple(left[r], numRows, k, false, false, left, right)] = minVal;
//         }

//         minVal = 
//         m[] = 
//     }

//     // fill base case states (row number = size, k > 0)
//     minVal = MAXINT;
//     for (int i = 1; i <= k; i++) {
//         ret[make_tuple(0, numRows, k, false, false, left, right)] = minVal;
//         ret[make_tuple(0, numRows, k, true, false, left, right)] = minVal;
//         ret[make_tuple(0, numRows, k, false, true, left, right)] = minVal;
//     }


//     return minVal;
// }


int main() {
    int N, k, r1, r2;

    cin >> N;
    while (N != 0) {
        v.resize(N);
        cin >> k;
        loop (i, 0, N) {
            cin >> r1 >> r2;
            v[i].push_back(r1);
            v[i].push_back(r2);
        }

        // run the DP
        int maxRoom = NAGTopDown(N-1, 2, k);
        cout << maxRoom << endl;

        v.clear();
        cin >> N;
    }
    cin >> k;
}