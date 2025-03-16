#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<vector<int> > adj;  // Adjacency list for the graph

public:
    Graph(int V);  // Constructor to initialize the graph with V vertices
    void addEdge(int u, int v);  // Add a directed edge from u to v
    void dfs(int node, vector<bool>& visited, stack<int>& topoStack);  // Helper function for DFS
    void topologicalSort();  // Function to perform topological sorting
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);  // Directed edge from u to v
}

void Graph::dfs(int node, vector<bool>& visited, stack<int>& topoStack) {
    visited[node] = true;  // Mark the node as visited

    // Visit all unvisited neighbors using an iterator
    for (vector<int>::iterator it = adj[node].begin(); it != adj[node].end(); ++it) {
        int neighbor = *it;
        if (!visited[neighbor]) {
            dfs(neighbor, visited, topoStack);
        }
    }

    // Push the node to the stack after all its neighbors are processed
    topoStack.push(node);
}

void Graph::topologicalSort() {
    vector<bool> visited(V, false);  // To track visited nodes
    stack<int> topoStack;  // To store the topological order

    // Perform DFS for all unvisited nodes
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i, visited, topoStack);
        }
    }

    // Print the topological order
    cout << "Topological Sort: ";
    while (!topoStack.empty()) {
        cout << topoStack.top() << " ";
        topoStack.pop();
    }
    cout << endl;
}

int main() {
    int V, E, u, v;

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

    // Perform topological sort
    g.topologicalSort();

    return 0;
}

