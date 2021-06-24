#include <iostream>
#include <set>
using namespace std;

int main() {
	// std::ios::sync_with_stdio(false);
	// cin.tie(false);
	// cout.tie(false);

	int l, d, n;
	cin >> l >> d >> n;
	set<int> birds;
	int numBirds;

	int bird;
	while (n--) {
		cin >> bird;
		birds.insert(bird);
	}

	//cout << numBirds << endl;

	// may have no birds
	if (birds.empty()) {
		numBirds += (l - 6 - 6) / d + 1;
	}

	else {
		//numBirds += birds.size();
		// get # of birds that can fit from left edge to leftmost bird
		set<int>::iterator it = birds.begin();
		int numBetween = (*it - 6) / d;
		numBirds += numBetween;
		//cout << numBirds << endl;
		int prevBird = *it;

		// get # of birds that can fit in between prev and curr bird
		advance(it, 1);
		while(it != birds.end()) {
			// if we can fit another bird in between
			numBetween = (*it - prevBird) / d;
			//cout << "num between: " << numBetween << endl;
			if (numBetween != 1 || numBetween != 0) {
				numBirds += numBetween - 1;
			}
			prevBird = *it;
			advance(it, 1);
			//cout << numBirds << endl;
		}

		// get # of birds that can fit from rigthmost bird to right edge
		numBetween = (l - 6 - prevBird) / d;
		//cout << "num between: " << numBetween << endl;
		numBirds += numBetween;
	}

	cout << numBirds;

	return 0;
}
