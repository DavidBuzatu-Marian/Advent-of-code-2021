#include <bits/stdc++.h>

#include <fstream>

using namespace std;

vector<string> read_data() {
    fstream f("in.txt");
    vector<string> parans;
    while (!f.eof()) {
        string x;
        f >> x;
        parans.push_back(x);
    }
    return parans;
}

long long find_illegal(const vector<string> &parans) {
    long long res = 0;
    unordered_map<char, int> scores;
    scores[')'] = 3;
    scores[']'] = 57;
    scores['}'] = 1197;
    scores['>'] = 25137;
    for (const string &s : parans) {
        stack<char> st;
        for (const char &c : s) {
            if (c == '(' || c == '{' || c == '[' || c == '<') {
                st.push(c);
            } else {
                if (st.empty()) {
                    res += (scores[c]);
                    break;
                }
                if (c == ')' && st.top() != '(') {
                    res += (scores[c]);
                    break;
                }
                if (c == ']' && st.top() != '[') {
                    res += (scores[c]);
                    break;
                }
                if (c == '}' && st.top() != '{') {
                    res += (scores[c]);
                    break;
                }
                if (c == '>' && st.top() != '<') {
                    res += (scores[c]);
                    break;
                }
                st.pop();
            }
        }
    }

    return res;
}

long long find_incomplete(const vector<string> &parans) {
    vector<long long> line_scores;
    unordered_map<char, int> scores;
    scores['('] = 1;
    scores['['] = 2;
    scores['{'] = 3;
    scores['<'] = 4;
    for (const string &s : parans) {
        stack<char> st;
        int illegal = 0;
        for (const char &c : s) {
            if (c == '(' || c == '{' || c == '[' || c == '<') {
                st.push(c);
            } else {
                if (st.empty()) {
                    illegal = 1;
                    break;
                }
                if (c == ')' && st.top() != '(') {
                    illegal = 1;
                    break;
                }
                if (c == ']' && st.top() != '[') {
                    illegal = 1;
                    break;
                }
                if (c == '}' && st.top() != '{') {
                    illegal = 1;
                    break;
                }
                if (c == '>' && st.top() != '<') {
                    illegal = 1;
                    break;
                }
                st.pop();
            }
        }
        if (!illegal) {
            long long res = 0;
            while (!st.empty()) {
                res *= 5;
                res += scores[st.top()];
                st.pop();
            }
            line_scores.push_back(res);
        }
    }
    auto m = begin(line_scores) + line_scores.size() / 2;
    nth_element(begin(line_scores), m, end(line_scores));
    return line_scores[line_scores.size() / 2];
}

int main() {
    vector<string> parans = read_data();
    cout << find_incomplete(parans) << '\n';
    return 0;
}