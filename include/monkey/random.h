#pragma once

#include <monkey/singleton.h>
#include <random>
#include <memory>

class __attribute__ ((visibility ("default"))) Random : public Singleton<Random> {
private:
    friend class Singleton<Random>;
    Random();
public:
    int GetUniform (int min, int max);
    float GetUniformReal (float min, float max);
private:
    std::unique_ptr<std::mt19937> m_gen;
};