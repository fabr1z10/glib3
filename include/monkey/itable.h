#pragma once

#include <functional>
#include <monkey/error.h>
#include <monkey/typename.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <glm/glm.hpp>

class ITab {
public:

    template<typename T>
    T as() const {
        GLIB_FAIL("Don't know how to read " << TypeName<T>::Get());
    }

    template<typename T>
    T as(T fallback) const {
        try {
            T value = as<T>();
        } catch (...) {
            return fallback;
        }
    }

    template<typename T>
    T get(const std::string& id) const {
        return this->operator[](id)->as<T>();
    }

    template<typename T>
    T get(const std::string& id, T fallback) const {
        try {
            auto ptr = this->operator[](id);
            if (ptr == nullptr) {
                return fallback;
            }
            return ptr->as<T>();
        } catch (...) {
            return fallback;
        }
    }

    virtual bool has(const std::string& id) const = 0;

    // iterate on a vector
    virtual void foreach(std::function<void(const ITab&)> f) const = 0;
    virtual void foreach(const std::string& id, std::function<void(const ITab&)> f) const = 0;

    // iterate on a dict
    virtual void foreach(std::function<void(const std::string&, const ITab&)> f) const = 0;
    virtual void foreach(const std::string& id, std::function<void(const std::string&, const ITab&)> f) const = 0;

    virtual std::unique_ptr<ITab> operator[](const std::string&) const = 0;
private:
    virtual int _asInt() const = 0;
    virtual float _asFloat() const = 0;
    virtual bool _asBool() const = 0;
    virtual std::string _asString() const = 0;
    virtual pybind11::function _asFunction() const = 0;
    virtual pybind11::object _asPyObject() const = 0;

    // glm stuff
    virtual glm::vec2 _asVec2() const = 0;
    virtual glm::vec3 _asVec3() const = 0;
    virtual glm::vec4 _asVec4() const = 0;
    virtual glm::mat4 _asMat4() const = 0;

    // shortcut for vecs
    virtual std::vector<int> _asVecInt() const = 0;
    virtual std::vector<float> _asVecFloat() const = 0;
    virtual std::vector<std::string> _asVecStr() const = 0;
};

template<> int ITab::as() const;
template<> float ITab::as() const;
template<> bool ITab::as() const;
template<> std::string ITab::as() const;

template<> glm::vec2 ITab::as() const;
template<> glm::vec3 ITab::as() const;
template<> glm::vec4 ITab::as() const;
template<> glm::mat4 ITab::as() const;
template<> inline pybind11::function ITab::as() const { return _asFunction(); }
template<> inline pybind11::object ITab::as() const { return _asPyObject(); }

template<> std::vector<int> ITab::as() const;
template<> std::vector<float> ITab::as() const;
template<> std::vector<std::string> ITab::as() const;



