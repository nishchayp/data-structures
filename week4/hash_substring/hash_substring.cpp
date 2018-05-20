#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (int i = output.size() - 1; i >= 0; i--)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

ull hash_func(const string str, ull prime, ull x) {
    ull hash = 0;
    for (int i = str.length() - 1; i >= 0; i--) {
        hash = ((hash * x + str[i]) % prime + prime) % prime;
    }
    return hash;
}

std::vector<ull> pre_compute_hash(string text, int length, ull prime, ull x) {
    std::vector<ull> hash_table;
    ull extra_term = 1;
    ull hash = hash_func(text.substr(text.length() - length, length), prime, x);
    hash_table.push_back(hash);
    for (int i = 0; i < length; i++)
        extra_term = extra_term * x;
    for (int i = text.length() - length - 1; i >= 0; i--) {
        hash = (((hash * x) + text[i] - text[i + length] * extra_term) % prime + prime) % prime; 
        hash_table.push_back(hash);
    }
    return hash_table;
}

std::vector<int> get_occurrences(const Data& input) {
    ull prime = 100000007;
    ull x = 1;
    const std::vector<ull>& hash_table_substr = pre_compute_hash(input.text, input.pattern.length(), prime, x);
    ull hash_pattern = hash_func(input.pattern, prime, x);
    std::vector<int> ans;

    int table_size = hash_table_substr.size();
    for (int i = input.text.length() - input.pattern.length(); i >= 0; i--) {
        if (hash_pattern == hash_table_substr[table_size - i - 1]) {
            bool match_found = true;
            for (int j = i, k = 0; k < input.pattern.length(); k++, j++) {
                if (input.text[j] != input.pattern[k]) {
                    match_found = false;
                    break;
                }
            }
            if (match_found) {
                ans.push_back(i);
            }
        }
    }

    return ans;
}

std::vector<int> get_occurrences_naive(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    std::reverse(ans.begin(), ans.end());
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));

// bool status = true;
// int count = 0;
// while(status && count < 10000) {
//     std::cout << ++count << " " << ++count << " " << ++count << " " << ++count << '\n';
//     std::vector<int> my = get_occurrences(read_input());
//     std::vector<int> naive = get_occurrences_naive(read_input());
//     std::cout << "naive\n";
//     print_occurrences(naive);
//     std::cout << "my\n";
//     print_occurrences(my);
//     if (my.size() != naive.size()) {
//         status = false;
//         break;
//     }
//     for (int i = 0; i < naive.size(); i++) {
//         if (my[i] != naive[i]) {
//             status = false;
//             break;
//         }
//     }
// }
    return 0;
}
