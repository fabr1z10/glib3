#include "monkey/python/wrap1.h"
#include <monkey/entity.h>
#include <monkey/components/renderer.h>
#include <monkey/model/textmodel.h>
#include <glm/gtx/transform.hpp>
#include <monkey/entities/textview.h>
#include <monkey/components/hotspot.h>

Wrap1::Wrap1() : m_entity(nullptr) {
    //m_entity = x.cast<Entity *>();
}

float Wrap1::x() const {
    return m_entity->GetPosition().x;
}

void Wrap1::setColor(std::vector<float> &l) {
    if (m_entity) {
        m_entity->GetComponent<Renderer>()->setMultColor(
                glm::vec4(l[0] / 255.0f, l[1] / 255.0f, l[2] / 255.0f, l[3] / 255.0f));
    }
}

void Wrap1::setText(const std::string& text) {

    Renderer *r = m_entity->GetComponent<Renderer>();
    auto tm = dynamic_cast<TextModel *>(r->GetModel());
    glm::vec2 oldOffset = tm->GetOffset();
    tm->SetText(text);
    glm::vec2 offset = tm->GetOffset();
    r->SetTransform(glm::translate(glm::vec3(offset, 0.0f)));
}

void Wrap1::appendText(pybind11::object text) {
    TextView* r = dynamic_cast<TextView*>(m_entity);
    r->AddItem(text);
}

void Wrap1::clearText() {
    auto r = dynamic_cast<TextView*>(m_entity);
    r->ClearText();
}

void Wrap1::setActive(bool value) {
    m_entity->setActive(value);
}

void Wrap1::enableControls(bool value) {
    auto hs = m_entity->GetComponent<HotSpotManager>();
    hs->setActive(value);

    //m_entity->SetControlsEnabled(value);
}