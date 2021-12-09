#include <bits/stdc++.h>

#include <fstream>

using namespace std;

vector<vector<int>> read_data() {
    fstream f("in.txt");
    vector<vector<int>> heights;
    int sz = 0;
    while (!f.eof()) {
        string row;
        f >> row;
        heights.push_back({});
        sz = row.size();
        if (heights.size() == 1) {
            for (int i = 0; i <= row.size() + 1; ++i) {
                heights.back().push_back(INT_MAX);
            }
            heights.push_back({});
        }
        heights.back().push_back(INT_MAX);
        for (char &c : row) {
            heights.back().push_back(c - '0');
        }
        heights.back().push_back(INT_MAX);
    }
    heights.push_back({});
    for (int i = 0; i <= sz + 1; ++i) {
        heights.back().push_back(INT_MAX);
    }
    return heights;
}

void print_heights(vector<vector<int>> &heights) {
    for (vector<int> &r : heights) {
        for (int &c : r) {
            cout << c << " ";
        }
        cout << '\n';
    }
}

long find_lowest_heights(const vector<vector<int>> &heights) {
    long res = 0;
    for (int i = 1; i < heights.size() - 1; ++i) {
        for (int j = 1; j < heights[i].size() - 1; ++j) {
            if (heights[i][j] < heights[i - 1][j] &&
                heights[i][j] < heights[i][j - 1] &&
                heights[i][j] < heights[i][j + 1] &&
                heights[i][j] < heights[i + 1][j]) {
                res += heights[i][j] + 1;
            }
        }
    }

    return res;
}

int BFS(const vector<vector<int>> &heights, const int &i, const int &j) {
    vector<vector<int>> vis(heights.size(), vector<int>(heights[0].size(), 0));
    queue<pair<int, int>> q;
    q.push({i, j});
    vector<int> dirs = {0, -1, 0, 1, 0};
    int basin_size = 0;
    vis[i][j] = 1;
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        ++basin_size;
        for (int k = 0; k < 4; ++k) {
            int new_i = curr.first + dirs[k];
            int new_j = curr.second + dirs[k + 1];
            if (new_i > 0 && new_i < heights.size() - 1 && new_j > 0 &&
                new_j < heights[0].size() - 1 && vis[new_i][new_j] == 0 &&
                heights[new_i][new_j] != 9) {
                q.push({new_i, new_j});
                vis[new_i][new_j] = 1;
            }
        }
    }
    cout << basin_size << '\n';
    return basin_size;
}

long find_basins(const vector<vector<int>> &heights) {
    long res = 1;
    priority_queue<int> pq;
    for (int i = 1; i < heights.size() - 1; ++i) {
        for (int j = 1; j < heights[i].size() - 1; ++j) {
            if (heights[i][j] < heights[i - 1][j] &&
                heights[i][j] < heights[i][j - 1] &&
                heights[i][j] < heights[i][j + 1] &&
                heights[i][j] < heights[i + 1][j]) {
                pq.push(BFS(heights, i, j));
            }
        }
    }
    int cnt = 0;
    while (!pq.empty() && cnt++ < 3) {
        res *= pq.top();
        pq.pop();
    }

    return res;
}

int main() {
    vector<vector<int>> heights = read_data();
    // print_heights(heights);
    cout << find_basins(heights);
    return 0;
}