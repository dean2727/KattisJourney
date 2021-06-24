#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge {
    int from;
    int to;
    int weight;
};

struct UF {
    // if negative, it represents size (e.g. -5 has size 5, -1 = single element set)
    // if its positive, it represents the parent
	vector<int> e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

bool cmp(const edge& x, const edge& y) {
    // if tie in weight, take edge with lowest from node value
    if (x.weight == y.weight) return x.from < y.from;
    // take lowest weight
    else return x.weight < y.weight;
}

/*
Kruskals algorithm for minimum spanning tree:
1. Sort edges from lowest weight to highest
2. Add edges by doing a union-find set combination on the two vertices, if they are not already in the same set
3. If they are in the same set, ignore this edge
Done when you have just one set (i.e. have added n-1 edges, thus joining all n vertices)
*/
int main() {
    int numNodes, numEdges;
    cout << "Input number of nodes and edges (space separated):\n";
    cin >> numNodes >> numEdges;
    UF parent(numNodes);

    int from, to, weight;
    vector<edge> edges;
    cout << "Enter edges (from, to, weight_\n";
    for (int i=0;i<numEdges;i++) {
        edge e;
        cin >> from >> to >> weight;
        e.from = from;
        e.to = to;
        e.weight = weight;
        edges.push_back(e);
    }
    sort(edges.begin(), edges.end(), cmp);

    // kruskals: done when all of the stations are in the same set
    int i = 0;
    while (parent.size(1) != numNodes) {
        edge e = edges[i];
        if (!parent.sameSet(e.from, e.to)) {
            parent.join(e.from, e.to);
            // *handle the edge weight here*
        }
        i++;
    }
}



