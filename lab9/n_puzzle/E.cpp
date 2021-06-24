#include <iostream>
#include <map>
#include <math.h>
using namespace std;

int main() {
    int dist = 0;
    map<char, pair<int, int> > coor;
    string line;
    cin >> line;
    for (int i=0;i<4;i++) {
        coor.insert(make_pair(line[i], make_pair(0, i)));
    }
    cin >> line;
    for (int i=0;i<4;i++) {
        coor.insert(make_pair(line[i], make_pair(1, i)));
    }
    cin >> line;
    for (int i=0;i<4;i++) {
        coor.insert(make_pair(line[i], make_pair(2, i)));
    }
    cin >> line;
    for (int i=0;i<4;i++) {
        coor.insert(make_pair(line[i], make_pair(3, i)));
    }

    char c = 'A';
    dist += abs(coor[c].first - 0) + abs(coor[c].second - 0);
    c = 'B';
    dist += abs(coor[c].first - 0) + abs(coor[c].second - 1);
    c = 'C';
    dist += abs(coor[c].first - 0) + abs(coor[c].second - 2);
    c = 'D';
    dist += abs(coor[c].first - 0) + abs(coor[c].second - 3);

    c = 'E';
    dist += abs(coor[c].first - 1) + abs(coor[c].second - 0);
    c = 'F';
    dist += abs(coor[c].first - 1) + abs(coor[c].second - 1);
    c = 'G';
    dist += abs(coor[c].first - 1) + abs(coor[c].second - 2);
    c = 'H';
    dist += abs(coor[c].first - 1) + abs(coor[c].second - 3);

    c = 'I';
    dist += abs(coor[c].first - 2) + abs(coor[c].second - 0);
    c = 'J';
    dist += abs(coor[c].first - 2) + abs(coor[c].second - 1);
    c = 'K';
    dist += abs(coor[c].first - 2) + abs(coor[c].second - 2);
    c = 'L';
    dist += abs(coor[c].first - 2) + abs(coor[c].second - 3);

    c = 'M';
    dist += abs(coor[c].first - 3) + abs(coor[c].second - 0);
    c = 'N';
    dist += abs(coor[c].first - 3) + abs(coor[c].second - 1);
    c = 'O';
    dist += abs(coor[c].first - 3) + abs(coor[c].second - 2);

    cout << dist;
 }