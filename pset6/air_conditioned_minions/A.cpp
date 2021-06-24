#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // greedy approach: sort temp preferences by lower limit. loop through the preferences,
    // if the preference interval overlaps with the previous one, its in the same room. also,
    // update the upper limit if the preference's upper limit exceeds the previous preference's
    // upper limit. when we come across an interval whose lower limit isnt touching the upper limit,
    // add 1 and reset the upper limit

    int N, L, U, count = 1;
    vector<pair<int, int> > prefs;
    cin >> N;

    while (N--){
        cin >> L >> U;
        prefs.push_back(make_pair(L, U));
    }

    sort(prefs.begin(), prefs.end());

    U = prefs[0].second;
    for (int i=1;i<prefs.size();i++){
        if (prefs[i].first > U) {
            count++;
            U = prefs[i].second;
        }
        else {
            if (prefs[i].second < U) {
                U = prefs[i].second;
            }
        }
    }

    cout << count;
}