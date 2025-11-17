#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cctype>
using namespace std;

// --------------------------------------
string toLower(const string &s) {
    string r = s;
    for (char &c : r) c = tolower(c);
    return r;
}

// --------------------------------------
bool isProperNoun(const string &word, char prevChar) {
    if (!isupper(word[0])) return false;
    if (prevChar == '.' || prevChar == '!' || prevChar == '?')
        return false;
    return true;
}

// --------------------------------------
vector<pair<string, char>> extractWords(const string &line) {
    vector<pair<string, char>> words;  

    int n = line.size();
    for (int i = 0; i < n; ) {
        if (isalpha(line[i])) {
            int start = i;
            string w = "";
            while (i < n && isalpha(line[i])) {
                w += line[i];
                i++;
            }

            char prev = ' ';
            int p = start - 1;
            while (p >= 0 && isspace(line[p])) p--;
            if (p >= 0) prev = line[p];

            words.push_back({w, prev});
        } else {
            i++;
        }
    }
    return words;
}

// --------------------------------------
int main() {
    ifstream fstop("stopw.txt");
    ifstream ftext("Alice30.txt");

    if (!fstop || !ftext) {
        cout << "Khong mo duoc file!" << endl;
        return 1;
    }

    set<string> stopWords;
    string w;
    while (fstop >> w) stopWords.insert(toLower(w));

    map<string, set<int>> indexTable;

    string line;
    int lineNum = 0;

    while (getline(ftext, line)) {
        lineNum++;

        auto words = extractWords(line);

        for (auto &[word, prevChar] : words) {
            string lw = toLower(word);

            if (stopWords.count(lw)) continue;
            if (isProperNoun(word, prevChar)) continue;

            indexTable[lw].insert(lineNum);
        }
    }

    for (auto &p : indexTable) {
        cout << p.first << "    ";
        bool first = true;
        for (int ln : p.second) {
            if (!first) cout << ", ";
            first = false;
            cout << ln;
        }
        cout << "\n";
    }

    return 0;
}
