#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

#define loop(i, a, b) for(i = (a); i < (b); i++)

int main() {	
	int l, w, n, r, i, j, k;
	cin >> l >> w >> n >> r;

	vector<pair<int, int> > craneCoord;
	int x, y;
	loop (i, 0, n) {
		cin >> x >> y;
		craneCoord.push_back(make_pair(x, y));
	}
	
	// left wall
	pair<float, float> c1(-(float)l/2, 0);
	// right wall
	pair<float, float> c2((float)l/2, 0);
	// bottom wall
	pair<float, float> c3(0, -(float)w/2);
	// top wall
	pair<float, float> c4(0, (float)w/2);

	// reachability of cranes
	int cranes[n];

	loop (i, 0, n) {
		cranes[i] = 0;
	}
	
	// classify each crane by which walls it can put into place via bitmask
	// A | B -> which walls can be by either. e.g. 1010 | 0001 = 1011
	float dist;
	int cx, cy;
	loop (i, 0, n) {
		cx = craneCoord[i].first, cy = craneCoord[i].second;
		// distance to left wall
		dist = sqrt(pow(c1.first - cx, 2) + pow(c1.second - cy, 2));
		if (dist <= r) {  // is the distance within the radius of the crane
			cranes[i] |= (1 << 0);
		} 
		// distance to right wall
		dist = sqrt(pow(c2.first - cx, 2) + pow(c2.second - cy, 2));
		if (dist <= r) {
			cranes[i] |= (1 << 1);
		} 
		// distance to bottom wall
		dist = sqrt(pow(c3.first - cx, 2) + pow(c3.second - cy, 2));
		if (dist <= r) {
			cranes[i] |= (1 << 2);
		}
		// distance to top wall
		dist = sqrt(pow(c4.first - cx, 2) + pow(c4.second - cy, 2));
		if (dist <= r) {
			cranes[i] |= (1 << 3);
		}
	}

	// 1. see if any crane can assemble all 4 walls (+1)
	loop (i, 0, n) {
		if ((cranes[i] & 15) == 15) {
			cout << "1";
			return 0;
		}
	}

	// 2. double nested for loops for checking if any pairs of cranes can assemble all 4 walls (+2) (n choose 2 combos)
	loop (i, 0, n-1) {
		loop (j, i+1, n) {
			if (((cranes[i] | cranes[j]) & 15) == 15) {
				cout << "2";
				return 0;
			}
		}
	}

	// 3. triply nested for loops for check if a set of 3 canes can assemble the walls (+3) (n choose 3 combos)
	loop (i, 0, n-2) {
		loop (j, i+1, n-1) {
			loop (k, j+1, n) {
				if (((cranes[i] | cranes[j] | cranes[k]) & 15) == 15) {
					cout << "3";
					return 0;
				}
			}
		}
	}

	// 4. can any set of 4 cranes assemble them? aka is each bit hit by some crane?
	bool oneCanHitLeft = false, oneCanHitRight = false, oneCanHitBottom = false, oneCanHitTop = false;
	loop (i, 0, n) {
		if (cranes[i] & 1) {
			oneCanHitLeft = true;			
		}
		if (cranes[i] & 2) {
			oneCanHitRight = true;
		}
		if (cranes[i] & 4) {
			oneCanHitBottom = true;
		}
		if (cranes[i] & 8) {
			oneCanHitTop = true;
		}
	}
	if (oneCanHitLeft && oneCanHitRight && oneCanHitBottom && oneCanHitTop) {
		cout << "4";
		return 0;
	}

	// otherwise, impossible
	cout << "Impossible";
	return 0;
}