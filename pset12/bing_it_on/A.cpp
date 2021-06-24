#include <iostream>
using namespace std;

string word;

// assuming lowercase letters
class node {
public:
    bool isin;
    node* children[26];
    int occurences;
    node() {
        isin = false;
        occurences = 0;
        for(int i=0;i<26;i++) children[i] = NULL;
    }

    // add to the trie, character by character
    int add(string s) {
        // at destination node, return
        if (s.length() == 0) {
            isin = true;
            return occurences;
        }
        // strip off first character, and then do the rest
        char c = s[0];
        if (children[c-'a'] == NULL) {
            children[c-'a'] = new node();
            children[c-'a']->occurences = 1;
        }
        else {
            children[c-'a']->occurences++;
        }
        string s2 = s.substr(1);
        return children[c-'a']->add(s2);
    }

    // inorder traversal of the tree
    void printout(string s = "") {
        // if at the final position, output the string
        if (isin) cout << s << endl;
        string s2;
        for(int i=0;i<26;i++) {
            if (children[i] != NULL) {
                s2 = s + (char) (i+'a');
                children[i]->printout(s2);
            }
        }
    }
};


int main() {
    int N;
    node trie;
    cin >> N;
    for (int i=0;i<N;i++) {
        cin >> word;
        // subtract 1 because we also count the current prefix
        cout << trie.add(word) - 1 << "\n";        
    }
}