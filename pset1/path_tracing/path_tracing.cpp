#include <iostream>
#include <set>

using namespace std;

int main() {
    int maxDown = 0, maxUp = 0, maxLeft = 0, maxRight = 0;
    set<pair<int, int> > coordinates;

    string direction;
    int currentHorizontal = 0, currentVertical = 0;
    coordinates.insert(make_pair(0, 0));  // start position is origin
    while (cin >> direction) {

        if (direction == "down") {
            currentVertical--;
            if (currentVertical < maxDown) {
                maxDown = currentVertical;
            }
        }

        else if (direction == "up") {
            currentVertical++;
            if (currentVertical > maxUp) {
                maxUp = currentVertical;
            }
        }

        else if (direction == "left") {
            currentHorizontal--;
            if (currentHorizontal < maxLeft) {
                maxLeft = currentHorizontal;
            }
        }

        else if (direction == "right") {
            currentHorizontal++;
            if (currentHorizontal > maxRight) {
                maxRight = currentHorizontal;
            }
        }

        coordinates.insert(make_pair(currentHorizontal, currentVertical));
    }

    // fill out the coordinate plane, loop from maxLeft - 1 to maxRight + 1 and maxUp + 1 to maxDown - 1
    for (int y = maxUp + 1; y != maxDown - 2; y--) {
        for (int x = maxLeft - 1; x != maxRight + 2; x++) {

            pair<int, int> thisCoordinate = make_pair(x, y);

            if (x == maxLeft - 1 || x == maxRight + 1 || y == maxUp + 1 || y == maxDown - 1) {
                cout << "#";
            }

            // end position
            else if (x == currentHorizontal && y == currentVertical) {
                cout << "E";
            }

            // start position
            else if (x == 0 && y == 0) {
                cout << "S";
            }
            
            else {
                // if these coordinates are on the path, print *
                if (coordinates.count(thisCoordinate) == 1) {
                    cout << "*";
                }
                else {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
}