#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iomanip>
using namespace std;

struct edge {
    int from;
    int to;
    double weight;
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
    int n, m, i, j;
    float x, y;
    cin >> n;

    while(n--) {
        cin >> m;
        UF parent(m*m);
        int from, to;
        double weight;
        vector<edge> edges;
        vector<pair<float,float> > coords;
        for (i=0;i<m;i++) {
            cin >> x >> y;
            coords.push_back(make_pair(x, y));
        }

        pair<float, float> fromc;
        pair<float, float> toc;
        for (i=0;i<m;i++) {
            fromc = coords[i];
            for (j=i+1;j<m;j++) {
                toc = coords[j];
                weight = sqrt(pow(fromc.first-toc.first,2) + pow(fromc.second-toc.second,2));
                edge e;
                e.from = i;
                e.to = j;
                e.weight = weight;
                edges.push_back(e);
            }
        }

        // kruskals: done when all of the stations are in the same set
        sort(edges.begin(), edges.end(), cmp);
        int i = 0;
        double res = 0.0;
        while (parent.size(1) != m) {
            edge e = edges[i];
            if (!parent.sameSet(e.from, e.to)) {
                parent.join(e.from, e.to);
                res += e.weight;
            }
            i++;
        }

        cout << fixed << setprecision(9) << res << "\n";
    }
}