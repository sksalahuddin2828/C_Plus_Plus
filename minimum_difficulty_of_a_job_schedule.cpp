#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int minDifficulty(std::vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();
        if (n < d) {
            return -1;
        }

        std::vector<std::vector<int>> memo(n, std::vector<int>(d + 1, -1));

        return dp(jobDifficulty, 0, d, memo);
    }

    int dp(std::vector<int>& jobDifficulty, int i, int d, std::vector<std::vector<int>>& memo) {
        if (d == 1) {
            int maxDifficulty = INT_MIN;
            for (int j = i; j < jobDifficulty.size(); j++) {
                maxDifficulty = std::max(maxDifficulty, jobDifficulty[j]);
            }
            return maxDifficulty;
        }

        if (i == jobDifficulty.size() - 1) {
            return INT_MAX;
        }

        if (memo[i][d] != -1) {
            return memo[i][d];
        }

        int curDifficulty = jobDifficulty[i];
        int minDifficulty = INT_MAX;

        for (int j = i; j < jobDifficulty.size() - d + 1; j++) {
            curDifficulty = std::max(curDifficulty, jobDifficulty[j]);
            int change = curDifficulty + dp(jobDifficulty, j + 1, d - 1, memo);
            minDifficulty = std::min(minDifficulty, change);
        }

        memo[i][d] = minDifficulty;
        return minDifficulty;
    }
};

int main() {
    std::vector<int> jobDifficulty = {6, 5, 4, 3, 2, 1};
    int days = 2;

    Solution solution;
    int result = solution.minDifficulty(jobDifficulty, days);

    std::cout << "Minimum difficulty: " << result << std::endl;

    return 0;
}
