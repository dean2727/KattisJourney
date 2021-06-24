#include <iostream>
#include <string>

using namespace std;

// assuming capital letters
class node {
public:
    bool isin;
    node* children[26];
    node() {
        isin = false;
        for(int i=0;i<26;i++) children[i] = NULL;
    }

    // add to the trie, character by character
    void add(string s) {
        // at destination node, return
        if (s.length() == 0) {
            isin = true;
            return;
        }
        // strip off first character, and then do the rest
        char c = s[0];
        if (children[c-'A'] == NULL) {
            children[c-'A'] = new node();
        }
        string s2 = s.substr(1);
        children[c-'A']->add(s2);
    }

    // inorder traversal of the tree
    void printout(string s = "") {
        // if at the final position, output the string
        if (isin) cout << s << endl;
        string s2;
        for(int i=0;i<26;i++) {
            if (children[i] != NULL) {
                s2 = s + (char) (i+'A');
                children[i]->printout(s2);
            }
        }
    }
};

int main() {
    string s;
    node trie;
    while(true) {
        cin >> s;
        if (s=="DONE") {
            break;
        }
        // insert s into the trie
        trie.add(s);
    }
    cout << "---- The dictionary is: ----" << endl;
    trie.printout();
}