#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
	vector<int> distances;
	int cx, cy, n;
	cin >> cx >> cy >> n;

	int x, y, r;
	int dist;
	while (n--) {
		cin >> x >> y >> r;
		dist = (int)sqrt(pow(cx - x, 2) + pow(cy - y, 2)) - r;
		//cout << dist << endl;
		distances.push_back((int)dist);
	}

	sort(distances.begin(), distances.end());

	if (distances[2] < 0) {
		cout << "0";
	}
	else {
		cout << distances[2];
	}
	return 0;
}
