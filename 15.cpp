#include <bits/stdc++.h>

#include <fstream>

using namespace std;

vector<string> read_data() {
    fstream f("in.txt");
    vector<string> matrix;
    while (!f.eof()) {
        string line;
        getline(f, line);
        matrix.push_back(line);
    }
    return matrix;
}

long long shortest_path(const vector<string> &matrix) {
    int cols = matrix[0].size();
    int rows = matrix.size();
    vector<pair<int, int>> prev(rows * cols);
    priority_queue<pair<long long, pair<int, int>>,
                   vector<pair<long long, pair<int, int>>>, greater<>>
        pq;
    vector<long long> dist(rows * cols, LONG_LONG_MAX);
    pq.push({0, {0, 0}});
    dist[0] = 0;
    vector<int> dirs = {0, -1, 0, 1, 0};
    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();
        for (int i = 0; i < 4; ++i) {
            int new_i = curr.second.first + dirs[i];
            int new_j = curr.second.second + dirs[i + 1];
            if (new_i >= 0 && new_i < rows && new_j >= 0 && new_j < cols) {
                if (dist[new_i * cols + new_j] >
                    curr.first + matrix[new_i][new_j] - '0') {
                    dist[new_i * cols + new_j] =
                        curr.first + matrix[new_i][new_j] - '0';
                    pq.push({dist[new_i * cols + new_j], {new_i, new_j}});
                    prev[new_i * cols + new_j] = curr.second;
                }
            }
        }
    }

    return dist.back();
}

long long shortest_path_2(const vector<string> &matrix) {
    int orig_cols = matrix[0].size();
    int orig_rows = matrix.size();

    int cols = matrix[0].size() * 5;
    int rows = matrix.size() * 5;
    priority_queue<pair<long long, pair<int, int>>,
                   vector<pair<long long, pair<int, int>>>, greater<>>
        pq;
    vector<long long> dist(rows * cols, LONG_LONG_MAX);
    pq.push({0, {0, 0}});
    dist[0] = 0;
    vector<int> dirs = {0, -1, 0, 1, 0};
    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();
        for (int i = 0; i < 4; ++i) {
            int new_i = curr.second.first + dirs[i];
            int new_j = curr.second.second + dirs[i + 1];
            if (new_i >= 0 && new_i < rows && new_j >= 0 && new_j < cols) {
                long long distance =
                    (new_i / orig_rows + new_j / orig_cols +
                     matrix[new_i % orig_rows][new_j % orig_cols] - '0');
                distance = (distance >= 10 ? distance % 10 + 1 : distance);
                if (dist[new_i * cols + new_j] > curr.first + distance) {
                    dist[new_i * cols + new_j] = curr.first + distance;
                    pq.push({dist[new_i * cols + new_j], {new_i, new_j}});
                }
            }
        }
    }

    return dist.back();
}

/*
i, j

+1 for every level i
+1 for every column j
8 9 1 2 3
9 1 2 3 4
1 2 3 4 5
2 3 4 5 6
3 4 5 6 7

*/

int main() {
    vector<string> matrix = read_data();
    cout << shortest_path_2(matrix);
    return 0;
}