#include <bits/stdc++.h>

#include <fstream>

using namespace std;

vector<vector<int>> read_data() {
    fstream f("in.txt");
    vector<vector<int>> matrix;
    while (!f.eof()) {
        string x;
        f >> x;
        matrix.push_back({});
        for (char &c : x) {
            matrix.back().push_back(c - '0');
        }
    }
    return matrix;
}

void print_matrix(const vector<vector<int>> &matrix) {
    for (const vector<int> &row : matrix) {
        for (const int &col : row) {
            cout << col << ' ';
        }
        cout << '\n';
    }
}

long count_flashes(vector<vector<int>> &matrix, const int &steps) {
    long res = 0;
    queue<pair<int, int>> q;
    vector<int> dirs_r = {0, -1, -1, -1, 0, 1, 1, 1};
    vector<int> dirs_c = {-1, -1, 0, 1, 1, 1, 0, -1};
    for (int i = 0; i < steps; ++i) {
        vector<vector<bool>> flashed(matrix.size(),
                                     vector<bool>(matrix[0].size()));
        for (int r = 0; r < matrix.size(); ++r) {
            for (int c = 0; c < matrix[0].size(); ++c) {
                matrix[r][c]++;
                if (matrix[r][c] > 9) {
                    q.push({r, c});
                }
            }
        }
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            if (flashed[curr.first][curr.second]) {
                continue;
            }
            flashed[curr.first][curr.second] = 1;
            ++res;
            matrix[curr.first][curr.second] = 0;
            for (int k = 0; k < dirs_c.size(); ++k) {
                int new_r = curr.first + dirs_r[k];
                int new_c = curr.second + dirs_c[k];
                if (new_r >= 0 && new_r < matrix.size() && new_c >= 0 &&
                    new_c < matrix[0].size() && !flashed[new_r][new_c]) {
                    matrix[new_r][new_c]++;
                    if (matrix[new_r][new_c] > 9) {
                        q.push({new_r, new_c});
                    }
                }
            }
        }
    }
    return res;
}

long count_simultaneous_flash(vector<vector<int>> &matrix) {
    queue<pair<int, int>> q;
    vector<int> dirs_r = {0, -1, -1, -1, 0, 1, 1, 1};
    vector<int> dirs_c = {-1, -1, 0, 1, 1, 1, 0, -1};
    int i = 0;
    int flashes = 0;
    while (flashes != matrix.size() * matrix[0].size()) {
        flashes = 0;
        vector<vector<bool>> flashed(matrix.size(),
                                     vector<bool>(matrix[0].size()));
        for (int r = 0; r < matrix.size(); ++r) {
            for (int c = 0; c < matrix[0].size(); ++c) {
                matrix[r][c]++;
                if (matrix[r][c] > 9) {
                    q.push({r, c});
                }
            }
        }
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            if (flashed[curr.first][curr.second]) {
                continue;
            }
            flashed[curr.first][curr.second] = 1;
            ++flashes;
            matrix[curr.first][curr.second] = 0;
            for (int k = 0; k < dirs_c.size(); ++k) {
                int new_r = curr.first + dirs_r[k];
                int new_c = curr.second + dirs_c[k];
                if (new_r >= 0 && new_r < matrix.size() && new_c >= 0 &&
                    new_c < matrix[0].size() && !flashed[new_r][new_c]) {
                    matrix[new_r][new_c]++;
                    if (matrix[new_r][new_c] > 9) {
                        q.push({new_r, new_c});
                    }
                }
            }
        }
        ++i;
    }
    return i;
}

int main() {
    vector<vector<int>> matrix = read_data();
    cout << count_simultaneous_flash(matrix) << '\n';
    print_matrix(matrix);
    return 0;
}