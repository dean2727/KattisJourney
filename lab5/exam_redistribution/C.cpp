#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(const pair<int, int>& x, const pair<int, int>& y) {
	return x.second > y.second;
}

int main() {
	int n, s;
	cin >> n;
	map<int, int> rs;

	for (int i=1;i<=n;i++){
		cin >> s;
		rs.insert(make_pair(i, s));
	}

	vector<pair<int, int> > vec;  
	copy(rs.begin(),
			rs.end(),
			back_inserter<vector<pair<int, int> > >(vec));
	sort(vec.begin(),vec.end(),cmp);

	// loop through the rooms, adding onto papersGiven 
	vector<pair<int,int> >::iterator it=vec.begin();
	int numInitial = it->second;  // # of original papers
	int init = it->second;
	advance(it, 1);
	while (it != vec.end()) {
		numInitial -= it->second;
		advance(it, 1);
	}

	if (numInitial <= 0) {
		vector<pair<int,int> >::iterator it=vec.begin();
		cout << it->first;
		advance(it, 1);
		while (it != vec.end()) {
			cout << " " << it->first;
			advance(it, 1);
		}
	}
	else {
		cout << "impossible";
	}

	return 0;
}
