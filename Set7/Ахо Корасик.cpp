#include <iostream>
#include <queue>
#include <vector>

class Sol;

enum class Color {
    white,
    grey,
    black
};

struct Node {
    char prev;
    bool fl;
    Node *parent;
    Node *pointer;
    std::vector<Node *> children;
    std::vector<Node *> next;

    Color color;

    Node(char prev_, Node *parent_) {
        fl = false;
        parent = parent_;
        pointer = nullptr;
        prev = prev_;
        color = Color::white;
        children.resize(2, nullptr);
        next.resize(2, nullptr);
    }


    ~Node() {
        for (auto &_: children) {
            delete _;
        }
    }
};

Node *get_pointer_1(Node *node, Sol *st);

Node *get_pointer(Node *node, char c, Sol *st);


bool dfs(Node *n) {
    if (n->color == Color::grey) {
        return true;
    }

    if (n->fl) {
        return false;
    }

    if (n->color == Color::white) {
        n->color = Color::grey;
        for (int i = 0; i < 2; ++i) {
            if (n->next[i] && dfs(n->next[i])) {
                return true;
            }
        }
        n->color = Color::black;
    }

    return false;
}

class Sol {

public:
    Node *root;

    explicit Sol(std::vector<std::string> &viruses) {
        root = new Node('\0', nullptr);

        for (std::string &s: viruses) {
            Node *current = root;
            for (char c: s) {
                int index = c - '0';
                if (!current->children[index]) {
                    current->children[index] = new Node(c, current);
                }
                current = current->children[index];
            }
            current->fl = true;
        }

        std::queue<Node *> q;
        q.push(root);

        while (!q.empty()) {
            Node *current = q.front();
            q.pop();
            if (current) {
                if (get_pointer_1(current, this)->fl) {
                    current->fl = true;
                }
                for (int i = 0; i < 2; ++i) {
                    get_pointer(current, '0' + i, this);
                    q.push(current->children[i]);
                }
            }
        }
    }

    ~Sol() {
        delete root;
    }

    [[nodiscard]] bool hasCycle() const {
        bool hasCycle = false;
        for (int i = 0; i < 2; ++i) {
            hasCycle = hasCycle | dfs(root->next[i]);
        }
        return hasCycle;
    }
};


Node *get_pointer_1(Node *n, Sol *st) {
    if (n->pointer == nullptr) {
        if (n == st->root || n->parent == st->root) {
            n->pointer = st->root;
        } else {
            n->pointer = get_pointer(get_pointer_1(n->parent, st), n->prev, st);
        }
    }
    return n->pointer;
}

Node *get_pointer(Node *n, char c, Sol *st) {
    const int index = c - '0';
    if (n->next[index] == nullptr) {
        if (n->children[index]) {
            n->next[index] = n->children[index];
        } else if (n == st->root) {
            n->next[index] = st->root;
        } else {
            n->next[index] = get_pointer(get_pointer_1(n, st), c, st);
        }
    }
    return n->next[index];
}


int Viruses() {
    int n;
    std::cin >> n;

    std::vector<std::string> viruses(n);
    for (int i = 0; i < n; ++i) {
        std::string virus;
        std::cin >> virus;
        viruses[i] = virus;
    }
    auto tmp = Sol(viruses);
    std::cout << (tmp.hasCycle() ? "TAK" : "NIE");

    return 0;
}
