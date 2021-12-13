#include <bits/stdc++.h>

#include <fstream>

using namespace std;

void get_folds(vector<pair<char, int>> &folds, string &row) {
    size_t pos = 0;
    if ((pos = row.find("y")) != string::npos) {
        string num = row.substr(pos + 2);
        folds.push_back({'y', stoi(num)});
    }
    if ((pos = row.find("x")) != string::npos) {
        string num = row.substr(pos + 2);
        folds.push_back({'x', stoi(num)});
    }
}

pair<unordered_map<int, unordered_set<int>>, vector<pair<char, int>>> read_data(
    int &max_x, int &max_y) {
    fstream f("in.txt");
    unordered_map<int, unordered_set<int>> coords;
    vector<pair<char, int>> folds;
    int finished_coords = 0;
    while (!f.eof()) {
        string line;
        getline(f, line);
        if (line.size() == 0) {
            finished_coords = 1;
            continue;
        }
        if (finished_coords) {
            get_folds(folds, line);
        } else {
            size_t pos = line.find(",");
            int x = stoi(line.substr(0, pos));
            int y = stoi(line.substr(pos + 1));
            coords[x].insert(y);
            max_x = max(max_x, x);
            max_y = max(max_y, y);
        }
    }
    return {coords, folds};
}

void print_data(const pair<unordered_map<int, unordered_set<int>>,
                           vector<pair<char, int>>> &data) {
    for (auto it : data.first) {
        for (auto y : it.second) {
            cout << it.first << " " << y << '\n';
        }
    }
    for (auto p : data.second) {
        cout << p.first << " " << p.second << '\n';
    }
}

long fold_once(
    pair<unordered_map<int, unordered_set<int>>, vector<pair<char, int>>> &data,
    int &max_x, int &max_y) {
    int res = 0;
    pair<char, int> fold_one = data.second[0];
    if (fold_one.first == 'y') {
        int fold_y = fold_one.second;
        for (auto it : data.first) {
            int idx = 0;
            for (int y = max_y; y > fold_y; --y, ++idx) {
                if (it.second.count(y)) {
                    data.first[it.first].erase(y);
                    data.first[it.first].insert(idx);
                }
            }
        }
    } else {
        int fold_x = fold_one.second;
        for (auto it : data.first) {
            int idx = 0;
            for (int x = max_x; x > fold_x; --x, ++idx) {
                if (it.first == x) {
                    for (auto y : it.second) {
                        data.first[it.first].erase(y);
                        data.first[idx].insert(y);
                    }
                    data.first.erase(it.first);
                }
            }
        }
    }
    for (auto it : data.first) {
        res += it.second.size();
    }
    return res;
}

void print_matrix(vector<vector<char>> &matrix, const int &max_x,
                  const int &max_y) {
    for (int i = 0; i < max_y; ++i) {
        for (int j = 0; j < max_x; ++j) {
            cout << matrix[i][j];
        }
        cout << "\n";
    }
}

void fold_all(vector<vector<char>> &matrix, vector<pair<char, int>> &folds,
              int &max_x, int &max_y) {
    for (auto p : folds) {
        if (p.first == 'y') {
            int fold_y = p.second;
            for (int y = max_y - 1; y > fold_y; --y) {
                for (int x = 0; x < max_x; ++x) {
                    if (matrix[y][x] == '#') {
                        matrix[fold_y * 2 - y][x] = '#';
                    }
                }
            }
            max_y = fold_y;
        } else {
            int fold_x = p.second;
            for (int y = 0; y < max_y; ++y) {
                for (int x = max_x - 1; x > fold_x; --x) {
                    if (matrix[y][x] == '#') {
                        matrix[y][fold_x * 2 - x] = '#';
                    }
                }
            }
            max_x = fold_x;
        }
    }
}

vector<vector<char>> build_matrix(unordered_map<int, unordered_set<int>> &data,
                                  const int &max_x, const int &max_y) {
    vector<vector<char>> matrix(max_y + 1, vector<char>(max_x + 1, ' '));
    for (auto it : data) {
        for (auto y : it.second) {
            matrix[y][it.first] = '#';
        }
    }
    return matrix;
}

int main() {
    int max_x = 0;
    int max_y = 0;
    auto data = read_data(max_x, max_y);
    ++max_x;
    ++max_y;
    vector<vector<char>> matrix = build_matrix(data.first, max_x, max_y);
    fold_all(matrix, data.second, max_x, max_y);
    print_matrix(matrix, max_x, max_y);
    return 0;
}