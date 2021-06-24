#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define loop(i, a, b) for(i = (a); i < (b); i++)

/*
This problem is a topological sort problem. Starting nodes are 
nodes that are on top of the bundle of sticks and have no
in-degree (the stick is never b in the pair a,b)

We can perform a DFS/BFS through the graph, 

Input is:
n, m = # of nodes (sticks), # of edges (a, b)
a_i, b_i, for all i <= m, where a is on top of b (a points to b in the directed graph)
*/

vector<vector<int> > adjList;
int i, j;
  
vector<int> topologicalSortBFS(int n) { 
    queue<int> q; 
    vector<int> indegree(n+1, 0);
    vector<int> solution;

    loop(i, 1, n+1) {
        loop(j, 0, adjList[i].size()) {
            indegree[adjList[i][j]]++;
        }
    }
    
    // enqueue nodes with indegree 0
    loop(i, 1, n+1) {
        if (indegree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();
        solution.push_back(currentNode);

        loop(j, 0, adjList[currentNode].size()) {

            // remove all edges
            int newNode = adjList[currentNode][j];
            indegree[newNode]--;

            // target node has now no more incoming edges -> wanna process it next
            if (indegree[newNode] == 0) { 
                q.push(newNode);
            }
        }
    }

    return solution;
}

int main() {
    int n, m, a, b;
    cin >> n >> m;

    adjList.resize(n+1);
    loop(i, 1, m+1) {
        cin >> a >> b;
        adjList[a].push_back(b);
    }

    vector<int> soln = topologicalSortBFS(n);

    // if the solution vector's size is less than , then there was some cycle, so output impossible
    if (soln.size() < n) cout << "IMPOSSIBLE";
    else {
        loop(i, 0, soln.size()) {
            cout << soln[i] << endl;
        }
    }
}