#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
 
// precalculates SPF (Smallest Prime Factor) for every number till n, included
vector<int> sieve(int n) {
    vector<int> spf(n + 1);
    spf[0] = 0;
    spf[1] = 1;
    for (int i = 2; i <= n; i++)
    // marking smallest prime factor for every
    // number to be itself.
    spf[i] = i;
 
    // separately marking spf for every even
    // number as 2
    for (int i = 4; i <= n; i += 2)
        spf[i] = 2;
 
    for (int i = 3; i * i <= n; i++) {
        // checking if i is prime
        if (spf[i] == i) {
            // marking SPF for all numbers divisible by i
            for (int j = i * i; j <= n; j += i)
                // marking spf[j] if it is not previously marked
                if (spf[j] == j)
                    spf[j] = i;
        }
    }

    return spf;
}

// returns shortest path found with BFS
vector<int> shortestPath(const vector<vector<int> >& graph, int start, int end) {
    int numNodes = graph.size();
    if (start < 1 || start > numNodes || end < 1 || end > numNodes) {
        // One or both nodes are not present in the graph
        return {};
    }

    queue<int> q;
    vector<bool> visited(numNodes + 1, false);
    vector<int> parent(numNodes + 1, -1);

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == end) {
            // Reconstruct the path
            stack<int> pathStack;
            int node = end;
            while (node != -1) {
                pathStack.push(node);
                node = parent[node];
            }
            vector<int> path;
            while (!pathStack.empty()) {
                path.push_back(pathStack.top());
                pathStack.pop();
            }
            return path;
        }

        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    // No path found
    return {};
}
 
int main() {
    int n;
    cin >> n;
    int N = 300000;
    int MAX = 0;
    vector<int> legs(n+1); // legs[i] = number of legs of i-spider
    
    for(int i=1; i<n+1; i++) {
        cin >> legs[i];
        MAX = max(MAX, legs[i]);
    }

    vector<int> spf = sieve(MAX);
    vector< vector<int> > adj(MAX + N + 1); // graph

    // create bidirectional graph
    for(int node=1; node<n+1; node++) {
        int x = legs[node]; // variable that calculates prime factors
        vector<int> pfactors; // set of prime factors
        while (x != 1) {
            pfactors.push_back(spf[x] + N);

            // add opposite direction in the graph
            adj[spf[x] + N].push_back(node);
            
            // next prime factor
            x = x / spf[x];
        }
        // conect prime factors to node in graph
        adj[node] = pfactors;
    }

    int s, t;
    cin >> s >> t;
    int path_length = 0;
    auto path = shortestPath(adj, s, t);

    if(path.empty()) {
        cout << -1 << endl;
        return 0;
    }

    for(int i=0; i<path.size(); i+=2) {
        if(path[i] <= N) {
            path_length++;
        }
    }

    cout << path_length << endl;

    for(int i=0; i<path.size(); i++) {
        if(path[i] <= N) {
            cout << path[i] << " ";
        }
    }

    cout << endl;
    return 0;
}
