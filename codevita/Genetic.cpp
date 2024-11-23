#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <ctime>
#include <cmath>
#include<bits/stdc++.h>

using namespace std;

const int NUM_CITIES = 5;
const int DISTANCES[NUM_CITIES][NUM_CITIES] = {
    {0, 2, 9, 10, 7},
    {1, 0, 6, 4, 3},
    {15, 7, 0, 8, 3},
    {6, 3, 12, 0, 11},
    {10, 4, 8, 5, 0}
};

const int POPULATION_SIZE = 10;
const int NUM_GENERATIONS = 100;
const double MUTATION_RATE = 0.2;

// Function to calculate fitness (inverse of path cost)
double calculateFitness(const vector<int>& path) {
    double cost = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        cost += DISTANCES[path[i]][path[i + 1]];
    }
    cost += DISTANCES[path.back()][path[0]]; // Returning to the start
    return 1.0 / cost; // Fitness is the inverse of cost
}

// Roulette Wheel Selection
vector<int> selectParent(const vector<vector<int>>& population, const vector<double>& fitnesses) {
    double totalFitness = accumulate(fitnesses.begin(), fitnesses.end(), 0.0);
    double randValue = (double)rand() / RAND_MAX * totalFitness;
    double cumulative = 0;

    for (size_t i = 0; i < fitnesses.size(); ++i) {
        cumulative += fitnesses[i];
        if (cumulative >= randValue) {
            return population[i];
        }
    }
    return population.back(); // Default case
}

// Crossover: Single-point crossover
vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2) {
    int n = parent1.size();
    vector<int> child(n, -1);

    // Random crossover point
    int crossoverPoint = rand() % n;

    // Copy first part from parent1
    copy(parent1.begin(), parent1.begin() + crossoverPoint, child.begin());

    // Fill the rest from parent2 maintaining the order
    int index = crossoverPoint;
    for (int gene : parent2) {
        if (find(child.begin(), child.end(), gene) == child.end()) {
            child[index++] = gene;
        }
    }
    return child;
}

// Mutation: Swap two cities in the path
void mutate(vector<int>& chromosome) {
    int i = rand() % chromosome.size();
    int j = rand() % chromosome.size();
    swap(chromosome[i], chromosome[j]);
}

// Generate a random chromosome
vector<int> generateRandomPath(int numCities) {
    vector<int> path(numCities);
    iota(path.begin(), path.end(), 0); // Fill with 0 to numCities - 1
    random_shuffle(path.begin(), path.end());
    return path;
}

// Main TSP solver using Genetic Algorithm
void solveTSP() {
    // Step 1: Initialize population
    vector<vector<int>> population;
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        population.push_back(generateRandomPath(NUM_CITIES));
    }

    for (int generation = 0; generation < NUM_GENERATIONS; ++generation) {
        // Step 2: Calculate fitness for each chromosome
        vector<double> fitnesses(POPULATION_SIZE);
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            fitnesses[i] = calculateFitness(population[i]);
        }

        // Step 3: Create new population
        vector<vector<int>> newPopulation;
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            // Select two parents
            vector<int> parent1 = selectParent(population, fitnesses);
            vector<int> parent2 = selectParent(population, fitnesses);

            // Perform crossover
            vector<int> child = crossover(parent1, parent2);

            // Perform mutation
            if ((double)rand() / RAND_MAX < MUTATION_RATE) {
                mutate(child);
            }

            newPopulation.push_back(child);
        }

        population = newPopulation; // Replace old population with the new one

        // Step 4: Find the best solution in the current generation
        vector<int> bestChromosome = population[0];
        double bestFitness = calculateFitness(bestChromosome);
        for (int i = 1; i < POPULATION_SIZE; ++i) {
            double fitness = calculateFitness(population[i]);
            if (fitness > bestFitness) {
                bestFitness = fitness;
                bestChromosome = population[i];
            }
        }

        // Output the best chromosome and its cost for this generation
        cout << "Generation " << generation << ": Best Path = ";
        for (int city : bestChromosome) {
            cout << city << " ";
        }
        cout << ", Cost = " << (1.0 / bestFitness) << endl;
    }
}

int main() {
    srand(time(0)); // Seed random number generator
    solveTSP();
    return 0;
}







// Initialization:

// Create an initial population of random paths (chromosomes) representing possible routes through the cities.
// Fitness Calculation:

// For each path in the population, calculate its fitness as the inverse of the total cost (distance). Lower costs yield higher fitness.
// Selection:

// Use Roulette Wheel Selection to choose parents based on their fitness. Higher fitness means a higher chance of selection.
// Crossover:

// Perform single-point crossover to produce offspring:
// Randomly select a crossover point in the parent paths.
// Copy the first part from one parent and fill the rest from the other parent while maintaining the order of cities.
// Mutation:

// With a small probability, apply mutation by swapping two cities in the path to introduce diversity.
// Replacement:

// Replace the old population with the new population of offspring.
// Repeat:

// Repeat steps 2–6 for a fixed number of generations or until a stopping criterion is met.
// Output:

// Identify the best path (chromosome) in the final population and calculate its total cost as the solution.

