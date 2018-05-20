#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using std::string;
using std::vector;
using std::list;
using std::cin;

using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

// class QueryProcessor {
//     int bucket_count;
//     // store all strings in one vector
//     vector<string> elems;
//     size_t hash_func(const string& s) const {
//         static const size_t multiplier = 263;
//         static const size_t prime = 1000000007;
//         unsigned long long hash = 0;
//         for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
//             hash = (hash * multiplier + s[i]) % prime;
//         return hash % bucket_count;
//     }

// public:
//     explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

//     Query readQuery() const {
//         Query query;
//         cin >> query.type;
//         if (query.type != "check")
//             cin >> query.s;
//         else
//             cin >> query.ind;
//         return query;
//     }

//     void writeSearchResult(bool was_found) const {
//         std::cout << (was_found ? "yes\n" : "no\n");
//     }

//     void processQuery(const Query& query) {
//         if (query.type == "check") {
//             // use reverse order, because we append strings to the end
//             for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
//                 if (hash_func(elems[i]) == query.ind)
//                     std::cout << elems[i] << " ";
//             std::cout << "\n";
//         } else {
//             vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
//             if (query.type == "find")
//                 writeSearchResult(it != elems.end());
//             else if (query.type == "add") {
//                 if (it == elems.end())
//                     elems.push_back(query.s);
//             } else if (query.type == "del") {
//                 if (it != elems.end())
//                     elems.erase(it);
//             }
//         }
//     }

//     void processQueries() {
//         int n;
//         cin >> n;
//         for (int i = 0; i < n; ++i)
//             processQuery(readQuery());
//     }
// };

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    // vector<string> elems;

    // stores all strings in vector of lists
    vector < list<string> > elems = vector < list<string> >(bucket_count);

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            // for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
            //     if (hash_func(elems[i]) == query.ind)
            //         std::cout << elems[i] << " ";
            // std::cout << "\n";

            list<string>::iterator it;
            for (it = elems[query.ind].begin(); it != elems[query.ind].end(); ++it)
                std::cout << *it << " ";
            std::cout << "\n";

        } else {
            // vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            size_t hash_value = hash_func(query.s);

            list<string>::iterator it;
            for (it = elems[hash_value].begin(); it != elems[hash_value].end(); ++it)
                if (*it == query.s)
                    break;

            if (query.type == "find")
                writeSearchResult(it != elems[hash_value].end());
            else if (query.type == "add") {
                if (it == elems[hash_value].end())
                    elems[hash_value].push_front(query.s);
            } else if (query.type == "del") {
                if (it != elems[hash_value].end())
                    elems[hash_value].erase(it);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
