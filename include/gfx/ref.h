#pragma once

#include <string>

class Ref {
public:
    Ref() : m_id{g_idCount++} {}
    virtual ~Ref();
    void SetTag(const std::string&);
    std::string GetTag() const;
    int GetId() const;
private:
    static int g_idCount;
    // unique identifier
    int m_id;
    std::string m_tag;
};

inline int Ref::GetId() const {
    return m_id;
}

