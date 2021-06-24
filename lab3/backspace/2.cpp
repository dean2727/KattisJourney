#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {
    // input
    string line;
    cin >> line;

    // loop through the string, when < encountered, erase
    stack<char> s;
    for (int i=0;i<line.length();i++) {
        //cout << line.at(i) << endl;
        if (line.at(i) == '<') {
            //cout << "Popping\n";
            if (s.size() != 0) {
                s.pop();
            }
        }
        else {
            s.push(line.at(i));
            //cout << s.top() << endl;
        }
    }

    // output
    //cout << s.size() << endl;
    stack<char> s2;
    int loops = s.size();
    for (int i=0;i<loops;i++) {
        s2.push(s.top());
        s.pop();
    }

    //cout << s2.size() << endl;
    for (int i=0;i<loops;i++) {
        cout << s2.top();
        s2.pop();
    }
}