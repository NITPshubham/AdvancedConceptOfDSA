/*
Any number is Ra-one 
if the Difference between Sum of digits at even location and Sum of digits at odd location is One (1).

For eg... for 234563 is Ra-One number

digits at odd location are 3,5,3 (unit place is location 1 )
digits at even location are 2,4,6

Diff = (2+4+6)-(3+5+3)=12-11 = 1.

And 123456 is not Ra-One number
diff = (5+3+1) - (2+4+6) = -4
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static const int OFFSET = 100;
    long long dp[12][2][205];
    string s;

    long long dfs(int pos, int tight, int diff) {
        if (pos == s.size())
            return diff == 1;

        long long &res = dp[pos][tight][diff + OFFSET];
        if (res != -1) return res;

        res = 0;
        int limit = tight ? (s[pos] - '0') : 9;
        int len = s.size();

        for (int d = 0; d <= limit; d++) {
            int newDiff = diff;

            int remaining = len - pos;
            if (remaining % 2 == 0)
                newDiff += d;   // even position
            else
                newDiff -= d;   // odd position

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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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
