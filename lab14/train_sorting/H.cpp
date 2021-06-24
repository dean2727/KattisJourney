#include <iostream>
#include <vector>
using namespace std;

// longest train -> longest increasing subsequence
// https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
// Binary search (note boundaries in the caller)
int CeilIndex(vector<int>& v, int l, int r, int key)
{
	while (r - l > 1) {
		int m = l + (r - l) / 2;
		if (v[m] >= key)
			r = m;
		else
			l = m;
	}

	return r;
}

// any valid sequence consists of an increasing subsequence and decreasing subsequence 
// from some point. binary search for these 

int LongestIncreasingSubsequenceLength(vector<int>& v)
{
	if (v.size() == 0)
		return 0;

	vector<int> tail(v.size(), 0);
	int length = 1; // always points empty slot in tail

	tail[0] = v[0];
	for (size_t i = 1; i < v.size(); i++) {

		// new smallest value
		if (v[i] < tail[0])
			tail[0] = v[i];

		// v[i] extends largest subsequence
		else if (v[i] > tail[length - 1])
			tail[length++] = v[i];

		// v[i] will become end candidate of an existing
		// subsequence or Throw away larger elements in all
		// LIS, to make room for upcoming grater elements
		// than v[i] (and also, v[i] would have already
		// appeared in one of LIS, identify the location
		// and replace it)
		else
			tail[CeilIndex(tail, -1, length - 1, v[i])] = v[i];
	}

	return length;
}

int main() {
    int n, tr;
    vector<int> seq;
    cin >> n;
    while(n--) {
        cin >> tr;
        seq.push_back(tr);
    }
    cout << LongestIncreasingSubsequenceLength(seq);
}