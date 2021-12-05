#include <bits/stdc++.h>

#include <fstream>

using namespace std;

void get_coords(unordered_map<int, unordered_map<int, int>> &coords_map,
                string coords) {
    size_t pos = 0;
    int x1, y1, x2, y2;
    while ((pos = coords.find("->")) != string::npos) {
        string coords_with_colon = coords.substr(0, pos);
        size_t colon = coords_with_colon.find(",");
        x1 = stoi(coords_with_colon.substr(0, colon));
        y1 = stoi(coords_with_colon.substr(colon + 1, pos - colon - 2));
        coords.erase(0, pos + 3);
    }
    size_t colon = coords.find(",");
    x2 = stoi(coords.substr(0, colon));
    y2 = stoi(coords.substr(colon + 1, coords.size() - colon - 1));
    if (x1 > x2) {
        swap(x1, x2);
    }
    if (y1 > y2) {
        swap(y1, y2);
    }
    if (x1 == x2 || y1 == y2) {
        for (int i = x1; i <= x2; ++i) {
            for (int j = y1; j <= y2; ++j) {
                coords_map[i][j]++;
            }
        }
    }
}

void get_coords_diagonals_included(
    unordered_map<int, unordered_map<int, int>> &coords_map, string coords) {
    size_t pos = 0;
    int x1, y1, x2, y2;
    while ((pos = coords.find("->")) != string::npos) {
        string coords_with_colon = coords.substr(0, pos);
        size_t colon = coords_with_colon.find(",");
        x1 = stoi(coords_with_colon.substr(0, colon));
        y1 = stoi(coords_with_colon.substr(colon + 1, pos - colon - 2));
        coords.erase(0, pos + 3);
    }
    size_t colon = coords.find(",");
    x2 = stoi(coords.substr(0, colon));
    y2 = stoi(coords.substr(colon + 1, coords.size() - colon - 1));
    if (x1 == x2 || y1 == y2) {
        if (x1 > x2) {
            swap(x1, x2);
        }
        if (y1 > y2) {
            swap(y1, y2);
        }
        for (int i = x1; i <= x2; ++i) {
            for (int j = y1; j <= y2; ++j) {
                coords_map[i][j]++;
            }
        }
    } else {
        if (x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        for (int i = x1, j = y1; i <= x2, (y1 > y2) ? j >= y2 : j <= y2;
             (y1 > y2) ? --j : ++j, ++i) {
            coords_map[i][j]++;
        }
    }
}

unordered_map<int, unordered_map<int, int>> read_data() {
    fstream f("in.txt");
    unordered_map<int, unordered_map<int, int>> coords_map;
    while (!f.eof()) {
        string coords;
        getline(f, coords);
        get_coords_diagonals_included(coords_map, coords);
    }
    return coords_map;
}

long count_intersections(
    const unordered_map<int, unordered_map<int, int>> &coords) {
    long res = 0;
    for (auto it : coords) {
        for (auto it2 : it.second) {
            if (it2.second >= 2) {
                ++res;
            }
        }
    }
    return res;
}

int main() {
    unordered_map<int, unordered_map<int, int>> coords;
    coords = read_data();
    for (int i = 0; i <= 9; ++i) {
        for (int j = 0; j <= 9; ++j) {
            cout << coords[i][j] << " ";
        }
        cout << '\n';
    }
    cout << count_intersections(coords);
    return 0;
}