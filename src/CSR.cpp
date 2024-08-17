// CSR实现稀疏矩阵

#include <iostream>
#include <vector>

class SparseGraph {
public:
    SparseGraph(int numVertices) : V(numVertices) {
        rowOffsets.resize(V + 1, 0); // Initialize with zeros
    }

    void addEdge(int u, int v) {
        column_indices.push_back(v);
        rowOffsets[u + 1]++; // Increment the row offset for the next vertex
    }

    void finalize() {
        for (int i = 1; i <= V; ++i) {
            rowOffsets[i] += rowOffsets[i - 1]; // Calculate cumulative row offsets
        }
    }

    void printGraph() {
        for (int i = 0; i < V; ++i) {
            std::cout << "Vertex " << i << ": ";
            for (int j = rowOffsets[i]; j < rowOffsets[i + 1]; ++j) {
                std::cout << column_indices[j] << " ";
            }
            std::cout << std::endl;
        }
    }

public:
    int V; // Number of vertices
    std::vector<int> rowOffsets;
    std::vector<int> column_indices;
    std::vector<int> value;
};

int main() {
    int numVertices = 5;
    SparseGraph graph(numVertices);

    graph.addEdge(0, 2);
    graph.addEdge(0, 1);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    graph.finalize(); // Calculate cumulative row offsets
    graph.printGraph();

    return 0;
}
