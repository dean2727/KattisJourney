#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(const pair<int, int>& p1, const pair<int, int>& p2) {
	return p1.second > p2.second;
}

int main() {
	int N, K, A, B;
	cin >> N >> K;

	int players[N];
	for (int i=0;i<N;i++){
		players[i] = i;
	}

	vector<pair<int, int> > legs;
	while (K--) {
		// A = index of vertical line on left of leg, B = distance from top
		cin >> A >> B;
		legs.push_back(make_pair(A, B));
	}

	// sort legs from bottom to top (sort by decreasing value of distance from top)
	sort(legs.begin(), legs.end(), cmp);

	// for each leg, index pair->first of the leg of the player and +1 index swap
	int temp, l;
	for (int i=0;i<legs.size();i++){
		l = legs[i].first;
		// only swap if we havent gone down the vertical yet
		temp = players[l];
		players[l] = players[l + 1];
		players[l + 1] = temp;		
	}

	for (int i=0;i<N;i++){
		cout << players[i];
		if (i!=N-1) cout << " ";
	}

	return 0;
}
