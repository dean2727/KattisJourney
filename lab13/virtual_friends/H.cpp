#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

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
    int t, F, i;
    cin >> t;
    while (t--) {
        cin >> F;
        string f1, f2;
        set<string> seenNames;
        map<string, int> nameToNode;
        vector<pair<string, string> > connects;
        int node = 0;
        for (i=0;i<F;i++) {
            cin >> f1 >> f2;
            if (!seenNames.count(f1)) {
                seenNames.insert(f1);
                nameToNode[f1] = node;
                node++;
            }
            if (!seenNames.count(f2)) {
                seenNames.insert(f2);
                nameToNode[f2] = node;
                node++;
            }
            connects.push_back(make_pair(f1, f2));
        }

        UF network(seenNames.size());
        // network.join(0, 1);
        // cout << network.size(0) << ", " << network.size(2);
        for (i=0;i<F;i++) {
            int n1 = nameToNode[connects[i].first];
            int n2 = nameToNode[connects[i].second];

            // get size of network for the 2 people
            // are they in the same network? then just get the size from 1 of them
            if (network.find(n1) == network.find(n2)) {
                cout << network.size(n1) << "\n";
            }
            // otherwise, add sizes together
            else {
                cout << network.size(n1) + network.size(n2) << "\n";
                // join them
                network.join(n1, n2);
            }            
        }
    }
}