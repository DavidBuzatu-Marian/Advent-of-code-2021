#include <bits/stdc++.h>

#include <fstream>

using namespace std;

void get_ranges(pair<int, int> &x_range, pair<int, int> &y_range,
                string &line) {
    size_t pos;
    if ((pos = line.find("=")) != string::npos) {
        size_t dots = line.find(".");
        size_t comma = line.find(",");
        x_range.first = stoi(line.substr(pos + 1, dots - pos - 1));
        x_range.second = stoi(line.substr(dots + 2, comma - dots - 2));

        line = line.substr(comma);
        pos = line.find("=");
        dots = line.find(".");
        comma = line.find(",");
        y_range.first = stoi(line.substr(pos + 1, dots - pos - 1));
        y_range.second = stoi(line.substr(dots + 2, comma - dots - 2));
    }
}

pair<pair<int, int>, pair<int, int>> read_data() {
    fstream f("in.txt");
    pair<int, int> x_range;
    pair<int, int> y_range;
    while (!f.eof()) {
        string line;
        getline(f, line);
        get_ranges(x_range, y_range, line);
    }
    return {x_range, y_range};
}

void print_data(pair<pair<int, int>, pair<int, int>> &data) {
    cout << data.first.first << " " << data.first.second << '\n';
    cout << data.second.first << " " << data.second.second << '\n';
}

/*

Rules x: if x > max_x -> stop
         if x < min_x and vel_x < 0 -> stop
Rules y: if y < min_y and vel_y + y < min_y -> stop
*/

int find_max_y(const pair<pair<int, int>, pair<int, int>> &ranges) {
    int max_y = 0;
    for (int vel_x = 0; vel_x < ranges.first.first; ++vel_x) {
        for (int vel_y = ranges.second.first; vel_y < -ranges.second.first;
             ++vel_y) {
            int x = 0;
            int y = 0;
            int velocity_x = vel_x;
            int velocity_y = vel_y;
            int curr_max_y = 0;
            int cnt = 0;
            while (cnt++ < 1000 && x <= ranges.first.second) {
                // cout << x << " " << y << '\n';
                x += velocity_x;
                y += velocity_y;

                velocity_x = velocity_x > 0   ? velocity_x - 1
                             : velocity_x < 0 ? velocity_x + 1
                                              : 0;
                velocity_y--;
                curr_max_y = max(curr_max_y, y);
                if (x >= ranges.first.first && x <= ranges.first.second &&
                    y >= ranges.second.first && y <= ranges.second.second) {
                    max_y = max(max_y, curr_max_y);
                    break;
                }
            }
        }
    }
    return max_y;
}

int find_velocities(const pair<pair<int, int>, pair<int, int>> &ranges) {
    set<pair<int, int>> velocities;
    for (int vel_x = 0; vel_x <= ranges.first.second; ++vel_x) {
        for (int vel_y = ranges.second.first; vel_y <= -ranges.second.first;
             ++vel_y) {
            int x = 0;
            int y = 0;
            int velocity_x = vel_x;
            int velocity_y = vel_y;
            int cnt = 0;
            while (cnt++ < 1000 && x <= ranges.first.second) {
                x += velocity_x;
                y += velocity_y;

                velocity_x = velocity_x > 0   ? velocity_x - 1
                             : velocity_x < 0 ? velocity_x + 1
                                              : 0;
                velocity_y--;
                if (x >= ranges.first.first && x <= ranges.first.second &&
                    y >= ranges.second.first && y <= ranges.second.second) {
                    velocities.insert({vel_x, vel_y});
                }
            }
        }
    }
    return velocities.size();
}

int main() {
    auto data = read_data();
    // print_data(data);
    cout << find_velocities(data) << '\n';
    return 0;
}