#pragma once

#include <string>
#include <unordered_map>

class Ref {
public:
    Ref();
    virtual ~Ref();
    void SetTag(const std::string&);
    std::string GetTag() const;
    int GetId() const;
    static Ref* Get(int);
private:
    static int g_idCount;
    static std::unordered_map<int, Ref*> g_refs;
    // unique identifier
    int m_id;
    std::string m_tag;

};

inline int Ref::GetId() const {
    return m_id;
}

