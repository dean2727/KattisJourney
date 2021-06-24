#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;

#define loop(i,a,b) for(i=(a);i<(b);i++)
int i, j;
int W, H;

// Bellman Ford code
// https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
// a structure to represent a weighted edge in graph
struct Edge {
	int src, dest, weight;
};

// a structure to represent a connected, directed and
// weighted graph
struct Graph {
	// V-> Number of vertices, E-> Number of edges
	int V, E;

	// graph is represented as an array of edges.
    vector<Edge> edge;
};

// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V)
{
	struct Graph* graph = new Graph;
	graph->V = V;
	return graph;
}

void addEdge(Graph* g, int src, int dest, int weight) {
    Edge e;
    e.src = src;
    e.dest = dest;
    e.weight = weight;
    g->edge.push_back(e);
}

void printArr(int dist[], int n)
{
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < n; ++i)
		printf("%d %d \t\t %d\n", i/W, i%W, dist[i]);
}

// print the distance to the upper left corner (index (W-1)*H+(H-1))
void toUpperRight(int dist[], int n) {
    if (dist[n-1] == INT_MAX) printf("Impossible\n");
    else printf("%d\n", dist[n-1]);
}

// The main function that finds shortest distances from src to
// all other vertices using Bellman-Ford algorithm. The function
// also detects negative weight cycle
void BellmanFord(struct Graph* graph, int src)
{
	int V = graph->V;
	int E = graph->E;
	int dist[V];

	// Step 1: Initialize distances from src to all other vertices as INFINITE
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX;
	dist[src] = 0;

	// Step 2: Relax all edges |V| - 1 times. A simple shortest
	// path from src to any other vertex can have at-most |V| - 1 edges
	for (int i = 1; i <= V - 1; i++) {
		for (int j = 0; j < E; j++) {
			int u = graph->edge[j].src;
			int v = graph->edge[j].dest;
			int weight = graph->edge[j].weight;
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
				dist[v] = dist[u] + weight;
		}
	}

	// Step 3: check for negative-weight cycles. The above step
	// guarantees shortest distances if graph doesn't contain
	// negative weight cycle. If we get a shorter path, then there
	// is a cycle.
	for (int i = 0; i < E; i++) {
		int u = graph->edge[i].src;
		int v = graph->edge[i].dest;
		int weight = graph->edge[i].weight;
		if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
			printf("Never\n");
			return; // If negative cycle is detected, simply return
		}
	}

    // Uncomment to see distances to each node from source 0,0
	//printArr(dist, V);

    toUpperRight(dist, V);

	return;
}

int main() {
    int X,Y,X1,Y1,X2,Y2,T,G,E;
    cin >> W;
    // W = number of rows. H = number of columns (rotate the graph 90 degrees clockwise)
    while (W) {
        cin >> H;
        vector<int> graveyard(W*H, 1); // 1 = grass, all are grass initially
        int numNodes = W * H;

        cin >> G;
        loop(i,0,G) {
            cin >> X >> Y;
            graveyard[X * H + Y] = -1;  // -1 = graveyard
        }

        cin >> E;
        map<int,int> gyTime;
        map<int,int> gyDest;
        loop(i,0,E) {
            cin >> X1 >> Y1 >> X2 >> Y2 >> T;
            graveyard[X1 * H + Y1] = -2;  // -2 = hole
            gyTime[X1 * H + Y1] = T;
            gyDest[X1 * H + Y1] = X2 * H + Y2;
        }

        // create the directed graph from the graveyard, where nodes are tiles and edges are of weight 1
        // unless its an edge from a hole. when we see a hole, it is a directed edge of weight t from its source
        // to its destination
        Graph* gyGraph = createGraph(W*H);
        int numEdges = 0, thisSpot;
        loop(i,0,W) {
            loop(j,0,H) {
                thisSpot = graveyard[i * H + j];

                // if graveyard or ending reached, continue, dont add edges
                if ((i == W-1 && j == H-1) || thisSpot == -1) {
                    continue;
                }

                // if a hole, create the edge from source to dest and use t as weight
                if (thisSpot == -2) {
                    addEdge(gyGraph, i * H + j, gyDest[i * H + j], gyTime[i * H + j]);
                    numEdges++;
                    continue;
                }

                // can get left/right/up/down if not passed the border and not a graveyard
                // left
                if (i-1 >= 0 && graveyard[(i-1) * H + j] != -1) {
                    addEdge(gyGraph, i * H + j, (i-1) * H + j, 1);
                    numEdges++;
                }
                // right
                if (i+1 <= W-1 && graveyard[(i+1) * H + j] != -1) {
                    addEdge(gyGraph, i * H + j, (i+1) * H + j, 1);
                    numEdges++;
                }
                // up
                if (j+1 <= H-1 && graveyard[i * H + j+1] != -1) {
                    addEdge(gyGraph, i * H + j, i * H + j+1, 1);
                    numEdges++;
                }
                // down
                if (j-1 >= 0 && graveyard[i * H + j-1] != -1) {
                    addEdge(gyGraph, i * H + j, i * H + j-1, 1);
                    numEdges++;
                }
            }
        }

        gyGraph->E = numEdges;

        BellmanFord(gyGraph, 0);
        
        cin >> W;
    }
    cin >> H;
}