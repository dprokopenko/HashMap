#include <bits/stdc++.h>

using namespace std;

template<class KeyType, class ValueType, class Hash = hash<KeyType>>
class HashMap {
    typedef typename list<pair<const KeyType, ValueType>>::iterator IteratorPair;
    Hash Hasher;
    list<pair<const KeyType, ValueType>> HashArray;
    vector<list<IteratorPair>> HashTable;
public:
    HashMap(Hash Hasher = Hash()) : Hasher(Hasher), HashTable(1) {
    }
    template<class Iter>
    HashMap(Iter first, Iter last, Hash Hasher = Hash()) : HashMap(Hasher) {
        for (Iter iter = first; iter != last; ++iter) {
            insert(*iter);
        }
    }
    HashMap(initializer_list<pair<const KeyType, ValueType>> init) : HashMap() {
        for (const auto& key : init) {
            insert(key);
        }
    }
    int size() const {
        return HashArray.size();
    }
    bool empty() const {
        return HashArray.empty();
    }
    Hash hash_function() const {
        return Hasher;
    }
    void insert(pair<const KeyType, ValueType> key) {
        int pos = Hasher(key.first) % HashTable.size();
        for (const auto& iter : HashTable[pos]) {
            if (iter->first == key.first) {
                return;
            }
        }
        HashTable[pos].push_back(HashArray.insert(HashArray.begin(), key));
        if (HashArray.size() >= HashTable.size()) {
            vector<list<IteratorPair>> newHashTable(HashTable.size() << 1);
            for (IteratorPair iter = HashArray.begin(); iter != HashArray.end(); ++iter) {
                newHashTable[Hasher(iter->first) % newHashTable.size()].push_back(iter);
            }
            HashTable = newHashTable;
        }
    }
    void erase(KeyType key) {
        int pos = Hasher(key) % HashTable.size();
        for (auto iter = HashTable[pos].begin(); iter != HashTable[pos].end(); ++iter) {
            if ((*iter)->first == key) {
                HashArray.erase(*iter);
                HashTable[pos].erase(iter);
                return;
            }
        }
    }
    typedef typename list<pair<const KeyType, ValueType>>::iterator iterator;
    typedef typename list<pair<const KeyType, ValueType>>::const_iterator const_iterator;
    iterator begin() {
        return HashArray.begin();
    }
    const_iterator begin() const {
        return HashArray.begin();
    }
    iterator end() {
        return HashArray.end();
    }
    const_iterator end() const {
        return HashArray.end();
    }
    iterator find(KeyType key) {
        int pos = Hasher(key) % HashTable.size();
        for (const auto& iter : HashTable[pos]) {
            if (iter->first == key) {
                return iter;
            }
        }
        return HashArray.end();
    }
    const_iterator find(KeyType key) const {
        int pos = Hasher(key) % HashTable.size();
        for (const auto& iter : HashTable[pos]) {
            if (iter->first == key) {
                return iter;
            }
        }
        return HashArray.end();
    }
    ValueType& operator[](KeyType key) {
        int pos = Hasher(key) % HashTable.size();
        for (const auto& iter : HashTable[pos]) {
            if (iter->first == key) {
                return iter->second;
            }
        }
        HashTable[pos].push_back(HashArray.insert(HashArray.begin(), make_pair(key, ValueType())));
        if (HashArray.size() >= HashTable.size()) {
            vector<list<IteratorPair>> newHashTable(HashTable.size() << 1);
            for (IteratorPair iter = HashArray.begin(); iter != HashArray.end(); ++iter) {
                newHashTable[Hasher(iter->first) % newHashTable.size()].push_back(iter);
            }
            HashTable = newHashTable;
        }
        return HashArray.begin()->second;
    }
    const ValueType& at(KeyType key) const {
        int pos = Hasher(key) % HashTable.size();
        for (const auto& iter : HashTable[pos]) {
            if (iter->first == key) {
                return iter->second;
            }
        }
        throw out_of_range("HashTable has no this element!");
    }
    void clear() {
        while (HashArray.begin() != HashArray.end()) {
            erase(HashArray.begin()->first);
        }
    }
};

int main() {
}
