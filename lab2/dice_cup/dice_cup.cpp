#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    int N = 0, M = 0;
    cin >> N >> M;

    // starting at a total of 2, loop through all the possible totals,
    // storing in a map<total, num combinations>
    multimap<int, int> totalAndCombos;
    int total = N + M, totalCombos = 0;
    for (int i = 2; i <= total; i++) {
        int numCombos = 0;
        for (int n = 1; n <= N; n++) {
            for (int m = 1; m <= M; m++) {
                if (n + m == i) {
                    numCombos++;
                    totalCombos++;
                }
            }
        }
        totalAndCombos.insert(make_pair(numCombos, i));
    }
    // loop through map and update the highest probability
    double highestProb = 0.0;
    double thisProb = 0.0;
    int associatedCombos = 0;
    for (multimap<int, int>::iterator it = totalAndCombos.begin(); it != totalAndCombos.end(); it++) {
        thisProb = (double)it -> first / totalCombos;
        // if this probability is the same as the last, we're at highest probability
        if (thisProb >= highestProb) {
            
            highestProb = thisProb;
            associatedCombos = it -> first;
        }
    }

    // print all totals with highest prob
    for (multimap<int, int>::iterator it = totalAndCombos.begin(); it != totalAndCombos.end(); it++) {
        if (it -> first == associatedCombos) {
            cout << it -> second << endl;
        }
    }
}