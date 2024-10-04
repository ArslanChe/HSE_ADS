#include <iostream>
#include <stdexcept>
#include <cstdint>
#include <functional>

template<class KeyType, class ValueType>
struct Node {
    KeyType key_;
    ValueType value_;
    Node *next_;

    Node(KeyType key, ValueType value) : key_(key), value_(value), next_(nullptr) {}
};

template<class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
private:
    std::vector<Node<KeyType, ValueType> *> table;
    size_t table_capacity;
    size_t table_size;
    double load_factor;
    Func hasher;

    void rehash() {
        size_t new_capacity = 2 * table_capacity;
        std::vector<Node<KeyType, ValueType> *> new_table(new_capacity, nullptr);

        for (size_t i = 0; i < table_capacity; ++i) {
            Node<KeyType, ValueType> *current = table[i];
            while (current != nullptr) {
                uint64_t new_hash = hasher(current->key_) % new_capacity;
                Node<KeyType, ValueType> *temp = current->next_;
                current->next_ = new_table[new_hash];
                new_table[new_hash] = current;
                current = temp;
            }
        }
        table.swap(new_table);
        table_capacity = new_capacity;
    }

public:
    HashTable(size_t capacity, double coeff, Func hasher_ = std::hash<KeyType>())
            : table(std::vector<Node<KeyType, ValueType> *>(capacity, nullptr)), table_capacity(capacity),
              table_size(0),
              load_factor((coeff > 0 && coeff <= 1) ? coeff : 0.5), hasher(hasher_) {

    }

    HashTable() : table(std::vector<Node<KeyType, ValueType> *>(100, nullptr)), table_capacity(100), table_size(0),
                  load_factor(0.5), hasher(Func()) {}

    HashTable(Func hasher_) : table(std::vector<Node<KeyType, ValueType> *>(100, nullptr)), table_capacity(100),
                              table_size(0), load_factor(0.5), hasher(hasher_) {}

    ~HashTable() {
        for (size_t i = 0; i < table_capacity; ++i) {
            Node<KeyType, ValueType> *current = table[i];
            while (current != nullptr) {
                Node<KeyType, ValueType> *temp = current;
                current = current->next_;
                delete temp;
            }
        }
    }

    void erase(KeyType key) {
        size_t hash_code = hasher(key) % table_capacity;
        Node<KeyType, ValueType> *current = table[hash_code];
        Node<KeyType, ValueType> *prev = nullptr;

        while (current) {
            if (current->key_ == key) {
                if (prev) {
                    prev->next_ = current->next_;
                } else {
                    table[hash_code] = current->next_;
                }
                delete current;
                --table_size;
                return;
            }
            prev = current;
            current = current->next_;
        }
    }

    void insert(KeyType key, ValueType value) {
        size_t hash_code = hasher(key) % table_capacity;
        auto *newNode = new Node<KeyType, ValueType>(key, value);
        if (table[hash_code] == nullptr) {
            table[hash_code] = newNode;
        } else {
            Node<KeyType, ValueType> *current = table[hash_code];
            while (current->next_) {
                if (current->key_ == key) {
                    current->value_ = value;
                    delete newNode;
                    return;
                }
                current = current->next_;
            }
            if (current->key_ == key) {
                current->value_ = value;
                delete newNode;
                return;
            }
            current->next_ = newNode;
        }
        ++table_size;

        if ((static_cast<double>(table_size) / table_capacity) > load_factor) {
            rehash();
        }
    }

    ValueType *find(KeyType key) {
        uint64_t hash = hasher(key) % table_capacity;
        Node<KeyType, ValueType> *current = table[hash];
        while (current != nullptr) {
            if (current->key_ == key) {
                return &(current->value_);
            }
            current = current->next_;
        }
        return nullptr;
    }


    Node<KeyType, ValueType> &operator[](uint64_t hash) {
        if (hash >= table_capacity) {
            throw std::out_of_range("");
        }

        if (table[hash] == nullptr) {
            throw std::runtime_error("");
        }

        return *(table[hash]);
    }

    Node<KeyType, ValueType> at(uint64_t hash) {
        if (hash >= table_capacity) {
            throw std::out_of_range("");
        }

        if (table[hash] == nullptr) {
            throw std::runtime_error("");
        }

        return *table[hash];
    }

    size_t size() const {
        return table_size;
    }

    size_t capacity() const {
        return table_capacity;
    }
};

