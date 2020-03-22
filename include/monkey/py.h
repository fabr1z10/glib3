#pragma once

#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <monkey/error.h>
#include <sstream>
#include <functional>
#include <glm/glm.hpp>


// wrapper for python dictionary with error checking
//class PyDict {
//public:
//    //PyTable () {}
//    PyDict (pybind11::dict d) : dict(d) {}
//
//    template <typename T>
//    T get(const std::string& key) const {
//        try {
//            auto o = dict[key.c_str()];
//            return cast<T>(o);
//        } catch (...) {
//            GLIB_FAIL("Cannot find key " << key);
//        }
//    }
//
//    template <typename T>
//    T get(const std::string& key, T defaultValue) const {
//        try {
//            auto o = dict[key.c_str()];
//            return cast<T>(o, defaultValue);
//        } catch (...) {
//            GLIB_FAIL("Cannot find key " << key);
//        }
//    }
//
//
//    bool hasKey (const std::string& key) const {
//        return dict.contains(key);
//    }
//
//private:
//    template <typename T>
//    T cast(pybind11::detail::str_attr_accessor o) const {
//        // default impl
//        return o.cast<T>();
//    }
//
//    template <typename T>
//    T cast(pybind11::detail::str_attr_accessor o, T value) const {
//        // default impl
//        try {
//            return o.cast<T>();
//        } catch (...) {
//            return value;
//        }
//
//    }
//
//
//    pybind11::dict dict;
//};

// wrapper for python dictionary with error checking

class PyTable {
public:
    //PyTable () {}
    PyTable (pybind11::object o) : obj(o) {}

    template <typename T>
    T get(const std::string& key) const {
        try {
            auto o = obj.attr(key.c_str());
            return cast<T>(o);
        } catch (...) {
            GLIB_FAIL("Cannot find key " << key);
        }
    }

    template <typename T>
    T get(const std::string& key, T defaultValue) const {
        try {
            auto o = obj.attr(key.c_str());
            return cast<T>(o, defaultValue);
        } catch (...) {
            GLIB_FAIL("Cannot find key " << key);
        }
    }


    bool hasKey (const std::string& key) const {
        try {
            auto a = obj.attr(key.c_str());
            if (a && !a.is_none()) {
                return true;
            }
            return false;
        } catch (...) {
            return false;
        }
    }

    void processVector (const std::string& name, std::function<void(const pybind11::handle&)> f) const;

    template <typename T>
    void foreach(const std::string& name, std::function<void(const T&)> f) const {
        if (hasKey(name)) {
            auto l = obj.attr(name.c_str());
            auto list = l.cast<pybind11::list>();
            for (auto &i : list) {
                auto t = i.cast<T>();
                f(t);
            }
        }
    }


private:
    template <typename T>
    T cast(pybind11::detail::str_attr_accessor o) const {
        // default impl
        return o.cast<T>();
    }

    template <typename T>
    T cast(pybind11::detail::str_attr_accessor o, T value) const {
        // default impl
        try {
            return cast<T>(o);
        } catch (...) {
            return value;
        }

    }


    pybind11::object obj;
};

template <>
inline void PyTable::foreach(const std::string& name, std::function<void(const PyTable&)> f) const {
    if (this->hasKey(name)) {
        auto l = obj.attr(name.c_str());
        auto list = l.cast<pybind11::list>();
        for (auto &i : list) {
            PyTable t(i.cast<pybind11::object>());
            f(t);
        }
    }
}


//// cast to 2d - 3d - 4d vectors
template <>
inline glm::vec2 PyTable::cast(pybind11::detail::str_attr_accessor o) const {
    auto vec = o.cast<std::vector<int>>();
    return glm::vec2(vec[0], vec[1]);
}

template <>
inline glm::vec3 PyTable::cast(pybind11::detail::str_attr_accessor o) const {
    auto vec = o.cast<std::vector<int>>();
    return glm::vec3(vec[0], vec[1], vec[2]);
}

template <>
inline glm::vec4 PyTable::cast(pybind11::detail::str_attr_accessor o) const {
    auto vec = o.cast<std::vector<int>>();
    return glm::vec4(vec[0], vec[1], vec[2], vec[3]);
}


template <>
inline PyTable PyTable::cast(pybind11::detail::str_attr_accessor o) const {
    PyTable table( o.cast<pybind11::object>());
    return table;
}

