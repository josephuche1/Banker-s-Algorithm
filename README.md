# Banker's Algorithm Implementation (Uche Joseph & Uche Hadassah)

This project implements the Banker's Algorithm for deadlock avoidance in operating systems. It manages resource allocation to ensure the system remains in a safe state.

## Prerequisites

- Windows operating system
- CMake (version 3.10 or higher)
- MinGW-w64 (GCC compiler)

## Installation Steps

1. Install CMake:
   - Download from https://cmake.org/download/
   - Choose Windows x64 Installer
   - During installation, select "Add CMake to the system PATH"

2. Install MinGW-w64:
   - Download from https://github.com/niXman/mingw-builds-binaries/releases
   - Choose x86_64-posix-seh version
   - Extract to `C:\mingw64`
   - Add `C:\mingw64\bin` to your system PATH

3. Verify installations:
   ```bash
   cmake --version
   g++ --version
   ```

## Building the Project

1. Clone or download this repository

2. Create and navigate to build directory:
   ```bash
   mkdir build
   cd build
   ```

3. Generate build files:
   ```bash
   cmake -G "MinGW Makefiles" ..
   ```

4. Build the project:
   ```bash
   cmake --build .
   ```

## Running the Program

1. Make sure `maximum.txt` is in the build directory:
   ```bash
   cp ../maximum.txt .
   ```

2. Run the program with initial resources: (please make sure that you are in the build directory)
   ```bash
   ./bankers_algorithm 10 5 7 8
   ```
   The numbers represent the initial available resources of each type.

## Testing the Program

1. Check initial state:
   ```
   Enter command: *
   ```

2. Request resources for a customer:
   ```
   Enter command: RQ 0 3 1 2 1
   ```

3. Release resources from a customer:
   ```
   Enter command: RL 4 1 2 3 1
   ```

4. View current state:
   ```
   Enter command: *
   ```

5. Exit the program:
   ```
   Enter command: quit
   ```

## Troubleshooting

- If `cmake` command is not found:
  - Ensure CMake is added to PATH
  - Restart your terminal

- If `g++` command is not found:
  - Ensure MinGW-w64 is added to PATH
  - Restart your terminal

- If `maximum.txt` not found:
  - Copy the file to the build directory
  - Or run the program from the project root directory 
