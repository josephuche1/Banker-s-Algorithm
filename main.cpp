#include "banker.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// Function to parse command line arguments into initial resources
std::vector<int> parseInitialResources(int argc, char* argv[]) {
    std::vector<int> resources;
    for (int i = 1; i < argc; i++) {
        resources.push_back(std::stoi(argv[i]));
    }
    return resources;
}

// Function to parse a command string into tokens
std::vector<std::string> parseCommand(const std::string& command) {
    std::vector<std::string> tokens;
    std::stringstream ss(command);
    std::string token;
    
    while (ss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

int main(int argc, char* argv[]) {
    // Check if correct number of arguments provided
    if (argc != NUMBER_OF_RESOURCES + 1) {
        std::cerr << "Usage: " << argv[0] << " <resource1> <resource2> <resource3> <resource4>" << std::endl;
        return 1;
    }
    
    // Parse initial resources from command line
    std::vector<int> initial_resources = parseInitialResources(argc, argv);
    
    // Create Banker instance
    Banker banker(initial_resources);
    
    // Initialize maximum resources from file
    if (!banker.initializeMaximum("maximum.txt")) {
        std::cerr << "Failed to initialize maximum resources. Exiting..." << std::endl;
        return 1;
    }
    
    std::string command;
    std::cout << "Banker's Algorithm Simulation" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  RQ <customer> <resource1> <resource2> <resource3> <resource4> - Request resources" << std::endl;
    std::cout << "  RL <customer> <resource1> <resource2> <resource3> <resource4> - Release resources" << std::endl;
    std::cout << "  * - Show current state" << std::endl;
    std::cout << "  quit - Exit program" << std::endl;
    
    while (true) {
        std::cout << "\nEnter command: ";
        std::getline(std::cin, command);
        
        if (command == "quit") {
            break;
        }
        
        std::vector<std::string> tokens = parseCommand(command);
        
        if (tokens.empty()) {
            continue;
        }
        
        if (tokens[0] == "*") {
            banker.printState();
        }
        else if (tokens[0] == "RQ" || tokens[0] == "RL") {
            if (tokens.size() != NUMBER_OF_RESOURCES + 2) {
                std::cerr << "Invalid command format" << std::endl;
                continue;
            }
            
            int customer = std::stoi(tokens[1]);
            std::vector<int> resources;
            
            for (int i = 2; i < tokens.size(); i++) {
                resources.push_back(std::stoi(tokens[i]));
            }
            
            if (tokens[0] == "RQ") {
                int result = banker.requestResources(customer, resources);
                if (result == 0) {
                    std::cout << "Request granted" << std::endl;
                }
            }
            else {
                banker.releaseResources(customer, resources);
                std::cout << "Resources released" << std::endl;
            }
        }
        else {
            std::cerr << "Unknown command" << std::endl;
        }
    }
    
    return 0;
} 