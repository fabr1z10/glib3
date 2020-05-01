#pragma once

#include <monkey/python/wrap1.h>

class Monkey;
class Engine;

extern Monkey * m_monkey;
extern Engine * m_engine;


Wrap1 get(const std::string & tag) ;
void rmv(int);
void rmvt(const std::string&);
std::vector<float> campos(const std::string&);
void play (pybind11::object);
//void addLine (const std::string&, pybind11::object&);
void restart();
pybind11::list getDeviceSize();
