#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<vector<int> > adj;  // Adjacency list for the graph

public:
    Graph(int V);  // Constructor to initialize the graph with V vertices
    void addEdge(int u, int v);  // Add an edge to the graph
    void bfs(int start, int end);  // Perform BFS to find the shortest path from start to end
    void printPath(vector<int>& parent, int node);  // Utility to print the shortest path from start to end
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);  // As the graph is undirected
}

void Graph::bfs(int start, int end) {
    vector<int> dist(V, INT_MAX);  // Distance from start to each vertex
    vector<int> parent(V, -1);  // To store the parent of each vertex
    queue<int> q;

    dist[start] = 0;  // Distance to the start node is 0
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        // If we've reached the destination, we can stop the search
        if (node == end) {
            cout << "Shortest path from " << start << " to " << end << " is: ";
            printPath(parent, end);
            cout << endl;
            return;
        }

        // Explore all neighbors of the current node
        for (vector<int>::iterator it = adj[node].begin(); it != adj[node].end(); ++it) {
            int neighbor = *it;
            if (dist[neighbor] == INT_MAX) {  // If not visited
                dist[neighbor] = dist[node] + 1;  // Set the distance
                parent[neighbor] = node;  // Set the parent
                q.push(neighbor);
            }
        }
    }

    // If we get here, there is no path from start to end
    cout << "No path found from " << start << " to " << end << endl;
}

void Graph::printPath(vector<int>& parent, int node) {
    if (node == -1) return;  // Base case for recursion
    printPath(parent, parent[node]);  // Recursively print the path
    cout << node << " ";  // Print the current node
}

int main() {
    int V, E, u, v, start, end;
    
    // Take user input for number of vertices and edges
    cout << "Enter the number of vertices: ";
    cin >> V;
    Graph g(V);
    
    cout << "Enter the number of edges: ";
    cin >> E;
    
    // Take user input for the edges
    cout << "Enter the edges (u v):\n";
    for (int i = 0; i < E; i++) {
        cin >> u >> v;
        g.addEdge(u, v);
    }

    // Take user input for the start and end nodes
    cout << "Enter the start node: ";
    cin >> start;
    cout << "Enter the end node: ";
    cin >> end;

    // Perform BFS to find the shortest path from start to end
    g.bfs(start, end);

    return 0;
}

