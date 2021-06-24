#include <iostream>
#include <vector>
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

int main() {
    int n, m;

    // minimum spanning tree is maximized

    
    UF parent(n);
}