#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>
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
    int N, X, Y, R, i, j;
    cin >> N;
    UF parent(N);

    // tuple of X, Y, and radius
    vector<tuple<int,int,int> > satellites;
    for (i=0;i<N;i++) {
        cin >> X >> Y >> R;
        satellites.push_back(make_tuple(X,Y,R));
    }

    // form edge between each pair of satellites (which wont overlap, but may touch)
    vector<edge> edges;
    for (i=0;i<N;i++) {
        for(j=i+1;j<N;j++) {
            tuple<int,int,int> s1 = satellites[i];
            tuple<int,int,int> s2 = satellites[j];
            // length of strut = distance from centers - radius 1 - radius 2
            double centersDist = sqrt(pow(get<0>(s1)-get<0>(s2), 2) + pow(get<1>(s1)-get<1>(s2), 2));
            //cout << centersDist << endl;
            edge e;
            e.from = i;
            e.to = j;
            e.weight = centersDist - (double)get<2>(s1) - (double)get<2>(s2);
            //cout << e.weight << endl;
            edges.push_back(e);
        }
    }
    sort(edges.begin(), edges.end(), cmp);

    // run the kruskals
    i = 0;
    double minBeamSum = 0.0;
    while (parent.size(1) != N) {
        edge e = edges[i];
        if (!parent.sameSet(e.from, e.to)) {
            parent.join(e.from, e.to);
            minBeamSum += e.weight;
        }
        i++;
    }

    // print with  the absolute or relative error is less than 10e-6
    cout << fixed << setprecision(8) << minBeamSum;
}