#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // input
    int n = 0;
    cin >> n;
    int count = 0;

    string s;
    for (int i=0;i<n;i++) {
        cin >> s;

        bool cd = false;
        for (int j=0;j<s.length()-1;j++) {
            if (s.at(j) == 'C') {
                if (s.at(j + 1) == 'D') {
                    cd = true;
                    break;
                }
            }
        }

        if (!cd) {
            count++;
        }
    }


    // output
    cout << count;
}