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

At startup, the program loads `maximum.txt`, which contains the maximum resources each customer might request. Each line represents a customer:
```
6,4,7,3  # Customer 0
4,2,3,2  # Customer 1
2,5,3,3  # Customer 2
6,3,3,2  # Customer 3
5,6,7,5  # Customer 4
```

These values are used to calculate:
Need Matrix = Maximum - Allocation

## Core Data Structures
- Available: Vector showing how many units of each resource are free.
- Maximum: Matrix from maximum.txt, showing the max demand per customer
- Allocation: What's already allocated t each customer.
- Need: What's left to satisfy each customer (Maximum - Allocation).

### How the safety check works
Before granting a request, the algorithm performs the following checks:
- Is the request less than or equal to the customer’s remaining need?
- Is the request less than or equal to currently available resources?
- If temporarily granted, will the system remain in a safe state?
A safe state means there is at least one order in which all customers can complete without deadlock.

## Safety Algorithm

The program uses the Banker's Algorithm to ensure the system remains in a safe state:

1. When a request is made, the program checks if:
   - The request doesn't exceed the customer's maximum need
   - The request doesn't exceed available resources
   - The resulting state would be safe

2. A state is considered safe if there exists a sequence of resource allocations that allows all customers to complete their work.

3. If a request would make the system unsafe, it is denied and the previous state is restored.
## User Commands
You interact with the program using commands:

* — Show Current State
Displays:
- Available
-  Maximum
-  Allocation
-  Remaining Need
-  
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
If the system remains safe after this, request is granted.

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

### quit (Exit Program)
Exits the program gracefully.

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
### Edge cases handled
- Requests exceeding Maximum -> denied
- Requests exceeding Available -> denied
- Requests making the system unsafe → rolled back
- Releases exceeding Allocation → ignored or handled safely

## Final notes
This project enforces safe resource allocation. No request is granted if it risks a deadlock. The Banker's Algorithm guarantees that all customers can eventually finish — as long as their requests respect the declared limits.
  
