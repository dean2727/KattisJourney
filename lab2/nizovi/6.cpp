#include <iostream>
#include <string>
using namespace std;

int main() {
    string line;
    cin >> line;

    cout << "{\n";
    int numSpaces = 2;

    // if line isnt {}, print inital spaces
    if (line.length() > 2) {
        cout << "  ";
    }
    int d = 1;  // depth level
    for (int i=1; i<line.length()-1;i++) {
        char c = line.at(i);

        if (c == '}') {
            d--;
            numSpaces -= 2;
            //cout << "\n";
            for (int j=0;j<numSpaces;j++) {
                cout << ' ';
            }
            cout << c;
            if (line.at(i + 1) == '}') {
                cout << "\n";
            }
        }
        else if (c == '{') {
            d++;
            cout << c << endl;
            numSpaces += 2;
            if (line.at(i + 1) == '}') {
                for (int j=0;j<numSpaces-2*d;j++) {
                    cout << ' ';
                }
            }
            else {
                for (int j=0;j<numSpaces;j++) {
                    cout << ' ';
                }
            }
        }
        else if (c == ',') {
            cout << c << "\n";
            for (int j=0;j<numSpaces;j++) {
                cout << ' ';
            }
        }
        else {
            cout << c;
            if (line.at(i + 1) == '}') {
                cout << "\n";
            }
        }
    }
    cout << "}\n";
}