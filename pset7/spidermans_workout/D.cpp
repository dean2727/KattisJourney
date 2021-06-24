#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
using namespace std;

const int MAXINT = 1000000;
vector<int> dist;

#define loop(i, a, b) for(i = (a); i < (b); i++)
typedef tuple<int,int,int,string> t;

map<t, int> seen;
map<int, string> moves;
int i;

/*
DP[a][b][c][seq]: find the sequence of moves corresponding to the minimum max height, c, of a building for
spiderman's workout given his current distance from ground level, a, and 1..b distances. seq = the string to
specify the moves

base cases:
1. if b == dist.size() and a != 0, return MAXINT
2. if a - dist[b] < 0, return MAXINT
3. if b == dist.size() and a == 0, return c

we take the minimum of climbing down b distance from a and then considering the next distance in the
sequence, and climbing up b distance from a and then considering the next distance
DP[a][b][c] = min {
    DP[a - dist[b]][b + 1][c]
    DP[a + dist[b]][b + 1][max(a + dist[b] + 2, c)]
}
*/

int spiderManTopDown(int a, int b, int c, string seq) {
    if (b == dist.size()) {  
        if (a == 0) {
            moves.insert(make_pair(c, seq));
            return c;            
        }
        else return MAXINT;
    }
    if (a < 0) return MAXINT;

    t tupl(a, b, c, seq);
    if (seen.count(tupl)) {
        return seen[tupl];
    }

    int ret;
    ret = min(
        spiderManTopDown(a-dist[b], b+1, c, seq+"D"),
        spiderManTopDown(a+dist[b], b+1, max(a+dist[b]+2, c), seq+"U")
    );
    seen[tupl] = ret;
    return ret;
}

int spiderManBottomUp() {
    int ret;

    // store the case of being below 

    return ret;
}

int main() {
    int N, M, d;
    cin >> N;
    while (N--) {
        string seq = "";
        cin >> M;
        loop(i, 0, M) {
            cin >> d;
            dist.push_back(d);
        }

        int x = dpRecursive(0, 0, 2, "");
        if (moves.count(x) == 0) {
            cout << "IMPOSSIBLE\n";
        }
        else {
            cout << moves[x] << endl;
        }

        dist.clear();
        seen.clear();
        moves.clear();
    }
}