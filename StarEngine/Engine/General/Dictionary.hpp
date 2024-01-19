//
// Created by ReSung on 2021-09-11.
//

#ifndef B_OBJ_DICTIONARY_HPP
#define B_OBJ_DICTIONARY_HPP

#include <vector>
#include <iostream>
#include <glm/fwd.hpp>

template<typename Key, typename Val>
class Dictionary {
private:
    std::vector<Key> keys{};
    std::vector<Val> values{};

public:
    Dictionary() = default;

    void Add(Key k, Val v) {
        if(GetIndex(k) == -1) {
            keys.push_back(k);
            values.push_back(v);
        } else {
            std::cout << "Element with key: " << k << " already in map" << std::endl;
        }
    };
    Val Get(Key k){
        int index = GetIndex(k);
        if(index>-1) {
            return values[index];
        }
        return nullptr;
    };
    int GetIndex(Key k) {
        int i = 0;
        for(Key sk : keys) {
            if(sk == k) {
                return i;
            }
            i++;
        }
        return -1;
    };
    void Del(Key k) {
        int index = GetIndex(k);
        if(index>-1) {
            keys.erase(index);
            delete(values[index]);
            values.erase(index);
        } else {
            std::cout << "Element with key: " << k << " not in map" << std::endl;
        }
    };
    void Clear() {
        keys.clear();
        values.clear();
    };

    Val GetAtIndex(glm::uint32_t index) {
        return values[index];
    }

    glm::uint32_t Size() { return keys.size(); }

    std::vector<Val> GetAll() { return values; }

    auto begin() { return values.begin(); }
    auto end() { return values.end(); }
    auto begin() const { return values.begin(); }
    auto end() const { return values.end(); }
};

#endif //B_OBJ_DICTIONARY_HPP
