#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
	int N, K, h;
	long long walks = 0;
	vector<int> green;
	cin >> N >> K;

	// there could be no watch houses, thus no safe walks
	if (K == 0) {
		cout << "0";
		return 0;
	}

	while (K--) {
		cin >> h;
		green.push_back(h);
	}

	// Loop through all houses (could be “start” or “end” house). Say it is “start” house. Call this house A.
	// Find next safe house in list that is equal or larger than current house. Call that house B.
	int i = 0;
	int B = green[i]-1;
	for (int A=0;A<N;A++) {
		if (A > B) {
			i++;
			if (i == green.size()) break;
			B = green[i]-1;
		}
		walks += N-B;
	}

	cout << walks;
	
	return 0;
}
