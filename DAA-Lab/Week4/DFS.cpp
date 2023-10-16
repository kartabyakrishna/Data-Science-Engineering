#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(int start, int numVertices, bool visited[], int adjacencyMatrix[][7]) {
    stack<int> stack;
    stack.push(start);

    while (!stack.empty()) {
        int vertex = stack.top();
        stack.pop();

        if (!visited[vertex]) {
            visited[vertex] = true;
            cout << "Push: " << vertex << endl;

            for (int i = numVertices - 1; i >= 0; i--) {
                if (adjacencyMatrix[vertex][i] == 1 && !visited[i]) {
                    stack.push(i);
                }
            }
        }
        else {
            cout << "Pop: " << vertex << endl;
        }
    }
}

int main() {
    int numVertices = 7;
    bool visited[numVertices] = { false };
    int adjacencyMatrix[][7] = {
        {0, 1, 1, 0, 0, 0, 0},
        {1, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 1, 1},
        {0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0}
    };

    cout << "DFS Traversal: " << endl;
    dfs(0, numVertices, visited, adjacencyMatrix);

    return 0;
}

