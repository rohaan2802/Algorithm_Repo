#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
#include<algorithm>
using namespace std;

const long long MOD2 = 1000000007LL;
const long long BASE2 = 257LL;

bool hasCommonOfLength(const string& A, const string& B, int L) {
    if (L == 0) return true;
    int n = (int)A.size();
    int m = (int)B.size();
    if (L > n || L > m) return false;

    long long hashA = 0;
    long long hashB = 0;
    long long power = 1;

    for (int i = 0; i < L - 1; i++)
        power = (power * BASE2) % MOD2;

    unordered_set<long long> seen;
    seen.reserve(max(1, n - L + 1) * 2);

    // Build rolling hash for A
    for (int i = 0; i < L; i++) {
        hashA = (hashA * BASE2 + (unsigned char)A[i]) % MOD2;
    }
    seen.insert(hashA);

    for (int i = L; i < n; i++) {
        long long left = (unsigned char)A[i - L];
        long long right = (unsigned char)A[i];
        hashA = (hashA - (left * power) % MOD2 + MOD2) % MOD2;
        hashA = (hashA * BASE2 + right) % MOD2;
        seen.insert(hashA);
    }

    // Build rolling hash for B and compare
    hashB = 0;
    for (int i = 0; i < L; i++) {
        hashB = (hashB * BASE2 + (unsigned char)B[i]) % MOD2;
    }
    if (seen.count(hashB)) return true;

    for (int i = L; i < m; i++) {
        long long left = (unsigned char)B[i - L];
        long long right = (unsigned char)B[i];
        hashB = (hashB - (left * power) % MOD2 + MOD2) % MOD2;
        hashB = (hashB * BASE2 + right) % MOD2;
        if (seen.count(hashB)) return true;
    }

    return false;
}

int maxCommonSubstringLength(const string& A, const string& B) {
    int low = 0;
    int high = (int)min(A.size(), B.size());
    int best = 0;

    // Divide & conquer on the substring length (binary search)
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (hasCommonOfLength(A, B, mid)) {
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string A, B;

    cout << "===== MAXIMUM COMMON SUBSTRING FINDER =====\n\n";

    cout << "Enter Document A:\n";
    if (!getline(cin, A)) return 0;

    cout << "\nEnter Document B:\n";
    if (!getline(cin, B)) return 0;

    cout << "\nProcessing...\n\n";

    int ans = maxCommonSubstringLength(A, B);

    cout << "===========================================\n";
    cout << "Maximum common substring length: " << ans << "\n";
    cout << "===========================================\n";

    return 0;
}
