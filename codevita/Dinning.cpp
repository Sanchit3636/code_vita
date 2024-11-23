#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <vector>
#include <unistd.h> // For sleep()

using namespace std;

// Mutex for safe printing
pthread_mutex_t print_lock;

// Semaphore to control access to forks
vector<sem_t> forks;

// Barrier semaphore to control when philosophers start eating in rounds
sem_t round_start;

// Function to safely print messages
void safe_print(const string& msg) {
    pthread_mutex_lock(&print_lock);
    cout << msg << endl;
    pthread_mutex_unlock(&print_lock);
}

// Structure for philosopher arguments
struct PhilosopherArgs {
    int id;
    int max_meals;
};

// Philosopher thread function
void* philosopher(void* arg) {
    PhilosopherArgs* args = (PhilosopherArgs*)arg;

    int id = args->id;
    int left_fork = id; // Left fork (same as philosopher ID)
    int right_fork = (id + 1) % forks.size(); // Right fork (next in the circle)

    for (int i = 0; i < args->max_meals; ++i) {
        safe_print("Philosopher " + to_string(id + 1) + " is thinking");
        sleep(1); // Simulate thinking

        // Wait for the round to start
        sem_wait(&round_start);

        // Pick up forks
        sem_wait(&forks[left_fork]);
        sem_wait(&forks[right_fork]);

        // Eating
        safe_print("Philosopher " + to_string(id + 1) + " is eating");
        sleep(1); // Simulate eating

        // Put down forks
        sem_post(&forks[right_fork]);
        sem_post(&forks[left_fork]);

        // Signal the next philosopher
        sem_post(&round_start);
    }

    safe_print("Philosopher " + to_string(id + 1) + " has finished eating");
    return NULL;
}

int main() {
    int num_philosophers, max_meals;

    // Input the number of philosophers and meals
    cout << "Enter the number of philosophers: ";
    cin >> num_philosophers;
    cout << "Enter the maximum meals each philosopher can have: ";
    cin >> max_meals;

    // Initialize forks and the round-start semaphore
    forks.resize(num_philosophers);
    for (int i = 0; i < num_philosophers; ++i) {
        sem_init(&forks[i], 0, 1);
    }
    sem_init(&round_start, 0, 1);

    // Initialize mutex for printing
    pthread_mutex_init(&print_lock, NULL);

    // Create philosopher threads
    vector<pthread_t> threads(num_philosophers);
    vector<PhilosopherArgs> args(num_philosophers);
    for (int i = 0; i < num_philosophers; ++i) {
        args[i] = {i, max_meals};
        pthread_create(&threads[i], NULL, philosopher, &args[i]);
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        pthread_join(thread, NULL);
    }

    // Clean up resources
    for (auto& fork : forks) {
        sem_destroy(&fork);
    }
    sem_destroy(&round_start);
    pthread_mutex_destroy(&print_lock);

    cout << "All philosophers have finished eating." << endl;
    return 0;
}
