#include <bits/stdc++.h>

#include <fstream>

using namespace std;

pair<string, string> add_edges(string line,
                               unordered_map<string, vector<string>> &graph) {
    size_t pos = 0;
    string n1, n2;
    while ((pos = line.find("-")) != string::npos) {
        n1 = line.substr(0, pos);
        line.erase(0, pos + 1);
    }
    n2 = line;
    graph[n1].push_back(n2);
    graph[n2].push_back(n1);
    return {n1, n2};
}

int is_lower(const string &s) {
    int lower = 1;
    for (char c : s) {
        if (!islower(c)) {
            lower = 0;
            break;
        }
    }
    return lower;
}

unordered_map<string, vector<string>> read_data(
    unordered_set<string> &lower_strings) {
    fstream f("in.txt");
    unordered_map<string, vector<string>> graph;
    while (!f.eof()) {
        string x;
        f >> x;
        pair<string, string> nodes = add_edges(x, graph);
        int lower = is_lower(nodes.first);
        if (lower) {
            lower_strings.insert(nodes.first);
        }
        lower = is_lower(nodes.second);
        if (lower) {
            lower_strings.insert(nodes.second);
        }
    }
    return graph;
}

void print_graph(unordered_map<string, vector<string>> &graph) {
    for (auto it : graph) {
        cout << it.first << ": ";
        for (string &s : it.second) {
            cout << s << " ";
        }
        cout << '\n';
    }
}

int dfs(unordered_map<string, vector<string>> &graph,
        unordered_set<string> &vis, const unordered_set<string> &lower,
        const string &curr) {
    if (curr == "end") {
        return 1;
    }
    if (vis.count(curr)) {
        return 0;
    }
    if (!vis.count(curr) && lower.count(curr)) {
        vis.insert(curr);
    }
    int res = 0;
    for (string neigh : graph[curr]) {
        if (!vis.count(neigh)) {
            res += dfs(graph, vis, lower, neigh);
        }
    }
    vis.erase(curr);
    return res;
}

unordered_set<string> paths;
int dfs_small_twice(unordered_map<string, vector<string>> &graph,
                    unordered_map<string, int> &vis,
                    const unordered_set<string> &lower, const string &curr,
                    const string &twice, const string &path) {
    if (curr == "end" && !paths.count(path)) {
        paths.insert(path);
        return 1;
    }
    if ((vis[curr] == 1 && curr != twice) ||
        (vis[curr] == 2 && curr == twice)) {
        return 0;
    }
    if (lower.count(curr)) {
        vis[curr]++;
    }
    int res = 0;
    for (string neigh : graph[curr]) {
        if (vis[neigh] <= 0 || (vis[neigh] == 1 && neigh == twice)) {
            res += dfs_small_twice(graph, vis, lower, neigh, twice,
                                   path + ", " + neigh);
        }
    }
    vis[curr]--;
    return res;
}

int main() {
    unordered_set<string> lower_strings;
    unordered_map<string, vector<string>> graph = read_data(lower_strings);
    int res = 0;
    for (const string &lower : lower_strings) {
        if (lower != "start" && lower != "end") {
            unordered_map<string, int> vis;
            res += dfs_small_twice(graph, vis, lower_strings, "start", lower,
                                   "start");
        }
    }
    unordered_map<string, int> vis;
    res += dfs_small_twice(graph, vis, lower_strings, "start", "", "start");
    cout << res << '\n';
    return 0;
}