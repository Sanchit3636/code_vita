#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// Function to display the adjacency matrix
void displayMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            std::cout << value << "\t";
        }
        std::cout << std::endl;
    }
}

// Function to display the TSP route (chromosome)
void displayRoute(const std::vector<int>& route) {
    for (int city : route) {
        std::cout << city << " ";
    }
    std::cout << std::endl;
}

// Mutation function: swaps two cities in the route
void mutateChromosome(std::vector<int>& chromosome) {
    std::srand(std::time(0)); // Seed for randomization

    // Choose two random indices to swap
    int index1 = std::rand() % chromosome.size();
    int index2 = std::rand() % chromosome.size();

    // Ensure indices are different
    while (index1 == index2) {
        index2 = std::rand() % chromosome.size();
    }

    // Swap cities
    std::swap(chromosome[index1], chromosome[index2]);
    std::cout << "Mutation: Swapped cities at indices " << index1 << " and " << index2 << std::endl;
}

int main() {
    // Input adjacency matrix (cost matrix)
    std::vector<std::vector<int>> matrix = {
        {0, 10, 15, 20},
        {5,  0,  9, 10},
        {6, 13,  0, 12},
        {8,  8,  9,  0}
    };

    std::cout << "Adjacency Matrix (Cost Matrix):" << std::endl;
    displayMatrix(matrix);

    // Initial TSP route (chromosome): Visiting all cities in order
    std::vector<int> chromosome = {0, 1, 2, 3};

    std::cout << "\nOriginal TSP Route: ";
    displayRoute(chromosome);

    // Perform mutation
    mutateChromosome(chromosome);

    std::cout << "\nMutated TSP Route: ";
    displayRoute(chromosome);

    return 0;
}
