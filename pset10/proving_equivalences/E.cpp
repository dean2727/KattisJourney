#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <stack>
using namespace std;

#define loop(i,a,b) for(i=a;i<b;i++)
int i;
map<int, int> nodeToSCC;

class Graph
{
    int V; // No. of vertices
    list<int> *adj; // An array of adjacency lists

    // Fills Stack with vertices (in increasing order of finishing
    // times). The top element of stack has the maximum finishing
    // timeq
    void fillOrder(int v, bool visited[], stack<int> &Stack);

    // A recursive function to print DFS starting from v
    void DFSUtil(int v, bool visited[], int base);
public:
    Graph(int V);
    void addEdge(int v, int w);

    // The main function that assigns nodes to the SCC they are apart of
    int fillSCCmap();

    // Function that returns reverse (or transpose) of this graph
    Graph getTranspose();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V+1];
}

// A recursive function to print DFS starting from v
void Graph::DFSUtil(int v, bool visited[], int base)
{
    // Mark the current node as visited and print it
    visited[v] = true;
    nodeToSCC[v] = base;
    //cout << v << " ";

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited, base);
}

Graph Graph::getTranspose()
{
    Graph g(V+1);
    for (int v = 1; v <= V; v++)
    {
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            fillOrder(*i, visited, Stack);

    // All vertices reachable from v are processed by now, push v
    Stack.push(v);
}

// The main function that finds and prints all strongly connected
// components
int Graph::fillSCCmap()
{
    stack<int> Stack;
    int SCCnum = 0;

    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[V+1];
    for(int i = 1; i <= V; i++)
        visited[i] = false;

    // Fill vertices in stack according to their finishing times
    for(int i = 1; i <= V; i++)
        if(visited[i] == false)
            fillOrder(i, visited, Stack);

    // Create a reversed graph
    Graph gr = getTranspose();

    // Mark all the vertices as not visited (For second DFS)
    for(int i = 1; i <= V; i++)
        visited[i] = false;

    // Now process all vertices in order defined by Stack
    while (Stack.empty() == false)
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();

        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
            SCCnum++;
            //cout << "SCC num " << v << endl;
            gr.DFSUtil(v, visited, SCCnum);
            //cout << endl;
        }
    }

    return SCCnum;
}


// dfs() and findMinimumEdges() from:
// https://www.geeksforgeeks.org/minimum-edges-required-to-make-a-directed-graph-strongly-connected/

// Perform DFS to count the in-degree and out-degree of the graph
void dfs(int u, const vector<vector<int>>& adj, int* vis, int* inDeg,
         int* outDeg) {
    // Mark the source as visited
    vis[u] = 1;
 
    // Traversing adjacent nodes
    //cout << "there are " << adj[u].size() << " adj nodes to " << u << endl;
    loop(i, 0, adj[u].size()) {
        int v = adj[u][i];

        // Mark out-degree as 1
        outDeg[u] = 1;
        // Mark in-degree as 1
        inDeg[v] = 1;
 
        // If not visited
        if (vis[v] == 0) {
            // DFS Traversal on adjacent vertex
            dfs(v, adj, vis, inDeg, outDeg);
        }
    }
}

// Function to return minimum number of edges required to make the graph strongly connected
int findMinimumEdges(int source[], int N, int M, int dest[]) {
    // For Adjacency List
    vector<vector<int>> adj(N + 1);
 
    // Create the Adjacency List
    int i;
    loop(i, 0, M) {
        adj[source[i]].push_back(dest[i]);
    }
 
    // in-degree array
    int inDeg[N + 1];
    // out-degree array
    int outDeg[N + 1];
    // visited array
    int vis[N + 1];
    loop(i, 0, N+1) {
        inDeg[i] = 0;
        outDeg[i] = 0;
        vis[i] = 0;
    }
 
    // Perform DFS to count in-degrees and out-degrees
    loop(i, 0, M) {
        if (!vis[source[i]]) {
            dfs(source[i], adj, vis, inDeg, outDeg);
        }
    }
  
    // The roots and leaves are the only ones that need to “connect” – there has to be a
    // way to get from any leaf to any root. Thus, need at least min(# leaves, # roots) new edges,
    // which is max(# in degree = 0, # out degree = 0)
    int in0 = 0;
    int out0 = 0;
    loop(i, 1, N+1) {
        //cout << "node " << i << endl;
        if (inDeg[i] == 0) {
            in0++;
            //cout << "no in\n";
        }
        if (outDeg[i] == 0) {
            out0++;
            //cout << "no out\n";
        }
    }
    //minEdges = max(N - totalIndegree, N - totalOutdegree);
    //cout << in0 << ", " << out0 << endl;
    int minEdges = max(in0, out0);
 
    // Return the minimum edges
    return minEdges;
}

int main() {
    int t, n, m, s1, s2;
    cin >> t;
    while(t--) {
        cin >> n >> m;
        Graph equalities(n);
        vector<pair<int,int>> edges;

        for (i=0;i<m;i++) {
            cin >> s1 >> s2;
            equalities.addEdge(s1, s2);
            edges.push_back(make_pair(s1, s2));
        }

        // reduce the strongly connected components to be vertices, then we have a DAG
        int numSCC = equalities.fillSCCmap();

        if (numSCC == 1) {
			cout << "0\n";
			nodeToSCC.clear();
			continue;
		}

        set<pair<int, int>> DAGedges;

        // loop through the edges from input. if the SCC of node u is different from SCC of node v,
        // add edge to this new graph
        loop(i,0,m) {
            int u = edges[i].first, v = edges[i].second;
            int uSCC = nodeToSCC[u], vSCC = nodeToSCC[v];
            //cout << uSCC << ", " << vSCC << endl;
            if (uSCC != vSCC && !DAGedges.count(make_pair(uSCC, vSCC))) {
                DAGedges.insert(make_pair(uSCC, vSCC));
            }
        }
        
        // run findMinimumEdges to see how many edges will be needed to make the graph strongly connected
        n = numSCC;
        //cout << "n = " << n << endl;
        m = DAGedges.size();
        //cout << "m = " << m << endl;
        int source[m];
        int dest[m];

        i = 0;
        for (set<pair<int,int>>::iterator it=DAGedges.begin();it!=DAGedges.end();it++) {
            //cout << it->first << " --> " << it->second << endl;
            source[i] = it->first;
            dest[i] = it->second;
            i++;
        }

        cout << findMinimumEdges(source, n, m, dest) << "\n";
        nodeToSCC.clear();
    }
}