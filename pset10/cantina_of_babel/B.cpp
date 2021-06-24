#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <stack>
#include <list>
#include <string>
using namespace std;

#define loop(i,a,b) for(i=a;i<b;i++)
#define trav(a, x) for(auto& a : x)

// C++ Implementation of Kosaraju's algorithm to print all SCCs
// https://www.geeksforgeeks.org/strongly-connected-components/
class Graph
{
	int V; // No. of vertices
	list<int> *adj; // An array of adjacency lists

	// Fills Stack with vertices (in increasing order of finishing
	// times). The top element of stack has the maximum finishing
	// time
	void fillOrder(int v, bool visited[], stack<int> &Stack);

	// A recursive function to print DFS starting from v
	void DFSUtil(int v, bool visited[], int& componentNodes);
public:
	Graph(int V);
	void addEdge(int v, int w);

	// The main function that finds and prints strongly connected
	// components
	int largestSCC();

	// Function that returns reverse (or transpose) of this graph
	Graph getTranspose();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

// A recursive function to print DFS starting from v
void Graph::DFSUtil(int v, bool visited[], int& componentNodes)
{
	// Mark the current node as visited and print it
	visited[v] = true;
	componentNodes++;

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFSUtil(*i, visited, componentNodes);
}

Graph Graph::getTranspose()
{
	Graph g(V);
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
int Graph::largestSCC()
{
	stack<int> Stack;
    int maxSCC = 0;

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

		// how many nodes in this SCC?
        int componentNodes = 0;
		if (visited[v] == false)
		{
			gr.DFSUtil(v, visited, componentNodes);
			if (componentNodes > maxSCC) {
                maxSCC = componentNodes;
            }
		}
	}

    return maxSCC;
}


void tokenize(string const &str, const char delim, vector<string> &out) {
	size_t start;
	size_t end = 0;
	while ((start = str.find_first_not_of(delim, end)) != string::npos) {
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}


int main() {
    int N, i;
    cin >> N;

    string line;
	getline(cin, line);
    map<int, set<string> > langs;
    vector<string> speaks;
    loop(i,0,N) {
        getline(cin, line);
        vector<string> toks;
        tokenize(line, ' ', toks);

        set<string> charLangs;
        for (int j=1;j<toks.size();j++) {
            charLangs.insert(toks[j]);
        }

        langs[i] = charLangs;
        speaks.push_back(toks[1]);
    }

    Graph communicate(N);

    // nodes in the graph are characters, edge exists between u and v if v understands what u speaks
    map<int, set<string> >::iterator it;
    loop(i,0,N) {
        string charSpeaks = speaks[i];
        trav(it, langs) {
            if (it.first == i) continue;
            if (it.second.count(charSpeaks)) {
                communicate.addEdge(i, it.first);
            }
        }
    }

    // find the size of the smallest set of characters that should leave so everyone else can communicate
    // in other words, subtract the size of the largest strongly connected component from the # of characters
    cout << N - communicate.largestSCC();
}