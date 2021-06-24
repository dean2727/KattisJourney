/*
t1.in
example graph edge list - start, end, weight
6 nodes
7 edges
1 2 4
3 2 5
1 3 7
5 4 6
3 6 1
4 3 3
5 6 9
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int main() {
    // n nodes, k edges
    int n, j, i, j, a, b, w;
    cin >> n;

    // using an adjacency table/matrix. better for dense graphs
    // O(V^2)
    // doesnt work for 2 nodes that have multiple edges to each other (since only 1 entry in table)
    vector<vector<int> > v(n+1);

    for (i=1;i<=n;i++) {
        // read in values per node
        v[i].resize(n+1, -1);
    }

    cin >> k;
    for (i=0;i<k;i++) {
        cin >> a >> b >> w;
        v[a][b] = w;
        // skip this line if directed graph
        v[b][a] = w;
    }

    // BFS (unweighted)
    vector<int> value(n+1, -1);
    value[1] = 1;
    queue<int> q;  // DFS uses stack
    q.push(1);
    int time = 0;  // may need to keep time
    while (!q.empty()) {
        a = q.front();  // .top() for DFS
        q.pop();
        time++;
        cout << "Encountered node " << a << " at time " << time << endl;
        for (b=1;b<=n;b++) {
            // if a is connected to b and unvisited
            if (v[a][b] != -1 && value[b] == -1) {
                value[b] = value[a]+1;
            }
        }
    }

    for (i=1;i<=n;i++) {
        cout << "The distance of node " << i << " is " << value[i] << endl;
    }
}