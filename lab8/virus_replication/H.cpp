#include <iostream>
#include <string>
using namespace std;

int main() {
    string bef, aft;
    cin >> bef;
    cin >> aft;

    // take as many from the beginning of first string as match the second string, and same for the end
    // The amount remaining in the first string, after pulling off the matching front and back ones is the (minimum) string that was added
    int befLen = bef.length(), aftLen = aft.length();
    int i = 0;
    while (bef[i] == aft[i] && i < befLen && i < aftLen) {
        i++;
    }

    int be = befLen - 1, ae = aftLen - 1;
    while (bef[be] == aft[ae] && be >= i && ae >= i) {
        be--;
        ae--;
    }

    if (ae - i + 1 < 0) cout << "0";
    else cout << ae - i + 1;
}