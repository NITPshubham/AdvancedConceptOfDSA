Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.

Example 1:
Input: n = 13
Output: 6

Example 2:
Input: n = 0
Output: 0

Constraints:
0 <= n <= 109

Code:

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
long long dp[12][2][12];
long long solve(string &s, int idx, int tight, int count) {
        if (idx == s.size()){
            return count;
        }

        if (dp[idx][tight][count] != -1) 
            return dp[idx][tight][count];

        int limit = tight ? (s[idx] - '0') : 9;
        int res = 0;
        for (int d = 0; d <= limit; d++) {
            int newcount = count + (d == 1);

            res += solve(s, idx + 1, tight && (d == limit), newcount);
        }
        return dp[idx][tight][count] = res;
    }
    int countDigitOne(int n) {
        if (n < 0) 
            return 0;
        string s = to_string(n);
        memset(dp, -1, sizeof(dp));
        return solve(s, 0, 1, 0);
    }
};

int main() {
    int t;
    cin >> t;
    Solution obj;

    while (t--) {
        long long N;
        cin >> N;
        cout << obj.solve(N) << "\n";
    }
    return 0;
}
