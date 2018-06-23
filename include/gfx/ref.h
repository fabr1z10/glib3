#pragma once

#include <string>
#include <unordered_map>

class Ref {
public:
    Ref();
    virtual ~Ref();
    std::string GetTag() const;
    void SetTag(const std::string&);

    int GetId() const;
    static Ref* Get(int);
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

