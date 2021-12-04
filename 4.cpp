#include <bits/stdc++.h>

#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

void get_turns(vector<int> &turns, string &row) {
    size_t pos = 0;
    while ((pos = row.find(",")) != string::npos) {
        string num = row.substr(0, pos);
        turns.push_back(stoi(num));
        row.erase(0, pos + 1);
    }
    turns.push_back(stoi(row));
}

void get_row(unordered_set<int> &row_s, string &row, vector<int> &col) {
    size_t pos = 0;
    while ((pos = row.find(" ")) != string::npos) {
        string num = row.substr(0, pos);
        row_s.insert(stoi(num));
        col.push_back(stoi(num));
        row.erase(0, pos + 1);
    }

    row_s.insert(stoi(row));
    col.push_back(stoi(row));
}

pair<vector<int>, vector<vector<unordered_set<int>>>> read_data() {
    fstream f("in.txt");
    vector<int> turns;
    vector<vector<unordered_set<int>>> boards;
    while (!f.eof()) {
        string row;
        getline(f, row);
        if (row.empty()) {
            continue;
        }
        if (turns.empty()) {
            get_turns(turns, row);
        } else {
            boards.push_back({});
            vector<unordered_set<int>> cols;

            while (!row.empty() && !f.eof()) {
                unordered_set<int> row_s;
                vector<int> col;
                get_row(row_s, row, col);
                boards.back().push_back(row_s);
                if (cols.empty()) {
                    for (int i = 0; i < row_s.size(); ++i) {
                        cols.push_back(unordered_set<int>());
                        cols.back().insert(col[i]);
                    }
                } else {
                    for (int i = 0; i < col.size(); ++i) {
                        cols[i].insert(col[i]);
                    }
                }
                getline(f, row);
            }
            for (unordered_set<int> col : cols) {
                boards.back().push_back(col);
            }
        }
    }
    return {turns, boards};
}

void print(pair<vector<int>, vector<vector<unordered_set<int>>>> p) {
    vector<int> turns = p.first;
    for (int t : turns) {
        cout << t << ' ';
    }
    cout << '\n';
    for (vector<unordered_set<int>> &board : p.second) {
        for (unordered_set<int> &r_c : board) {
            for (int i : r_c) {
                cout << i << " ";
            }
            cout << '\n';
        }
        cout << "\n\n";
    }
}

long best_board(const vector<int> &turns,
                vector<vector<unordered_set<int>>> &boards) {
    for (const int &t : turns) {
        for (vector<unordered_set<int>> &board : boards) {
            for (unordered_set<int> &b : board) {
                b.erase(t);
                if (b.empty()) {
                    cout << t << '\n';
                    long rest = 0;
                    for (unordered_set<int> &b2 : board) {
                        b2.erase(t);  // erase in rest
                        rest += accumulate(begin(b2), end(b2), 0L);
                    }
                    return (rest * t) / 2;
                }
            }
        }
    }
    return 0;
}

long best_board_last(const vector<int> &turns,
                     vector<vector<unordered_set<int>>> &boards) {
    unordered_set<int> winner_boards;
    for (const int &t : turns) {
        int i = 0;
        for (vector<unordered_set<int>> &board : boards) {
            if (winner_boards.count(i)) {
                ++i;
                continue;  // already won
            }
            for (unordered_set<int> &b : board) {
                b.erase(t);
                if (b.empty()) {
                    winner_boards.insert(i);
                    if (winner_boards.size() == boards.size()) {
                        long rest = 0;
                        for (unordered_set<int> &b2 : board) {
                            b2.erase(t);  // erase in rest
                            rest += accumulate(begin(b2), end(b2), 0L);
                        }
                        return (rest * t) / 2;
                    }
                    break;
                }
            }
            ++i;
        }
    }
    return 0;
}

int main() {
    pair<vector<int>, vector<vector<unordered_set<int>>>> p = read_data();
    vector<int> turns = p.first;
    vector<vector<unordered_set<int>>> boards = p.second;
    auto start = high_resolution_clock::now();
    cout << best_board_last(turns, boards) << '\n';
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << duration.count() << '\n';
    return 0;
}