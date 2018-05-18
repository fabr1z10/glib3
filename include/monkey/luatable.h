#pragma once
#include <monkey/luawrapper.h>
#include <gfx/error.h>
#include <vector>
#include <glm/glm.hpp>

class LuaTable {
public:
    LuaTable(const std::string&);
    bool isNil () const;
    template <typename T>
    T Get(const std::string& key) {
        luabridge::LuaRef ref = m_ref[key];
        if (ref.isNil())
            GLIB_FAIL("Unknown value " << key);
        return ref.cast<T>();
    }
    template <typename T>
    T Get(const std::string& key, T defaultValue) {
        luabridge::LuaRef ref = m_ref[key];
        if (ref.isNil())
            return defaultValue;
        return ref.cast<T>();
    }

    template <typename T>
    void Set(const std::string& key, T value) {
        m_ref[key] = value;

    }


    template <typename T>
    std::vector<T> GetVector (const std::string& key, bool required = false) {
        luabridge::LuaRef ref = m_ref[key];
        if (ref.isNil()) {
            if (required) {
                GLIB_FAIL("Missing required vector " << key);
            }
            else {
                return std::vector<T>();
            }
        }
        std::vector<T> out;
        for (int i = 0; i < ref.length(); ++i) {
            luabridge::LuaRef r = ref[i+1];
            out.push_back(r.cast<T>());
        }
        return out;

    }

private:
    luabridge::LuaRef m_ref;
};

inline bool LuaTable::isNil() const {
    return m_ref.isNil();
}

template<>
inline glm::vec2 LuaTable::Get<glm::vec2>(const std::string& key) {
    luabridge::LuaRef ref = m_ref[key];
    if (ref.isNil())
        GLIB_FAIL("Unknown value " << key);
    glm::vec2 out;
    out.x = ref[1].cast<float>();
    out.y = ref[2].cast<float>();
    return out;

}


