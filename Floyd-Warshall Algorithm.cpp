#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int INF = 1e9;  // A large number to represent infinity

void floydWarshall(int V, vector<vector<int> >& graph) {
    vector<vector<int> > dist = graph;  // Copy the graph as the initial distance matrix

    // Floyd-Warshall algorithm
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            cout << "Graph contains a negative weight cycle.\n";
            return;
        }
    }

    // Output the shortest distances
    cout << "Shortest distance matrix:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << setw(5) << "INF";
            else
                cout << setw(5) << dist[i][j];
        }
        cout << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<int> > graph(V, vector<int>(V, INF));

    // Initialize diagonal elements to 0
    for (int i = 0; i < V; i++) {
        graph[i][i] = 0;
    }

    cout << "Enter the edges (u v weight):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;  // Directed graph
    }

    // Run Floyd-Warshall algorithm
    floydWarshall(V, graph);

    return 0;
}

