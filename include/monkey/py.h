#pragma once

#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <monkey/error.h>
#include <sstream>
#include <functional>
#include <glm/glm.hpp>

class ITable {
public:
    template <typename T>
    T get(const std::string& key) const {
        try {
            auto handle = getHandle(key);
            return cast<T>(handle);
        } catch (...) {
            GLIB_FAIL("Cannot find key " << key);
        }
    }

    template <typename T>
    T get(const std::string& key, T defaultValue) const {
        try {
            auto handle = getHandle(key);
            return cast<T>(handle, defaultValue);
        } catch (...) {
            return defaultValue;
        }
    }

    bool hasKey (const std::string& key) const {
        try {
            auto a = getHandle(key);
            if (a && !a.is_none()) {
                return true;
            }
            return false;
        } catch (...) {
            return false;
        }
    }


    template <typename T>
    T cast(pybind11::object o) const  {
        // default impl
        return o.cast<T>();
    }


    template <typename T>
    void foreach(const std::string& name, std::function<void(const T&)> f)  const {
        if (hasKey(name)) {
            auto l = getHandle(name);
            auto list = l.cast<pybind11::list>();
            for (auto &i : list) {
                pybind11::object o = i.cast<pybind11::object>();
                auto t = cast<T>(o);
                f(t);
            }
        }
    }

    template <typename T>
    T cast(pybind11::object o, T value) const {
        // default impl
        try {
            return cast<T>(o);
        } catch (...) {
            return value;
        }

    }

private:
    virtual pybind11::object getHandle (const std::string& key) const = 0;


};

//// cast to 2d - 3d - 4d vectors
template <>
inline glm::vec2 ITable::cast(pybind11::object o) const {
    auto vec = o.cast<std::vector<float>>();
    return glm::vec2(vec[0], vec[1]);
}

template <>
inline glm::vec3 ITable::cast(pybind11::object o) const  {
    auto vec = o.cast<std::vector<float>>();
    return glm::vec3(vec[0], vec[1], vec[2]);
}

template <>
inline glm::vec4 ITable::cast(pybind11::object o) const {
    auto vec = o.cast<std::vector<float>>();
    return glm::vec4(vec[0], vec[1], vec[2], vec[3]);
}


class PyTable : public ITable {
public:
    PyTable (pybind11::object o) : obj(o) {}
private:
    virtual pybind11::object getHandle (const std::string& key) const;
    pybind11::object obj;
};

class PyDict : public ITable {
public:
    PyDict (pybind11::dict o) : obj(o) {}
private:
    virtual pybind11::object getHandle (const std::string& key) const;
    pybind11::dict obj;
};

template <>
inline PyTable ITable::cast(pybind11::object o) const {
    PyTable table(o);
    return table;
}


//template <>
//inline void PyTable::foreach(const std::string& name, std::function<void(const PyTable&)> f) const {
//    if (this->hasKey(name)) {
//        auto l = obj.attr(name.c_str());
//        auto list = l.cast<pybind11::list>();
//        for (auto &i : list) {
//            PyTable t(i.cast<pybind11::object>());
//            f(t);
//        }
//    }
//}




