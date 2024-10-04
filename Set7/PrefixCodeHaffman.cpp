#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct Node {
    char data;
    int freq;
    Node *left;
    Node *right;

    ~Node() {
        delete left;
        delete right;
    }

    Node(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {

    }

    Node() = default;
};

struct Compare {
    bool operator()(Node *l, Node *r) {
        return l->freq > r->freq;
    }
};

Node *createNode(char data, int freq, Node *left, Node *right) {
    Node *node = new Node();
    node->data = data;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

void encode(Node *root, const string &str, map<char, string> &huffmanCode) {
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->data] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void buildHuffmanTree(const string &text) {
    unordered_map<char, int> freq(128);
    for (char ch: text) {
        freq[ch]++;
    }

    priority_queue<Node *, vector<Node *>, Compare> pq;

    for (auto pair: freq) {
        pq.push(createNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1) {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        int sumFreq = left->freq + right->freq;
        pq.push(createNode('\0', sumFreq, left, right));
    }

    Node *root = pq.top();

    map<char, string> huffmanCode;
    encode(root, "", huffmanCode);
    string encodedString;
    for (char ch: text) {
        encodedString += huffmanCode[ch];
    }
    cout << huffmanCode.size() << " " << encodedString.size() << endl;
    for (const auto &pair: huffmanCode) {
        cout << pair.first << ": " << pair.second << endl;
    }
    delete root;

    cout << encodedString << endl;
}


int PrefixCodeHaffman() {
    string s;
    getline(cin, s);
    if (std::all_of(s.begin(), s.end(), [&s](int i) { return i == s[0]; })) {
        cout << "1 " << s.size() << endl;
        cout << s[0] << ": 0" << endl;
        for ([[maybe_unused]] char _: s) {
            cout << "0";
        }
    } else { buildHuffmanTree(s); }
    return 0;
}
