#pragma once
#include <monkey/luawrapper.h>
#include <gfx/error.h>
#include <vector>
#include <glm/glm.hpp>

template <typename T>
std::vector<T> ReadVector(luabridge::LuaRef& ref) {
    if (ref.isNil()) {
        GLIB_FAIL("Nil vector");
    }
    std::vector<T> out;
    for (int i = 0; i < ref.length(); ++i) {
        luabridge::LuaRef r = ref[i+1];
        out.push_back(r.cast<T>());
    }
    return out;
}

class LuaTable {
public:
    explicit LuaTable(luabridge::LuaRef ref) : m_ref(ref) {}
    LuaTable(const std::string&);
    bool isNil () const;
    template <typename T>
    T Get(const std::string& key) {
        luabridge::LuaRef ref = m_ref[key];
        if (ref.isNil())
            GLIB_FAIL("Unknown value " << key);
        return ref.cast<T>();
    }
    
    //template<> glm::vec2 Get<glm::vec2>(const std::string&);
    //template<> glm::vec3 Get<glm::vec3>(const std::string&);
    
    template <typename T>
    T Get(const std::string& key, T defaultValue) {
        luabridge::LuaRef ref = m_ref[key];
        if (ref.isNil())
            return defaultValue;
        return Get<T>(key);
    }
    
    
    bool HasKey (const std::string& key) {
        return !(m_ref[key].isNil());
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
        return ReadVector<T>(ref);
//        std::vector<T> out;
//        for (int i = 0; i < ref.length(); ++i) {
//            luabridge::LuaRef r = ref[i+1];
//            out.push_back(r.cast<T>());
//        }
//        return out;

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

template<>
inline glm::vec3 LuaTable::Get<glm::vec3>(const std::string& key) {
    luabridge::LuaRef ref = m_ref[key];
    if (ref.isNil())
        GLIB_FAIL("Unknown value " << key);
    glm::vec3 out;
    out.x = ref[1].cast<float>();
    out.y = ref[2].cast<float>();
    out.z = ref[3].cast<float>();
    return out;
}

template<>
inline glm::vec4 LuaTable::Get<glm::vec4>(const std::string& key) {
    luabridge::LuaRef ref = m_ref[key];
    if (ref.isNil())
        GLIB_FAIL("Unknown value " << key);
    glm::vec4 out;
    out.x = ref[1].cast<float>();
    out.y = ref[2].cast<float>();
    out.z = ref[3].cast<float>();
    out.w = ref[4].cast<float>();
    return out;
}
