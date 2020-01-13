#include <monkey/random.h>

Random::Random() {
    std::random_device rd;
    m_gen = std::unique_ptr<std::mt19937>(new std::mt19937(rd()));
}

int Random::GetUniform(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(*(m_gen.get()));

}

float Random::GetUniformReal (float min, float max) {
    std::uniform_real_distribution<> dis(min, max);
    return dis(*(m_gen.get()));
}