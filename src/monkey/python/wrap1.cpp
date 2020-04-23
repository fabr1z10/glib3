#include "monkey/python/wrap1.h"
#include <monkey/entity.h>
#include <monkey/components/renderer.h>
#include <monkey/model/textmodel.h>
#include <glm/gtx/transform.hpp>
#include <monkey/entities/textview.h>
#include <monkey/components/hotspot.h>
#include <monkey/components/ianimator.h>
#include <monkey/engine.h>
#include <monkey/components/info.h>
#include <monkey/components/statemachine.h>
#include <monkey/components/dynamics2d.h>

namespace py = pybind11;

Wrap1::Wrap1() : m_entity(nullptr) {
    //m_entity = x.cast<Entity *>();
}

int Wrap1::id() const {
    return m_entity->GetId();
}

float Wrap1::x() const {
    return m_entity->GetPosition().x;
}

float Wrap1::y() const {
    return m_entity->GetPosition().y;
}

float Wrap1::getVy() const {
    return m_entity->GetComponent<Dynamics2D>()->m_velocity.y;
}

bool Wrap1::getFlipx() const {
    return m_entity->GetFlipX();
}

void Wrap1::setVy(float value) {
    m_entity->GetComponent<Dynamics2D>()->m_velocity.y = value;
}
float Wrap1::getVx() const {
    return m_entity->GetComponent<Dynamics2D>()->m_velocity.x;
}

void Wrap1::setVx(float value) {
    m_entity->GetComponent<Dynamics2D>()->m_velocity.x = value;
}

void Wrap1::move(float dx, float dy, float dz) {
    m_entity->MoveOrigin(glm::vec3(dx, dy, dz));
}

void Wrap1::setColor(std::vector<float> &l) {
    if (m_entity) {
        m_entity->GetComponent<Renderer>()->setMultColor(
                glm::vec4(l[0] / 255.0f, l[1] / 255.0f, l[2] / 255.0f, l[3] / 255.0f));
    }
}

void Wrap1::setModel(const std::string& modelId, const std::string& anim) {
    Renderer* r = m_entity->GetComponent<Renderer>();
    IAnimator* a = m_entity->GetComponent<IAnimator>();
    auto model = Engine::get().GetAssetManager().GetModel(modelId);
    r->SetModel(model);
    a->setModel(model);
    r->Start();
    auto collider = m_entity->GetComponent<ICollider>();
    if (collider != nullptr) collider->Start();
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

int Wrap1::add(pybind11::object ref) {

    auto mf = Engine::get().GetSceneFactory();
    PyTable table(ref);
    auto ptr = mf->make2<Entity>(table);
    m_entity->AddChild(ptr);
    return ptr->GetId();
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

pybind11::object Wrap1::create(Entity* e) {
    pybind11::object example = py::module::import("example").attr("Wrap1");
    pybind11::object w = example();
    Wrap1* wo = w.cast<Wrap1*>();
    wo->setEntity(e);
    return w;

}

pybind11::object Wrap1::getParent() {
    return Wrap1::create(m_entity->GetParent());
}

py::object Wrap1::getInfo() {
    auto hs = m_entity->GetComponent<LuaInfo>();
    return hs->getStuff();

}

std::string Wrap1::getState() {
    return m_entity->GetComponent<StateMachine>()->GetState();
}

void Wrap1::setState(const std::string & s, py::dict d) {
    m_entity->GetComponent<StateMachine>()->SetState(s, d);
}