#include <bits/stdc++.h>

#include <fstream>

using namespace std;

void set_connection(string &line, map<pair<char, char>, char> &connections) {
    size_t pos;
    if ((pos = line.find(" ")) != string::npos) {
        string from = line.substr(0, pos);
        string to = line.substr(pos + 4);
        connections[{from[0], from[1]}] = to[0];
    }
}

pair<string, map<pair<char, char>, char>> read_data() {
    fstream f("in.txt");
    map<pair<char, char>, char> connections;
    string code;
    f >> code;
    while (!f.eof()) {
        string line;
        getline(f, line);
        set_connection(line, connections);
    }
    return {code, connections};
}

long step_polymer(unordered_map<string, string> &connections, string &polymer,
                  const int &steps) {
    string curr = polymer;
    for (int i = 0; i < steps; ++i) {
        string next = "";
        for (int j = 0; j <= curr.size() - 2; ++j) {
            string pair = curr.substr(j, 2);
            if (next.empty()) {
                next += pair[0];
            }
            next += connections[pair] + pair[1];
        }
        // cout << next << '\n';
        curr = next;
    }
    unordered_map<char, long> cnts(26);
    long maxi = LONG_MIN;
    long mini = LONG_MAX;
    for (const char &c : curr) {
        cnts[c]++;
        maxi = max(maxi, cnts[c]);
    }
    for (auto it : cnts) {
        mini = min(mini, it.second);
    }
    return maxi - mini;
}

/*
    NN - 1
    NC - 1
    CB - 1

    NN -> NC, CN
    NC -> NB, BC
    CB -> CH, HB

*/

long long step_polymer_optim(map<pair<char, char>, char> &connections,
                             string &polymer, const int &steps) {
    map<pair<char, char>, long long> pairs;
    for (int j = 0; j < polymer.size() - 1; ++j) {
        pairs[{polymer[j], polymer[j + 1]}]++;
    }
    for (int i = 0; i < steps; ++i) {
        map<pair<char, char>, long long> aux;
        for (auto pair : pairs) {
            char conn = connections[pair.first];
            aux[{pair.first.first, conn}] += pair.second;
            aux[{conn, pair.first.second}] += pair.second;
        }
        pairs = aux;
    }
    unordered_map<char, long long> cnts(26);
    long long maxi = LONG_LONG_MIN;
    long long mini = LONG_LONG_MAX;
    for (auto pair : pairs) {
        char c1 = pair.first.first;
        char c2 = pair.first.second;
        cnts[c1] += pair.second;
        cnts[c2] += pair.second;
        maxi = max({maxi, cnts[c1], cnts[c2]});
    }
    for (auto it : cnts) {
        mini = min(mini, it.second);
    }
    return maxi / 2 - mini / 2 + 1;
}

void print_connections(const map<pair<char, char>, char> &connections) {
    for (auto it : connections) {
        cout << it.first.first << it.first.second << " " << it.second << '\n';
    }
}

int main() {
    auto data = read_data();
    // print_connections(data.second);
    cout << step_polymer_optim(data.second, data.first, 40) << '\n';
    return 0;
}