*Copyright Preda Diana 324CA 2022-2023*

# Algorithm Design Assignment 2

**Student:** *Preda Diana*

**Group:** *324CA*

## **Supercomputer**

We use Kahn's algorithm, an improved topological sorting algorithm, to determine the minimum number of context switches required to execute a set of tasks on a supercomputer. The algorithm processes the tasks with no dependencies first, updating the number of switches needed for each task. It avoids context switches when consecutive tasks require the same data set. The algorithm continues until all tasks are processed. Finally, the solution outputs the minimum number of switches required.

Exemple:

    N = 5
    M = 6
    DataSet {1, 2, 1, 2, 1}
    Task Dependencies {(1, 2); (1, 3); (2, 4); (3, 4); (2, 5); (3, 5)}

Step 1:

    We create empty queues q1 and q2.
    We create empty vectors incEdges and switches with size N.

Step 2:

    We perform the Kahn's algorithm:
    - We find tasks with no incoming edges (dependencies) and add them to the appropriate queues based on their required data sets:
        - Task 1 has no incoming edges and requires data set 1, so we add it to q1.
        - Task 2 has no incoming edges and requires data set 2, so we add it to q2.
        - Task 3 has no incoming edges and requires data set 1, so we add it to q1.   

Step 3:

    Ww process the queues:
        - We start with queue q1:
            - We process Task 1:
                - We update the number of switches for Task 2 as switches[2] = switches[1] + 1 = 0 + 1 = 1.
                - We update the number of switches for Task 3 as switches[3] = switches[1] + 1 = 0 + 1 = 1.
                - We decrease the number of incoming edges for Task 2 and Task 3.
            - We process Task 3:
                - We update the number of switches for Task 5 as switches[5] = switches[3] + 1 = 1 + 1 = 2.
                - We decrease the number of incoming edges for Task 5.
        - Next, process queue q2:
            -We process Task 2:
                - We update the number of switches for Task 4 as switches[4] = switches[2] + 0 = 1 + 0 = 1.
                - We decrease the number of incoming edges for Task 4.  

Step 4:
    We determine the maximum number of switches.
    The maximum number of switches needed among all tasks is 2 (for Task 5).

Step 5:
    We write the output.
    The minimum number of context switches required to execute all tasks is 2.

Time Complexity

    Overall, the time complexity of the code is O(N + M) for reading input and building the dependency graph, and O(N) for performing the Kahn's algorithm and finding the maximum number of switches. The dominant factor in the time complexity depends on the relationship between N and M, and in the worst case, it can be considered as O(N + M).

## **Ferate**

We use Tarjan's algorithm to find strongly connected components (SCCs) in a directed graph. We perform a depth-first search (DFS) on the graph, assigning discovery times and low values to each node. We use a stack to keep track of the visited nodes and identify SCCs based on the low values. The number of SCCs and the SCC information are then used to calculate the minimum number of railways that need to be built.

Exemple:

    N = 4
    M = 4
    S = 4
    (X, y) = {(1, 3); (4, 3); (1, 2); (1, 4)}

Adj:

    1: 3, 2, 4
    2:
    3:
    4: 3

Step 1:
    
    We initialize the Tarjan algorithm with the number of train stations (n = 4).

Step 2:

    We add the edges to the graph.

Step 3:

    - We apply the Tarjan algorithm to find the strongly connected components (SCCs):
    - We initialize the necessary data structures.
    - We start the DFS traversal from node 1.
        - We mark node 1 as visited and assign it a discovery time (disc[1] = 1).
        - We set the low value of node 1 as the discovery time (low[1] = 1).
        - We explore the neighbors of node 1.
            - Node 3 is not visited. We recursively apply DFS on node 3.
                - We mark node 3 as visited and assign it a discovery time (disc[3] = 2).
                - We set the low value of node 3 as the discovery time (low[3] = 2).
                - No neighbors to explore for node 3.
            - Node 2 is not visited. We recursively apply DFS on node 2.
                - We mark node 2 as visited and assign it a discovery time (disc[2] = 3).
                - We set the low value of node 2 as the discovery time (low[2] = 3).
                - No neighbors to explore for node 2.
            - Node 4 is not visited. Recursively apply DFS on node 4.
                - We mark node 4 as visited and assign it a discovery time (disc[4] = 4).
                - We set the low value of node 4 as the discovery time (low[4] = 4).
                - No neighbors to explore for node 4.
            - Since all neighbors are explored, node 1 is the root of a strongly connected component. We mark the component as SCC 1 and increment the SCC count (scc[1] = scc[3] = scc[2] = scc[4] = 1, sccCount = 1).

