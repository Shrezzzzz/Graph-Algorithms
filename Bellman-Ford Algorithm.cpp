#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Structure to represent an edge
struct Edge {
    int u, v, weight;
};

// Bellman-Ford Algorithm
void bellmanFord(int V, int E, vector<Edge>& edges, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;  // Distance to the source is 0

    // Relax all edges (V-1) times
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            if (dist[edges[j].u] != INT_MAX && dist[edges[j].u] + edges[j].weight < dist[edges[j].v]) {
                dist[edges[j].v] = dist[edges[j].u] + edges[j].weight;
            }
        }
    }

    // Check for negative weight cycles
    bool hasNegativeCycle = false;
    for (int j = 0; j < E; j++) {
        if (dist[edges[j].u] != INT_MAX && dist[edges[j].u] + edges[j].weight < dist[edges[j].v]) {
            hasNegativeCycle = true;
            break;
        }
    }

    // Output results
    if (hasNegativeCycle) {
        cout << "Graph contains a negative weight cycle.\n";
    } else {
        cout << "Shortest distances from source node " << src << ":\n";
        for (int i = 0; i < V; i++) {
            if (dist[i] == INT_MAX) {
                cout << "Node " << i << ": INF\n";
            } else {
                cout << "Node " << i << ": " << dist[i] << "\n";
            }
        }
    }
}

int main() {
    int V, E, src;

    // Input: Number of vertices and edges
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<Edge> edges;

    // Input: Edges with weights
    cout << "Enter the edges (u v weight):\n";
    for (int i = 0; i < E; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        edges.push_back({u, v, weight});
    }

    // Input: Source node
    cout << "Enter the source node: ";
    cin >> src;

    // Perform Bellman-Ford Algorithm
    bellmanFord(V, E, edges, src);

    return 0;
}

