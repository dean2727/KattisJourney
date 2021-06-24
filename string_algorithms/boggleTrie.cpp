// https://algotree.org/algorithms/trie/trie_dfs_boggle/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

class TrieNode {

    public:

    TrieNode * children[26];
    bool end_of_word;
    char letter;

    TrieNode () {

        end_of_word = false;
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
    void Insert (string str) {

        TrieNode * current = &root;

        for (size_t i = 0; i < str.size(); i++) {
            if (current->children[str.at(i)-'A'] == NULL) {
                current->children[str.at(i)-'A'] = new TrieNode;
                current->children[str.at(i)-'A']->letter = str.at(i);
            }
            current = current->children[str.at(i)-'A'];
        }
        current->end_of_word = true;
    }

    // Search the word in trie
    int Search (string str) {

        TrieNode * current = &root;

        for (size_t i = 0; i < str.size(); i++) {

            if (current->children[str.at(i)-'A'] != NULL) {
                current = current->children[str.at(i)-'A'];
            } else {
                return 0;
            }
        }

        //Check if string 'str' exists as a word in the trie.
        if (current->end_of_word == true)
            return 2;

        //String str exists as the prefix of a word that is possibly present.
        return 1;
    }
};

class Boggle {

    private:

    vector<vector<char>> grid;
    vector<vector<bool>> visited;
    string current_str;
    Trie wordtrie;

    public:

    Boggle() {}

    Boggle (vector<vector<char>> arg_grid, Trie& arg_trie) {

        wordtrie = arg_trie;
        grid = arg_grid;
        visited.resize(grid.size());

        for (auto& v: visited)
            v.resize(grid[0].size());
    }

    void SearchWord (int row, int col) {

        int ret = wordtrie.Search(current_str);

        // Check if the current string exists as the end of the word or the prefix of a word that is possibly present.
        if (ret != 0) {
            // For the current string, the end of the word was set to true
            if (ret == 2) {
                cout << "Found : " << current_str << endl;
            }
            // Visit all the eight characters from top and bottom row and left and right column.
            for (int r = row-1; r <= row+1; r++) {
                for (int c = col-1; c <= col+1; c++) {
                    if (r >= 0 and r < grid.size() and c >= 0 and c < grid[0].size() and visited[r][c] == false) {
                        visited[r][c] = true;
                        current_str.push_back(grid[r][c]);
                        SearchWord(r, c);
                        current_str.pop_back();
                        visited[r][c] = false;
                    }
                }
            }
        }
    }

    // Search if a word can be formed from every character in a grid.
    void TraverseGrid () {
        for (int row = 0; row < grid.size(); row++) {
            current_str = "";
            for (int col = 0; col < grid[0].size(); col++) {
                visited[row][col] = true;
                current_str.push_back(grid[row][col]);
                SearchWord (row, col);
                current_str.pop_back();
                visited[row][col] = false;
            }
        }
    }
};

int main() {

    // C++11 Initialize two dimensional vector 
    vector<vector<char>> grid { { 'A', 'L', 'G', 'N', 'E' },
                                { 'T', 'E', 'O', 'D', 'L' },
                                { 'E', 'R', 'T', 'D', 'T' },
                                { 'O', 'U', 'F', 'Y', 'A' },
                                { 'F', 'U', 'S', 'E', 'R' } };
    Trie wordtrie;

    wordtrie.Insert("ROCK");
    wordtrie.Insert("LEGO");
    wordtrie.Insert("DUGEE");
    wordtrie.Insert("ALGOTREE");
    wordtrie.Insert("ATE");
    wordtrie.Insert("FUSE");
    wordtrie.Insert("TALE");
    wordtrie.Insert("TOFU");
    wordtrie.Insert("DELTA");
    wordtrie.Insert("NODDY");
    wordtrie.Insert("TAR");
    wordtrie.Insert("TRUE");
    wordtrie.Insert("POCKETS");

    Boggle b(grid, wordtrie);
    b.TraverseGrid();

    return 0;
}