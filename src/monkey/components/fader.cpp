#include "monkey/components/fader.h"
#include "monkey/components/renderer.h"
#include "monkey/entity.h"

Fader::Fader(const ITable & t) {
    t.foreach<PyDict> ("colors", [&] (const PyDict& dict) {
       auto t = dict.get<float>("t");
       auto color = dict.get<glm::vec4>("color");
       color /= 255.0f;
       m_colors.push_back(color);
       m_times.push_back(t);
    });

}

void Fader::Start() {
    m_renderer = m_entity->GetComponent<Renderer>();
    m_t = 0;
    m_index = 0;
}

void Fader::Update(double dt) {
    m_t += dt;
    if (m_t > m_times[m_index+1]) {
        // increase index
        m_index += 1;
        if (m_index >= m_times.size()) {
            m_index = 0;
            m_t = m_t - m_times.back();
        }
    }
    float k = (m_t - m_times[m_index]) / (m_times[m_index+1]- m_times[m_index]);
    glm::vec4 color = m_colors[m_index]+ k* (m_colors[m_index+1] - m_colors[m_index]);

    m_renderer->setMultColor (color);

}

