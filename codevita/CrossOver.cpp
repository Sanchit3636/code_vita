#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to perform Order Crossover (OX)
vector<int> orderCrossover(const vector<int>& parent1, const vector<int>& parent2) {
    int size = parent1.size();
    vector<int> child(size, -1);

    // Generate random crossover points
    int start = rand() % size;
    int end = rand() % size;
    if (start > end) swap(start, end);

    // Copy the segment from parent1 to child
    for (int i = start; i <= end; i++) {
        child[i] = parent1[i];
    }

    // Fill the remaining positions from parent2
    int currentIndex = (end + 1) % size;
    for (int i = 0; i < size; i++) {
        int parent2Index = (end + 1 + i) % size;
        if (find(child.begin(), child.end(), parent2[parent2Index]) == child.end()) {
            child[currentIndex] = parent2[parent2Index];
            currentIndex = (currentIndex + 1) % size;
        }
    }

    return child;
}

// Function to print a chromosome (route)
void printChromosome(const vector<int>& chromosome) {
    for (int city : chromosome) {
        cout << city << " ";
    }
    cout << endl;
}

int main() {
    // Seed random number generator
    srand(time(0));

    // Example distance matrix (not used directly in crossover)
    vector<vector<int>> distanceMatrix = {
        {0, 10, 15, 20},
        {5, 0, 9, 10},
        {6, 13, 0, 12},
        {8, 8, 9, 0}
    };

    // Example parent chromosomes (routes)
    vector<int> parent1 = {0, 1, 2, 3};
    vector<int> parent2 = {3, 2, 0, 1};

    cout << "Parent 1: ";
    printChromosome(parent1);

    cout << "Parent 2: ";
    printChromosome(parent2);

    // Perform crossover
    vector<int> child = orderCrossover(parent1, parent2);

    cout << "Child: ";
    printChromosome(child);

    return 0;
}
