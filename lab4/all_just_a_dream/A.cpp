#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

int main() {
	std::ios::sync_with_stdio(false);
	vector<string> events;
	map<string, int> eventsAndIndexes;
	int n, idx = 0;
	char c;
	string e;
	cin >> n;
	while (n--){
		cin >> c;
		if (c == 'E') {
			cin >> e;
			events.push_back(e);
			eventsAndIndexes[e] = idx;
			idx++;
		}
		else if (c == 'D') {
			int r;
			cin >> r;

			// dont remove if already empty
			while (r--){
				if (!events.empty()) {
					eventsAndIndexes.erase(events.back());
					events.pop_back();
				}
			}
		}
		else {
			int numEvents;
			string event;
			cin >> numEvents;

			// Find latest event that should be there, and first event that should not
			int shouldLatest = 0, shouldntFirst = 100000, smallestr = 100000, farBack;
			bool plotError = false, consistent = true;

			while (numEvents--){
				cin >> event;
				//cout << event << endl;
				// if didnt happen and is not in the map, then should be there
				if (event[0] == '!') {
					string ss = event.substr(1, event.length()-1);
					if (!(eventsAndIndexes.count(ss) == 0)) {
						consistent = false;
						//cout << eventsAndIndexes[ss] << endl;
						if (eventsAndIndexes[ss] < shouldntFirst) {
							shouldntFirst = eventsAndIndexes[ss];							
							//cout << "new shouldnt first = " << shouldntFirst << endl;
						}
						// farBack = events.size() - eventsAndIndexes[ss];
						// //cout << "far back = " << farBack << endl;
						// if (farBack < smallestr) {
						// 	smallestr = farBack;
						// }
					}
				}
				// however if it did happen and is not in the map, then there may be a plot error
				else {
					if (eventsAndIndexes.count(event) == 0) {
						plotError = true;
						consistent = false;
						//cout << "String: " << event << " is NOT in the map" << endl;
					}
					else {
						//cout << "String: " << event << " is in the map" << endl;
						if (eventsAndIndexes[event] > shouldLatest) {
							shouldLatest = eventsAndIndexes[event];
							//cout << "new should latest = " << shouldLatest << endl;
						}
					}
				}
			}
			
			// If all the events are in the the map and the negated ones are not in the map, the scenario
			// is consistent with what's happened so far
			if (consistent) {
				cout << "Yes\n";
			}
			// If event that should be there does not exist, or comes after the first event that should not,
			// then output “Plot Error”
			else if (plotError || shouldLatest > shouldntFirst) {
				cout << "Plot Error\n";
			}
			// Otherwise, output how many back the first event that should not be there is.
			else {
				cout << events.size() - shouldntFirst << " Just A Dream\n";
			}
		}
	}

	return 0;
}
