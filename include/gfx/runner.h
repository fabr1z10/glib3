#pragma once

#include <gfx/ref.h>

class Runner : public Ref {
    
public:
    Runner() : Ref(), m_active{true} {}
    virtual void Update(double) = 0;
    bool isActive() const;
    void setActive(bool);
private:
    bool m_active;
};


inline bool Runner::isActive() const {
    return m_active;
}

inline void Runner::setActive(bool value) {
    m_active = value;
};
