// Copyright Preda Diana 324CA 2022-2023
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Graph {
 public:
    explicit Graph(int numVertices) : adj(numVertices) {}

    // add an edge from node u to node v
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // find the depot that is the target-th node to be visited
    int findDepot(int start, int target) {
        vector<bool> visited(adj.size(), false);
        int count = 0;
        int result = -1;

        // dfs from the start node
        dfs(start, visited, count, target, result);
        return result;
    }

 private:
    // adj[i] = nodes adjacent to node i
    vector<vector<int>> adj;

    // dfs algorithm
    void dfs(int node, vector<bool>& visited, int& count, int targetCount,
             int& result) {
        // if we have visited the target-th node, we have found the depot
        if (count == targetCount) {
            result = node;
            return;
        }

        // mark the current node as visited
        visited[node] = true;

        // visit all unvisited neighbors
        for (int neighbor : adj[node]) {
            // if we haven't visited the neighbor, visit it
            if (!visited[neighbor]) {
                // increment the count of visited nodes
                count++;
                // dfs from the neighbor
                dfs(neighbor, visited, count, targetCount, result);

                // if we have found the depot, return
                if (result != -1) {
                    return;
                }
            }
        }
    }
};

int main() {
    ifstream fin("magazin.in");
    ofstream fout("magazin.out");

    // check if the input and output files were successfully opened
    if (!fin.is_open() || !fout.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    // read the number of nodes and the number of queries
    int N, Q;
    fin >> N >> Q;

    // create the graph
    Graph graph(N);

    // read the edges
    int k;
    for (int i = 1; i < N && fin >> k; i++) {
        graph.addEdge(k - 1, i);
    }

    // find the depot for each query
    for (int i = 0; i < Q; i++) {
        // read the query
        int D, E;
        fin >> D >> E;

        // find the depot
        int result = graph.findDepot(D - 1, E);

        // write the result to the output file
        if (result == -1) {
            fout << -1 << endl;
        } else {
            // the result is 0-indexed, so we add 1 to it
            fout << result + 1 << endl;
        }
    }

    return 0;
}
