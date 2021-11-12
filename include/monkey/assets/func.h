#pragma once

#include <memory>
#include <vector>
#include <monkey/ref.h>
#include <monkey/bounds.h>
#include <monkey/imesh.h>
#include <monkey/animation.h>
#include <monkey/asset.h>

class Func : public Object {
public:
    Func(pybind11::function f) : m_f(f) {}
    pybind11::function m_f;
};