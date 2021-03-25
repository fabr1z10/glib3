#pragma once

#include <monkey/error.h>
#include <monkey/typename.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>

class ITab {
public:

    template<typename T>
    T get() const {
        GLIB_FAIL("Don't know how to read " << TypeName<T>::Get());
    }


private:
    virtual int _getInt() const = 0;
    virtual float _getFloat() const = 0;
    virtual std::string _getString() const = 0;


};

template<> int ITab::get() const { return _getInt(); }
template<> float ITab::get() const { return _getFloat(); }
template<> std::string ITab::get() const { return _getString(); }

class PyTab : public ITab {
public:
    PyTab(pybind11::object obj) : m_obj(obj) {}
private:
    int _getInt() const override;
    float _getFloat() const override;
    std::string _getString() const override;
    pybind11::object m_obj;
};