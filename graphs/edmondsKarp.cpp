#include <vector>
#include <string>
#include <iostream>
#include <queue>
using namespace std;

// Edmonds Karp is an algorithm for max flow

typedef vector<int> vi;
#define INF 10000000

// global variables
int n, mf, f, s, t;
vi res;  // nxn residual graph

// p stores the BFS spanning tree from s
vi p;

// traverse BFS spanning tree from s->t
void augment(int v, int minEdge) {
    // record minEdge in a global var f
    if (v == s) {
        f = minEdge;
        return;
    }
    else if (p[v] != -1) {
        augment(p[v], min(minEdge, res[p[v]][v]));
        res[p[v]][v] -= f;
        res[v][p[v]] += f;
    }

    mf = 0;  // max flow
    // O(VE^2) Edmond Karps algorithm
    while (1) {
        f = 0;
        // run BFS, compare with the original BFS
        vi dist(n, INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);

        // record the BFS spanning tree from s->t
        p.assign(n, -1);
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // immediately stop BFS if we already reach sink t
            if (u == t) break;
            for (int v = 0; v < MAX_V; v++) {
                if (res[u][v] > 0 && dist[v] == INF) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                    p[v] = u;
                }
            }
        }
        // find the min edge weight 'f' in this path, if any
        augment(t, INF);
        // cant send any more flow, so terminate
        if (f == 0) break;
        // can still send a flow, so increase max flow
        mf += f;
    }
    cout << mf << "\n";
}


// int main(): set up ‘res’, ‘s’, and ‘t’ with appropriate values