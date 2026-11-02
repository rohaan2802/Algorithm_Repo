#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
#include<algorithm>
using namespace std;

const long long MOD4 = 1000000007LL;
const long long BASE4 = 257LL;

bool hasRepeatedOfLength(const string& s, int L) {
    if (L == 0) return true;
    int n = (int)s.size();
    if (L > n) return false;

    long long hashVal = 0;
    long long power = 1;

    for (int i = 0; i < L - 1; i++)
        power = (power * BASE4) % MOD4;

    unordered_set<long long> seen;
    seen.reserve(max(1, n - L + 1) * 2);

    for (int i = 0; i < L; i++) {
        hashVal = (hashVal * BASE4 + (unsigned char)s[i]) % MOD4;
    }
    seen.insert(hashVal);

    for (int i = L; i < n; i++) {
        long long left = (unsigned char)s[i - L];
        long long right = (unsigned char)s[i];
        hashVal = (hashVal - (left * power) % MOD4 + MOD4) % MOD4;
        hashVal = (hashVal * BASE4 + right) % MOD4;

        if (seen.count(hashVal)) {
            return true;
        }
        seen.insert(hashVal);
    }

    return false;
}

int longestRepeatedSubstringLength(const string& s) {
    int low = 0;
    int high = (int)s.size();
    int best = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (hasRepeatedOfLength(s, mid)) {
            best = mid;
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return best;
}

int main() {
   

    cout << "===== LONGEST REPEATED SUBSTRING (Divide & Conquer + Rolling Hash) =====\n\n";

    cout << "Enter a string: ";
    string s;
    if (!getline(cin, s)) return 0;

    cout << "\nProcessing...\n\n";

    int ans = longestRepeatedSubstringLength(s);

    cout << "=============================================================\n";
    cout << "Longest repeated substring length: " << ans << "\n";
    cout << "=============================================================\n";

    return 0;
}
