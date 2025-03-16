#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>  // For reverse
using namespace std;

// Define a structure to represent a graph edge
struct Edge {
    int vertex, weight;
};

// Dijkstra's Algorithm
void dijkstra(int V, vector<vector<Edge> >& adj, int src, int dest) {
    // Distance vector to store the shortest distance from src to each vertex
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;  // Distance to the source is 0

    // Priority queue to select the vertex with the smallest distance
    // Use 'pair<int, int>' instead of 'greater<>' because 'greater' might cause issues in C++98 mode.
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(0, src));  // Push the source with distance 0

    // Parent vector to reconstruct the path
    vector<int> parent(V, -1);

    while (!pq.empty()) {
        int currentDist = pq.top().first;  // Current shortest distance
        int currentNode = pq.top().second;  // Current vertex
        pq.pop();

        // Process each neighbor of the current vertex
        for (int i = 0; i < adj[currentNode].size(); i++) {
            Edge edge = adj[currentNode][i];
            int nextNode = edge.vertex;
            int weight = edge.weight;

            // Relaxation step
            if (dist[currentNode] + weight < dist[nextNode]) {
                dist[nextNode] = dist[currentNode] + weight;
                pq.push(make_pair(dist[nextNode], nextNode));
                parent[nextNode] = currentNode;
            }
        }
    }

    // Output the shortest distance to the destination
    cout << "Shortest distance from " << src << " to " << dest << ": " << dist[dest] << endl;

    // Reconstruct the shortest path
    cout << "Path: ";
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl;
}

int main() {
    int V, E, u, v, w, src, dest;

    // Input: Number of vertices and edges
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<Edge> > adj(V);

    // Input: Edges with weights
    cout << "Enter the edges (u v weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        adj[u].push_back(Edge{v, w});
        adj[v].push_back(Edge{u, w});  // Undirected graph
    }

    // Input: Source and destination nodes
    cout << "Enter the source node: ";
    cin >> src;
    cout << "Enter the destination node: ";
    cin >> dest;

    // Perform Dijkstra's Algorithm
    dijkstra(V, adj, src, dest);

    return 0;
}


