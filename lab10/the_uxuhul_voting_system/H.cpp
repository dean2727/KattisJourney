#include <iostream>
#include <vector>
using namespace std;

#define loop(i,a,b) for(i=a;i<b;i++)
vector<vector<int> > prefs;

/*
DP[i][j] = ending position if person i is given starting position j for the 3 stones

DP[i][j] = max {
   DP[i-1][a],
   DP[i-1][b],
   DP[i-1][c] (a, b, c resulting from flipping each of the 3 bits)
}

Base case: DP[0][0]
*/

int recoverOutcome(int i, int j) {
    cout << i << j << endl;
    if (i == 0 && j == 0) {
        return 0;
    }

    // flip the first stone, second stone, and third stone
    int a = j, b = j, c = j;
    a ^= (1 << 2);
    b ^= (1 << 1);
    c ^= (1 << 0);

    int ret, max1;
    if (i == 0) {
        max1 = max(a, b);
        ret = max(max1, c);
    }
    else {
        max1 = max(recoverOutcome(i-1, a), recoverOutcome(i-1, b));
        ret = max(max1, recoverOutcome(i-1, c));
    }
    return ret;
}

int main() {
    int n, m, i, j, k, pref, i2, maxRes = -1;
    cin >> n;
    
    loop(i2,0,n) {
        cin >> m;
        prefs.resize(m);
        loop(j,0,m) {
            prefs[j].resize(8);
            loop(k,0,8) {
                cin >> pref;
                prefs[j][k] = pref-1;
            }
        }

        loop(i,0,8) {
            pref = recoverOutcome(m-1, prefs[m-1][i]);
            if (pref > maxRes) {
                maxRes = pref;
            }
        }
        cout << maxRes << endl;

        prefs.clear();
    }
}