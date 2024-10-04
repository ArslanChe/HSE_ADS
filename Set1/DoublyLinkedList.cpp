#include <vector>
#include <stdexcept>
#include <algorithm>
#include <set>


struct Node {
    int data;
    Node *previous;
    Node *next;

    Node() {
        next = nullptr;
        previous = nullptr;
    }

    Node(int value) {
        data = value;
        previous = nullptr;
        next = nullptr;
    }
};

class DoublyLinkedList {
public:
    Node *head;
    Node *tail;

    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    DoublyLinkedList(const DoublyLinkedList &other) {
        head = nullptr;
        tail = nullptr;
        Node *current = other.head;
        while (current != nullptr) {
            pushBack(current->data);
            current = current->next;
        }
    }

    DoublyLinkedList(const std::vector<int> &array) {
        head = nullptr;
        tail = nullptr;
        for (int value: array) {
            pushBack(value);
        }
    }

    ~DoublyLinkedList() {
        erase();
    }


    void pushBack(int value) {
        Node *node = new Node(value);
        node->previous = tail;
        if (head == nullptr) {
            head = node;
        }
        if (tail != nullptr) {
            tail->next = node;
        }

        tail = node;
    }

    void pushFront(int value) {
        Node *node = new Node(value);
        node->next = head;
        if (tail == nullptr) {
            tail = node;
        }
        if (head != nullptr) {
            head->previous = node;
        }

        head = node;
    }

    void insert(Node *prev, int value) {
        if (prev == nullptr) {
            throw std::runtime_error("Wrong position for insertion!");

        }
        bool fl = false;
        Node *current = head;
        while (current != nullptr) {
            if (current == prev) {
                fl = true;
            }
            current = current->next;
        }
        if (!fl) {
            throw std::runtime_error("Wrong position for insertion!");
        }
        Node *newNode = new Node(value);
        newNode->previous = prev;

        if (prev == tail) {
            prev->next = newNode;
            newNode->next = nullptr;
            tail = newNode;
        } else {
            prev->next->previous = newNode;
            newNode->next = prev->next;
            prev->next = newNode;
        }
    }

    void popBack() {
        if (tail == nullptr) {
            throw std::runtime_error("Deletion error!");
        }
        if (tail->previous == nullptr) {
            delete tail;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node *ntail = tail;
        tail = tail->previous;
        delete ntail;
    }

    void popFront() {
        if (head == nullptr) {
            throw std::runtime_error("Deletion error!");
        }
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node *nhead = head;
        head = head->next;
        delete nhead;
    }

    void pop(Node *pos) {
        if (pos == nullptr) {
            throw std::runtime_error("Wrong position for deletion!");
        }
        bool fl = false;
        for (Node *cur = head; cur != nullptr; cur = cur->next) {
            if (cur == pos) {
                fl = true;
                break;
            }
        }
        if (!fl) {
            throw std::runtime_error("Wrong position for deletion!");
        }

        Node *prev = pos->previous;
        Node *next = pos->next;
        if (next != nullptr) {
            next->previous = prev;
        } else {
            tail = prev;
        }
        if (prev != nullptr) {
            prev->next = next;
        } else {
            head = next;
        }
        delete pos;
    }

    void erase() {
        while (head != nullptr) {
            popBack();
        }
    }

    void reverse() {
        Node *current = head;
        while (current != nullptr) {
            Node *tmp = current->next;
            current->next = current->previous;
            current->previous = tmp;
            current = tmp;
        }
        Node *tmp = head;
        head = tail;
        tail = tmp;
    }

    void replace(int el, int new_el) {
        for (Node *cur = head; cur != nullptr; cur = cur->next) {
            if (cur->data == el) {
                cur->data = new_el;
            }
        }
    }

    void removeDuplicates() {
        std::set<int> uniqueValues;

        for (Node *cur = head; cur != nullptr; cur = cur->next) {
            if (!uniqueValues.count(cur->data)) {
                uniqueValues.insert(cur->data);
            } else {
                Node *temp = cur;
                cur = cur->next;
                pop(temp);
                continue;
            }
        }
    }
};
