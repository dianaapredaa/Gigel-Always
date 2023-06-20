// Copyright Preda Diana 324CA 2022-2023
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

class Tarjan {
 public:
    explicit Tarjan(int n) : adj(n + 1), disc(n + 1, -1), low(n + 1, -1),
                             scc(n + 1, -1), visited(n + 1, false) {}

    // add an edge from node u to node v
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // find the number of strongly connected components
    int findSCC(int n) {
        sccCount = 0;
        time = 0;
        stack<int> stack;

        // find all strongly connected components
        for (int i = 1; i <= n; i++) {
            if (disc[i] == -1) {
                tarjan(i, stack);
            }
        }

        return sccCount;
    }

    // get the adjacency list
    const vector<vector<int>>& getAdj() const {
        return adj;
    }

    // get the strongly connected component that each node is in
    const vector<int>& getSCC() const {
        return scc;
    }

 private:
    // sccCount = no of strongly connected components
    int sccCount = 0;
    // time = discovery time of a node
    int time = 0;
    // adj[i] = nodes adjacent to node i
    vector<vector<int>> adj;
    // disc[i] = discovery time of node i
    vector<int> disc;
    // low[i] = lowest discovery time of a node reachable from node i
    vector<int> low;
    // scc[i] = the strongly connected component that node i is in
    vector<int> scc;
    // visited[i] = whether node i has been visited
    vector<bool> visited;

    // tarhan algorithm
    void tarjan(int i, stack<int>& stack) {
        visited[i] = true;
        // initialize the discovery time and low value of v
        disc[i] = low[i] = time;
        time++;
        // push v to the stack
        stack.push(i);

        int node;
        for (const int& node : adj[i]) {
            if (disc[node] == -1) {
                // if w has not been visited, run TarjanDFS on it
                tarjan(node, stack);
                // update the low value of v
                (low[node] < low[i]) ? low[i] = low[node] : int(0);
            } else if (disc[node] < disc[i] && visited[node]) {
                (disc[node] < low[i]) ? low[i] = disc[node] : int(0);
                // update the low value of v
            }
        }

        // check if v is the root of a strongly connected component
        if (low[i] == disc[i]) {
            while (true) {
                node = stack.top();
                stack.pop();
                visited[node] = false;
                // assign the same SCC id to all nodes in the component
                scc[node] = sccCount;

                if (node == i) {
                    break;
                }
            }
            sccCount++;
        }
    }
};

int calculateMinRailways(const Tarjan& tarjan, int n, int sccCount, int s) {
    // get the adjacency list and the strongly connected component that each
    const vector<vector<int>>& adj = tarjan.getAdj();
    const vector<int>& scc = tarjan.getSCC();

    // incomingEdgesCount[i] = no of incoming edges to scc i
    vector<int> incomingEdgesCount(sccCount, 0);
    int i = 1;
    while (i <= n) {
        // for each edge (i, w) where scc[i] != scc[w], there is an incoming
        // edge to scc[w]
        for (int w : adj[i]) {
            (scc[i] != scc[w]) ? incomingEdgesCount[scc[w]]++ : (int)0;
        }

        i++;
    }

    // minRailways = minimum number of railways that need to be built
    int minRailways = 0;

    // for each strongly connected component, if it has no incoming edges and
    // it is not the main train station, then a railway needs to be built to it
    for (int i = 0; i < sccCount; i++) {
        (incomingEdgesCount[i] == 0 && i != scc[s]) ? minRailways++ : (int)0;
    }

    return minRailways;
}

int main() {
    ifstream fin("ferate.in");
    ofstream fout("ferate.out");

    // check if the input and output files were successfully opened
    if (!fin.is_open() || !fout.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    // read the number of train stations, the number of railways and the main
    // train station
    int N, M, S;
    fin >> N >> M >> S;

    // create a Tarjan object
    Tarjan tarjan(N);

    // read the railways
    for (int i = 0, x, y; i < M && fin >> x >> y; i++) {
        tarjan.addEdge(x, y);
    }

    // find the number of strongly connected components
    int sccCount = tarjan.findSCC(N);

    // calculate the minimum number of railways that need to be built
    int minRailways = calculateMinRailways(tarjan, N, sccCount, S);

    // write the minimum number of railways that need to be built
    fout << minRailways << "\n";

    fin.close();
    fout.close();

    return 0;
}
