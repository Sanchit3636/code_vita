#include<bits/stdc++.h>
using namespace std;

int solve(vector<string>& instructions) {
    int n = instructions.size();
    unordered_map<string, int> tileMap = {
        {"up", 0}, 
        {"down", 1}, 
        {"left", 2}, 
        {"right", 3}
    };
    
    vector<vector<vector<int>>> dp(n + 1, 
            vector<vector<int>>(4, 
            vector<int>(4, INT_MAX)
        )
    );
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j){
                dp[0][i][j] = 0;
            }
        }
    }
    
    for (int step = 0; step < n; step++) {
        int target = tileMap[instructions[step]]; 
        for (int left = 0; left < 4; left++) {
            for (int right = 0; right < 4; right++) {
                if (dp[step][left][right] == INT_MAX){
                    continue;
                }
                
                if (left != target) {
                    dp[step + 1][target][right] = min(dp[step + 1][target][right], dp[step][left][right] + 1);
                } 
                else {
                    dp[step + 1][left][right] = min(dp[step + 1][left][right], dp[step][left][right]);
                }
                
                if (right != target) {
                    dp[step + 1][left][target] = min(dp[step + 1][left][target], dp[step][left][right] + 1);
                } 
                else {
                    dp[step + 1][left][right] = min(dp[step + 1][left][right], dp[step][left][right]);
                }
            }
        }
    }
    
    int minMovements = INT_MAX;
    for (int left = 0; left < 4; left++) {
        for (int right = 0; right < 4; right++) {
            minMovements = min(minMovements, dp[n][left][right]);
        }
    }
    
    return minMovements;
}

int main() {
    int N;
    cin >> N;
    vector<string> instructions(N);
    for (int i = 0; i < N; i++) {
        cin >> instructions[i];
    }
    
    cout << solve(instructions) << endl;
    return 0;
}
