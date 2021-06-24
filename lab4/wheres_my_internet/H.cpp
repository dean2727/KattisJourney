#include <iostream>
#include <vector>
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

    // if theyre equal in height, then you want to merge to the one containing house 1 (if possible)
    if (mh[x] == mh[y]) {
      if (x == 1) {
        p[y] = x;
        mh[x]++;
      }
      else {
        p[x] = y;
        mh[y]++;
      }
    }

    // shorter points to longer, except if the shorter contains house 1
    else if (mh[x] < mh[y]) {
        if (x == 1) {
          p[y] = x;
        }
        else {
          p[x] = y;
        }
    }
    else {
        if (y == 1) {
          p[x] = y;
        }
        else {
          p[y] = x;
        }        
    }
}

int main() {
	int N, M;
	cin >> N >> M;

	vector<int> parent(N+1);
  vector<int> maxheight(N+1);

  for (int i=1;i<=N;i++) {
      parent.at(i) = i;
      maxheight.at(i) = 1;
  }

	int a, b;
	while (M--) {
		cin >> a >> b;
		merge(a, b, parent, maxheight);
	}

	// when outputting, increment house number (because 0-indexed vectors)
	bool oneDisconnected = false;
	for (int i=1;i<parent.size();i++) {
    int p = findset(i, parent);
		if (parent[p] != 1) {
			cout << i << "\n";
			oneDisconnected = true;
		}
	}

	if (!oneDisconnected) {
		cout << "Connected";
	}

	return 0;
}
