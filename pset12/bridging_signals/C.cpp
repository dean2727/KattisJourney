#include <iostream>
#include <vector>
using namespace std;

/* this problem is a longest increasing subsequence problem, but because of input
size, runtime can be too slow, so need to use the O(nlgn) version, which
involved binary search */

// https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
// Binary search (note boundaries in the caller)
int CeilIndex(vector<int>& v, int l, int r, int key) {
	while (r - l > 1) {
		int m = l + (r - l) / 2;
		if (v[m] >= key)
			r = m;
		else
			l = m;
	}

	return r;
}

int LongestIncreasingSubsequenceLength(vector<int>& v) {
	if (v.size() == 0)
		return 0;

	vector<int> tail(v.size(), 0);
	int length = 1;

	tail[0] = v[0];
	for (size_t i = 1; i < v.size(); i++) {

		if (v[i] < tail[0])
			tail[0] = v[i];

		else if (v[i] > tail[length - 1])
			tail[length++] = v[i];

		else
			tail[CeilIndex(tail, -1, length - 1, v[i])] = v[i];
	}

	return length;
}

int main() {
    int p, portNum;
    cin >> p;
    vector<int> a1(p+1);
    for (int i=1;i<=p;i++) {
        cin >> portNum;
        a1[i] = portNum;
    }

    // find the longest increasing subsequence of the 2 arrays
    cout << LongestIncreasingSubsequenceLength(a1);
}