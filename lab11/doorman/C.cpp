#include <iostream>
using namespace std;

int main() {
    int X;
    cin >> X;
    string peeps;
    cin >> peeps;
    
    // keep track of whether a man or woman is in front of the line
    int numMen = 0, numWomen = 0, i;
    char fr = peeps[0];
    bool frontSkipped = false, brokeOut = false;
    for (i=0;i<peeps.length();i++) {
        char p = peeps[i];

        if (p == 'M') numMen++;
        else numWomen++;

        if (p != fr && !frontSkipped) {
            fr = p;
        }

        else {
            if (abs(numMen-numWomen) > X) {
                // if the current front is different gender, we can take him/her
                if (frontSkipped && p != fr) {
                    if (fr == 'M') {
                        numMen++;
                        numWomen--;
                    }
                    else {
                        numWomen++;
                        numMen--;
                    }
                    frontSkipped = false;
                    fr = p;
                }

                // if someone isnt skipped right now, is the person behind the front a different gender?
                else if (i < peeps.size()-1 && fr != peeps[i+1] && !frontSkipped) {
                    if (peeps[i+1] == 'M') {
                        numMen++;
                        numWomen--;
                    }
                    else {
                        numWomen++;
                        numMen--;
                    }
                    frontSkipped = true;
                    i++;
                }

                // if we got here, break, since we have encountered 2 consecutive problematic genders
                else {
                    // need to remove the person we just took
                    if (p == 'M') numMen--;
                    else numWomen--;
                    brokeOut = true;
                    break;
                }
            }
        }
    }

    if (frontSkipped && !brokeOut) cout << numMen + numWomen + 1;
    else cout << numMen + numWomen;
}