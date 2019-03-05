#pragma once

#include <string>
#include <unordered_map>
#include <gfx/error.h>


class Ref {
public:
    Ref();
    virtual ~Ref();
    std::string GetTag() const;
    void SetTag(const std::string&);
    int GetId() const;
    static Ref* Get(int);
    template<class T>
    static T* GetFromId(int id) {
        auto it = g_refs.find(id);
        if (it == g_refs.end()) {
            GLIB_FAIL("Unknown id!");
        }
        return dynamic_cast<T*>(it->second);
    }

    bool IsAlive(int);
private:
    static int g_idCount;
    static std::unordered_map<int, Ref*> g_refs;
    // unique identifier
    int m_id;
    std::string m_tag;

};


inline std::string Ref::GetTag() const {
    return m_tag;
}
inline int Ref::GetId() const {
    return m_id;
}

