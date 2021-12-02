#include <bits/stdc++.h>

#include <fstream>

using namespace std;

vector<pair<string, int>> read_data() {
    fstream f("in.txt");
    vector<pair<string, int>> res;
    while (!f.eof()) {
        int x;
        string type;
        f >> type >> x;
        res.push_back({type, x});
    }
    return res;
}

long find_coords(const vector<pair<string, int>> &input) {
    long res = 0;
    long w = 0;
    long d = 0;
    for (pair<string, int> in : input) {
        if (in.first == "forward") {
            w += in.second;
        } else if (in.first == "down") {
            d += in.second;
        } else {
            d -= in.second;
        }
    }
    return w * d;
}

long find_coords_2(const vector<pair<string, int>> &input) {
    long res = 0;
    long w = 0;
    long d = 0;
    long aim = 0;
    for (pair<string, int> in : input) {
        if (in.first == "forward") {
            w += in.second;
            d += in.second * aim;
        } else if (in.first == "down") {
            aim += in.second;
        } else {
            aim -= in.second;
        }
    }
    return w * d;
}

int main() {
    vector<pair<string, int>> input = read_data();
    cout << find_coords_2(input);
    return 0;
}