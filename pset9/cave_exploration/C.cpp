#include <iostream>
#include <list>
#include <set>
#include <queue>
using namespace std;

/*
In this problem, we are finding all the bridges sources out from junction 0 and
seeing what the size (# of nodes) is in our graph when we cut off all these bridges
*/

set<int> bridgeExits;

// graph code from:
// https://www.geeksforgeeks.org/bridge-in-a-graph/
class Graph {
    int V;    // No. of vertices
    list<int> *adj;    // A dynamic array of adjacency lists
    void bridgeUtil(int v, bool visited[], int disc[], int low[],
                    int parent[]);
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // to add an edge to graph
    void bridge();
    void BFS();
    int numSafeJunctions;
};
  
Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
    numSafeJunctions = 0;
}
  
void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}

void Graph::bridgeUtil(int u, bool visited[], int disc[], 
                                  int low[], int parent[])
{
    // A static variable is used for simplicity, we can 
    // avoid use of static variable by passing a pointer.
    static int time = 0;
  
    // Mark the current node as visited
    visited[u] = true;
  
    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;
  
    // Go through all vertices aadjacent to this
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;  // v is current adjacent of u
  
        // If v is not visited yet, then recur for it
        if (!visited[v])
        {
            parent[v] = u;
            bridgeUtil(v, visited, disc, low, parent);
  
            // Check if the subtree rooted with v has a 
            // connection to one of the ancestors of u
            low[u]  = min(low[u], low[v]);

            if (low[v] > disc[u]) {
                bridgeExits.insert(v);
            }
        }
  
        // Update low value of u for parent function calls.
        else if (v != parent[u])
            low[u]  = min(low[u], disc[v]);
    }
}

// DFS based function to find all bridges. It uses recursive 
// function bridgeUtil()
void Graph::bridge() {
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    int *disc = new int[V];
    int *low = new int[V];
    int *parent = new int[V];
  
    // Initialize parent and visited arrays
    for (int i = 0; i < V; i++)
    {
        parent[i] = -1;
        visited[i] = false;
    }
  
    // Call the recursive helper function to find Bridges
    // in DFS tree rooted with vertex 'i'
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            bridgeUtil(i, visited, disc, low, parent);
}

void Graph::BFS() {
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    }

    queue<int> q;
    visited[0] = true;
    q.push(0);
    numSafeJunctions++;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            // if leads to bridge, dont enqueue
            if (!bridgeExits.count(*i) && !visited[*i]) {
                visited[*i] = true;
                q.push(*i);
                numSafeJunctions++;
            }
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    Graph cave(N);

    int from, to;
    for (int i=0;i<M;i++) {
        cin >> from >> to;
        cave.addEdge(from, to);
    }

    // get the nodes in the graph that are entries to bridges
    cave.bridge();

    // run a BFS on the graph starting at 0 until no more nodes to explore
    cave.BFS();

    cout << cave.numSafeJunctions;
}