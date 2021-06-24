#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    // we want to sort the runnners by second time, then 
    // loop though all runners first times and see which
    // sum is smallest (dont count same runner twice)

    // name and first time
    vector<pair<string, double> > nft;

    // name and second time
    vector<pair<double, string> > nst;

    int n;
    string name;
    double t1, t2;
    cin >> n;
    while (n--) {
        cin >> name;
        cin >> t1 >> t2;
        //cout << t1 << t2;
        nft.push_back(make_pair(name, t1));
        nst.push_back(make_pair(t2, name));
    }

    sort(nst.begin(), nst.end());
    
    vector<string> runners;
    pair<double, vector<string> > optimal;
    double mini = 10000000.0, time = 0.0;
    for (int i=0;i<nft.size();i++) {
        name = nft[i].first;
        runners.push_back(name);
        //cout << "\nfirst: " << name << endl;
        time += nft[i].second;
        int chosen = 0, idx = 0;
        while (chosen != 3) {
            //cout << nst[idx].second << endl;
            //cout << nst[idx].first << endl;
            if (nst[idx].second != name) {
                runners.push_back(nst[idx].second);
                chosen++;
                time += nst[idx].first;
            }
            idx++;
        }
        
        //cout << "time: " << time << endl;
        // if this is the minimum time to run, update optimal 
        if (time < mini) {
            optimal.first = time;
            optimal.second = runners;
            mini = time;
        }

        time = 0.0;
        runners.clear();
    }

    // 2 decimal places
    cout << fixed << setprecision(9) << optimal.first << endl;
    for (int i=0;i<optimal.second.size();i++) {
        cout << optimal.second[i] << endl;
    }
}