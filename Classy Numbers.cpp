/*
Let's call some positive integer classy if its decimal representation contains no more than 3non-zero digits. 

For example, numbers 4, 200000, 10203 are classy and numbers 4231, 102306, 7277420000 are not.

You are given a segment [L;R]. Count the number of classy integers x such that L≤x≤R.

Each testcase contains several segments, for each of them you are required to solve the problem separately.

Input
The first line contains a single integer T(1≤T≤104) — the number of segments in a testcase.

Each of the next T lines contains two integers Li and Ri(1≤Li≤Ri≤1018).

Output
Print T lines — the i-th line should contain the number of classy integers on a segment [Li;Ri].

Input:
4
1 1000
1024 1024
65536 65536
999999 1000001

Output:
1000
1
0
2
*/

#include <bits/stdc++.h>
using namespace std;
 
class Solution {
public:
    long long dp[20][2][4];
 
    long long solve(string &s, int idx, int tight, int count) {
        if (count > 3) return 0;
        if (idx == s.size()) return 1;
 
        long long &res = dp[idx][tight][count];
        if (res != -1) return res;
 
        int limit = tight ? (s[idx] - '0') : 9;
        res = 0;
 
        for (int digit = 0; digit <= limit; digit++) {
            res += solve(
                s,
                idx + 1,
                tight && (digit == (s[idx] - '0')),
                count + (digit != 0)
            );
        }
 
        return res;
    }
 
    long long countDigitOne(long long lo, long long ro) {
        if (ro < 0) return 0;
 
        if (lo == 0) {
            string r = to_string(ro);
            memset(dp, -1, sizeof(dp));
            return solve(r, 0, 1, 0);
        }
 
        string l = to_string(lo - 1);
        string r = to_string(ro);
 
        memset(dp, -1, sizeof(dp));
        long long left = solve(l, 0, 1, 0);
 
        memset(dp, -1, sizeof(dp));
        long long right = solve(r, 0, 1, 0);
 
        return right - left;
    }
};
 
int main() {
    int t;
    cin >> t;
    Solution obj;
 
    while (t--) {
        long long L, R;
        cin >> L >> R;
        cout << obj.countDigitOne(L, R) << "\n";
    }
    return 0;
}
