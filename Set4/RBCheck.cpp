#include <iostream>
#include <vector>

enum Color {
    RED, BLACK
};

struct Node {
    int key;
    Color color = BLACK;
    int black_height = 0;
    int left = 0;
    int right = 0;

    Node(int n, int l, int r, Color c) : key(n), left(l), right(r), color(c) {}

    Node() = default;
};

bool CheckBH(std::vector<Node *> &tree, int index) {
    if (tree[tree[index]->right]->black_height != tree[tree[index]->left]->black_height)
        return false;
    tree[index]->black_height = tree[tree[index]->right]->black_height;
    if (tree[index]->color == BLACK)
        ++tree[index]->black_height;
    return true;
}

bool CheckC(std::vector<Node *> &tree, int index) {
    return !(tree[index]->color != BLACK &&
             (tree[tree[index]->left]->color == RED || tree[tree[index]->right]->color == RED));
}


bool CheckRB(std::vector<Node *> &tree, int index) {

    return index == 0 ||
           CheckRB(tree, tree[index]->left) && CheckRB(tree, tree[index]->right)
           && CheckC(tree, index)
           && CheckBH(tree, index);
}

bool CheckBinary(std::vector<Node *> &tree, int index, int min, int max) {
    if (min > max)
        return false;
    if (index == 0)
        return true;
    if (tree[index]->key > max || min > tree[index]->key)
        return false;
    return CheckBinary(tree, tree[index]->left, min, tree[index]->key) &&
           CheckBinary(tree, tree[index]->right, tree[index]->key, max);
}

int RBCheck() {
    int n, root, key, number;
    std::string left, right, color;
    std::cin >> n;
    if (n == 0) {
        std::cout << "NO" << std::endl;
        return 0;
    }
    std::cin >> root;
    std::vector<Node *> tree(n + 1);
    for (int i = 0; i < n + 1; ++i)
        tree[i] = new Node();
    for (int i = 1; i < n + 1; ++i) {
        std::cin >> number >> key >> left >> right >> color;
        tree[number]->key = key;
        if (left != "null")
            tree[number]->left = stoi(left);
        if (right != "null")
            tree[number]->right = stoi(right);
        if (color == "R")
            tree[number]->color = RED;
    }

    if (!CheckBinary(tree, root, -1000000001, 1000000001) || !CheckRB(tree, root))
        std::cout << "NO" << std::endl;
    else
        std::cout << "YES" << std::endl;
    return 0;
}
