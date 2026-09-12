# C++ Package Dependency Resolver

A high-performance command-line tool built in C++ that models how production package managers (like `npm` or `apt`) resolve software dependencies. It processes a directed acyclic graph (DAG) of packages and uses Kahn's Algorithm for topological sorting to determine the correct installation order, ensuring no circular dependencies exist.

## Features
* **Topological Sorting:** Implements Kahn's Algorithm to find a valid linear execution order for dependencies.
* **Cycle Detection:** Automatically detects circular dependencies in the dependency graph and safely halts execution, preventing infinite loops.
* **Dynamic JSON Parsing:** Integrates `nlohmann/json` to dynamically load and parse dependency trees from external configuration files.
* **Graph Theory Application:** Showcases practical application of core data structures (Adjacency Lists, Hash Maps, Queues) and graph traversal techniques.

## Technical Stack
* **Language:** C++11 (Standard Template Library)
* **External Libraries:** `nlohmann/json` (Single-header JSON parser)
* **Core Algorithms:** Kahn's Algorithm, Graph Traversal

## Setup and Installation

### Prerequisites
* A C++ compiler (e.g., `g++` or `clang++`)
* macOS / Linux environment (or WSL on Windows)

### 1. Clone or Download the Repository
Ensure all files are placed in a single directory:
* `main.cpp`
* `packages.json`

### 2. Download the JSON Dependency
Download the single-header JSON library directly into the project folder:
```bash
curl -O https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp
```

### 3. Build the Project
Compile the source code using `g++`:
```bash
g++ -std=c++11 main.cpp -o resolver
```

## Usage

Define your package dependencies in the `packages.json` file using a standard dictionary format where the key is the package name and the value is an array of its dependencies:

```json
{
  "javascript-core": [],
  "react": ["javascript-core"],
  "axios": ["javascript-core"],
  "my-app": ["react", "axios"]
}
```

Run the compiled executable:
```bash
./resolver
```

**Expected Output:**
```text
Installation Order: javascript-core -> react -> axios -> my-app -> 
```

## Why This Project?
This tool was built to demonstrate a strong command of core computer science fundamentals—specifically graph algorithms and memory management in C++—applied to a real-world system design challenge. It translates abstract competitive programming concepts into a practical engineering utility.
