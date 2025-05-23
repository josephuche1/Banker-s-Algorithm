# Understanding the Banker's Algorithm Program

## Program Overview

The Banker's Algorithm is a resource allocation and deadlock avoidance algorithm that tests for safety by simulating the allocation of predetermined maximum possible amounts of all resources, and then makes a "safe-state" check to test for possible deadlock conditions.

## Initial Resource Values

When you run the program with:
```bash
./bankers_algorithm 10 5 7 8
```

These numbers represent the initial available resources of each type:
- 10 units of Resource 1
- 5 units of Resource 2
- 7 units of Resource 3
- 8 units of Resource 4

## Maximum Resources

The `maximum.txt` file contains the maximum resource requirements for each customer:
```
6,4,7,3  # Customer 0's maximum needs
4,2,3,2  # Customer 1's maximum needs
2,5,3,3  # Customer 2's maximum needs
6,3,3,2  # Customer 3's maximum needs
5,6,7,5  # Customer 4's maximum needs
```

Each line represents a customer, and each number represents their maximum need for a particular resource type.

## Commands

### RQ (Request Resources)
```
RQ <customer> <resource1> <resource2> <resource3> <resource4>
```
- `customer`: Customer number (0-4)
- `resource1-4`: Amount of each resource type requested

Example:
```
RQ 0 3 1 2 1
```
This means Customer 0 is requesting:
- 3 units of Resource 1
- 1 unit of Resource 2
- 2 units of Resource 3
- 1 unit of Resource 4

### RL (Release Resources)
```
RL <customer> <resource1> <resource2> <resource3> <resource4>
```
- `customer`: Customer number (0-4)
- `resource1-4`: Amount of each resource type to release

Example:
```
RL 4 1 2 3 1
```
This means Customer 4 is releasing:
- 1 unit of Resource 1
- 2 units of Resource 2
- 3 units of Resource 3
- 1 unit of Resource 4

### * (Show State)
Shows the current state of:
- Available Resources: Currently available resources
- Maximum Resources: Maximum needs of each customer
- Allocated Resources: Currently allocated resources
- Remaining Need: Resources still needed by each customer

## Safety Algorithm

The program uses the Banker's Algorithm to ensure the system remains in a safe state:

1. When a request is made, the program checks if:
   - The request doesn't exceed the customer's maximum need
   - The request doesn't exceed available resources
   - The resulting state would be safe

2. A state is considered safe if there exists a sequence of resource allocations that allows all customers to complete their work.

3. If a request would make the system unsafe, it is denied and the previous state is restored.

## Example Scenario

1. Initial state (after running with 10 5 7 8):
   - Available: [10, 5, 7, 8]
   - All customers have their maximum needs set
   - No resources are allocated yet

2. After `RQ 0 3 1 2 1`:
   - Available: [7, 4, 5, 7]
   - Customer 0's allocation: [3, 1, 2, 1]
   - Customer 0's need: [3, 3, 5, 2]

3. After `RL 4 1 2 3 1`:
   - Available: [8, 6, 8, 8]
   - Customer 4's allocation decreases
   - Customer 4's need increases 