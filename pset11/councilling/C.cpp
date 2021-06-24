#include <vector>
#include <queue>
#include <iostream>
#include <map>
#include <set>
#include <list>
#include <climits>
using namespace std;

#define trav(a, x) for(auto& a : x)
typedef map<string, set<string> >::iterator mit;
typedef map<string, string>::iterator mit2;
typedef set<string>::iterator sit;

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
    vector<Edge> *adj;
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
    int sendFlow(int u, int flow, int t, int start[], vector<int>& trace)
    {
        //cout << "sending flow from " << u << " to " << t << endl;
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
    
                int temp_flow = sendFlow(e.v, curr_flow, t, start, trace);
    
                // flow is greater than zero
                if (temp_flow > 0)
                {
                    //cout << "added flow from " << u << " to " << e.v << endl;
                    trace.push_back(u);
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


    int DinicMaxflow(int s, int t, vector<vector<int> >& traces)
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
            vector<int> trace;
            while (int flow = sendFlow(s, INT_MAX, t, start, trace)) {
                //cout << "adding flow of " << " when total is " << total << endl;
                // Add path flow to overall flow
                total += flow;
                traces.push_back(trace);
                trace.clear();
            }
        }
    
        // return maximum flow
        return total;
    }
};

int main() {
    int T, n, numClubs, i;
    string resident, party, club;
    cin >> T;

    while (T--) {
        cin >> n;

        // there are # clubs + # people + # parties + 2 (for source and sink) nodes in the flow graph
        int numNodes = 2;
        map<string, set<string> > clubsToPeople;
        map<string, string> peopleToParties;
        // to find the number of nodes we need
        set<string> parties;
        set<string> clubs;

        for(i=0;i<n;i++) {
            cin >> resident >> party >> numClubs;

            numNodes += 1;  // 1 more resident -> 1 more node

            peopleToParties[resident] = party;
            parties.insert(party);

            int j;
            for (j=0;j<numClubs;j++) {
                cin >> club;
                clubsToPeople[club].insert(resident);
                clubs.insert(club);
            }
        }

        // Build a graph with 3 partitions: clubs, residents and parties
        numNodes += parties.size() + clubs.size();
        Graph dalg(numNodes);

        // Need to have a way of numbering the nodes, so map clubs, residents, and parties to node numbers
        map<string, int> c2n;
        map<string, int> r2n;
        map<string, int> p2n;
        // and vice versa
        map<int, string> n2c;
        map<int, string> n2r;
        map<int, string> n2p;
        int nodeNum = 1;
        sit it1;
        trav(it1, clubs) {
            //cout << it1 << " -> " << nodeNum << endl;
            c2n[it1] = nodeNum;
            n2c[nodeNum] = it1;
            nodeNum++;
        }
        mit2 it2;
        trav(it2, peopleToParties) {
            //cout << it2.first << " -> " << nodeNum << endl;
            r2n[it2.first] = nodeNum;
            n2r[nodeNum] = it2.first;
            nodeNum++;
        }
        trav(it1, parties) {
            //cout << it1 << " -> " << nodeNum << endl;
            p2n[it1] = nodeNum;
            n2p[nodeNum] = it1;
            nodeNum++;
        }
        
        // Connect a club c and a resident r if r can represent c, the capacity of the edge is 1
        mit it3;
        trav(it3, clubsToPeople) {
            trav(it1, it3.second) {
                //cout << it3.first << " can represent " << it1 << endl;
                dalg.addEdge(c2n[it3.first], r2n[it1], 1);
            }
            // Connect the source to the club with capacity 1
            dalg.addEdge(0, c2n[it3.first], 1);
        }

        // Connect each resident to the party that resident belongs to. Capacity 1, since there is only 1 person
        trav(it2, peopleToParties) {
            //cout << it2.first << " belongs to party " << it2.second << endl;
            dalg.addEdge(r2n[it2.first], p2n[it2.second], 1);
        }

        // Connect the parties with the sink
        trav(it1, parties) {
            // capacity = (total number of clubs) / 2 - 1 if #clubs is even
            if (clubs.size() % 2 == 0) {
                dalg.addEdge(p2n[it1], numNodes-1, clubs.size()/2-1);
            }
            // capacity = (total number of clubs) / 2 if #clubs is odd
            else {
                dalg.addEdge(p2n[it1], numNodes-1, clubs.size()/2);
            }
        }

        // Run max-flow and use the flow in each edge to reconstruct the answer
        // Those with 0 remaining flow at end were the ones used
        vector<vector<int> > traces;  // this will hold the paths of node #s as we add flow
        int maxFlow = dalg.DinicMaxflow(0, numNodes-1, traces);
        // edge case: 1 person, 1 club -> just print out the person then the club
        if (clubs.size() == 1 && peopleToParties.size() == 1) {
            it1 = clubs.begin();
            it2 = peopleToParties.begin();
            cout << it2->first << " " << *it1 << "\n";
        }
        // if not all clubs were used, or if there just werent any clubs in the first place, impossible
        else if (traces.size() < clubs.size() || clubs.empty()) cout << "Impossible.\n";
        else {
            // check if the 1-to-1 ratio is correct
            set<int> traceRes;
            set<int> traceClub;
            for (i=0;i<traces.size();i++) {
                // the 2nd thing we push = our resident. 3rd thing = our club
                traceRes.insert(traces[i][1]);
                traceClub.insert(traces[i][2]);
            }
            if (traceRes.size() != traceClub.size()) {
                cout << "Impossible.\n";
            }
            else {
                for (i=0;i<traces.size();i++) {                    
                    cout << n2r[traces[i][1]] << " " << n2c[traces[i][2]] << "\n";
                }
            }
        }

        if (T != 0) cout << "\n";
    }
}