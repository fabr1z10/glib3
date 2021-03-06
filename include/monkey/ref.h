#pragma once

#include <string>
#include <monkey/object.h>
#include <monkey/itable.h>
#include <unordered_map>
#include <monkey/error.h>
#include <memory>


class __attribute__ ((visibility ("default"))) Ref : public Object {
public:
    Ref();
    Ref(const Ref&);
    Ref(const ITab&);
    ~Ref() override;
    std::string GetTag() const;
    void SetTag(const std::string&);
    int GetId() const;
    static void dump ();
    //virtual std::string toString();
    // bool IsAlive(int);
    virtual void setActive(bool);
    bool isActive() const;
protected:
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

