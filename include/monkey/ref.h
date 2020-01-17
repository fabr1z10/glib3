#pragma once

#include <string>
#include <unordered_map>
#include <monkey/error.h>
#include <memory>

class Ref {
public:
    template <typename T, typename ...Args>
    static std::shared_ptr<T> Create (Args... a) {
        auto ptr = std::make_shared<T>(a...);
        g_refs[ptr->GetId()] = ptr;
        return ptr;
    }

    template <typename T>
    static std::shared_ptr<T> Clone (const T& orig) {
        auto ptr = std::make_shared<T>(orig);
        g_refs[ptr->GetId()] = ptr;
        return ptr;

    }


    virtual ~Ref();
    std::string GetTag() const;
    void SetTag(const std::string&);
    int GetId() const;
    static int GetId(const std::string &tag) {
        auto it = g_taggedRefs.find(tag);
        if (it == g_taggedRefs.end())
            return -1;
        auto ptr = it->second.lock();
        if (ptr) {
            return ptr->GetId();
        }
        return -1;

    }

    template<class T>
    static std::shared_ptr<T> Get(int id) {
        auto it = g_refs.find(id);
        if (it == g_refs.end()) {
            GLIB_FAIL("Unknown id!");
        }
        return std::dynamic_pointer_cast<T>(std::shared_ptr<Ref>(it->second));
    }



    template<class T>
    static std::shared_ptr<T> Get(const std::string& tag) {
        auto it = g_taggedRefs.find(tag);
        if (it == g_taggedRefs.end()) {
            GLIB_FAIL("Unknown tag!");
        }
        return std::dynamic_pointer_cast<T>(std::shared_ptr<Ref>(it->second));
    }

    static bool isAlive(int);
    static void dump ();
    virtual std::string toString();
    // bool IsAlive(int);
    virtual void setActive(bool);
    bool isActive() const;
    static std::unordered_map<int, std::weak_ptr<Ref>> g_refs;

protected:
    Ref();
    Ref(const Ref&);
    static int g_idCount;
    static std::unordered_map<std::string, std::weak_ptr<Ref>> g_taggedRefs;

    // unique identifier
    int m_id;
    std::string m_tag;
    bool m_active;
};


inline std::string Ref::GetTag() const {
    return m_tag;
}
inline int Ref::GetId() const {
    return m_id;
}

inline void Ref::setActive(bool value) {
    m_active = value;
}
inline bool Ref::isActive() const {
    return m_active;
}

