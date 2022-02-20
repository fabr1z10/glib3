#include <monkey/components/scaler.h>
#include <monkey/entity.h>

Scaler::Scaler(const ITab & t) {
    auto p0 = t.get<glm::vec2>("p0");
    auto p1 = t.get<glm::vec2>("p1");
    float z0 = p0[0];
    float s0 = p0[1];
    float z1 = p1[0];
    float s1 = p1[1];
    float idz = 1.0f / (z1 - z0);
    m_a = (s1 - s0) * idz;
    m_b = (s0 * z1 - s1 * z0) * idz;

}

void Scaler::Start() {
    m_scale = m_entity->getScaleVec();
}

void Scaler::Update(double) {
    auto z = m_entity->GetPosition().z;
    auto scaleFactor = m_a * z + m_b;
    auto scale = scaleFactor * m_scale;
    std::cerr << "now scale " << z << " " << scale[0] << std::endl;
    m_entity->setScale(scale);
}