#include <iostream>
#include <vector>
#include <math.h>
#include <cstring>
using namespace std;

/*
Graph setup:
There is a source node, s, a sink node, t, and 2 "layers", the first one containing the
gopher start holes, and the other containing the end holes. From the source node, s, draw edges
of weight 1 to each of the gopher starting holes. Then, for each starting hole, calculate the 
euclidean distance to each ending hole. The time in seconds for the gopher to get from point
A to point B is distance / velocity. If this is <= s, draw the edge (weight 1) to B, since
the gopher can make it there in time. Draw edges of weight 1 from each ending hole to t.

Solving:
Perform a max cardinality bipartite matching, and subtract the result from the number of
gophers to get the number of vulnerable gophers
*/

int n, m;

// maximum bipartite matching code:
// https://www.geeksforgeeks.org/maximum-bipartite-matching/

// A DFS based recursive function that returns true if a matching for vertex u is possible
bool bpm(bool** bpGraph, int u,
         bool seen[], int matchR[])
{
    // Try every end hole one by one
    for (int v = 0; v < m; v++)
    {
        // If gopher can make it, and its not occupied
        if (bpGraph[u][v] && !seen[v])
        {
            // Mark v as visited
            seen[v] = true; 
  
            // If gopher 'v' is not assigned to a hole OR previously assigned 
            // gopher for hole v (which is matchR[v]) has an alternate hole available. 
            // Since v is marked as visited in the above line, matchR[v] in the following 
            // recursive call will not get gopher 'v' again
            if (matchR[v] < 0 || bpm(bpGraph, matchR[v],
                                     seen, matchR))
            {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}
  
// Returns maximum cardinality matching for the gopher flow graph
int maxBPM(bool** bpGraph)
{
    // An array to keep track of the gophers assigned to holes. 
    // The value of matchR[i] is the gopher number assigned to hole i,
    // the value -1 indicates nobody is assigned.
    int matchR[m];
  
    // Initially all holes are available
    memset(matchR, -1, sizeof(matchR));
  
    // Number of holes assigned to gophers
    int result = 0; 
    for (int u = 0; u < n; u++)
    {
        // Mark all holes as not occupied 
        bool seen[m];
        memset(seen, 0, sizeof(seen));
  
        // Find if the gopher 'u' can get a hole
        if (bpm(bpGraph, u, seen, matchR))
            result++;
    }
    return result;
}

int main() {
    int s, v, i, j;
    while (cin >> n >> m >> s >> v) {
        float x, y;
        vector<pair<float,float> > start;
        vector<pair<float,float> > end;
        for (i=0;i<n;i++) {
            cin >> x >> y;
            start.push_back(make_pair(x, y));
        }
        for (i=0;i<m;i++) {
            cin >> x >> y;
            end.push_back(make_pair(x, y));
        }

        // Make an Edmonds matrix (i, j = 1 if gopher can go from i to j safely)
        bool** matrix = new bool*[n];
        for (i=0;i<n;i++) {
            matrix[i] = new bool[m];
            for (j=0;j<m;j++) {
                float dist = sqrt(pow(start[i].first-end[j].first, 2) + pow(start[i].second-end[j].second, 2));
                float time = dist / v;
                if (time <= s) {
                    matrix[i][j] = true;
                }
                else {
                    matrix[i][j] = false;
                }
                //cout << "DEBUG: assigned\n";
            }
        }

        cout << n - maxBPM(matrix) << endl;
    }
}