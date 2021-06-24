#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	int h;
	vector<int> hs;
	while (n--) {
		cin >> h;
		hs.push_back(h);
	}
	sort(hs.begin(), hs.end());

	// make single pass through all buildings
	int sz = hs.size(), cost = 0, min = 1000000000, prev = -1;

	for (int i=0;i<sz;i++) {
		cost = hs[i];
		prev = hs[i];
		for (int j=i+1;j<sz;j++) {
			if (hs[j] != hs[i] && hs[j] != prev) {
				cost++;
				prev = hs[j];
			}
		}

		if (cost < min) {
			min = cost;
		}
	}

	cout << min;
	return 0;
}
