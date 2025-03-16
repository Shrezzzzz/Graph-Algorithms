#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<vector<int> > adj;  // Adjacency list for the graph

public:
    Graph(int V);  // Constructor to initialize the graph with V vertices
    void addEdge(int u, int v);  // Add an edge to the graph
    bool dfsTopologicalSort(int node, vector<int>& visited, stack<int>& topoStack);  // DFS for topological sort
    bool dfsCycleDetection(int node, vector<int>& visited);  // DFS for cycle detection
    void topologicalSort();  // Function to perform topological sort
    bool detectCycle();  // Function to check if the graph has a cycle
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);  // Directed edge from u to v
}

bool Graph::dfsTopologicalSort(int node, vector<int>& visited, stack<int>& topoStack) {
    visited[node] = 1;  // Mark the node as visited (in the current DFS path)
    
    for (vector<int>::iterator it = adj[node].begin(); it != adj[node].end(); ++it) {
        int neighbor = *it;
        if (visited[neighbor] == 0) {
            // If the neighbor is unvisited, recurse
            if (!dfsTopologicalSort(neighbor, visited, topoStack)) {
                return false;  // If there is a cycle, return false
            }
        } else if (visited[neighbor] == 1) {
            // If the neighbor is in the current DFS path, cycle detected
            return false;
        }
    }
    
    visited[node] = 2;  // Mark the node as fully processed
    topoStack.push(node);  // Push to topological stack
    return true;
}

bool Graph::dfsCycleDetection(int node, vector<int>& visited) {
    visited[node] = 1;  // Mark the node as being visited (in the current DFS path)
    
    for (vector<int>::iterator it = adj[node].begin(); it != adj[node].end(); ++it) {
        int neighbor = *it;
        if (visited[neighbor] == 0) {
            // If the neighbor is unvisited, recurse
            if (dfsCycleDetection(neighbor, visited)) {
                return true;  // Cycle detected
            }
        } else if (visited[neighbor] == 1) {
            // If the neighbor is in the current DFS path, cycle detected
            return true;
        }
    }
    
    visited[node] = 2;  // Mark the node as fully processed
    return false;
}

void Graph::topologicalSort() {
    vector<int> visited(V, 0);  // 0: unvisited, 1: visiting, 2: visited
    stack<int> topoStack;

    // Call DFS for all unvisited nodes
    for (int i = 0; i < V; i++) {
        if (visited[i] == 0) {
            if (!dfsTopologicalSort(i, visited, topoStack)) {
                cout << "Graph has a cycle, topological sort is not possible." << endl;
                return;
            }
        }
    }

    // Print the topological sort
    cout << "Topological Sort: ";
    while (!topoStack.empty()) {
        cout << topoStack.top() << " ";
        topoStack.pop();
    }
    cout << endl;
}

bool Graph::detectCycle() {
    vector<int> visited(V, 0);  // 0: unvisited, 1: visiting, 2: visited

    // Check for cycle in each component
    for (int i = 0; i < V; i++) {
        if (visited[i] == 0) {
            if (dfsCycleDetection(i, visited)) {
                return true;  // Cycle detected
            }
        }
    }
    return false;  // No cycle detected
}

int main() {
    int V, E, u, v, choice;

    // Take user input for number of vertices and edges
    cout << "Enter the number of vertices: ";
    cin >> V;
    Graph g(V);

    cout << "Enter the number of edges: ";
    cin >> E;

    // Take user input for the edges
    cout << "Enter the edges (u v) in a directed graph:\n";
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        g.addEdge(u, v);
    }

    // Menu to choose between topological sort or cycle detection
    cout << "Enter 1 for Topological Sort or 2 for Cycle Detection: ";
    cin >> choice;

    if (choice == 1) {
        g.topologicalSort();  // Perform topological sorting
    } else if (choice == 2) {
        if (g.detectCycle()) {
            cout << "Graph contains a cycle.\n";
        } else {
            cout << "Graph does not contain any cycles.\n";
        }
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}


