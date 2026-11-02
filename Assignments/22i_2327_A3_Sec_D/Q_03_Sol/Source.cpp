#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
#include<algorithm>
#include<queue>
using namespace std;

struct Node {
    int next[26];
    int link;
    vector<int> out;
    Node() {
        fill(next, next + 26, -1);
        link = -1;
    }
};

vector<Node> trie;
vector<string> patterns;

int getIndex(char c) {
    if ('A' <= c && c <= 'Z') c = char(c - 'A' + 'a');
    if ('a' <= c && c <= 'z') return c - 'a';
    return -1;
}

void addPattern(const string& pat, int id) {
    int v = 0;
    for (char ch : pat) {
        int idx = getIndex(ch);
        if (idx == -1) continue;
        if (trie[v].next[idx] == -1) {
            trie[v].next[idx] = (int)trie.size();
            trie.push_back(Node());
        }
        v = trie[v].next[idx];
    }
    trie[v].out.push_back(id);
}

void buildAutomaton() {
    queue<int> q;
    trie[0].link = 0;

    for (int c = 0; c < 26; c++) {
        int u = trie[0].next[c];
        if (u != -1) {
            trie[u].link = 0;
            q.push(u);
        }
        else {
            trie[0].next[c] = 0;
        }
    }

    while (!q.empty()) {
        int v = q.front(); q.pop();
        int link = trie[v].link;

        for (int x : trie[link].out)
            trie[v].out.push_back(x);

        for (int c = 0; c < 26; c++) {
            int u = trie[v].next[c];
            if (u != -1) {
                trie[u].link = trie[link].next[c];
                q.push(u);
            }
            else {
                trie[v].next[c] = trie[link].next[c];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;

    cout << "Enter number of patterns: ";
    if (!(cin >> k)) return 0;

    string dummy;
    getline(cin, dummy); // clear leftover newline

    patterns.assign(k, "");
    trie.clear();
    trie.push_back(Node());

    cout << "\nEnter " << k << " patterns (one per line):\n";
    for (int i = 0; i < k; i++) {
        cout << "Pattern " << i + 1 << ": ";
        string pat;
        getline(cin, pat);
        patterns[i] = pat;
        addPattern(pat, i);
    }

    cout << "\nEnter the text to search in:\n";
    string text;
    getline(cin, text);

    cout << "\nBuilding automaton...\n";
    buildAutomaton();

    cout << "Searching...\n\n";

    vector<vector<int>> positions(k);

    int v = 0;
    for (int i = 0; i < (int)text.size(); i++) {
        char ch = text[i];
        int idx = getIndex(ch);
        if (idx == -1) {
            v = 0;
            continue;
        }
        v = trie[v].next[idx];
        for (int id : trie[v].out) {
            int len = (int)patterns[id].size();
            int start = i - len + 1;
            positions[id].push_back(max(start, 0));
        }
    }

    cout << "===== MATCH RESULTS =====\n\n";

    for (int i = 0; i < k; i++) {
        cout << "Pattern " << i + 1 << " (\"" << patterns[i] << "\") matches at: ";
        if (positions[i].empty()) {
            cout << "none\n";
        }
        else {
            for (int p : positions[i]) cout << p << " ";
            cout << "\n";
        }
    }

    return 0;
}
