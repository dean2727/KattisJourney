#include <iostream>
#include <vector>
using namespace std;

int main() {
    string ins;
    cin >> ins;
    int lastCap;
    vector<int> capSpots;
    for (int i=0;i<ins.length();i++) {
        if (ins[i] < 97) {
            capSpots.push_back(i);
        }
    }

    int num = 0;
    for (int i=0;i<capSpots.size()-1;i++) {
        //cout << "asd" << (capSpots[i+1] - capSpots[i]) << endl;
        //cout << 4 % (capSpots[i+1] - capSpots[i]) << endl;
        int idx = capSpots[i+1] - capSpots[i];
        while (idx % 4 != 0) {
            num += 1;
            idx += 1;
        }
    }

    cout << num;
}