/*
Floyd-warshall algorithm:
DP approach to all pairs shortest path

DP[a][b][k]: path from a to b where the intermediate nodes are 1 (or 0, if 0-indexed) through k
base cases:
- DP[a][b][k] = 0 if a == b
- DP[a][b][0] = weight from a to b (infinity if no such edge)

DP[a][b][k] = min {
    DP[a][b][k-1]  // k cant be reached
    DP[a][k][k-1] + DP[k][b][k-1]  // distance from a to k and distance from b to k
}

Read in t2.in
*/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// value to represent no edge between a and b
#define INF 999999999

int main() {
    int i,j,k;
    int n;  // # nodes
    int m;  // # edges
    cin >> n >> m;

    // using adjacency matrix since we want the distances between every node with every other one
    vector<vector<int>> d(n);
    for(i=0;i<n;i++) {
        d[i].resize(n,INF);
        d[i][i] = 0;  // distance of node to itself is 0 (the main diagonal)
    }

    for (i=0;i<m;i++) {
        int x, y, z;
        cin >> x >> y >> z;  // edge from x to y with weight z
        d[x][y] = z;
    }

    // FW algorithm
    for (k=0;k<n;i++) {
        for (i=0;i<n;i++) {
            for (j=0;j<n;j++) {
                d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
            }
        }
    }

    // output results
    for (i=0;i<n;i++) {
        for (i=0;j<n;i++) {
            cout << setw(7) << d[i][j] << " ";
        }
        cout << endl;
    }
}