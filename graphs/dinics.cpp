#include <vector>
#include <queue>
using namespace std;

// max flow code from: https://www.geeksforgeeks.org/dinics-algorithm-maximum-flow/
// A structure to represent a edge between
// two vertex
struct Edge
{
    int v ;  // Vertex v (or "to" vertex)
             // of a directed edge u-v. "From"
             // vertex u can be obtained using
             // index in adjacent array.
 
    int flow ; // flow of data in edge
 
    int C;    // capacity
 
    int rev ; // To store index of reverse
              // edge in adjacency list so that
              // we can quickly find it.
};
 
// Residual Graph
class Graph
{
public :
    int V; // number of vertex
    int *level ; // stores level of a node
    vector< Edge > *adj;
    Graph(int V)
    {
        adj = new vector<Edge>[V];
        this->V = V;
        level = new int[V];
    }
 
    // add edge to the graph
    void addEdge(int u, int v, int C)
    {
        // Forward edge : 0 flow and C capacity
        Edge a = {v, 0, C, (int)adj[v].size()};

 
        // Back edge : 0 flow and 0 capacity
        Edge b = {u, 0, 0, (int)adj[u].size()};
 
        adj[u].push_back(a);
        adj[v].push_back(b); // reverse edge
    }
 
    // Finds if more flow can be sent from s to t.
    // Also assigns levels to nodes.
    bool BFS(int s, int t)
    {
        for (int i = 0 ; i < V ; i++)
        level[i] = -1;
 
        level[s] = 0;  // Level of source vertex
    
        // Create a queue, enqueue source vertex
        // and mark source vertex as visited here
        // level[] array works as visited array also.
        list<int> q;
        q.push_back(s);
    
        vector<Edge>::iterator i ;
        while (!q.empty())
        {
            int u = q.front();
            q.pop_front();
            for (i = adj[u].begin(); i != adj[u].end(); i++)
            {
                Edge &e = *i;
                if (level[e.v] < 0  && e.flow < e.C)
                {
                    // Level of current vertex is,
                    // level of parent + 1
                    level[e.v] = level[u] + 1;
    
                    q.push_back(e.v);
                }
            }
        }
    
        // IF we can not reach to the sink we
        // return false else true
        return level[t] < 0 ? false : true ;
    }

    // A DFS based function to send flow after BFS has
    // figured out that there is a possible flow and
    // constructed levels. This function called multiple
    // times for a single call of BFS.
    // flow : Current flow send by parent function call
    // start[] : To keep track of next edge to be explored.
    //           start[i] stores  count of edges explored
    //           from i.
    //  u : Current vertex
    //  t : Sink
    int sendFlow(int u, int flow, int t, int start[])
    {
        cout << "sending flow from " << u << " to " << t << endl;
        // Sink reached
        if (u == t)
            return flow;
    
        // Traverse all adjacent edges one -by - one.
        for (  ; start[u] < adj[u].size(); start[u]++)
        {
            // Pick next edge from adjacency list of u
            Edge &e = adj[u][start[u]];
                                        
            if (level[e.v] == level[u]+1 && e.flow < e.C)
            {
                // find minimum flow from u to t
                int curr_flow = min(flow, e.C - e.flow);
    
                int temp_flow = sendFlow(e.v, curr_flow, t, start);
    
                // flow is greater than zero
                if (temp_flow > 0)
                {
                    // add flow  to current edge
                    e.flow += temp_flow;
    
                    // subtract flow from reverse edge
                    // of current edge
                    adj[e.v][e.rev].flow -= temp_flow;
                    return temp_flow;
                }
            }
        }
    
        return 0;
    }


    int DinicMaxflow(int s, int t)
    {
        // Corner case
        if (s == t)
            return -1;
    
        int total = 0;  // Initialize result
    
        // Augment the flow while there is path
        // from source to sink
        while (BFS(s, t) == true)
        {
            // store how many edges are visited
            // from V { 0 to V }
            int *start = new int[V+1] {0};
    
            // while flow is not zero in graph from S to D
            while (int flow = sendFlow(s, INT_MAX, t, start))
    
                // Add path flow to overall flow
                total += flow;
        }
    
        // return maximum flow
        return total;
    }
};


// Dinics algorithm for max flow
// https://cp-algorithms.com/graph/dinic.html
struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};