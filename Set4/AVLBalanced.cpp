#include <iostream>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode *root;
    TreeNode *insert(TreeNode *node, int val) {
        if (node == nullptr) {
            return new TreeNode(val);
        }
        if (val < node->val) {
            node->left = insert(node->left, val);
        } else if (val > node->val) {
            node->right = insert(node->right, val);
        }
        return node;
    }
    std::pair<bool, int> isBalanced(TreeNode *node) {
        if (node == nullptr) {
            return {true, -1};
        }
        auto left = isBalanced(node->left);
        auto right = isBalanced(node->right);
        if (!left.first || !right.first || std::abs(left.second - right.second) > 1) {
            return {false, std::max(left.second, right.second) + 1};
        }

        return {true, std::max(left.second, right.second) + 1};
    }

public:
    BinaryTree() : root(nullptr) {}

    void insert(int val) {
        root = insert(root, val);
    }

    bool isAVLBalanced() {
        return isBalanced(root).first;
    }
};

int AVL() {
    BinaryTree tree;

    int val;
    while (std::cin >> val && val != 0) {
        tree.insert(val);
    }
    if (tree.isAVLBalanced()) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
