#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <math.h>
#include <iomanip>
using namespace std;

#define loop(i, a, b) for(i = (a); i < (b); i++)
#define trav(a, x) for(auto& a : x)

typedef tuple<double, int, int> t;
typedef map<int, pair<int, int> >::iterator mit;

int main() {
    int n, m, p, x, y, i;
    double dist = 0.0;
    cin >> n >> m >> p;

    // keep track of visited judges and tar houses
    int usedJudgesTar[n+1];
    int usedJudgesFeathers[n+1];
    int usedTar[m+1];
    int usedFeathers[p+1];

    loop(i, 1, n+1) {
        usedJudgesTar[i] = 0;
        usedJudgesFeathers[i] = 0;
    }
    loop(i, 1, m+1) {
        usedTar[i] = 0;
    }
    loop(i, 1, p+1) {
        usedFeathers[i] = 0;
    }
    
    map<int, pair<int, int> > judgeLoc;
    map<int, pair<int, int> > tarLoc;
    map<int, pair<int, int> > featherLoc;

    loop(i, 1, n+1) {
        cin >> x >> y;
        judgeLoc.insert(make_pair(i, make_pair(x, y)));
    }
    loop(i, 1, m+1) {
        cin >> x >> y;
        tarLoc.insert(make_pair(i, make_pair(x, y)));
    }
    loop(i, 1, p+1) {
        cin >> x >> y;
        featherLoc.insert(make_pair(i, make_pair(x, y)));
    }

    priority_queue<t> jfeathers;
    priority_queue<t> jtar;
    
    // Go through all judges, calculate distance to each tar and put in (distance, judge, tar house)
    // tuple in the tar queue.  Do likewise for feathers.
    mit it1, it2, it3;
    double jDist;
    t tup;
    trav(it1, judgeLoc) {
        trav(it2, tarLoc) {
            jDist = sqrt(pow(it1.second.first - it2.second.first, 2) + pow(it1.second.second - it2.second.second, 2));
            // pushing negative elements into priority queue in order to sort without the need of a comparator
            tup = make_tuple(-jDist, -it1.first, -it2.first);
            jtar.push(tup);
        }

        trav(it3, featherLoc) {
            jDist = sqrt(pow(it1.second.first - it3.second.first, 2) + pow(it1.second.second - it3.second.second, 2));
            tup = make_tuple(-jDist, -it1.first, -it3.first);
            jfeathers.push(tup);
        }
    }

    // Then, just pull from the priority queues – pull out the next one, and see if that judge and that tar
    // house (feather house) have been used – if both are unused, then mark them used, and add distance to the total.
    while (!jtar.empty()) {
        tup = jtar.top();
        jtar.pop();
        if (!usedJudgesTar[-get<1>(tup)] && !usedTar[-get<2>(tup)]) {
            dist += (-get<0>(tup));
            usedJudgesTar[-get<1>(tup)] = 1;
            usedTar[-get<2>(tup)] = 1;
        }
    }

    while (!jfeathers.empty()) {
        tup = jfeathers.top();
        jfeathers.pop();
        if (!usedJudgesFeathers[-get<1>(tup)] && !usedFeathers[-get<2>(tup)]) {
            dist += (-get<0>(tup));
            usedJudgesFeathers[-get<1>(tup)] = 1;
            usedFeathers[-get<2>(tup)] = 1;
        }
    }

    cout << fixed << setprecision(6) << dist;
}