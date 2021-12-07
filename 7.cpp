#include <bits/stdc++.h>

#include <fstream>

using namespace std;

vector<int> read_data() {
    fstream f("in.txt");
    vector<int> positions;
    while (!f.eof()) {
        int x;
        f >> x;
        positions.push_back(x);
    }
    return positions;
}

long find_cost(vector<int> &positions) {
    sort(begin(positions), end(positions));
    int median = positions[positions.size() / 2];
    long cost = 0;
    for (int &p: positions) {
        cost += abs(median - p);
    }
    return cost;
}

long compute_cost(const vector<int> &positions, const int &optim) {
    long cost = 0;
    for (const int &p: positions) {
        int n = abs(optim - p);
        cost += (n * (n + 1)) / 2;
    }
    return cost;
}

long find_cost_2(vector<int> &positions) {
    long sum = accumulate(begin(positions), end(positions), 0L);
    long mean_up = ceil(sum / positions.size());
    long mean_low = floor(sum / positions.size());
    return max(compute_cost(positions, mean_low), compute_cost(positions, mean_up));
}

int main() {
    vector<int> positions = read_data();
    cout << find_cost_2(positions);
    return 0;
}