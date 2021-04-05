#pragma once

#include <typeinfo>
#include <vector>

// default implementation
template <typename T>
struct TypeName
{
    static const char* Get()
    {
        return typeid(T).name();
    }
};

// a specialization for each type of those you want to support
// and don't like the string returned by typeid
template <>
struct TypeName<int> { static const char* Get() { return "int"; }};
template <>
struct TypeName<std::vector<float>> { static const char* Get() { return "vec<float>"; }};