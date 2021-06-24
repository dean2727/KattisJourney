#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

/*
For this problem, we will want to search each boggle via a DFS. The dictionary will
form a trie, and we search the trie as the DFS progresses. 
*/

vector<vector<char> > boggle;
vector<vector<bool> > visited;
set<string> seenWords;

// capital letters assumed
class TrieNode {
public:
    TrieNode* children[26];
    bool end;
    char letter;

    TrieNode() {
        end = false;
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }
        letter = '\0';
    }
};

class Trie {
private:
    TrieNode root;

public:
    // Insert the word in the trie
    void Insert(string str) {
        TrieNode * current = &root;
        for (size_t i = 0; i < str.size(); i++) {
            if (current->children[str.at(i)-'A'] == NULL) {
                current->children[str.at(i)-'A'] = new TrieNode;
                current->children[str.at(i)-'A']->letter = str.at(i);
            }
            current = current->children[str.at(i)-'A'];
        }
        current->end = true;
    }

    // Search the word in trie
    int Search(string str) {
        TrieNode* current = &root;
        for (int i = 0; i < str.size(); i++) {
            if (current->children[str.at(i)-'A'] != NULL) {
                current = current->children[str.at(i)-'A'];
            }
            else {
                return 0;
            }
        }

        // Check if string 'str' exists as a word in the trie.
        if (current->end == true)
            return 2;

        // String str exists as the prefix of a word that is possibly present.
        return 1;
    }
};

void SearchWord(int row, int col, Trie tr, string str, int& score, string& longest, int& numFound) {
    int ret = tr.Search(str);

    // see if the current string exists as the end of the word or the prefix of a word that is possibly present.
    if (ret != 0) {
        // is the current string a word in the dictionary?
        if (ret == 2) {
            // add to the score, update longest and num found (if not seen in the set of course)
            if (!seenWords.count(str)) {
                //cout << "Found : " << str << endl;
                seenWords.insert(str);
                numFound++;
                if (str.length() > longest.length()) longest = str;
                // get the lexicographically smallest one if equal
                else if (str.length() == longest.length()) {
                    if (str < longest) longest = str;
                }
                if (str.length() == 3 || str.length() == 4) score += 1;
                else if (str.length() == 5) score += 2;
                else if (str.length() == 6) score += 3;
                else if (str.length() == 7) score += 5;
                else if (str.length() == 8) score += 11;
            }
        }

        // visit all the characters from top and bottom rows and left and right columns
        for (int r = row-1; r <= row+1; r++) {
            for (int c = col-1; c <= col+1; c++) {
                if (r >= 0 && r < 4 && c >= 0 && c < 4 && visited[r][c] == false) {
                    visited[r][c] = true;
                    str.push_back(boggle[r][c]);
                    SearchWord(r, c, tr, str, score, longest, numFound);
                    str.pop_back();
                    visited[r][c] = false;
                }
            }
        }
    }
}

int main() {
    int w, i, j;
    cin >> w;
    Trie boggleDict;

    string word, line, row;
    for (i=0;i<w;i++) {
        cin >> word;
        boggleDict.Insert(word);
    }

    getline(cin, line);
    int numBoggles;
    cin >> numBoggles;
    while (numBoggles--) {
        //cout << "NEW BOGGLE!\n";
        boggle.resize(4);
        visited.resize(4);

        // populate the boggle and visited grids
        for (i=0;i<4;i++) {
            boggle[i].resize(4);
            visited[i].resize(4);
            cin >> row;
            for (j=0;j<4;j++) {
                boggle[i][j] = row.at(j);
                visited[i][j] = false;
            }
        }

        // run DFS on the grid, recording the max score, longest word, and # found words
        int score = 0, numFound = 0;
        string longest = "";
        for (int r = 0; r < 4; r++) {
            string curr = "";
            for (int c = 0; c < 4; c++) {
                visited[r][c] = true;
                curr.push_back(boggle[r][c]);
                SearchWord(r, c, boggleDict, curr, score, longest, numFound);
                curr.pop_back();
                visited[r][c] = false;
            }
        }

        cout << score << " " << longest << " " << numFound << "\n";

        // get newline, reset vectors
        if (numBoggles != 0) getline(cin, line);
        boggle.clear();
        visited.clear();
        seenWords.clear();
    }
}