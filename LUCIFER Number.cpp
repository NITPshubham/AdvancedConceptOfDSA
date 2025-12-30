/*
Any number is LUCIFER NUMBER if the difference between sum of digits at even location and sum of digits at odd location is prime number.

For example, 20314210 is a Lucifer number:

digits at odd location 0, 2, 1, 0.
digits at even location 1, 4, 3, 2.

difference = (1+4+3+2)-(0+2+1+0) = 10-3 = 7 ... a prime number.
*/

#include <bits/stdc++.h>

using namespace std;

static
const int OFFSET = 100;
long long dp[12][2][205];
string s;

class Solution {
    public: vector < bool > prime;
    Solution() {
        prime.assign(205, true);
        prime[0] = prime[1] = false;
        for (int i = 2; i * i < 205; i++) {
            if (prime[i]) {
                for (int j = i * i; j <= 205; j += i) {
                    prime[j] = false;
                }
            }
        }
    }

    long long dfs(int pos, int tight, int diff) {
        if (pos == s.size()){
            if(diff >= 0)
                return prime[diff] == true;
            return false;
        }

        long long & res = dp[pos][tight][diff + OFFSET];
        if (res != -1) return res;

        res = 0;
        int limit = tight ? (s[pos] - '0') : 9;
        int len = s.size();

        for (int d = 0; d <= limit; d++) {
            int newDiff = diff;

            int remaining = len - pos;
            if (remaining % 2 == 0)
                newDiff += d; // even position
            else
                newDiff -= d; // odd position

            res += dfs(
                pos + 1,
                tight && (d == limit),
                newDiff
            );
        }
        return res;
    }

    long long countRaOne(long long x) {
        if (x < 0) return 0;
        s = to_string(x);
        memset(dp, -1, sizeof(dp));
        return dfs(0, 1, 0);
    }

    long long solve(long long L, long long R) {
        return countRaOne(R) - countRaOne(L - 1);
    }
};

int main() {
    int t;
    cin >> t;
    Solution obj;

    while (t--) {
        long long L, R;
        cin >> L >> R;
        cout << obj.solve(L, R) << "\n";
    }
    return 0;
}
