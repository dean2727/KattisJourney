#include <iostream>
#include <vector>
#include <map>
using namespace std;

/*
DP[a][b]: returns true if stan wins and false if ollie wins. a = # of stones left. b = player indication
(stan is 0, ollie is 1)

Base cases:
- DP[0][0] = true
- DP[0][1] = false

DP[i][j] = {
    if DP[i-k][0] is true for any k, DP[i][0] is true, so stan can win
    if DP[i-k][1] is true for any k, DP[i][1] is false, so ollie can win
}
*/

vector<int> moves;
map<pair<int, int>, bool> seen;

bool findWinner(int a, int b) {
    //cout << "a = " << a << ". b = " << b << endl;
    if (seen.count(make_pair(a, b))) {
        return seen[make_pair(a, b)];
    }
    bool ret;
    if (a == 0) {
        if (b == 0) ret = true;
        else ret = false;
    }

    bool stanWins = false, ollieWins = false;
    // For Stan (DP[i][0]): For each stone, test each amount k that can be removed.
    // If DP[i-k][1] is true for any k, then DP[i][0] is true; means S can get to a winning state.
    // Otherwise, it’s false (meaning Ollie can win no matter what)
    if (b == 0) {
        //cout << "Stans turn!\n";
        for (int i=0;i<moves.size();i++) {
            //cout << "moves[i] = " << moves[i] << endl;
            if (a-moves[i] >= 0 && findWinner(a-moves[i], 1)) {
                //cout << "we can move, getting us to " << a-moves[i] << " stones, so stan wins!\n";
                ret = true;
                stanWins = true;
                break;
            }
        }
    }

    // For Ollie (DP[i][1]): For each stone, test amount k that can be removed
    // If DP[i-k][0] is false for any k, then DP[i][1] is false; means O can get to a winning state
    // Otherwise, it’s true (meaning Stan can win no matter what)
    else {
        //cout << "ollies turn!\n";
        for (int i=0;i<moves.size();i++) {   
            //cout << "moves[i] = " << moves[i] << endl;
            if (a-moves[i] >= 0 && !findWinner(a-moves[i], 0)) {
                //cout << "we can move, getting us to " << a-moves[i] << " stones, so ollie wins!\n";
                ret = false;
                ollieWins = true;
                break;
            }
        }
    }

    if (!stanWins) ret = false;
    if (!ollieWins) ret = true;
    
    // if (ret) cout << "Stan wins for when we have " << a << " stones left\n";
    // else cout << "Ollie wins for when we have " << a << " stones left\n";
    seen[make_pair(a, b)] = ret;
    return ret;
}

int main() {
    int n, m, k;

    while (cin >> n) {
        cin >> m;
        moves.resize(m);
        int move;
        for (int i=0;i<m;i++) {
            cin >> move;
            moves[i] = move;
        }
        //cout << "find winner on " << n << endl;
        //cout << moves.size() << endl;
        if (findWinner(n, 0)) cout << "Stan wins\n";
        else cout << "Ollie wins\n";
        moves.clear();
        seen.clear();
    }
}