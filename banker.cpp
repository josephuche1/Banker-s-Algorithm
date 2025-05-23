#include "banker.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

// Constructor implementation
Banker::Banker(const std::vector<int>& initial_resources) {
    // Initialize available resources
    available = initial_resources;
    
    // Initialize matrices with zeros
    maximum.resize(NUMBER_OF_CUSTOMERS, std::vector<int>(NUMBER_OF_RESOURCES, 0));
    allocation.resize(NUMBER_OF_CUSTOMERS, std::vector<int>(NUMBER_OF_RESOURCES, 0));
    need.resize(NUMBER_OF_CUSTOMERS, std::vector<int>(NUMBER_OF_RESOURCES, 0));
}

// Initialize maximum resources from file
bool Banker::initializeMaximum(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    int customer = 0;
    
    // Read each line from the file
    while (std::getline(file, line) && customer < NUMBER_OF_CUSTOMERS) {
        std::stringstream ss(line);
        std::string value;
        int resource = 0;
        
        // Parse comma-separated values
        while (std::getline(ss, value, ',') && resource < NUMBER_OF_RESOURCES) {
            maximum[customer][resource] = std::stoi(value);
            need[customer][resource] = std::stoi(value); // Initially, need equals maximum
            resource++;
        }
        customer++;
    }
    
    return true;
}

// Check if the system is in a safe state
bool Banker::isSafeState() {
    // Work vector represents available resources
    std::vector<int> work = available;
    
    // Finish vector indicates if a process can finish
    std::vector<bool> finish(NUMBER_OF_CUSTOMERS, false);
    
    // Find a process that can be allocated resources
    bool found;
    do {
        found = false;
        for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                
                if (canAllocate) {
                    // Process can be allocated resources
                    for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                }
            }
        }
    } while (found);
    
    // Check if all processes can finish
    return std::all_of(finish.begin(), finish.end(), [](bool f) { return f; });
}

// Request resources for a customer
int Banker::requestResources(int customer_num, const std::vector<int>& request) {
    // Validate customer number
    if (customer_num < 0 || customer_num >= NUMBER_OF_CUSTOMERS) {
        std::cerr << "Invalid customer number" << std::endl;
        return -1;
    }
    
    // Check if request exceeds need
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        if (request[i] > need[customer_num][i]) {
            std::cerr << "Request exceeds maximum need" << std::endl;
            return -1;
        }
    }
    
    // Check if request exceeds available resources
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        if (request[i] > available[i]) {
            std::cerr << "Request exceeds available resources" << std::endl;
            return -1;
        }
    }
    
    // Try to allocate resources
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[customer_num][i] += request[i];
        need[customer_num][i] -= request[i];
    }
    
    // Check if the new state is safe
    if (!isSafeState()) {
        // If not safe, rollback the allocation
        for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
            available[i] += request[i];
            allocation[customer_num][i] -= request[i];
            need[customer_num][i] += request[i];
        }
        std::cerr << "Request denied: System would be in unsafe state" << std::endl;
        return -1;
    }
    
    return 0;
}

// Release resources from a customer
void Banker::releaseResources(int customer_num, const std::vector<int>& release) {
    // Validate customer number
    if (customer_num < 0 || customer_num >= NUMBER_OF_CUSTOMERS) {
        std::cerr << "Invalid customer number" << std::endl;
        return;
    }
    
    // Release resources
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        if (release[i] > allocation[customer_num][i]) {
            std::cerr << "Cannot release more than allocated" << std::endl;
            return;
        }
        available[i] += release[i];
        allocation[customer_num][i] -= release[i];
        need[customer_num][i] += release[i];
    }
}

// Print the current state of the system
void Banker::printState() const {
    std::cout << "\nAvailable Resources:" << std::endl;
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        std::cout << available[i] << " ";
    }
    std::cout << "\n\nMaximum Resources:" << std::endl;
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            std::cout << maximum[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\nAllocated Resources:" << std::endl;
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            std::cout << allocation[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\nRemaining Need:" << std::endl;
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            std::cout << need[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
} 