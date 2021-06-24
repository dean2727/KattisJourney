#include <vector>
#include <queue>
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
    int n, m, x, y;
    double f, frac = 1.0;
    cin >> n;
    while (n != 0) {
        cin >> m;

        // adjacency list
        // each vector is adj list for a node, with pair<destination, factor>
        vector<vector<pair<int,double>>> adj(n);
        for (int i=0;i<m;i++) {
            cin >> x >> y >> f;
            adj[x].push_back(make_pair(y, f));
            adj[y].push_back(make_pair(x, f));
        }

        // using dikjstras
        // dist has 1-frac valus after applying fractions. e.g. 0->1 has f = .25, then this edge represents 1-.25=.75
        vector<double> dist(n, 1000000.0);
        dist[0] = 0.0;
        priority_queue<pair<double,int>> pq;  // <1-frac, node #>, sort by increasing 1-frac
        pq.push(make_pair(0.0, 0));
        int node;
        double nodedist, newdist;
        while (!pq.empty()) {
            nodedist = -pq.top().first;
            node = pq.top().second;
            pq.pop();

            if (-nodedist > dist[node]) {
                // this is an old node entered into the list (already processed bigger factor for this node previously)
                continue;
            }

            // relax all the edges from node
            for (int i=0;i<adj[node].size();i++) {
                newdist = 1 - (1 - dist[node]) * adj[node][i].second;
                
                // is the route to this edge shorter than what we got previously?
                if (newdist < dist[adj[node][i].first]) {
                    dist[adj[node][i].first] = newdist;
                    pq.push(make_pair(-newdist, adj[node][i].first));
                }
            }
        }

        cout << fixed << setprecision(4) << 1-dist[n-1] << "\n";
        cin >> n;
    }
    cin >> m;
}