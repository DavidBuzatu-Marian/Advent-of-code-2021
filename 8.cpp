#include <bits/stdc++.h>

#include <fstream>

using namespace std;

pair<vector<string>, vector<string>> read_data() {
    fstream f("in.txt");
    vector<string> signals;
    vector<string> outputs;
    int out = 0;
    int cnt = 0;
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
        }
        if (out) {
            outputs.push_back(x);
            ++cnt;
        } else {
            signals.push_back(x);
        }
    }
    return {signals, outputs};
}

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

int dfs(unordered_map<string, int> &bit_to_dig,
        unordered_map<char, int> &char_to_pos, string &bits) {
    if (bit_to_dig.find(bits) != bit_to_dig.end()) {
        return 1;
    }
}

long find_output_digits_sum(vector<string> &signals,
                            const vector<string> &outputs) {
    long sum = 0;
    for (string &sig : signals) {
        sort(begin(sig), end(sig));
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
    bit_to_dig["0010010"] = 1;
    bit_to_dig["1011101"] = 2;
    bit_to_dig["1011011"] = 3;
    bit_to_dig["0111010"] = 4;
    bit_to_dig["1101011"] = 5;
    bit_to_dig["1101111"] = 6;
    bit_to_dig["1010010"] = 7;
    bit_to_dig["1111111"] = 8;
    bit_to_dig["1111011"] = 9;

    dig_to_bit[1] = "0010010";
    dig_to_bit[2] = "1011101";
    dig_to_bit[3] = "1011011";
    dig_to_bit[4] = "0111010";
    dig_to_bit[5] = "1101011";
    dig_to_bit[6] = "1101111";
    dig_to_bit[7] = "1010010";
    dig_to_bit[8] = "1111111";
    dig_to_bit[9] = "1111011";

    for (string &sig : signals) {
        if (sig.size() == 2) {
            set_char_pos(1, sig, char_to_pos, dig_to_bit);
        }
        if (sig.size() == 3) {
            set_char_pos(7, sig, char_to_pos, dig_to_bit);
        }
        if (sig.size() == 4) {
            set_char_pos(4, sig, char_to_pos, dig_to_bit);
        }
        if (sig.size() == 7) {
            set_char_pos(8, sig, char_to_pos, dig_to_bit);
        }
    }

    for (string &sig : signals) {
        string bits = "0000000";
        for (int j = 0; j < sig.size(); ++j) {
            bits[char_to_pos[sig[j]]] = '1';
        }
        if (bit_to_dig.find(bits) == bit_to_dig.end()) {
            dfs(bit_to_dig, bits, char_to_pos);
        }
    }

    return sum;
}

int main() {
    pair<vector<string>, vector<string>> data = read_data();
    cout << find_output_digits_sum(data.first, data.second);
    return 0;
}