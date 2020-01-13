#include <monkey/math/funcs.h>

float PatchwiseLinear2D::operator() (float x, float y) {
    int i{0};
    for (auto& d : m_domains) {
        if (!(x < d[0] || x > d[2] || y < d[1] || y > d[3])) {
            return m_functions[i]->operator()(x, y);
        }
        // found the right patch
        ++i;
    }
    return 0.0f;
}

void PatchwiseLinear2D::AddFunction (glm::vec4 domain , std::shared_ptr<Function2D> f) {
    m_domains.push_back(domain);
    m_functions.push_back(std::move(f));
}
