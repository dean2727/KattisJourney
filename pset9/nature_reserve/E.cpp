#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

#define loop(i, a, b) for (i = (a); i < (b); i++)
#define trav(a, x) for (auto &a : x)

struct node {
    int val;
    bool activated;
};

struct edge {
    node from;
    node to;
    long long energy;
};

vector<node> vert;
vector<edge> channels;
int numActivated;
long long minEnergy, L;

bool cmp(const edge& x, const edge& y) {
    if (x.energy == y.energy) return x.from.val < y.from.val;
    else return x.energy < y.energy;
}

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

int main() {
    int T, M, N, S, i1, i2, i, j;
    long long E;
    cin >> T;
    loop(i1,0,T) {
        cin >> N >> M >> L >> S;

        channels.resize(M);
        vert.resize(N+1);
        UF parent(N+1);

        minEnergy = 0;

        loop(i2,1,N+1) {
            node n;
            n.val = i2;
            n.activated = false;
            vert[i2] = n;
        }

        int mergeWith, s;
        cin >> mergeWith;
        loop(i2,1,S) {
            cin >> s;
            parent.join(mergeWith, s);
        }

        loop(i2,0,M) {
            cin >> i >> j >> E;
            //cout << i << " " << j << " " << E << endl;
            edge e;
            e.energy = E;
            e.from = vert[i];
            e.to = vert[j];
            channels[i2] = e;
        }

        sort(channels.begin(), channels.end(), cmp);

        // kruskals: done when all of the stations are in the same set
        int i2 = 0;
        while (parent.size(1) != N) {
            //cout << i2 << endl;
            edge e = channels[i2];
            //cout << "edge from " << e.from.val << " to " << e.to.val << endl;
            if (!parent.sameSet(e.from.val, e.to.val)) {
                parent.join(e.from.val, e.to.val);
                minEnergy += e.energy + L;
            }
            i2++;
        }

        cout << minEnergy << "\n";
        vert.clear();
        channels.clear();
    }
}