#include <iostream>
#include <map>
using namespace std;

/*
DP[a][b] = is number of floors computable with a eggs and b drops allowed.

base cases:
- DP[0][b] = 0 (cant figure out anything no eggs)
- DP[a][0] = 0 (cant figure out anything no drops)
- DP[1][b] = b (1 egg can only test 1 floor at a time, so b maximum)

If it doesn’t break, then you still have a eggs, and b-1 drops left above this height, so DP[a][b-1]
If it breaks, you you have a-1 eggs left, and b-1 drops below this height, so DP[a-1][b-1]
Plus, you’ve tested this height, so 1 more level
DP[a][b] = DP[a][b-1] + DP[a-1][b-1] + 1
*/

long long dp(long long a, int b) {
    static map<pair<long long,int>, long long> seen;
    if (a == 0 || b == 0) {
        return 0;
    }
    if (a == 1 && b > 0) {
        return b;
    }

    if (seen.count(make_pair(a, b))) {
        return seen[make_pair(a, b)];
    }

    long long ret = dp(a, b-1) + dp(a-1, b-1) + 1;
    seen[make_pair(a, b)] = ret;
    return ret;
}
// problem test case: should be 32 but you output impossible

int main() {
    int T;
    cin >> T;
    while(T--) {
        long long N, K;
        cin >> N >> K;

        // for a given K (# of eggs), how many drops (i) needed for x = DP[K][i] to
        // be greater than or equal to N (# of floors)?
        long long x;
        bool impossible = true;
        for (int i=0;i<=32;i++) {
            //cout << "i = " << i << endl;
            x = dp(K, i);
            //cout << "x = " << x << endl;
            if (x >= N) {
                cout << i << "\n";
                impossible = false;
                break;
            }
        }
        if (impossible) cout << "Impossible\n";
    }
}