#pragma once

#include <glm/glm.hpp>
#include <functional>
#include <string>

template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {
    template<typename S, typename T>
    struct hash<pair < S, T>> {
    inline size_t operator()(const pair <S, T> &v) const {
        size_t seed = 0;
        ::hash_combine(seed, v.first);
        ::hash_combine(seed, v.second);
        return seed;
    }
};

template<>
struct hash<glm::vec2> {
    inline size_t operator()(const glm::vec2 &v) const {
        size_t seed = 0;
        ::hash_combine(seed, v.x);
        ::hash_combine(seed, v.y);
        return seed;
    }
};

template<>
struct hash<std::pair<std::string, int>> {
    inline size_t operator()(std::pair<std::string, int> p) const {
        size_t seed = 0;
        ::hash_combine(seed, p.first);
        ::hash_combine(seed, p.second);
        return seed;
    }
};

template<>
struct hash<glm::ivec3> {
    inline size_t operator()(const glm::ivec3& p) const {
        size_t seed = 0;
        ::hash_combine(seed, p.x);
        ::hash_combine(seed, p.y);
        ::hash_combine(seed, p.z);
        return seed;
    }
};

}
