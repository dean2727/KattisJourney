#include <iostream>
#include <math.h>
using namespace std;

long long big = 1e9 + 7;

/*
function to get the number of "11" substrings:
for bit i, it can be 0, in which case there are n-1 possible substrings of 11.
it can also be 1, and if the next bit is 1, there are 2^(n-2) possible substrings,
and if next bit is 0, there are n-2 possible substrings
*/
pair<long long, long long> dpBinary(int n) {
    long long dp[n+1];
    dp[0] = 0;
    dp[1] = 0;

    long long pow2[n+1];
    pow2[0] = 1;

    for (int i=1;i<=n;i++) {
        pow2[i] = (2 * pow2[i-1]) % big;
    }

    for (int i=2;i<=n;i++) {
        dp[i] = (dp[i-2] + dp[i-1] + pow2[i-2]) % big;
    }

    return make_pair(pow2[n], dp[n]);
}

int main() {
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        if (n == 1) cout << "2\n";
        else if (n == 2) cout << "3\n";
        else {
            pair<long long, long long> ans = dpBinary(n);

            /*
            just because x > y, doesnt mean that x mod n > y mod n,
            so if (x - y) mod n is negative, we need to make this positive
            by adding n
            */
            if (ans.first - ans.second < 0) {
                cout << ans.first - ans.second + big << "\n";
            }
            else {
                cout << ans.first - ans.second << "\n";
            }
        }
    }
}