#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

// string splitting from https://www.techiedelight.com/split-string-cpp-using-delimiter/
void tokenize(std::string const &str, const char delim,
            std::vector<std::string> &out)
{
    size_t start;
    size_t end = 0;
 
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

int main() {
    int ntc = 0;
    cin >> ntc;

    for (int i=0;i<ntc;i++) {
        string p = "";
        int n = 0;
        string ints = "";

        cin >> p;
        cin >> n;
        cin >> ints;

        list<int> integers;
        vector<string> tokens;
        const char delim = ',';
        tokenize(ints.substr(1, ints.length() - 2), delim, tokens);

        for (int j=0;j<tokens.size();j++) {
            //cout << tokens[j] << endl;
            integers.push_back(stoi(tokens[j]));
        }

        // perform list operations
        bool reversed = false;
        bool error = false;
        bool empty = false;
        //cout << "There are " << p.length() << " functions\n";
        for (int j=0;j<p.length();j++) {
            char function = p.at(j);
            //cout << "Function: " << function << endl;
            if (function == 'D') {
                //cout << "Size: " << integers.size() << endl;
                if (empty || integers.size() == 0) {
                    cout << "error" << endl;
                    error = true;
                    break;
                }
                else if (integers.size() == 1) {
                    empty = true;
                }
                else if (!reversed) {
                    integers.pop_front();
                }
                else {
                    integers.pop_back();
                }
            }

            else {
                reversed = reversed ? false : true;
            }
        }

        if (reversed) {
            integers.reverse();
        }

        if (!error) {
            cout << "[";
            if (empty || n == 0) {
                cout << "]\n";
            }
            else {
                int loops = integers.size() - 1;
                for (int j=0;j<loops;j++) {
                    cout << integers.front() << ",";
                    integers.pop_front();
                }
                cout << integers.front() << "]" << endl;
            }        
        }
    }
}