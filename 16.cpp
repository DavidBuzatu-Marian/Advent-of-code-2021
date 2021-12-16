#include <bits/stdc++.h>

#include <fstream>

using namespace std;

unordered_map<char, string> get_hex_to_bin_map() {
    unordered_map<char, string> res;
    res['0'] = "0000";
    res['1'] = "0001";
    res['2'] = "0010";
    res['3'] = "0011";
    res['4'] = "0100";
    res['5'] = "0101";
    res['6'] = "0110";
    res['7'] = "0111";
    res['8'] = "1000";
    res['9'] = "1001";
    res['A'] = "1010";
    res['B'] = "1011";
    res['C'] = "1100";
    res['D'] = "1101";
    res['E'] = "1110";
    res['F'] = "1111";
    return res;
}

string read_data() {
    fstream f("in.txt");
    string res;
    unordered_map<char, string> hex_to_bin = get_hex_to_bin_map();
    while (!f.eof()) {
        string line;
        getline(f, line);
        for (char c : line) {
            res += hex_to_bin[c];
        }
    }
    return res;
}

int sum_versions_of_packets(string &packets, int &size) {
    long res = 0;
    if (packets.size() == 0) {
        return 0;
    }

    res += stoi(packets.substr(0, 3), 0, 2);
    int packet_type = stoi(packets.substr(3, 3), 0, 2);
    cout << packets << '\n';
    if (packet_type == 4) {
        int k = 6;
        string num = "";
        size -= 6;
        while (k + 5 < packets.size() && packets[k] != '0') {
            num += packets.substr(k + 1, 4);
            k += 5;
            size -= 5;
        }
        if (k + 5 < packets.size() && packets[k] == '0') {
            num += packets.substr(k + 1, 4);
            k += 5;
            size -= 5;
        }
        cout << packets << '\n';
        packets = packets.substr(k);
        cout << stoll(num, 0, 2) << '\n';
        // somethign with num
    } else {
        char len_type_ID = packets[6];
        if (len_type_ID == '0') {
            // total len of sub packets
            cout << packets.size() << " " << size << '\n';
            int len = stoi(packets.substr(7, 15), 0, 2);
            packets = packets.substr(22);
            size -= (22 + len);
            while (len > 0) {
                res += sum_versions_of_packets(packets, len);
            }
        } else {
            cout << packets.size() << " " << size << '\n';
            int pack_num = stoi(packets.substr(7, 11), 0, 2);
            packets = packets.substr(18);
            if (size > 0) {
                size -= 18;
            }
            while (pack_num > 0) {
                res += sum_versions_of_packets(packets, size);
                --pack_num;
            }
        }
    }
    return res;
}

void compute_result(long long &res, long long &val, const int &id) {
    if (id == 0) {
        res += val;
    } else if (id == 1) {
        if (res == -1) {
            res = 1;
        }
        res *= val;
    } else if (id == 2) {
        res = min(res, val);
    } else if (id == 3) {
        res = max(res, val);
    } else if (id == 5) {
        if (res == -1) {
            res = val;
        } else {
            res = res > val;
        }
    } else if (id == 6) {
        if (res == -1) {
            res = val;
        } else {
            res = res < val;
        }
    } else {
        if (res == -1) {
            res = val;
        } else {
            res = (res == val);
        }
    }
}

long long compute_packet_value(string &packets, int &size) {
    long long res = 0;
    if (packets.size() == 0) {
        return 0;
    }
    int packet_type = stoi(packets.substr(3, 3), 0, 2);
    if (packet_type == 4) {
        int k = 6;
        string num = "";
        size -= 6;
        while (k + 5 <= packets.size() && packets[k] != '0') {
            num += packets.substr(k + 1, 4);
            k += 5;
            size -= 5;
        }
        if (k + 5 <= packets.size() && packets[k] == '0') {
            num += packets.substr(k + 1, 4);
            k += 5;
            size -= 5;
        }
        packets = packets.substr(k);
        return stoll(num, 0, 2);
    } else {
        if (packet_type == 1 || packet_type == 5 || packet_type == 6 ||
            packet_type == 7) {
            res = -1;
        }
        if (packet_type == 2) {
            res = LONG_LONG_MAX;
        }
        char len_type_ID = packets[6];
        if (len_type_ID == '0') {
            // total len of sub packets
            int len = stoi(packets.substr(7, 15), 0, 2);
            packets = packets.substr(22);
            size -= (22 + len);
            while (len > 0) {
                long long value = compute_packet_value(packets, len);
                compute_result(res, value, packet_type);
            }
        } else {
            int pack_num = stoi(packets.substr(7, 11), 0, 2);
            packets = packets.substr(18);
            if (size > 0) {
                size -= 18;
            }
            while (pack_num > 0) {
                long long value = compute_packet_value(packets, size);
                compute_result(res, value, packet_type);
                --pack_num;
            }
        }
    }
    return res;
}

int main() {
    string packets = read_data();
    int size = 0;
    cout << compute_packet_value(packets, size) << '\n';
    return 0;
}