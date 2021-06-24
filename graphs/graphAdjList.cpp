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

// adjacency list
// O(V + E)
struct node {
    int value;  // if we store a value in the node
    vector<int> adj;
    vector<int> weight;
};

int main() {
    // n nodes, k edges
    int n, j, i, j, a, b, w;
    cin >> n;

    vector<node> v(n+1);

    // read in values per node
    // for (i=1;i<=n;i++) {
    // }

    cin >> k;
    for (i=0;i<k;i++) {
        cin >> a >> b >> w;
        v[a].adj.push_back(b);
        v[a].weight.push_back(w);
        // if you need to sort adj, you also need to sort weight, so be careful,
        // could use pairs instead
        // skip these 2 if its a directed graph
        v[b].adj.push_back(a);
        v[b].weight.push_back(w);
    }

    // BFS (unweighted)
    // distances are initially -1
    for (i=1;i<=n;i++) v[i].value = -1;
    v[1].value = 1;
    // node we are going to look at
    queue<int> q;  // DFS uses stack
    q.push(1);
    int time = 0;  // may need to keep time
    while (!q.empty()) {
        a = q.front();  // .top() for DFS
        q.pop();
        time++;
        cout << "Encountered node " << a << " at time " << time << endl;
        // look at adj nodes, if not visited, stick in queue
        for (i=0;i<v[a].adj.size();i++) {
            b = v[a].adj[i];
            if (v[b].value == -1) {
                v[b].value = v[a].value+1;
                q.push(b);
            }
        }
    }

    for (i=1;i<=n;i++) {
        cout << "The distance of node " << i << " is " << v[i].value << endl;
    }
}