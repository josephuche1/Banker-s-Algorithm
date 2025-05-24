#ifndef BANKER_H
#define BANKER_H

#include <vector>
#include <string>

// Constants for the Banker's Algorithm 
const int NUMBER_OF_CUSTOMERS = 5;
const int NUMBER_OF_RESOURCES = 4;

class Banker {
private:
    // Available amount of each resource
    std::vector<int> available;
    
    // Maximum demand of each customer
    std::vector<std::vector<int>> maximum;
    
    // Amount currently allocated to each customer
    std::vector<std::vector<int>> allocation;
    
    // Remaining need of each customer
    std::vector<std::vector<int>> need;

    // Helper function to check if the system is in a safe state
    bool isSafeState();

public:
    // Constructor that initializes the system with available resources
    Banker(const std::vector<int>& initial_resources);
    
    // Initialize maximum resources from a file
    bool initializeMaximum(const std::string& filename);
    
    // Request resources for a customer
    int requestResources(int customer_num, const std::vector<int>& request);
    
    // Release resources from a customer
    void releaseResources(int customer_num, const std::vector<int>& release);
    
    // Print the current state of the system
    void printState() const;
};

#endif // BANKER_H 