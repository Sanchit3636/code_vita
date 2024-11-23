#include<bits/stdc++.h>

using namespace std;

static const int INF = INT_MAX;

// Node structure to store information about the current state in the TSP
struct Node {
    vector<vector<int>> reducedMatrix; // Reduced cost matrix
    vector<pair<int, int>> path; // Path taken so far (pairs of cities visited)
    int cost; // Total cost to reach this state
    int level; // Current level in the path (number of cities visited)
    int vertex; // Current vertex (city) being processed

    // Constructor to initialize the node
    Node(vector<vector<int>>& parentMatrix, vector<pair<int, int>>& parentPath, int level, int vertex) {
        this->reducedMatrix = parentMatrix;
        this->path = parentPath;
        this->level = level;
        this->vertex = vertex;
        this->cost = 0;
    }
};

// Function to create a new node by adding an edge to the path
Node newNode(vector<vector<int>>& parentMatrix, vector<pair<int, int>>& path, int level, int i, int j) {
    Node node(parentMatrix, path, level, j);

    if (level != 0) {
        node.path.push_back({i, j});  // Add edge (i -> j) to the path
    }

    // Invalidate outgoing and incoming paths for visited edges
    for (int k = 0; level != 0 && k < parentMatrix.size(); k++) {
        node.reducedMatrix[i][k] = INF;
        node.reducedMatrix[k][j] = INF;
    }

    // Invalidate the return path to the start city
    node.reducedMatrix[j][0] = INF;

    return node;
}

// Reduce the rows and return the row reduction values
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

// Calculate the cost of a reduced matrix
int calculateCost(vector<vector<int>>& matrix) {
    int cost = 0;

    vector<int> rowReduction = reduceRow(matrix);
    for (int value : rowReduction) {
        if (value != INF) cost += value;
    }

    vector<int> columnReduction = reduceColumn(matrix);
    for (int value : columnReduction) {
        if (value != INF) cost += value;
    }

    return cost;
}

// Print the path
void printPath(vector<pair<int, int>>& path) {
    for (auto& edge : path) {
        cout << (edge.first + 1) << " -> " << (edge.second + 1) << endl;
    }
}

// Solve the TSP problem using branch and bound
int solve(vector<vector<int>>& costMatrix) {
    int n = costMatrix.size();
    
    // Define the comparator lambda
    auto cmp = [](Node& a, Node& b) {
        return a.cost > b.cost;
    };

    // Initialize the priority queue with the comparator
    std::priority_queue<Node, std::vector<Node>, decltype(cmp)> pq(cmp);

    vector<pair<int, int>> path;
    Node root = newNode(costMatrix, path, 0, -1, 0);
    root.cost = calculateCost(root.reducedMatrix);
    pq.push(root);

    while (!pq.empty()) {
        Node min = pq.top();
        pq.pop();

        int i = min.vertex;

        // If we reached the last level, complete the path
        if (min.level == n - 1) {
            min.path.push_back({i, 0});
            printPath(min.path);
            return min.cost;
        }

        // Generate child nodes
        for (int j = 0; j < n; j++) {
            if (min.reducedMatrix[i][j] != INF) {
                Node child = newNode(min.reducedMatrix, min.path, min.level + 1, i, j);
                child.cost = min.cost + min.reducedMatrix[i][j] + calculateCost(child.reducedMatrix);
                pq.push(child);
            }
        }
    }

    return -1;
}

int main() {
    vector<vector<int>> costMatrix = {
        // {INF, 20, 30, 10, 11},
        // {15, INF, 16, 4, 2},
        // {3, 5, INF, 2, 4},
        // {19, 6, 18, INF, 3},
        // {16, 4, 7, 16, INF}
        {-1, 10, 15, 20},
        {10, -1, 35, 25},
        {15, 35, -1, 30},
        {20, 25, 30, -1}
    };

    cout << "\nCost is " << solve(costMatrix) << endl;

    return 0;
}
