#include<bits/stdc++.h>
using namespace std;


struct Node {
    vector<vector<int>> reducedMatrix;
    vector<pair<int, int>> path;
    int cost;
    int level;
    int vertex;

    Node(vector<vector<int>>& parentMatrix, vector<pair<int, int>>& parentPath, int level, int vertex){
        this->reducedMatrix = parentMatrix;
        this->path = parentPath;
        this->level = level;
        this->vertex = vertex;
        this->cost = 0;
    }
};

Node newNode(vector<vector<int>>& parentMatrix, vector<pair<int, int>>& path, int level, int i, int j){
    Node node(parentMatrix, path, level, j);

    if(level != 0){
        node.path.push_back({i, j});
    }

    for(int k = 0;level != 0 && k < parentMatrix.size();k++){
        node.reducedMatrix[i][k] = INT_MAX;
        node.reducedMatrix[k][j] = INT_MAX;
    }

    node.reducedMatrix[j][0] = INT_MAX;

    return node;
}
vector<int> reduceRow(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<int> rowReduction(n, INF);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < rowReduction[i]) {
                rowReduction[i] = matrix[i][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != INF && rowReduction[i] != INF) {
                matrix[i][j] -= rowReduction[i];
            }
        }
    }

    return rowReduction;
}

// Reduce the columns and return the column reduction values
vector<int> reduceColumn(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<int> columnReduction(n, INF);

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] < columnReduction[j]) {
                columnReduction[j] = matrix[i][j];
            }
        }
    }

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] != INF && columnReduction[j] != INF) {
                matrix[i][j] -= columnReduction[j];
            }
        }
    }

    return columnReduction;
}


int calculateCost(vector<vector<int>>& matrix){
    int cost = 0;

    vector<int> rowReduction = reduceRow(matrix);

    for(int val : rowReduction){
        if(val != INT_MAX){
            cost += val;
        }
    }

    vector<int> columnReduction = reduceColumn(matrix);

    for(int val : columnReduction){
        if(val != INT_MAX){
            cost += val;
        }
    }

    return cost;
}

void printPath(vector<pair<int, int>>& path) {
    for (auto& edge : path) {
        cout << (edge.first + 1) << " -> " << (edge.second + 1) << endl;
    }
}
int solve(vector<vector<int>>& costMatrix){
    int n = costMatrix.size();

    auto cmp = [](Node& a, Node& b){
        return a.cost > b.cost;
    }

    std::priority_queue<Node, std::vector<Node>, decltype(cmp)> pq(cmp);

    vector<pair<int, int>> path;

    Node root = newNode(costMatrix, path, 0, -1, 0);
    root.cost = calculateCost(root.reducedMatrix);

    pq.push(root);

    while(!pq.empty()){
        Node min = pq.top();
        pq.pop();

        int i = min.vertex;

        if(min.level == n-1){
            min.path.push_back({i, 0});
            printPath(min.path);
            return min.cost;
        }

        for(int j = 0;j < n;j++){
            if(min.reducedMatrix[i][j] != INT_MAX){
                Node child = newNode(min.reducedMatrix, min.path, min.level + 1, i, j);
                child.cost = min.cost + min.reducedMatrix[i][j] + calculateCost(child.reducedMatrix);
                pq.push(child);
            }
        }
    }

    return -1;
}

int main(){
    vector<vector<int>> costMatrix = {
        {-1, 10, 15, 20},
        {10, -1, 35, 25},
        {15, 35, -1, 30},
        {20, 25, 30, -1}
    };
    cout<<"\nCost is "<<solve(costMatrix)<<endl;
    return 0;
}