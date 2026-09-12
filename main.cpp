#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include "json.hpp" // Ensure this is in the same directory

// Use a convenience macro for the library namespace
using json = nlohmann::json;
using namespace std;

// 1. Data Structure for a Package
struct Package {
    string name;
    vector<string> dependencies; 
};

// 2. The Dependency Resolver Class
class PackageResolver {
private:
    unordered_map<string, vector<string>> graph; 
    unordered_map<string, int> inDegree; 

public:
    void buildGraph(const vector<Package>& packages) {
        for (const auto& pkg : packages) {
            if (inDegree.find(pkg.name) == inDegree.end()) {
                inDegree[pkg.name] = 0;
            }
            for (const auto& dep : pkg.dependencies) {
                graph[dep].push_back(pkg.name);
                inDegree[pkg.name]++; 
                
                if (inDegree.find(dep) == inDegree.end()) {
                    inDegree[dep] = 0;
                }
            }
        }
    }

    // Kahn's Algorithm
    vector<string> resolveDependencies() {
        vector<string> installationOrder;
        queue<string> readyQueue;

        for (const auto& pair : inDegree) {
            if (pair.second == 0) {
                readyQueue.push(pair.first);
            }
        }

        while (!readyQueue.empty()) {
            string current = readyQueue.front();
            readyQueue.pop();
            installationOrder.push_back(current);

            for (const string& dependentPkg : graph[current]) {
                inDegree[dependentPkg]--;
                if (inDegree[dependentPkg] == 0) {
                    readyQueue.push(dependentPkg); 
                }
            }
        }

        if (installationOrder.size() != inDegree.size()) {
            throw runtime_error("Error: Circular dependency detected! Cannot resolve.");
        }

        return installationOrder;
    }
};

// 3. Main Function
int main() {
    ifstream inputFile("packages.json");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open packages.json" << endl;
        return 1;
    }

    json jsonData;
    try {
        inputFile >> jsonData;
    } catch (const json::parse_error& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
        return 1;
    }

    vector<Package> packages;

    for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
        Package pkg;
        pkg.name = it.key();
        
        for (const auto& dep : it.value()) {
            pkg.dependencies.push_back(dep.get<string>());
        }
        packages.push_back(pkg);
    }

    PackageResolver resolver;
    resolver.buildGraph(packages);

    try {
        vector<string> order = resolver.resolveDependencies();
        cout << "Installation Order: ";
        for (size_t i = 0; i < order.size(); ++i) {
            cout << order[i];
            if (i < order.size() - 1) cout << " -> ";
        }
        cout << "\n";
    } catch (const exception& e) {
        cerr << e.what() << "\n";
    }

    return 0;
}