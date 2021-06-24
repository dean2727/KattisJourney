#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int main() {
    map<string, int> definitions;
    map<int, string> getWord;
    string command = "", definition = "", arg = "", result = "";
    int num = 0, x = 0, y = 0;
    char symbol;

    while (cin >> command) {
        vector<char> symbols;
        vector<string> args;

        if (command == "def") {
            cin >> definition >> num;

            // if this definition was not seen before, just insert into maps
            if (definitions.find(definition) == definitions.end()) {
                definitions.insert(make_pair(definition, num));
            }

            // else, adjust the keys
            else {
                definitions[definition] = num;
                // need to find the previous value, remove it, then add new
                for (map<int, string>::iterator it = getWord.begin(); it != getWord.end(); it++) {
                    if (getWord[it -> first] == definition) {
                        getWord.erase(it -> first);
                        break;
                    }
                }
            }
            getWord.insert(make_pair(num, definition));
        }

        else if (command == "calc") {
            cin >> arg >> symbol;
            if (definitions.find(arg) == definitions.end()) {
                result = "unknown";
            }
            args.push_back(arg);
            //symbols.push_back(symbol);

            // cin >> arg >> symbol;
            // if (definitions.find(arg) == definitions.end()) {
            //     result = "unknown";
            // }
            // args.push_back(arg);

            while (symbol != '=') {
                symbols.push_back(symbol);
                cin >> arg >> symbol;
                if (definitions.find(arg) == definitions.end()) {
                    result = "unknown";
                }
                args.push_back(arg);
            }
            //symbols.push_back(symbol);

            // loop through the args and symbols, performing the operation (only if result isnt unknown yet)
            if (result != "unknown") {
                num = definitions[args[0]];
            }
            cout << args[0] << " ";
            for (int i = 1; i < args.size(); i++) {
                cout << symbols[i-1] << " " << args[i] << " ";
                if (result != "unknown") {
                    if (definitions.find(args[i]) == definitions.end()) {
                        result = "unknown";
                    }
                    else if (symbols[i-1] == '+') {
                        num += definitions[args[i]];
                    }
                    else {
                        num -= definitions[args[i]];
                    }
                }
            }

            if (result != "unknown") {
                if (getWord.find(num) == getWord.end()) {
                    result = "unknown";
                }
                else {
                    result = getWord[num];
                }
            }
            cout << "= " << result << endl;
            num = 0;
            result = "";
        }

        // remove all definitions if "clear" command
        else {
            definitions.clear();
            getWord.clear();
        }
    }
}
