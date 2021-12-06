#include <bits/stdc++.h>

#include <fstream>

using namespace std;

vector<int> read_data() {
    fstream f("in.txt");
    vector<int> fish;
    while (!f.eof()) {
        int x;
        f >> x;
        fish.push_back(x);
    }
    return fish;
}

long nr_fish(vector<int> &fish, const int &nr_days) {
    for (int i = 1; i <= nr_days; ++i) {
        int sz = fish.size();
        for (int j = 0; j < sz; ++j) {
            fish[j]--;
            if (fish[j] < 0) {
                fish.push_back(8);
                fish[j] = 6;
            }
        }
    }
    return fish.size();
}

long long nr_fish_optim(vector<int> &fish, const int &nr_days) {
    unordered_map<int, long long> fish_map;
    const int LAST = 8;
    for (int &f : fish) {
        fish_map[f]++;
    }

    for (int i = 1; i <= nr_days; ++i) {
        long long prev = fish_map[LAST];
        for (int j = LAST - 1; j >= 0; --j) {
            long long next = fish_map[j];
            fish_map[j] = prev;
            prev = next;
        }
        fish_map[LAST] = prev;
        fish_map[LAST - 2] += prev;
    }
    long long res = 0;
    for (int i = 0; i <= LAST; ++i) {
        res += fish_map[i];
    }
    return res;
}

int main() {
    vector<int> fish = read_data();
    cout << nr_fish_optim(fish, 256);
    return 0;
}