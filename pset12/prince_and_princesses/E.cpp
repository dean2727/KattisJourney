#include <iostream>
#include <map>
#include <vector>
using namespace std;

// https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
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
    int t,n,i,j,p,q;
    cin >> t;
    for (i=1;i<=t;i++) {
        int longestCommonRoute;
        cin >> n >> p >> q;

        vector<int> kingSeq(p+1);
        map<int, int> kingMoveToIdx;
        vector<int> queenSeq(q+1);
        int square;
        for (j=0;j<p+1;j++) {
            cin >> square;
            kingSeq[j] = square;
            kingMoveToIdx[square] = j;
        }
        for (j=0;j<q+1;j++) {
            cin >> square;
            queenSeq[j] = square;
        }

        /* this problem is a longest common subsequence problem, but because of runtime 
        being an issue (can have a sequence of up to 62500 moves), need to transform
        it into a longest increasing subsequence problem with O(nlgn) runtime. to do so,
        we will make a new vector which holds, for each element in queen sequence, 
        the index of that element in the king sequence */
        vector<int> transformed;
        for (j=0;j<queenSeq.size();j++) {
            if (kingMoveToIdx.count(queenSeq[j])) {
                transformed.push_back(kingMoveToIdx[queenSeq[j]]);
            }
        }

        // find the length of longest common subsequence of the king and queen sequence
        longestCommonRoute = LongestIncreasingSubsequenceLength(transformed);

        cout << "Case " << i << ": " << longestCommonRoute << "\n";
    }
}