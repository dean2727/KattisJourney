#include <iostream>
#include <queue>
using namespace std;

int main() {
    int c, l, m, i;
    cin >> c;
    while (c--) {
        // ferry length and number of cars
        cin >> l >> m;
        l *= 1000;
        int carl;
        string side;
        queue<int> leftq;
        queue<int> rightq;
        int totCarl = 0, numTrip = 0;
        bool left = true;
        bool remLeft = false, remRight = false;
        int rrc = 0, lrc = 0;  // remaining car lengths
        for (i=0;i<m;i++) {
            cin >> carl >> side;
            cout << carl << " " << side << endl;
            // if side is different, transport
            // to the right
            if (left && side == "right") {
                cout << "goin to the right\n";
                left = false;
                numTrip++;
                totCarl = carl;
            }
            // to the left
            else if (!left && side == "left") {
                cout << "goin to the left\n";
                left = true;
                numTrip++;
                totCarl = carl;
            }

            // no more room, store remaining car
            else if (totCarl + carl > l) {
                numTrip++;
                totCarl = 0;
                if (left) {
                    cout << "goin to the right with remaining now\n";
                    remLeft = true;
                    lrc = carl;
                    left = false;
                }
                else {
                    cout << "goin to the left with remaining now\n";
                    remRight = true;
                    rrc = carl;
                    left = true;
                }
            }

            else {
                // take remaining
                // left side
                if (left && remLeft) {
                    cout << "left rem\n";
                    totCarl += lrc;
                    // can we still take the current?
                    // no
                    if (totCarl + carl > l) {
                        lrc = carl;
                    }
                    // yes
                    else {
                        remLeft = false;
                        totCarl += carl;
                    }
                }
                // right side
                else if (!left && remRight) {
                    cout << "right rem\n";
                    totCarl += rrc;
                    // can we still take the current?
                    // no
                    if (totCarl + carl > l) {
                        rrc = carl;
                    }
                    // yes
                    else {
                        remRight = false;
                        totCarl += carl;
                    }
                }
                else {
                    cout << "simply added\n";
                    totCarl += carl;
                }
            }
        }

        // may need to transport last one
        if (totCarl > 0) {
            numTrip++;
            if (left == true) numTrip++;
        }

        cout << numTrip << "\n";
    }
}