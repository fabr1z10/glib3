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
#include <monkey/components/follow.h>
#include <monkey/components/controller25.h>
#include <monkey/components/scriptplayer.h>

namespace py = pybind11;

Wrap1::Wrap1() : m_entity(nullptr) {
    //m_entity = x.cast<Entity *>();
}

bool Wrap1::valid() const {
    return m_entity != nullptr;
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

float Wrap1::z() const {
    return m_entity->GetPosition().z;
}

std::string Wrap1::tag() const {
    return m_entity->GetTag();
}


float Wrap1::getVy() const {
    return m_entity->GetComponent<Dynamics2D>()->m_velocity.y;
}

float Wrap1::getElevation() const {

    return m_entity->GetComponent<Controller25>()->getElevation();
}
void Wrap1::setElevation(float value) {

    m_entity->GetComponent<Controller25>()->setElevation(value);
}

bool Wrap1::getFlipx() const {
    return m_entity->GetFlipX();
}

std::string Wrap1::getAnim() const {
    return m_entity->GetComponent<IAnimator>()->GetAnimation();
}

void Wrap1::setVy(float value) {
    m_entity->GetComponent<Dynamics2D>()->m_velocity.y = value;
}
float Wrap1::getVx() const {
    return m_entity->GetComponent<Dynamics2D>()->m_velocity.x;
}
float Wrap1::getScale() const {
    return m_entity->GetScale();
}

void Wrap1::setVx(float value) {
    m_entity->GetComponent<Dynamics2D>()->m_velocity.x = value;
}
void Wrap1::setScale(float value) {
    m_entity->SetScale(value);
}

void Wrap1::follow(bool value) {
    m_entity->GetComponent<Follow>()->setActive(value);

}


void Wrap1::setPosition(float x, float y, float z) {

    m_entity->SetPosition(glm::vec3(x,y,z));
}
void Wrap1::move(float dx, float dy, float dz) {
    m_entity->MoveOrigin(glm::vec3(dx, dy, dz));
}

void Wrap1::setColor(std::vector<float> & mult, std::vector<float>& add) {
    if (m_entity) {
        m_entity->GetComponent<Renderer>()->setMultColor(
                glm::vec4(mult[0] / 255.0f, mult[1] / 255.0f, mult[2] / 255.0f, mult[3] / 255.0f));
        m_entity->GetComponent<Renderer>()->setAddColor(
                                                        glm::vec4(add[0] / 255.0f, add[1] / 255.0f, add[2] / 255.0f, add[3] / 255.0f));
    }
}

void Wrap1::setModel(const std::string& modelId) {
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
    if (hs != nullptr)
        hs->setActive(value);

    //m_entity->SetControlsEnabled(value);
}

void Wrap1::setEnableUpdate(bool value) {
	m_entity->SetEnableUpdate(value);
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

pybind11::list Wrap1::getAttackPos() {
    ICollider* collider = m_entity->GetComponent<ICollider>();
    auto bounds = collider->getAttackBounds();
    auto size = bounds.GetSize();
    auto center = bounds.GetCenter();
    pybind11::list l;
    l.append(center.x);
    l.append(center.y);
    return l;
}

pybind11::list Wrap1::getTextSize() {
	auto b = dynamic_cast<TextModel*>(m_entity->GetComponent<Renderer>()->GetModel())->getBounds();
	pybind11::list l;
	l.append(b.min.x);
	l.append(b.min.y);
	l.append(b.max.x);
	l.append(b.max.y);
	return l;

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

void Wrap1::rotx(float angle) {
	m_entity->Rotate(glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));

}

void Wrap1::play(pybind11::object o) {

    auto sp = m_entity->GetComponent<ScriptPlayer>();
    PyTable t(o);
    auto script = std::make_shared<Script>(t);
    sp->play(script);
}

void Wrap1::killScripts() {
    m_entity->GetComponent<ScriptPlayer>()->killScripts();
}