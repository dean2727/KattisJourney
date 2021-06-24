#include <iostream>
#include <vector>
using namespace std;

// Prints occurrences of txt[] in pat[]
bool KMPSearch(string pat, string txt)
{
    int M = pat.length();
    int N = txt.length();
  
    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];
  
    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);
  
    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {
        if (pat.at(j) == txt.at(i)) {
            j++;
            i++;
        }
  
        if (j == M) {
            return true;
            //printf("Found pattern at index %d ", i - j);
            //j = lps[j - 1];
        }
  
        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return false;
}
  
// Fills lps[] for given patttern pat[0..M-1]
void computeLPSArray(string pat, int M, int* lps)
{
    // length of the previous longest prefix suffix
    int len = 0;
  
    lps[0] = 0; // lps[0] is always 0
  
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat.at(i) == pat.at(len)) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0) {
                len = lps[len - 1];
  
                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

bool patternInWord(vector<string> pattern, const vector<string>& words) {
    
}

int main() {
    int n, i;
    cin >> n;
    string word;
    vector<string> words;
    for (i=0;i<n;i++) {
        cin >> word;
        words.push_back(word);
    }
    string pattern;
    cin >> pattern;

    // see if the pattern as a whole is in any of the words. if not, see if the first letter of the pattern
    // and the rest of it is in the words. if not, see if the first 2 letters and the rest are in..etc.
    vector<string> patterns = {pattern};
    int subStringLength
    while (!patternInWord(patterns, words)) {

    }
    cout << 
}