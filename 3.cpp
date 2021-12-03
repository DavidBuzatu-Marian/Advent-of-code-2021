#include <bits/stdc++.h>

#include <fstream>

using namespace std;

vector<string> read_data() {
    fstream f("in.txt");
    vector<string> res;
    while (!f.eof()) {
        string bits;
        f >> bits;
        res.push_back(bits);
    }
    return res;
}

long get_power_consumption(const vector<string> bits) {
    string gamma, epsilon;
    for (int i = 0; i < bits[0].size(); ++i) {
        int ones = 0;
        int zeros = 0;
        for (string bit : bits) {
            ones += (bit[i] == '1');
            zeros += (bit[i] == '0');
        }
        if (ones > zeros) {
            gamma += '1';
            epsilon += '0';
        } else {
            gamma += '0';
            epsilon += '1';
        }
    }
    cout << gamma << " " << epsilon << '\n';
    long l_gamma = stol(gamma, nullptr, 2);
    long l_epsilon = stol(epsilon, nullptr, 2);
    return l_gamma * l_epsilon;
}

string get_bits(const vector<string> &bits,
                bool (*comp)(const int &a, const int &b)) {
    vector<string> curr = bits;
    string oxygen;
    string co2;
    int len = curr[0].size();
    for (int i = 0; i < len; ++i) {
        int ones = 0;
        int zeros = 0;
        vector<string> ones_v;
        vector<string> zeros_v;
        for (string &bit : curr) {
            if (bit[i] == '1') {
                ones_v.push_back(bit);
            } else {
                zeros_v.push_back(bit);
            }
            ones += (bit[i] == '1');
            zeros += (bit[i] == '0');
        }
        if (comp(ones, zeros)) {
            curr = ones_v;
        } else {
            curr = zeros_v;
        }
        if (curr.size() == 1) {
            return curr[0];
        }
    }
    return "";
}

long get_life_support(const vector<string> &bits) {
    string oxygen =
        get_bits(bits, [](const int &a, const int &b) { return a >= b; });
    string co2 =
        get_bits(bits, [](const int &a, const int &b) { return a < b; });

    long l_oxygen = stol(oxygen, nullptr, 2);
    long l_co2 = stol(co2, nullptr, 2);
    return l_oxygen * l_co2;
}

int main() {
    vector<string> input = read_data();
    cout << get_life_support(input);
    return 0;
}