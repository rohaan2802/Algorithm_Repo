#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

// ---------- Naive search ----------
vector<int> naiveSearch(const string& text, const string& pattern) {
    vector<int> pos;
    int n = (int)text.size();
    int m = (int)pattern.size();
    if (m == 0 || n < m) return pos;

    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j]) j++;
        if (j == m) pos.push_back(i);
    }
    return pos;
}

// ---------- KMP helpers ----------
vector<int> buildLPS(const string& pat) {
    int m = (int)pat.size();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;

    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> pos;
    int n = (int)text.size();
    int m = (int)pattern.size();
    if (m == 0 || n < m) return pos;

    vector<int> lps = buildLPS(pattern);
    int i = 0, j = 0;

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++; j++;
            if (j == m) {
                pos.push_back(i - j);
                j = lps[j - 1];
            }
        }
        else {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return pos;
}

// ---------- Rabin–Karp with fallback ----------
const long long MOD = 1000000007LL;
const long long BASE = 257LL;

vector<int> rabinKarpWithFallback(const string& text,
    const string& pattern,
    bool& usedKMP) {

    int n = (int)text.size();
    int m = (int)pattern.size();
    vector<int> ans;
    if (m == 0 || n < m) return ans;

    long long hashP = 0, hashT = 0, power = 1;

    for (int i = 0; i < m - 1; i++)
        power = (power * BASE) % MOD;

    for (int i = 0; i < m; i++) {
        hashP = (hashP * BASE + (unsigned char)pattern[i]) % MOD;
        hashT = (hashT * BASE + (unsigned char)text[i]) % MOD;
    }

    long long collisionCount = 0;
    long long threshold = max(5LL, 2LL * (long long)sqrt((long double)n));

    for (int i = 0; i <= n - m; i++) {
        if (hashT == hashP) {
            bool same = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    same = false;
                    break;
                }
            }
            if (same) ans.push_back(i);
            else {
                collisionCount++;
                if (collisionCount > threshold) {
                    usedKMP = true;
                    return kmpSearch(text, pattern);
                }
            }
        }

        if (i < n - m) {
            long long left = (unsigned char)text[i];
            long long right = (unsigned char)text[i + m];

            hashT = (hashT - (left * power) % MOD + MOD) % MOD;
            hashT = (hashT * BASE + right) % MOD;
        }
    }

    usedKMP = false;
    return ans;
}

// ---------- Helper ----------
int estimateAlphabetSize(const string& s) {
    bool seen[256] = { false };
    int cnt = 0;
    for (unsigned char c : s) {
        if (!seen[c]) {
            seen[c] = true;
            cnt++;
        }
    }
    return cnt;
}

// ---------- Decision Logic ----------
string chooseAlgorithm(const string& text, const string& pattern, int numPatterns) {
    int n = (int)text.size();
    int m = (int)pattern.size();
    if (m == 0 || n == 0) return "NAIVE";

    long long work = 1LL * n * m;

    if (m <= 3) return "NAIVE";      // Very small pattern
    if (work <= 300LL) return "NAIVE"; // Tiny workload

    int sigma = estimateAlphabetSize(text);
    if (sigma <= 4) return "KMP";    // Small alphabet -> repetitive -> KMP best

    if (numPatterns > 1 && m >= 4)
        return "RK";                 // Multi-pattern scenario

    return "RK";                      // Default
}

// ---------- Main Program ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "===== HYBRID MULTI-ALGORITHM STRING MATCHER =====\n\n";

    // Input text
    cout << "Enter the main text:\n";
    string text;
    if (!getline(cin, text)) return 0;

    // Input patterns
    int k;
    cout << "\nEnter number of patterns: ";
    if (!(cin >> k)) return 0;

    string dummy;
    getline(cin, dummy);

    vector<string> patterns;

    cout << "\nEnter " << k << " patterns:\n";
    for (int i = 0; i < k; i++) {
        cout << "Pattern " << i + 1 << ": ";
        string pattern;
        getline(cin, pattern);
        patterns.push_back(pattern);
    }

    cout << "\n===== MATCHING RESULTS =====\n\n";

    // Process patterns
    for (int i = 0; i < k; i++) {
        string pattern = patterns[i];

        string algo = chooseAlgorithm(text, pattern, k);
        vector<int> result;
        bool usedKMPinsideRK = false;

        if (algo == "NAIVE") {
            result = naiveSearch(text, pattern);
            cout << "Pattern " << i + 1 << " -> Algorithm Used: Naive\n";
        }
        else if (algo == "KMP") {
            result = kmpSearch(text, pattern);
            cout << "Pattern " << i + 1 << " -> Algorithm Used: KMP\n";
        }
        else {
            result = rabinKarpWithFallback(text, pattern, usedKMPinsideRK);

            if (usedKMPinsideRK)
                cout << "Pattern " << i + 1 << " -> Algorithm Used: Rabin-Karp (Auto-switched to KMP)\n";
            else
                cout << "Pattern " << i + 1 << " -> Algorithm Used: Rabin-Karp\n";
        }

        cout << "Matches found at indices: ";
        if (result.empty()) cout << "none";
        else {
            for (int p : result) cout << p << " ";
        }
        cout << "\n---------------------------\n";
    }

    return 0;
}
