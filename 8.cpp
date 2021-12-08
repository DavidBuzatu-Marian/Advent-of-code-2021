#include <bits/stdc++.h>

#include <fstream>

using namespace std;

long find_unique_signal_digs(const vector<string> &outputs) {
    long res = 0;
    unordered_set<int> unique_lengths;
    unique_lengths.insert(2);
    unique_lengths.insert(4);
    unique_lengths.insert(3);
    unique_lengths.insert(7);
    for (const string &out : outputs) {
        if (unique_lengths.count(out.size())) {
            ++res;
        }
    }
    return res;
}

void set_char_pos(const int &dig, const string &sig,
                  unordered_map<char, int> &char_to_pos,
                  unordered_map<int, string> &dig_to_bit) {
    int j = 0;
    string bits = dig_to_bit[dig];
    for (int k = 0; k < sig.size(); ++k) {
        if (char_to_pos.find(sig[k]) != char_to_pos.end()) {
            bits[char_to_pos[sig[k]]] = '0';
        }
    }
    for (int i = 0; i < dig_to_bit[dig].size() && j < sig.size(); ++i) {
        while (j < sig.size() &&
               char_to_pos.find(sig[j]) != char_to_pos.end()) {
            ++j;
        }
        if (bits[i] == '1') {
            char_to_pos[sig[j++]] = i;
        }
    }
}

long dfs(vector<string> &signals, vector<string> &outputs,
         unordered_map<string, int> &bit_to_dig,
         unordered_map<char, int> &char_to_pos, const char &curr) {
    if (curr == 'h') {
        // all assigned
        string bits = "0000000";
        for (char c : signals[0]) {
            bits[char_to_pos[c]] = '1';
        }
        if (bit_to_dig[bits] != 1) {
            return -1;
        }
        bits = "0000000";
        for (char c : signals[1]) {
            bits[char_to_pos[c]] = '1';
        }
        if (bit_to_dig[bits] != 7) {
            return -1;
        }
        bits = "0000000";
        for (char c : signals[2]) {
            bits[char_to_pos[c]] = '1';
        }
        if (bit_to_dig[bits] != 4) {
            return -1;
        }
        for (int i = 3; i < signals.size(); ++i) {
            bits = "0000000";
            for (char c : signals[i]) {
                bits[char_to_pos[c]] = '1';
            }
            if (bit_to_dig.find(bits) == bit_to_dig.end()) {
                return -1;
            }
        }
        // everything fine
        long res = 0;
        for (string out : outputs) {
            bits = "0000000";
            for (char c : out) {
                bits[char_to_pos[c]] = '1';
            }
            res = (res * 10) + (bit_to_dig[bits]);
        }
        return res;
    } else {
        for (int i = 0; i < 7; ++i) {
            char_to_pos[curr] = i;
            long res = dfs(signals, outputs, bit_to_dig, char_to_pos, curr + 1);
            if (res != -1) {
                return res;
            }
        }
        return -1;
    }
}

long find_output_digits_sum(vector<string> &signals, vector<string> &outputs) {
    long sum = 0;
    for (string &sig : signals) {
        sort(begin(sig), end(sig));
    }
    for (string &out : outputs) {
        sort(begin(out), end(out));
    }
    sort(begin(signals), end(signals),
         [](const string &a, const string &b) { return a.size() < b.size(); });
    /*
0 -> top
1 -> top_left
2 -> top_right
3 -> mid
4 -> bottom_left
5 -> bottom_right
6 -> bottom

1 -> 0010010
2 -> 1011101
3 -> 1011011
4 -> 0111010
5 -> 1101011
6 -> 1101111
7 -> 1010010
8 -> 1111111
9 -> 1111011
*/
    unordered_map<string, int> bit_to_dig;
    unordered_map<int, string> dig_to_bit;
    unordered_map<char, int> char_to_pos;
    bit_to_dig["1110111"] = 0;
    bit_to_dig["0010010"] = 1;
    bit_to_dig["1011101"] = 2;
    bit_to_dig["1011011"] = 3;
    bit_to_dig["0111010"] = 4;
    bit_to_dig["1101011"] = 5;
    bit_to_dig["1101111"] = 6;
    bit_to_dig["1010010"] = 7;
    bit_to_dig["1111111"] = 8;
    bit_to_dig["1111011"] = 9;

    dig_to_bit[0] = "1110111";
    dig_to_bit[1] = "0010010";
    dig_to_bit[2] = "1011101";
    dig_to_bit[3] = "1011011";
    dig_to_bit[4] = "0111010";
    dig_to_bit[5] = "1101011";
    dig_to_bit[6] = "1101111";
    dig_to_bit[7] = "1010010";
    dig_to_bit[8] = "1111111";
    dig_to_bit[9] = "1111011";

    return dfs(signals, outputs, bit_to_dig, char_to_pos, 'a');
}

long long solve_2() {
    fstream f("in.txt");
    vector<string> signals;
    vector<string> outputs;
    int out = 0;
    int cnt = 0;
    long long res = 0;
    while (!f.eof()) {
        string x;
        f >> x;
        if (x == "|") {
            out = 1;
            continue;
        }
        if (cnt == 4) {
            out = 0;
            cnt = 0;
            res += find_output_digits_sum(signals, outputs);
            signals = vector<string>();
            outputs = vector<string>();
        }
        if (out) {
            outputs.push_back(x);
            ++cnt;
        } else {
            signals.push_back(x);
        }
    }
    return res;
}

int main() {
    cout << solve_2();
    return 0;
}