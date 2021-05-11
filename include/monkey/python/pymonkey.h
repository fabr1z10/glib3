#pragma once

#include <pybind11/pybind11.h>
#include <monkey/monkey.h>
#include <monkey/engine.h>
#include <monkey/python/wrap1.h>

class __attribute__ ((visibility ("default"))) PyEngine {
public:
    PyEngine() : m_monkey(nullptr) {}
    PyEngine(Monkey* m, Engine* e) : m_monkey(m), m_engine(e) {}
    //Wrap1 get(const std::string& s) const;
    //void jj(pybind11::object o);
    void prova();
    Monkey* getMo() {
        return m_monkey;
    }
    Engine* getEn() {
        return m_engine;
    }
private:
    int g;
    Engine* m_engine;
    Monkey* m_monkey;
};

