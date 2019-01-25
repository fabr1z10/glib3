#pragma once
#include <gfx/lua/luawrapper.h>
#include <gfx/error.h>
#include <gfx/enums.h>
#include <vector>
#include <glm/glm.hpp>
#include <unordered_map>
#include <functional>

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

template <>
inline std::vector<luabridge::LuaRef> ReadVector<luabridge::LuaRef>(luabridge::LuaRef& ref) {
    if (ref.isNil()) {
        GLIB_FAIL("Nil vector");
    }
    std::vector<luabridge::LuaRef> out;
    for (int i = 0; i < ref.length(); ++i) {
        luabridge::LuaRef r = ref[i+1];
        out.push_back(r);
    }
    return out;

}






class LuaTable {
public:
    explicit LuaTable(luabridge::LuaRef ref) : m_ref(ref) {}
    LuaTable(const std::string&);
    bool isNil () const;
    template <typename T>
    T Get(const std::string& key) const {
        luabridge::LuaRef ref = m_ref[key];
        if (ref.isNil())
            GLIB_FAIL("Unknown value " << key);
        return ref.cast<T>();
    }
    
    //template<> glm::vec2 Get<glm::vec2>(const std::string&);
    //template<> glm::vec3 Get<glm::vec3>(const std::string&);
    
    template <typename T>
    T Get(const std::string& key, T defaultValue) const {
        luabridge::LuaRef ref = m_ref[key];
        if (ref.isNil())
            return defaultValue;
        return Get<T>(key);
    }
    
    
    bool HasKey (const std::string& key) const {
        return !(m_ref[key].isNil());
    }

    template <typename T>
    void Set(const std::string& key, T value) {
        m_ref[key] = value;

    }


    template <typename T>
    std::vector<T> GetVector (const std::string& key, bool required = false) const {
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
    static std::unordered_map<std::string, luabridge::LuaRef> getKeyValueMap(const luabridge::LuaRef& ref);
    static std::unordered_map<int, luabridge::LuaRef> getIntValueMap(const luabridge::LuaRef& ref);
private:
    luabridge::LuaRef m_ref;
};

inline bool LuaTable::isNil() const {
    return m_ref.isNil();
}

template<>
inline glm::vec2 LuaTable::Get<glm::vec2>(const std::string& key) const {
    luabridge::LuaRef ref = m_ref[key];
    if (ref.isNil())
        GLIB_FAIL("Unknown value " << key);
    glm::vec2 out;
    out.x = ref[1].cast<float>();
    out.y = ref[2].cast<float>();
    return out;
}

template<>
inline glm::ivec2 LuaTable::Get<glm::ivec2>(const std::string& key) const {
    luabridge::LuaRef ref = m_ref[key];
    if (ref.isNil())
    GLIB_FAIL("Unknown value " << key);
    glm::ivec2 out;
    out.x = ref[1].cast<int>();
    out.y = ref[2].cast<int>();
    return out;
}



template<>
inline glm::vec3 LuaTable::Get<glm::vec3>(const std::string& key) const {
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
inline glm::vec4 LuaTable::Get<glm::vec4>(const std::string& key) const {
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

template<>
inline TextAlignment LuaTable::Get<TextAlignment>(const std::string& key) const {
    std::string as = m_ref[key].cast<std::string>();
    if (as == "bottomleft")
        return BOTTOM_LEFT;
    else if (as == "bottomright")
        return BOTTOM_RIGHT;
    else if (as == "bottom")
        return BOTTOM;
    else if (as == "topleft")
        return TOP_LEFT;
    else if (as == "topright")
        return TOP_RIGHT;
    else if (as == "top")
        return TOP;
    else if (as == "center")
        return CENTER;
    GLIB_FAIL("Unknown text alignment " << as);
    
    
}

void lua_loop_array (luabridge::LuaRef ref, std::function<void(const LuaTable&)>);
