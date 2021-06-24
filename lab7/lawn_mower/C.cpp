#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
	int nx, ny;
	float xi, yi, left, right;
	float w;

	cin >> nx;
	while (nx != 0) {
		cin >> ny >> w;
		bool horizGap = false, vertGap = false;
		
		vector<float> vertPasses;
		while (nx--) {
			cin >> xi;
			//cout << "xi is " << xi << endl;
			vertPasses.push_back(xi);
		}
		sort(vertPasses.begin(), vertPasses.end());
		
		if (vertPasses[0] - (w/2) > 0.0) vertGap = true;
		// if the next strip's left bound is larger than .1 away from this strips's right bound, we have gap
		//cout << "vertical:\n";
		for (int i=0;i<vertPasses.size()-1;i++){
			//cout << vertPasses[i] << endl;
			float nextLeft = vertPasses[i+1] - (w/2);
			float thisRight = vertPasses[i] + (w/2);
			//cout << nextLeft - thisRight << endl;
			if (nextLeft - thisRight > .0000001) vertGap = true;
		}
		if (vertPasses[vertPasses.size()-1] + (w/2) < 75.0) vertGap = true;

		vector<float> horizPasses;
		while (ny--){
			cin >> yi;
			horizPasses.push_back(yi);
			//cout << "yi is " << yi << endl;
		}
		sort(horizPasses.begin(), horizPasses.end());
		
		if (horizPasses[0] - (w/2) > 0.0) horizGap = true;
		//cout << "horizontal:\n";
		// if the next strip's left bound is larger than .1 away from this strips's right bound, we have gap
		for (int i=0;i<horizPasses.size()-1;i++){
			//cout << horizPasses[i] << endl;
			float nextLeft = horizPasses[i+1] - (w/2);
			float thisRight = horizPasses[i] + (w/2);
			//cout << nextLeft - thisRight << endl;
			if (nextLeft - thisRight > .0000001) horizGap = true;
		}
		if (horizPasses[horizPasses.size()-1] + (w/2) < 100.0) horizGap = true;

		if (vertGap || horizGap){
			cout << "NO\n";
		}
		else {
			cout << "YES\n";
		}
		cin >> nx;
	}
	cin >> ny >> w;
	return 0;
}