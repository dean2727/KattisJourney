#include <iostream>
#include <set>
using namespace std;

int main() {
    set<char> vowels;
    vowels.insert('a');
    vowels.insert('e');
    vowels.insert('i');
    vowels.insert('o');
    vowels.insert('u');
    vowels.insert('y');
    int N;
    while (cin >> N) {
        string word;
        int best = 0;
        string bestWord;
        for (int j=0;j<N;j++) {
            cin >> word;
            int pairs = 0;
            for (int i=0;i<word.length()-1;i++) {
                if (vowels.count(word[i]) && vowels.count(word[i+1]) && word[i] == word[i+1]) {
                    pairs++;
                }
            }
            if (pairs > best) {
                best = pairs;
                bestWord = word;
            } 
        }
        if (N==1) cout << word << "\n";
        else cout << bestWord << "\n";
    }
}