After traversing all nodes, we obtain:

Adjacency list:
    
    1: 3, 2, 4
    2:
    3:
    4: 3

Discovery time values (disc):

    1: 1
    2: 3
    3: 2
    4: 4

Lowest values (low):

    1: 1
    2: 3
    3: 2
    4: 4

Strongly connected component values (scc):

    1: 1
    2: 1
    3: 1
    4: 1

Step 4:
    
    - We calculate the minimum number of railways that need to be built.
    - We initialize the inDegree array with 0 values for each SCC (inDegree[0] = 0) and iterate over each node from 1 to 4:
    - For each neighbor w of node i, if scc[i] != scc[w], we increment inDegree[scc[w]]. We have inDegree[1] = 0, as there are no incoming edges to SCC 1 (main train station).
    - We alculate minRailways by counting the SCCs with inDegree = 0 and not being the main train station.
    - In this case, minRailways = 1.

Step 5:

    We write the result to the output file.

Time Complexity
    
    The time complexity of the Tarjan's algorithm used in this code is O(V + E), where V is the number of nodes (train stations) and E is the number of edges (railways). The SCC calculation and other operations have linear time complexities and do not significantly affect the overall complexity.

## **Magazin**

This problem can be solved using a graph-based approach. We represent the depots as nodes in a graph, where an edge from node u to node v represents a shipment from depot u to depot v. The problem is then reduced to finding the depot that is the target-th node to be visited in a depth-first search (DFS) traversal starting from a given depot.

Exemple:

    N = 8
    Q = 5
    Depot relationships: {1, 1, 1, 3, 3, 5, 5}
    Queries:
        Query 1: D = 1, E = 5
        Query 2: D = 1, E = 8
        Query 3: D = 3, E = 1
        Query 4: D = 3, E = 4
        Query 5: D = 4, E = 1

Step 1:

    We initialize an empty graph with N = 8 vertices and add edges based on the depot relationships.

Step 2:

    - Query 1: Starting from depot 1, we find the depot that will receive packages after 5 consecutive shipments.
        - We perform a DFS traversal starting from depot 1.
        - WE visit the adjacent depots in order: Depot 2, Depot 3.
        - After 5 shipments, the depot to visit is Depot 8.
        - We write the result 8 to the output file.
    - Query 2: Starting from depot 1, we find the depot that will receive packages after 8 consecutive shipments.
        - We perform a DFS traversal starting from depot 1.
        - We visit the adjacent depots in order: Depot 2, Depot 3.
        - After 8 shipments, it is not possible to continue the consecutive shipments.
        - Write -1 to the output file.
    - Query 3: Starting from depot 3, we find the depot that will receive packages after 1 consecutive shipment.
        - We perform a DFS traversal starting from depot 3.
        - We  isit the adjacent depot: Depot 5.
        - After 1 shipment, the depot to visit is Depot 7.
        - We write the result 7 to the output file.
    - Query 4: Starting from depot 3, we find the depot that will receive packages after 4 consecutive shipments.
        - We perform a DFS traversal starting from depot 3.
        - We visit the adjacent depots in order: Depot 5.
        - After 4 shipments, it is not possible to continue the consecutive shipments.
        - Write -1 to the output file.
    - Query 5: Starting from depot 4, we find the depot that will receive packages after 1 consecutive shipment.
        - We perform a DFS traversal starting from depot 4.
        - We visit the adjacent depot: No adjacent depot exists.
        - After 1 shipment, it is not possible to continue the consecutive shipments.
        - We write -1 to the output file.

Output

    8
    -1
    7
    -1
    -1


Time Complexity

The time complexity of constructing the graph is O(N) as we iterate through N-1 edges. For each query, the DFS traversal takes O(N) time in the worst case. Therefore, the overall time complexity of the solution is O(N + Q*N), where Q is the number of queries. Unfortunately, not good enough.

## **Weak spots** 

We assume that the input values are within the allowed range. The function may not return the correct result if the input values are not within the allowed range. </br>
We assume that the input vectors have the correct size and format. If the input vectors are not in the correct size or format, the function may not return the correct result. </br>
The time complexity for my implementatin for Magazin, exceed the time-out set for this problem. </br>

## **Sources** 

[1] https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/ - Kahn’s algorithm for Topological Sorting </br>
[2] https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/ - Tarjan’s Algorithm to find Strongly Connected Components </br>
[3] https://ocw.cs.pub.ro/courses/pa/laboratoare/laborator-07 - Tarjan’s Algorithm </br>
[4] https://ocw.cs.pub.ro/courses/pa/laboratoare/laborator-06 - DFS Algorithm </br>
