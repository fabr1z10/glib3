#pragma once

#include <pybind11/pybind11.h>
#include <monkey/monkey.h>
#include <monkey/python/wrap1.h>

class PyEngine {
public:
    PyEngine() :m_monkey(nullptr) {}
    PyEngine(Monkey* m) : m_monkey(m) {}
    Wrap1 get(const std::string& s) const;
    void prova();
private:
    int g;
    Monkey* m_monkey;
};

