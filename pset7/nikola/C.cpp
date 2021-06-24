#include <iostream>
#include <vector>
#include <map>
using namespace std;

/*
DP[a][i]: a = the amount to jump for next time, i = the index in costs we start the jump at for this time

We want to find whether the jump in the forward direction by previous jump + 1 or a jump in the reverse
direction by the previous jump gets us a smaller cost.

Base cases:
1. if i > N - 1, DP = infinity (MAXINT)
2. if i < 0, DP = infinity
3. if i == N - 1, DP = costs[N - 1] (reached the goal)

DP[a][i] = min {
    costs[i] + DP[a + 1][i + a + 1],
    costs[i] + DP[a][i - a]
}
*/

int N;
const int MAXINT = 1000000;
vector<int> costs;

int topDownNikola(int a, int i) {
    static map<pair<int, int>, int> mydp;
    if (i == N - 1) return costs[i];
    if (i < 0 || i > N - 1) return MAXINT;
    if (mydp.count(make_pair(a, i))) {
        return mydp[make_pair(a, i)];
    }

    int ret;
    ret = min(costs[i] + topDownNikola(a + 1, i + a + 1), costs[i] + topDownNikola(a, i - a));
    mydp[make_pair(a, i)] = ret;
    return ret;
}

int main() {
    cin >> N;
    costs.resize(N);

    int cost;
    for (int i = 0; i < N; i++) {
        cin >> cost;
        costs[i] = cost;
    }

    int smallestCost = topDownNikola(1, 1);
    cout << smallestCost;
}