#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define MAXINT 1000000

vector<int> val;

/*
DP[a][b]: find the minimum number of coins for giving change for $a, given coin denominations
of 1..b

base cases:
1. a = 0 -> min = 0 since we have no amount to make change for
2. b = 0 -> min = infinity since we have no denominations

DP[a][b] = min {
    DP[a - v[b]][b] + 1 (the value we get from taking the max value coin and subtracting from a), 
    DP[a][b - 1] (what we get when we cant use coin value b (its larger than a) and so try to use next highest)
}

Note that this is the recursive version and not the DP version. If a was large enough (thousands), 
the call stack would grow too heavy
*/
int dpRecursive(int a, int b) {
    if (a == 0) return 0;
    if (b < 0 || a < 0) return MAXINT;
    return min(dpRecursive(a - val[b], b) + 1, dpRecursive(a, b - 1));
}

// DP version (top-down)
int dpTopDown(int a, int b) {
    if (a == 0) return 0;
    if (b < 0 || a < 0) return MAXINT;
    static map<pair<int, int>, int> mydp;
    if (mydp.count(make_pair(a, b)) {
        return mydp[make_pair(a, b)];
    }
    int ret;
    ret = min(dpTopDown(a - val[b], b) + 1, dpTopDown(a, b - 1));
    mydp[make_pair(a, b)] = ret;
    return ret;
}


int main() {
    int numc;
    cin >> numc;
    val.resize(numc);

    int i, j, x;

    for (i = 0; i < numc; i++){
        cin >> x;
        val[i] = x;
    }

    int amt;

    // Code for bottom-up (make a table)
    int maxamt = 10000000 / numc;
    vector<vector<int> > dpBottomUp(maxamt + 1);
    for (i = 0; i <= maxamt; i++) {
        dp[i].resize(numc);
    }
    for (j = 0; j < numc; j++) dp[0][j] = 0;
    for (i = 1; i <= maxamt; i++) {
        for (j = 0; j < numc; j++) {
            // min is infinity if we get a value < 0 when we subtract a coin denomination greater than a
            int minval = MAXINT;
            if (i - val[j] >= 0) {
                minval = min(minval, dp[i - val[j]][j] + 1);
            }
            // j > 0 so that we dont negative index when taking next denomination
            if (j > 0) {
                minval = min(minval, dp[i][j - 1]);
            }
            dp[i][j] = minval;
        }
    }

    cin >> amt;
    while (amt > 0) {
        // Code for testing recursive and top-down
        // cout << "The min number of coins for " << amt << " is " << dpRecursive(amt, numc-1) << endl;
        // cout << "The min number of coins for " << amt << " is " << dpTopDown(amt, numc-1) << endl;

        // Code for testing bottom-up
        if (amt > maxamt) {
            cout << "Too big!\n";
        }
        else {
            // Look up in table instead of calling the unction
            cout << "The min number of coins for " << amt << " is " << dpBottomUp[amt, numc-1] << endl;
        }

        cin >> amt;
    }
}