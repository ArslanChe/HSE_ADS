#include <iostream>
#include <unordered_set>
#include <vector>

class BloomFilter {
public:

    BloomFilter(size_t hashes = 0, size_t bits = 0) : hashesCount(hashes), bitsCount(bits),
                                                      filter_(std::vector<int>(bits, 0)) {}

    ~BloomFilter() = default;

    void add(const std::string &obj) {
        added.insert(obj);
        for (size_t i = 0; i < hashesCount; ++i) {
            size_t hash_val = hasher(obj + std::to_string(i));
            filter_[hash_val % bitsCount]++;
        }

    }

    bool verify(const std::string &obj) {
        requestCount++;
        for (size_t i = 0; i < hashesCount; ++i) {
            size_t hash_val = hasher(obj + std::to_string(i));
            if (!filter_[hash_val % bitsCount]) {
                return false;
            }
        }
        if (added.find(obj) == added.end()) {
            errors_++;
        }
        return true;
    }

    double getFPRate() const {
        return (requestCount == 0) ? 0.0 : (errors_ + 0.0) / requestCount;
    }

    size_t numberOfHashFunctions() const {
        return hashesCount;
    }

    size_t numberOfBits() const {
        return bitsCount;
    }

private:
    std::vector<int> filter_;
    size_t hashesCount;
    size_t bitsCount;
    int errors_ = 0;
    int requestCount = 0;
    std::unordered_set<std::string> added;
    std::hash<std::string> hasher;

};