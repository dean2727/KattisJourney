#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

int main() {
	int m, sum, maxCount;
	cin >> m;

	// store the count of how often a sum is encountered
	int counts[m+1];
	for (int i=1;i<=m;i++) {
		counts[i] = 0;
	}

	for (int i=1;i<=cbrt(m);i++) {
		for (int j=1;j<=cbrt(m);j++) {
			sum = i*i*i + j*j*j;
			if (sum > m) break;
			counts[sum]++;
		}
	}

	for (int i=m;i>=1;i--) {
		if (counts[i] > 2) {
			cout << i;
			return 0;
		}
	}

	cout << "none";

	return 0;
}