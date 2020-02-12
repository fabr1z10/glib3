#pragma once

#include <monkey/ref.h>
#include <typeindex>


class Runner : public Ref {
public:
    Runner() : Ref() {}
    Runner (const LuaTable& t) : Ref(t) {}
    virtual ~Runner(){}
    virtual void Init () {}
    virtual void Update(double) = 0;
    virtual std::type_index GetType();
};


inline std::type_index Runner::GetType() {
    return std::type_index(typeid(*this));
}
