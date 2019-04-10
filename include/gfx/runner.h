#pragma once

#include <gfx/ref.h>
#include <typeindex>


class Runner : public Ref {
    
public:
    Runner() : Ref(), m_active{true} {}
    virtual ~Runner(){}
    virtual void Init () {}
    virtual void Update(double) = 0;
    bool isActive() const;
    void setActive(bool);
    virtual std::type_index GetType();
private:
    bool m_active;
};


inline bool Runner::isActive() const {
    return m_active;
}

inline void Runner::setActive(bool value) {
    m_active = value;
};

inline std::type_index Runner::GetType() {
    return std::type_index(typeid(*this));
}
