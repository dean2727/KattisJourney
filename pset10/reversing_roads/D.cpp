#include <iostream>
#include <vector>
#include <stack>
#include <list>
using namespace std;

#define loop(i,a,b) for(i=a;i<b;i++)
int i;

// C++ Implementation of Kosaraju's algorithm to print all SCCs
// https://www.geeksforgeeks.org/strongly-connected-components/
class Graph
{
    int V;    // No. of vertices
    int N;  // No. of edges
    list<int> *adj;    // An array of adjacency lists
  
    // Fills Stack with vertices (in increasing order of finishing
    // times). The top element of stack has the maximum finishing 
    // time
    void fillOrder(int v, bool visited[], stack<int> &Stack);
  
    // A recursive function to print DFS starting from v
    void DFSUtil(int v, bool visited[]);
public:
    Graph(int V, int N);
    void addEdge(int v, int w);
    pair<int,int> flipEdge(pair<int, int> newFlipEdge, bool firstFlip, pair<int, int> prevFlipEdge);
  
    // The main function that finds and prints strongly connected
    // components
    bool findSCCs();
  
    // Function that returns reverse (or transpose) of this graph
    Graph getTranspose();
};
  
Graph::Graph(int V, int N)
{
    this->V = V;
    this->N = N;
    adj = new list<int>[V];
}
  
// A recursive function to print DFS starting from v
void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    //cout << v << " ";  // if we want to print out the scc, uncomment
  
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}
  
Graph Graph::getTranspose()
{
    Graph g(V, N);
    for (int v = 0; v < V; v++)
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

pair<int,int> Graph::flipEdge(pair<int, int> newFlipEdge, bool firstFlip, pair<int, int> prevFlipEdge) {
    int j, u, v;
    if (!firstFlip) {
        // restore the previous flip (<v, u> becomes <u, v>, so remove u from adj of v and add v to adj of u)
        v = prevFlipEdge.first;
        u = prevFlipEdge.second;
        adj[v].remove(u);
        adj[u].push_back(v);
    }

    // do the new flip (<u, v> becomes <v, u>, so remove v from adj of u and add u to adj of v)
    u = newFlipEdge.first;
    v = newFlipEdge.second;
    adj[u].remove(v);
    adj[v].push_back(u);

    return make_pair(v, u);
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
  
// find the strongly connected components
bool Graph::findSCCs()
{
    stack<int> Stack;
    bool scc = false;
  
    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
  
    // Fill vertices in stack according to their finishing times
    for(int i = 0; i < V; i++)
        if(visited[i] == false)
            fillOrder(i, visited, Stack);
  
    // Create a reversed graph
    Graph gr = getTranspose();
  
    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < V; i++)
        visited[i] = false;
  
    // Now process all vertices in order defined by Stack
    while (Stack.empty() == false)
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();

        // strongly connected component of popped vertex
        if (visited[v] == false)
        {
            // if there is another strongly connected component, the roads are not strongly connected
            if (scc) {
                return false;
            }
            scc = true;

            gr.DFSUtil(v, visited);
            //cout << endl;
        }
    }

    // if we got here, then the entire graph is a connected component, which is what we want
    return true;
}

int main() {
    int m, n, caseNum = 1;

    while (cin >> m) {
        cin >> n;
 
        vector<pair<int,int> > inputRoads;
        Graph* roads = new Graph(m, n);

        int u, v;
        loop(i,0,n) {
            cin >> u >> v;
            roads->addEdge(u, v);
            inputRoads.push_back(make_pair(u, v));
        }

        cout << "Case " << caseNum << ": ";

        // initially run algorithm to see if roads are good as they were given
        if (roads->findSCCs()) {
            cout << "valid\n";
        }

        // else, continually flip the ith edge from input, and see if it works now
        else {            
            pair<int,int> flip = roads->flipEdge(inputRoads[0], true, make_pair(0,0));
            i = 1;
            bool found = roads->findSCCs();
            while (!found && i <= n-1) {
                flip = roads->flipEdge(inputRoads[i], false, flip);
                found = roads->findSCCs();
                i++;
            }
            
            if (found) {
                cout << flip.second << " " << flip.first << "\n";
            }
            else {
                cout << "invalid\n";
            }
        }

        caseNum++;
    }
}