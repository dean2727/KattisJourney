/*
Dikjstras algorithm:
For finding the single source shortest path. Relax the edges n stuff.
Works for negative weight edge, but not negative weight cycle

Read in t2.in
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INF 999999999

int main() {
    int i,j,k;
    int n, m;
    cin >> n >> m;

    // adjacency list
    // each vector is adj list for a node, with pair<destination, weight>
    vector<vector<pair<int,int>>> adj(n);
    for (i=0;i<m;i++) {
        int x, y, z;
        cin >> x >> y >> z;
        adj[x].push_back(make_pair(y,z));
    }

    vector<int> dist(n, INF);
    dist[0] = 0;
    priority_queue<pair<int,int>> pq;  // <distance, node #>
    pq.push(make_pair(0, 0));
    int node, nodedist, newdist;
    while (!pq.empty()) {
        // when we pull from top and push in new, we negate it, since the comparison is default decreasing (< command
        // used to create a max priority queue. if something is less than something else, it goes later in the queue)
        nodedist = -pq.top().first;
        node = pq.top().second;
        pq.pop();

        if (-nodedist > dist[node]) {
            // this is an old node entered into the list (already processed shorter distance for this node previously)
            // easier to just put into the queue over and over
            continue;
        }

        // relax all the edges from node
        for (i=0;i<adj[node].size();i++) {
            newdist = dist[node] + adj[node][i].second;
            // is the route to this edge shorter than what we got previously?
            if (newdist < dist[adj[node][i].first]) {
                dist[adj[node][i].first] = newdist;
                pq.push(make_pair(-newdist, adj[node][i].first));
            }
        }
    }
}