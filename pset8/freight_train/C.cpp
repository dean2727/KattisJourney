#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define loop(i, a, b) for(i = (a); i < (b); i++)
int i, L, N, W;

vector<int> wagLoc;

// can we use L locotomives to send off freight trains of min max length x to lux
string sufficient(int x) {
    // the number of locomotives we've used
    int used = 0;
    // the current wagon number in the entire train
    int wagNum = 1;
    // location of freight wagon in train (index for wagLoc)
    int idx = 0;
    // current wagon number with freight
    int freightWagon;
    // current size of the train this locomotive will transfer
    int trainSize = 0;

    bool freightDone = false;

    while (wagNum <= N) {
        // firstly, if idx >= W, then we have shipped off all the freight wagons, so we can just either
        // keep adding wagons to this train until train size surpasses x, or we can use a dummy locomotive
        // to send off the rest of the wagons
        if (idx >= W) {
            if (trainSize == 0) {
                used++;
                break;  // end of train reached
            }
            else {
                trainSize++;
                wagNum++;
                // need to search higher if the train size is now > x and no more locs available
                if (trainSize > x) {
                    cout << "finished off the one at the end\n";
                    used++;
                    trainSize = 0;
                }
            }
            //cout << "ok, so no more freights from here, wag num of entire train is " << wagNum << " and used is " << used << " and train size is " << trainSize << endl;
        }

        else {
            freightWagon = wagLoc[idx];
            cout << "\nwagon num of entire train: " << wagNum << "\ncurrent wagon with freight: " << freightWagon << endl;
            cout << wagNum - trainSize + x << " > " << freightWagon << "?\n";

            // 1. We included the current wagon in the current locomotive we have assigned, then we
            // just ignore it cause it is in our shipment.
            if (wagNum == freightWagon) {
                cout << "1\n";
                trainSize++;
                //cout << "train size = " << trainSize << endl;
                // if the train size is now > x, restart a new train here
                if (trainSize > x) {
                    used++;
                    trainSize = 1;
                    //cout << "this train size was greater than x\n";
                }
                idx++;
                wagNum++;
            }

            // 2. Otherwise, we check to see if the wagon we want to ship away is x + current_wagon that we are at.
            // This is because we can use another locomotive and just have it hold the range of wagons from curr
            // to curr + x now.
            else if (wagNum - trainSize + x > freightWagon) {
                cout << "2\n";
                //cout << x << " + " << " current wagon which is " << wagNum << " is " << wagNum + x << ". next is " << freightWagon << endl;
                // used++;
                // trainSize = 0;
                trainSize += freightWagon-wagNum+1;
                wagNum = freightWagon;
                //idx++;
                if (trainSize == x) {
                    used++;
                    trainSize = 0;
                }
            }

            // 3. If this is not true, it means that there are > x wagons in between the one we are at and the one
            // that we want to send off. In this case, we need two locomotives (one dummy one to send to another country,
            // cause this locomotive can hold any amount), and one starting from that wagon we want.
            else {
                cout << "3\n";
                // this big train could be at the very beginning
                if (used == 0 || wagNum - trainSize + x == freightWagon - 1) used++;
                else used += 2;
                trainSize = 0;
                wagNum = freightWagon;
                //cout << "wag num now " << wagNum << endl;
            }
        }

        cout << "used locs now = " << used << endl;
        cout << "train size now = " << trainSize << endl;
        cout << "wag num now = " << wagNum << endl;
    }
    if (trainSize != 0) used++;
    cout << "ended up using " << used << endl;
    
    // If the number of locomotives that we utilized to make this work is > L, then we can't do this
    // (and need to look higher). Otherwise, we can (and can try to look for better).
    if (used > L) return "higher";
    else return "lower";
}

// binary search for x (the min max length of a train with freight taken to luxembourg)
int binarySearch(int left, int right) {
    cout << "left = " << left << " right = " << right << endl;
    if (left > right) return -1;
    int mid = (left + right) / 2;

    // see if it would, would not (not enough locomotives), or would perfectly work if we had a
    // min max train length of mid
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~testing x = " << mid << endl;
    string status = sufficient(mid);
    cout << "got back " << status << endl;
    if (left == right) {
        if (status == "higher") return mid+1;
        else return mid;
    }
    else if (status == "higher")
        return binarySearch(mid+1, right);
    else
        return binarySearch(left, mid-1);
}

int main() {
    int T;
    cin >> T;
    while(T--){
        int wag, high, low;
        cin >> N >> W >> L;

        wagLoc.resize(W, 0);
        loop(i, 0, W) {
            cin >> wag;
            wagLoc[i] = wag;
        }

        // we want to know if it is possible to assign <= the locomotives (L of them), such that the maximum
        // of those locomotives holds x wagons
        high = N;
        low = 1;
        cout << binarySearch(low, high) << "\n";

        wagLoc.clear();
    }
}