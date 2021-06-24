#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <stack>
using namespace std;

map<string, set<string> > groups;

void tokenize(string const &str, const char delim,
 vector<string> &out) {
	size_t start;
	size_t end = 0;
	while ((start = str.find_first_not_of(delim, end)) != string::npos) {
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

int main() {
  string form, groupName, person, sequence;
  int numPeople;

  while (cin >> form) {
    if (form == "group") {
      cin >> groupName >> numPeople;
      set<string> group;
      while (numPeople--) {
        cin >> person;
        //cout << "DEBUG: " << person << endl;
        group.insert(person);
      }
      groups.insert(make_pair(groupName, group));
    }
    else {
      getline(cin, sequence);
      vector<string> parts;
      parts.push_back(form);

      const char delim = ' ';
      tokenize(sequence, delim, parts);

			// loop backwards through the parts, performing the operations
      set<string> result;
      bool interResultLeft = false, didOperation = false;

			int i = parts.size()-3, partLoc;
			while (i != -1) {
        //cout << "DEBUG: i = " << i << " part = " << parts[i] << "\n";
        if (parts[i] == "union"||parts[i] == "intersection"||parts[i] == "difference") {
          partLoc = i+1;
          set<string> lhs, rhs;

          // if the lhs was an intermediate result
          if (parts[partLoc+1] == " ") {
            //cout << "DEBUG: lefthand result. partloc = " << partLoc << "\n";
            interResultLeft = true;
            lhs = result;
            parts[partLoc] = " ";

            partLoc++;
            while (parts[partLoc] != " ") {
              partLoc++;
            }
            rhs = groups[parts[partLoc]];
            parts[partLoc] = " ";
          }
          // rhs is intermediate result
          else {
            //cout << "DEBUG: righthand result. partloc = " << partLoc << "\n";
            lhs = groups[parts[partLoc]];
            rhs = didOperation ? result : groups[parts[partLoc+1]];
            parts[partLoc] = " ";
            parts[partLoc + 1] = " ";
          }

          //cout << "\nDEBUG: lhs is\n";
          // for (set<string>::iterator it=lhs.begin();it!=lhs.end();it++) {
          //   cout << *it << " ";
          // }
          // //cout << "\nDEBUG: rhs is\n";
          // for (set<string>::iterator it=rhs.begin();it!=rhs.end();it++) {
          //   cout << *it << " ";
          // }

          result.clear();
          if (parts[i] == "union") {
            set_union(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), inserter(result, result.end()));
            //cout << "DEBUG: doing union\n";
          }
          else if (parts[i] == "intersection") {
            set_intersection(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), inserter(result, result.end()));
            //cout << "DEBUG: doing intersection\n";
          }
          else {
            set_difference(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), inserter(result, result.end()));
            //cout << "DEBUG: doing difference\n";
          }
          didOperation = true;
        }
				i--;
        interResultLeft = false;
			}

      //cout << "\nOk result is\n";
      set<string>::iterator it=result.begin();
      cout << *it;
      advance(it, 1);
      while (it != result.end()) {
        cout << " " << *it;
        advance(it, 1);
      }
      cout << "\n";
    }
  }
}
