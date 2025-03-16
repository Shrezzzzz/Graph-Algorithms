#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Graph {
    int V;  // Number of vertices
    vector< vector< pair<int, int> > > adj;  // Adjacency list: {neighbor, weight}

public:
    Graph(int V);  // Constructor
    void addEdge(int u, int v, int weight);  // Add an edge to the graph
    void primMST();  // Function to find the MST using Prim's algorithm
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int weight) {
    adj[u].push_back(make_pair(v, weight));  // Edge from u to v with weight
    adj[v].push_back(make_pair(u, weight));  // Edge from v to u with weight (undirected graph)
}

void Graph::primMST() {
    vector<int> key(V, INT_MAX);  // Minimum weight edge for each vertex
    vector<bool> inMST(V, false);  // To check if a vertex is included in the MST
    vector<int> parent(V, -1);  // To store the MST structure

    key[0] = 0;  // Start with the first vertex
    parent[0] = -1;  // Root of the MST

    for (int count = 0; count < V - 1; count++) {
        // Find the vertex with the minimum key value not in MST
        int minKey = INT_MAX, u = -1;
        for (int v = 0; v < V; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        // Include the picked vertex in the MST
        inMST[u] = true;

        // Update key and parent for adjacent vertices
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    // Print the MST
    cout << "Edges in the Minimum Spanning Tree (MST):\n";
    int totalWeight = 0;
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << " (Weight: " << key[i] << ")\n";
        totalWeight += key[i];
    }
    cout << "Total Weight of MST: " << totalWeight << endl;
}

int main() {
    int V, E, u, v, weight;

    // Take user input for number of vertices and edges
    cout << "Enter the number of vertices: ";
    cin >> V;
    Graph g(V);

    cout << "Enter the number of edges: ";
    cin >> E;

    // Take user input for the edges
    cout << "Enter the edges (u v weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> weight;
        g.addEdge(u, v, weight);
    }

    // Find and print the MST using Prim's algorithm
    g.primMST();

    return 0;
}


