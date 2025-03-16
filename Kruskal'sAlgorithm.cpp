#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an edge
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Disjoint Set Union (DSU) or Union-Find class
class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }

    bool unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return false;  // Cycle detected

        // Union by rank
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

// Function to find the MST using Kruskal's Algorithm
void kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());  // Sort edges by weight

    DSU dsu(V);
    vector<Edge> mst;  // Store edges in the MST
    int totalWeight = 0;

    // Traditional for loop to replace range-based for loop
    for (int i = 0; i < edges.size(); i++) {
        const Edge& edge = edges[i];
        if (dsu.unionSets(edge.u, edge.v)) {
            mst.push_back(edge);
            totalWeight += edge.weight;
        }
        if (mst.size() == V - 1) break;  // MST is complete
    }

    // Output the MST
    cout << "Edges in the Minimum Spanning Tree (MST):\n";
    for (int i = 0; i < mst.size(); i++) {
        cout << mst[i].u << " - " << mst[i].v << " (Weight: " << mst[i].weight << ")\n";
    }
    cout << "Total Weight of MST: " << totalWeight << endl;
}

int main() {
    int V, E, u, v, weight;

    // Take user input for number of vertices and edges
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<Edge> edges;
    cout << "Enter the edges (u v weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> weight;
        edges.push_back({u, v, weight});
    }

    // Find and print the MST using Kruskal's algorithm
    kruskalMST(V, edges);

    return 0;
}


