// Copyright Preda Diana 324CA 2022-2023
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

class Khan {
 public:
    // khan algorithm
    static void khan(vector<int>& dataSet, vector<int>& incEdges,
                     vector<vector<int>>& dependencies, vector<int>& switches,
                     queue<int>& q1, queue<int>& q2) {
        // process tasks with no incoming edges first
        // update the min no of switches
        while (!q1.empty() || !q2.empty()) {
            if (!q1.empty()) {
                processQueue(q1, dataSet, incEdges, dependencies, switches);
            } else {
                processQueue(q2, dataSet, incEdges, dependencies, switches);
            }
        }
    }

 private:
    // process queue q and update the min no of switches
    static void processQueue(queue<int>& q, vector<int>& dataSet,
                             vector<int>& incEdges,
                             vector<vector<int>>& dependencies,
                             vector<int>& switches) {
        int task = q.front();
        q.pop();

        for (int nextTask : dependencies[task]) {
            // if the data set of task and nextTask are different
            // add 1 to the no of switches needed to execute nextTask
            int aux = switches[task] + (dataSet[task] != dataSet[nextTask]);
            if (aux > switches[nextTask]) {
                switches[nextTask] = aux;
            }

            // decrease the no of incoming edges of nextTask
            incEdges[nextTask]--;

            // if all incoming edges of nextTask have been processed
            // add nextTask to the queue
            if (incEdges[nextTask] == 0) {
                q.push(nextTask);
            }
        }
    }
};

int main() {
    ifstream fin("supercomputer.in");
    ofstream fout("supercomputer.out");

    // check if the input and output files were successfully opened
    if (!fin.is_open() || !fout.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    // read no of tasks and dependencies
    int N, M;
    fin >> N >> M;

    // read data sets
    vector<int> dataSet(N);
    for (int i = 0; i < N; i++) {
        fin >> dataSet[i];
    }

    // incEdges[i] = no of incoming edges for task i
    vector<int> incEdges(N, 0);
    // dependencies[i] = tasks that depend on task i
    vector<vector<int>> dependencies(N);

    // read dependencies
    int u, v;
    for (int i = 0; i < M && fin >> u >> v; i++) {
        dependencies[u - 1].push_back(v - 1);
        incEdges[v - 1]++;
    }

    // q1 = tasks that can be executed with data set 1
    // q2 = tasks that can be executed with data set 2
    queue<int> q1, q2;
    // switches[i] = no of switches needed to execute task i
    vector<int> switches(N, 0);

    // add tasks with no incoming edges to the queues
    for (int i = 0; i < N; i++) {
        if (incEdges[i] == 0) {
            (dataSet[i] == 1) ? q1.push(i) : q2.push(i);
        }
    }

    // perform the khan algorithm on the graph of tasks and dependencies
    // to find the min no of switches needed
    Khan khan;
    khan.khan(dataSet, incEdges, dependencies, switches, q1, q2);

    // find the max no of switches needed
    int minSwitches = 0;
    for (int i = 0; i < N; i++) {
        (switches[i] > minSwitches) ? minSwitches = switches[i] : int(0);
    }

    // write the min no of switches needed to the output file
    fout << minSwitches << endl;

    fin.close();
    fout.close();

    return 0;
}
