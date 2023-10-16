#include <iostream>
#include <queue>

using namespace std;

void bfs(int start, int numVertices, int adjacencyMatrix[][100], bool visited[]) {
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int vertex = q.front();
        cout << vertex << " ";
        q.pop();

        for (int i = 0; i < numVertices; i++) {
            if (adjacencyMatrix[vertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

int main() {
    int numVertices = 7;
    bool visited[numVertices] = { false };
    int adjacencyMatrix[][100] = {
        {0, 1, 1, 0, 0, 0, 0},
        {1, 0, 0, 1, 1, 0, 0},
        {1, 0, 0, 0, 0, 1, 1},
        {0, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0}
    };

    cout << "BFS Traversal: ";
    bfs(0, numVertices, adjacencyMatrix, visited);
    cout << endl;

    return 0;
}

