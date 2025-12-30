/*
A G-One number is a number sum of whose digits is a prime number
For example 12 .. sum = 1+2 = 3 ... 3 is a prime number.

You will be given the range of population and you have to tell how many in this range are G-One Numbers.

Input:
3
10 19
1 9
20 29

Output:
4
4
5
Note: c will be less than 100
t and f will be less than 10^8 inclusive
*/

#include <bits/stdc++.h>

using namespace std;
class Solution {
    public: long long dp[10][2][100];
    vector < bool > prime;

    Solution() {
        prime.assign(200, true);
        prime[0] = prime[1] = false;
        for (int i = 2; i * i < 200; i++) {
            if (prime[i]) {
                for (int j = i * i; j < 200; j += i)
                    prime[j] = false;
            }
        }

    }
    long long solve(string & s, int idx, int tight, int count) {
        if (idx == s.size()) {
            return prime[count];
        }
        if (dp[idx][tight][count] != -1)
            return dp[idx][tight][count];

        int limit = tight ? (s[idx] - '0') : 9;
        long long ans = 0;
        for (int digit = 0; digit <= limit; digit++) {
            ans += solve(
                s,
                idx + 1,
                tight && (digit == s[idx] - '0'),
                count + digit
            );
        }

        return dp[idx][tight][count] = ans;
    }
    long long countDigitOne(long long lo, long long ro) {
        if (ro < 0) return 0;
        if (lo == 0) {
            string r = to_string(ro);
            memset(dp, -1, sizeof(dp));
            return solve(r, 0, 1, 0);
        }
        string left = to_string(lo - 1);
        memset(dp, -1, sizeof(dp));
        int l = solve(left, 0, 1, 0);

        string right = to_string(ro);
        memset(dp, -1, sizeof(dp));
        int r = solve(right, 0, 1, 0);

        return r - l;
    }
};

int main() {
    // your code goes here
    int n;
    cin >> n;
    while (n--) {
        long long left, right;
        cin >> left >> right;
        Solution obj;
        cout << obj.countDigitOne(left, right) << "\n";
    }
    return 0;
}
