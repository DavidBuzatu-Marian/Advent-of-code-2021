#include <bits/stdc++.h>

#include <fstream>

using namespace std;

vector<int> read_data() {
    fstream f("in.txt");
    vector<int> res;
    while (!f.eof()) {
        int x;
        f >> x;
        res.push_back(x);
    }
    return res;
}

long count_increments(const vector<int> &input) {
    int cnt = 0;

    for (int i = 1; i < input.size(); ++i) {
        if (input[i] > input[i - 1]) {
            ++cnt;
        }
    }
    return cnt;
}

long count_increments_2(const vector<int> &input) {
    long cnt = 0;

    int sum = input[0] + input[1] + input[2];
    for (int i = 3; i < input.size(); ++i) {
        int sum2 = sum - input[i - 3] + input[i];
        if (sum2 > sum) {
            ++cnt;
        }
        sum = sum2;
    }
    return cnt;
}

int main() {
    vector<int> input = read_data();
    cout << count_increments_2(input);
    return 0;
}