#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  long long key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(long long key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void in_order_traversal(int node_index, const vector<Node>& tree, vector <long long>& result) {
  if (node_index != -1) {
    in_order_traversal(tree[node_index].left, tree, result);
    result.push_back(tree[node_index].key);
    in_order_traversal(tree[node_index].right, tree, result);
  }
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  if (tree.size() == 0) {
    return true;
  }

  vector<long long> in_ord_tr;
  in_order_traversal(0, tree, in_ord_tr);

  for (int i = 0; i < in_ord_tr.size() - 1; i++) {
    if (in_ord_tr[i] >= in_ord_tr[i + 1])
      return false;
  }

  return true;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    long long key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
