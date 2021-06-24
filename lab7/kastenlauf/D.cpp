#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <stack>
using namespace std;

int findset(int i, vector<int> &p) {
    stack<int> s;
    
    // navigate down to the root parent, pushing to the stack
    while (i != p[i]) {
        s.push(i);
        i = p[i];
    }

    // set parent for all visited nodes to the root parent, and return this parent
    while (!s.empty()) {
        p[s.top()] = i;
        s.pop();
    }
    return i;
}

void merge(int x, int y, vector<int> &p, vector<int> &mh) {
    // first, find the set that each element is in (find the parent)
    x = findset(x, p);
    y = findset(y, p);

    // case 2
    if (mh[x] == mh[y]) {
        p[y] = x;
        mh[x]++;  // common height + 1 because we point to the base
    }

    // case 1 (shorter points to longer)
    else if (mh[x] < mh[y]) {
        p[x] = y;  // parent of shorter is the longer
    }
    else {
        p[y] = x;
    }
}


int main() {
	int t, n, x, y;
	int maxRun = 1000;
	cin >> t;

	while (t--){
		cin >> n;

		vector<int> locations;
		vector<int> starts;
		vector<int> ends;
		vector<int> parents;
		vector<int> mh;
		mh.resize(n + 2, 1);

		cin >> x >> y;
		int loc = 0;

		locations.push_back(loc);
		parents.push_back(loc);
		loc++;
		starts.push_back(x);
		ends.push_back(y);

		for (int i=0;i<n;i++){
			cin >> x >> y;
			locations.push_back(loc);
			parents.push_back(loc);
			loc++;
			starts.push_back(x);
			ends.push_back(y);
		}

		cin >> x >> y;
		locations.push_back(loc);
		parents.push_back(loc);
		starts.push_back(x);
		ends.push_back(y);

		// check every pair of locations, if abs(deltax) + abs(deltay) <= 1000, merge the locations
		int dist;
		for (int i = 0; i < n + 2 - 1; i++) {
			for (int j = i + 1; j < n + 2; j++) {
				dist = abs(starts[i] - starts[j]) + abs(ends[i] - ends[j]);
				if (dist <= 1000) {
					merge(i, j, parents, mh);
				}
			}
		}

		// if start and end in the same set, they are reachable from each other
		if (findset(0, parents) == findset(loc, parents)) {
			cout << "happy\n";
		}
		else {
			cout << "sad\n";
		}
	}
	return 0;
}