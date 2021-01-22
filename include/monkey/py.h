#pragma once

#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <monkey/error.h>
#include <sstream>
#include <tuple>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    virtual std::shared_ptr<ITable> clone() const = 0;

private:
    virtual pybind11::object getHandle (const std::string& key) const = 0;


};

//// cast to 2d - 3d - 4d vectors
template <>
inline glm::vec2 ITable::cast(pybind11::object o) const {
    auto vec = o.cast<std::tuple<float, float>>();
    return glm::vec2(std::get<0>(vec), std::get<1>(vec));
}

template <>
inline glm::mat4 ITable::cast(pybind11::object o) const {
	auto tu = o.cast<std::vector<pybind11::object>>();
	glm::mat4 m;
	for (size_t i =0;i <4; ++i) {
		auto b = tu[i].cast<std::vector<float>>();
		for (size_t j = 0; j< 4; ++j)
			m[i][j] = (b[j]);
	}
	return m;

}


template <>
inline glm::ivec2 ITable::cast(pybind11::object o) const {
    auto vec = o.cast<std::tuple<int, int>>();
    return glm::ivec2(std::get<0>(vec), std::get<1>(vec));
}


template <>
inline glm::vec3 ITable::cast(pybind11::object o) const  {
    auto vec = o.cast<std::tuple<float, float, float>>();
    return glm::vec3(std::get<0>(vec), std::get<1>(vec), std::get<2>(vec));
}

template <>
inline glm::vec4 ITable::cast(pybind11::object o) const {
    auto vec = o.cast<std::tuple<float, float, float, float>>();
    return glm::vec4(std::get<0>(vec), std::get<1>(vec), std::get<2>(vec), std::get<3>(vec));
}


class PyTable : public ITable {
public:
    PyTable (pybind11::object o) : obj(o) {}
    PyTable (const PyTable&);
    std::shared_ptr<ITable> clone() const override;
    pybind11::object& getObject() {
        return obj;
    }
private:
    virtual pybind11::object getHandle (const std::string& key) const;
    pybind11::object obj;
};

class PyDict : public ITable {
public:
    PyDict (pybind11::dict o) : obj(o) {}
    PyDict (const PyDict&);
    std::shared_ptr<ITable> clone() const override;

	template<typename Key, typename Value>
	std::unordered_map<Key, Value> toDict() {
		std::unordered_map<Key, Value> d;
		for (const auto a : obj) {
			d [cast<Key>(a.first.cast<pybind11::object>())] = cast<Value>(a.second.cast<pybind11::object>());
		}
		return d;
	}
private:
    virtual pybind11::object getHandle (const std::string& key) const;
    pybind11::dict obj;
};

template <>
inline PyTable ITable::cast(pybind11::object o) const {
    PyTable table(o);
    return table;
}


template <>
inline PyDict ITable::cast(pybind11::object o) const {
    PyDict table(o);
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




