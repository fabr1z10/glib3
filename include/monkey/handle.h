#pragma once

#include <monkey/monkey.h>

template<typename T>
class Handle {
public:
    Handle() : m_ref(nullptr), m_id(-1) {}
    Handle (T* ref) : m_ref(ref), m_id(ref->GetId()) {}
    T* operator->() const { return m_ref; }
    bool isValid() const {
        return Monkey::get().isAlive(m_ref->GetId());
    }
    T* get() {
        return m_ref;
    }
private:
    T* m_ref;
    int m_id;

};

