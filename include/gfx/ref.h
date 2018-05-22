#pragma once

#include <string>

class Ref {
public:
    Ref() {}
    virtual ~Ref();
    void SetTag(const std::string&);
    std::string GetTag() const;
private:
    std::string m_tag;
};

