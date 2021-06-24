#include <iostream>
#include <map>
using namespace std;

int main() {
    int n = 0, i;
    cin >> n;
    int maxProf = n;

    // record n professors, each professor representing k
    map<int, int> profsAndOpus;
    for (i = 1; i <= n; i++) {
        int p;
        cin >> p;
        profsAndOpus.insert(make_pair(i, p));
    }

    // initially, professor 1 calls out opus
    int nextProf = 1;
    int opus = profsAndOpus[1];
    int profOffset = (opus % profsAndOpus.size() == 0) ? profsAndOpus.size() : opus % profsAndOpus.size();
    profsAndOpus.erase(profOffset);
    //cout << "Erased " << profOffset << endl;

    // if we removed the last prof in the original line, decrement max prof number
    if (profOffset == maxProf) {
        maxProf--;
    }

    // call out the numbers for each prof until only 1 prof is left
    while (profsAndOpus.size() > 1) {

        // consecutive next profs may already be removed, find next available prof
        while (profsAndOpus.count(nextProf) == 0) {
            nextProf++;

            // the next prof could now be at index size + 1, if so, next prof is prof 1
            if (nextProf > maxProf) {
                nextProf = profsAndOpus.begin() -> first;
                break;
            }
        }

        // the next prof could now be at index size + 1, if so, next prof is prof 1
        //cout << "end element key is " <<  maxProf << endl;
        if (nextProf > maxProf) {
            nextProf = profsAndOpus.begin() -> first;
        }

        //cout << "size is " << profsAndOpus.size() << endl;
        //cout << "prof: " << nextProf << " gonna call out ";
        // get index of next professor to call out
        int indexOfProf = distance(profsAndOpus.begin(), profsAndOpus.find(nextProf)) + 1;
        // if (indexOfProf == 0) {
        //     indexOfProf = 1;
        // }

        // get opus to be called out
        opus = profsAndOpus.at(nextProf);
        //cout << opus << endl;

        //cout << "index of prof: " << indexOfProf << endl;
        //cout << "size: " << profsAndOpus.size() << endl;
        // get the next professor to be removed
        if (indexOfProf == 1) {
            profOffset = (opus % profsAndOpus.size() == 0) ? profsAndOpus.size() : opus % profsAndOpus.size();  
        }
        else {
            //profOffset = ((opus % profsAndOpus.size()) + indexOfProf - 1) % profsAndOpus.size();
            //cout << "opus: " << opus << ". size: " << profsAndOpus.size() << endl;
            profOffset = opus % profsAndOpus.size() + indexOfProf - 1;
        }

        // we may have already removed this prof (and more), so find first available one
        // while (profsAndOpus.count(profOffset) == 0) {
        //     profOffset++;

        //     // the next prof could now be at index size + 1, if so, next prof is prof 1
        //     if (profOffset > maxProf) {
        //         profOffset = profsAndOpus.begin() -> first;
        //         break;
        //     }
        // }
        map<int, int>::iterator it = profsAndOpus.begin();
        advance(it, profOffset - 1);
        
        //cout << "erasing prof: " << profsAndOpus.find(it -> first) << endl;
        profsAndOpus.erase(profsAndOpus.find(it -> first));

        // if we removed the last prof in the original line, decrement max prof number
        if (profOffset == maxProf) {
            maxProf--;
        }
        //cout << "Ok, erased. Size is now " << profsAndOpus.size() << endl;

        nextProf++;

        //cout << "next prof is " << nextProf << endl;

    }

    cout << profsAndOpus.begin() -> first;
}