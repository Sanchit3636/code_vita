#include<bits/stdc++.h>
using namespace std;

int Knapsack(int W, vector<int>& weights, vector<int>& values, int n){
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));

    for(int i = 1;i <= n;i++){
        for(int w = 1;w <= W;w++){
            if(weights[i-1] <= w){
                dp[i][w] = max(dp[i-1][w], dp[i-1][w-weights[i-1]] + values[i-1]);
            }
            else{
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    return dp[n][W];
}

int main(){
    int W, n;

    cout<<"Enter the number of Items: ";
    cin >> n;

    cout<<"Enter the maximum Weight of the Knapsack: ";
    cin >> W;

    vector<int> values(n);
    vector<int> weights(n);

    cout<<"Enter the values of the items : ";
    for(int i = 0;i < n;i++){
        cin >> values[i];
    }

    cout<<"Enter the weights of the items: ";
    for(int i = 0;i < n;i++){
        cin >> weights[i];
    }

    int result = Knapsack(W, weights, values, n);
    cout<<"Maximum Value that can be obtained: "<<result<<endl;
}