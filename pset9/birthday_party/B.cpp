#include <iostream>
#include <list>
using namespace std;

#define loop(i,a,b) for(i=(a);i<(b);i++)

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
    void bridge();    // prints all bridges
    bool bridgeExists;
};
  
Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
    bridgeExists = false;
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
  
            // If the lowest vertex reachable from subtree 
            // under v is  below u in DFS tree, then u-v 
            // is a bridge
            if (low[v] > disc[u]) {
                bridgeExists = true;
                return;
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

int main() {
    int p, c, a, b, i;
    cin >> p;
    while (p != 0) {
        cin >> c;

        Graph people(p);

        loop(i,0,c) {
            cin >> a >> b;
            people.addEdge(a, b);
            people.addEdge(b, a);
        }

        people.bridge();
        if (people.bridgeExists) cout << "Yes\n";
        else cout << "No\n";

        cin >> p;
    }
    cin >> c;
}