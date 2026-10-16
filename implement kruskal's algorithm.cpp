//input
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
    
    // Comparator function to sort edges by weight in ascending order
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Disjoint Set Union (DSU) class for cycle detection and component merging
class DSU {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        // Initially, every node is its own parent (representative element)
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find operation with Path Compression
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Compresses the path to the root
    }

    // Union operation by Rank
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            // Keep the tree shallow by attaching the smaller rank tree under the larger one
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            return true; // Successfully united (no cycle formed)
        }
        return false; // Already in the same set (would form a cycle)
    }
};

// Function to calculate and print the Minimum Spanning Tree
void kruskalsMST(int numVertices, vector<Edge>& edges) {
    // 1. Sort all edges in non-decreasing order of their weight
    sort(edges.begin(), edges.end());

    DSU dsu(numVertices);
    vector<Edge> mst; // Stores the edges included in the final MST
    int totalMSTWeight = 0;

    // 2. Iterate through all sorted edges
    for (const auto& edge : edges) {
        // If including this edge doesn't cause a cycle, add it to the MST
        if (dsu.unite(edge.src, edge.dest)) {
            mst.push_back(edge);
            totalMSTWeight += edge.weight;
        }
        
        // Optimization: An MST will always have exactly V - 1 edges
        if (mst.size() == numVertices - 1) {
            break;
        }
    }

    // Output the resulting Minimum Spanning Tree
    cout << "Edges in the Minimum Spanning Tree:\n";
    cout << "Source - Dest : Weight\n";
    for (const auto& edge : mst) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << "\n";
    }
    cout << "Total Weight of MST: " << totalMSTWeight << "\n";
}

int main() {
    int numVertices = 6;
    vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 4}, {1, 2, 2}, 
        {2, 3, 3}, {2, 5, 2}, {2, 4, 4}, 
        {3, 4, 3}, {5, 4, 3}
    };

    kruskalsMST(numVertices, edges);

    return 0;
}


//output
Edges in the Minimum Spanning Tree:
Source - Dest : Weight
1 - 2 : 2
2 - 5 : 2
2 - 3 : 3
3 - 4 : 3
0 - 1 : 4
Total Weight of MST: 14
