#include <bits/stdc++.h>
using namespace std;

#define R 12
#define C 10

int rowNum[] = { -1, 0, 0, 1 };
int colNum[] = { 0, -1, 1, 0 };

// Check valid cell
bool isValid(int x, int y) {
    return (x >= 0 && x < R && y >= 0 && y < C);
}

// Check safe cell
bool isSafe(int mat[R][C], int visited[R][C], int x, int y) {
    return (mat[x][y] == 1 && !visited[x][y]);
}

// Mark unsafe cells around landmines
void markUnsafeCells(int mat[R][C], int safeMat[R][C]) {
    // Copy original matrix to a working copy
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            safeMat[i][j] = mat[i][j];

    // Mark surrounding cells of landmines as unsafe
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (mat[i][j] == 0) {
                for (int k = 0; k < 4; k++) {
                    int ni = i + rowNum[k];
                    int nj = j + colNum[k];
                    if (isValid(ni, nj) && mat[ni][nj] == 1) {
                        safeMat[ni][nj] = -1;
                    }
                }
            }
        }
    }

    // Convert all temporarily unsafe (-1) to 0
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (safeMat[i][j] == -1)
                safeMat[i][j] = 0;
}

// To store the shortest path
vector<pair<int, int>> shortestPath;

// DFS to find shortest path
void findShortestPathUtil(int mat[R][C], int visited[R][C], int i, int j,
                          int &min_dist, int dist,
                          vector<pair<int, int>> &path) {
    if (j == C - 1) {
        if (dist < min_dist) {
            min_dist = dist;
            shortestPath = path;
        }
        return;
    }

    if (dist > min_dist) return;

    visited[i][j] = 1;
    path.push_back({i, j});

    for (int k = 0; k < 4; k++) {
        int ni = i + rowNum[k], nj = j + colNum[k];
        if (isValid(ni, nj) && isSafe(mat, visited, ni, nj)) {
            findShortestPathUtil(mat, visited, ni, nj, min_dist, dist + 1, path);
        }
    }

    visited[i][j] = 0;
    path.pop_back();
}

void findShortestPath(int inputMat[R][C]) {
    int mat[R][C];
    markUnsafeCells(inputMat, mat); // work on safe copy

    int min_dist = INT_MAX;
    int visited[R][C];

    for (int i = 0; i < R; i++) {
        if (mat[i][0] == 1) {
            memset(visited, 0, sizeof visited);
            vector<pair<int, int>> path;
            findShortestPathUtil(mat, visited, i, 0, min_dist, 0, path);
            if (min_dist == C - 1)
                break;
        }
    }

    cout << "========================================" << endl;
    cout << "     RESULTS OF SHORTEST SAFE ROUTE     " << endl;
    cout << "========================================" << endl;

    if (min_dist != INT_MAX) {
        cout << "The shortest safe route has been successfully calculated!" << endl;
        cout << "Length of the shortest safe route: " << min_dist << " steps" << endl;
        cout << "Detailed path coordinates (row, column):" << endl;
        cout << "---------------------------------------" << endl;
        for (auto cell : shortestPath) {
            cout << "Step: Position (" << cell.first << ", " << cell.second << ")" << endl;
        }
        cout << "---------------------------------------" << endl;
        cout << "Total number of steps taken: " << min_dist << endl;
        cout << "========================================" << endl;

        cout << "\nTime Complexity Analysis:" << endl;
        cout << "Estimated Time Complexity: O(R * C * 4^L), where L is the length of the path" << endl;
        cout << "In the worst-case scenario, L can reach up to R*C, but due to effective pruning," << endl;
        cout << "the practical execution time is significantly reduced." << endl;
    }
    else {
        cout << "Unfortunately, no safe route could be found!" << endl;
        cout << "Destination is not reachable from the given source." << endl;
        cout << "========================================" << endl;
    }
}

int main() {
    int mat[R][C] = {
    
 /* { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
        { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 0, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 } */

         /*{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1} */

         /* {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0} */

    };

    findShortestPath(mat);
    return 0;
}
