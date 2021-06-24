#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp (const int& a, const int& b) {
	return a > b;
}

int main() {
	// std::ios::sync_with_stdio(false);
	// cin.tie(false);
	// cout.tie(false);
	int T, len;
	long long int num;
	long long int prod1 = 0, prod2 = 0;
	cin >> T;

	int caseNum = 1;
	while (T--) {
		vector<long long int> v1;
		vector<long long int> v2;
		cin >> len;
		for (int j = 0; j < len; j++) {
			cin >> num;
			//cout << "num: " << num << endl;
			v1.push_back(num);
		}
		for (int j = 0; j < len; j++) {
			cin >> num;
			//cout << "num: " << num << endl;
			v2.push_back(num);
		}

		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end(), cmp);
		for (int i=0;i<v1.size();i++) {
			prod1 += v1[i] * v2[i];
		}

		sort(v2.begin(), v2.end());
		sort(v1.begin(), v1.end(), cmp);
		for (int i=0;i<v1.size();i++) {
			prod2 += v1[i] * v2[i];
		}

		cout << "Case #" << caseNum << ": ";
		if (prod1 < prod2) {
			cout << prod1;
		}
		else {
			cout << prod2;
		}
		cout << "\n";
		caseNum++;
		prod1 = 0;
		prod2 = 0;
	}

	return 0;
}
