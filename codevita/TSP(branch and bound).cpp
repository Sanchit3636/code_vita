// #include<bits/stdc++.h>
// using namespace std;

// int findMinEdge(int city, vector<vector<int>>& costMatrix, int n){
//     int minCost = INT_MAX;

//     for(int i = 0;i < n;i++){
//         if(costMatrix[city][i] != -1 && costMatrix[city][i] < minCost){
//             minCost = costMatrix[city][i];
//         }
//     }

//     return minCost;
// }

// int calculateLowerBound(vector<vector<int>>& costMatrix, vector<bool>& visited, int n){
//     int lowerBound = 0;

//     for(int i = 0;i < n;i++){
//         if(!visited[i]){
//             lowerBound += findMinEdge(i, costMatrix, n);
//         }
//     }

//     return lowerBound;
// }


// void tspBranchAndBound(vector<vector<int>>& costMatrix, int n){
//     int minCost = INT_MAX;

//     vector<int> bestPath;
//     queue<pair<int, vector<int>>> q;

//     vector<int> initialPath = {0};
//     q.push({0, initialPath});

//     while(!q.empty()){
//         int currentCost = q.front().first;
//         vector<int> currentPath = q.front().second;

//         q.pop();

//         int currentCity = currentPath.back();

//         if(currentPath.size() == n){
//             currentCost += costMatrix[currentCity][0];
//             if(currentCost < minCost){
//                 minCost = currentCost;
//                 bestPath = currentPath;

//                 bestPath.push_back(0);
//             }
//             continue;
//         }
        
//         for(int i = 0;i < n;i++){
//             if(find(currentPath.begin(), currentPath.end(), i) == currentPath.end()){
//                 int nextCost = currentCost + costMatrix[currentCity][i];

//                 vector<int> nextPath = currentPath;

//                 nextPath.push_back(i);

//                 vector<bool> visited(n, false);

//                 for(auto city : nextPath){
//                     visited[city] = true;
//                 }

//                 int lowerBound = nextCost + calculateLowerBound(costMatrix, visited, n);

//                 if(lowerBound < minCost){
//                     q.push({nextCost, nextPath});
//                 }
//             }
//         }
//     }

//     cout<<"Minimum Cost : "<<minCost<<endl;
//     cout<<"Best Path : ";

//     for(int city : bestPath){
//         cout<<city<<" ";
//     }
//     cout<<endl;
// }

// int main(){
//     vector<vector<int>> costMatrix = {
//         { -1,  10,  15,  20 },
//         { 10,  -1,  35,  25 },
//         { 15,  35,  -1,  30 },
//         { 20,  25,  30,  -1 }
//     };

//     int n = costMatrix.size();

//     tspBranchAndBound(costMatrix, n);

//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

// Function to reduce a matrix and calculate the reduction cost
int reduceMatrix(vector<vector<int>>& matrix, int n) {
    int reductionCost = 0;

    // Row Reduction
    for (int i = 0; i < n; i++) {
        int rowMin = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != -1) {
                rowMin = min(rowMin, matrix[i][j]);
            }
        }
        if (rowMin != INT_MAX && rowMin > 0) {
            reductionCost += rowMin;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] != -1) {
                    matrix[i][j] -= rowMin;
                }
            }
        }
    }

    // Column Reduction
    for (int j = 0; j < n; j++) {
        int colMin = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] != -1) {
                colMin = min(colMin, matrix[i][j]);
            }
        }
        if (colMin != INT_MAX && colMin > 0) {
            reductionCost += colMin;
            for (int i = 0; i < n; i++) {
                if (matrix[i][j] != -1) {
                    matrix[i][j] -= colMin;
                }
            }
        }
    }

    return reductionCost;
}

// Function to create a new reduced matrix for a specific branch
vector<vector<int>> createReducedMatrix(vector<vector<int>> matrix, int from, int to, int n) {
    for (int i = 0; i < n; i++) {
        matrix[from][i] = -1; // Invalidate the row
        matrix[i][to] = -1;   // Invalidate the column
    }
    matrix[to][from] = -1;   // Prevent returning to the same node
    return matrix;
}

// Branch and Bound for TSP
void tspBranchAndBound(vector<vector<int>>& costMatrix, int n) {
    int minCost = INT_MAX;
    vector<int> bestPath;

    // Priority queue to store states (sorted by lower bound cost)
    priority_queue<pair<int, pair<int, vector<int>>>, vector<pair<int, pair<int, vector<int>>>>, greater<>> pq;

    // Initial reduced matrix and cost
    vector<vector<int>> reducedMatrix = costMatrix;
    int initialCost = reduceMatrix(reducedMatrix, n);

    // Push the initial state (cost, current node, path)
    pq.push({initialCost, {0, {0}}});

    while (!pq.empty()) {
        auto currentCost = pq.top().first;
        auto state = pq.top().second;
        int currentNode = state.first;
        vector<int> currentPath = state.second;
        pq.pop();

        // If the path is complete, check the final cost
        if (currentPath.size() == n) {
            int finalCost = currentCost + costMatrix[currentNode][0];
            if (finalCost < minCost) {
                minCost = finalCost;
                bestPath = currentPath;
                bestPath.push_back(0);
            }
            continue;
        }

        // Explore all unvisited cities
        for (int i = 0; i < n; i++) {
            if (find(currentPath.begin(), currentPath.end(), i) == currentPath.end()) {
                vector<int> newPath = currentPath;
                newPath.push_back(i);

                // Create a reduced matrix for the next state
                vector<vector<int>> newReducedMatrix = createReducedMatrix(reducedMatrix, currentNode, i, n);

                // Calculate the cost for the next state
                int newCost = currentCost + costMatrix[currentNode][i] + reduceMatrix(newReducedMatrix, n);

                // Only push states with lower bounds less than current minimum cost
                if (newCost < minCost) {
                    pq.push({newCost, {i, newPath}});
                }
            }
        }
    }

    // Output the best path and cost
    cout << "Minimum Cost: " << minCost << endl;
    cout << "Best Path: ";
    for (int city : bestPath) {
        cout << city << " ";
    }
    cout << endl;
}

int main() {
    vector<vector<int>> costMatrix = {
        { -1, 10, 15, 20 },
        { 10, -1, 35, 25 },
        { 15, 35, -1, 30 },
        { 20, 25, 30, -1 }
    };

    int n = costMatrix.size();

    tspBranchAndBound(costMatrix, n);

    return 0;
}
