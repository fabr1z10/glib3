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
#include <monkey/skeletal/skmodel.hpp>
#include <monkey/skeletal/skcollider.hpp>
#include <monkey/skeletal/skanimator.hpp>
#include <monkey/model/boxedmodel.h>
#include <monkey/components/animator.h>
#include <monkey/input/pytab.h>
#include <monkey/scenefactory.h>
#include <monkey/components/animrenderer.h>
#include <monkey/components/skeletalrenderer.h>

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
    return m_entity->GetComponent<Dynamics>()->m_velocity.y;
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
    m_entity->GetComponent<Dynamics>()->m_velocity.y = value;
}
float Wrap1::getVx() const {
    return m_entity->GetComponent<Dynamics2D>()->m_velocity.x;
}
float Wrap1::getScale() const {
    return m_entity->GetScale();
}


int Wrap1::getKeyFrame() const {
	return 0;
	//return static_cast<SkAnimator*>(m_entity->GetComponent<IAnimator>())->getKeyFrame();
}

void Wrap1::clear() {
    m_entity->ClearAllChildren();
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

void Wrap1::setTransform(std::vector<float> &f) {
    for (const auto& a: f) {
        std::cout << a << ",";
    }
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

void Wrap1::setMesh(const std::string& jointId, const std::string& parentJointId, const std::string& keyPoint,
                    const std::string& meshId, float scale, float z, float ox, float oy) {
    auto renderer = static_cast<SkeletalRenderer*>(m_entity->GetComponent<Renderer>());
    auto model =renderer->getModel();
    int id = model->getJointId(jointId);
    auto point = model->getKeyPoint(parentJointId, keyPoint);
    model->setMesh(id, meshId, point, z, scale);
    model->prova();
//    renderer
//    model->setMesh(jointId, meshId, scale, z);
//    auto* a = m_entity->GetComponent<IAnimator>();
//    auto* model = static_cast<SkModel*>(a->getModel());
//    model->setMesh(jointId, meshId, scale, glm::vec2(ox, oy));
//    model->getRootJoint()->calcInverseBindTransform(glm::mat4(1.0f));
//    model->computeOffset();
//    auto* collider = m_entity->GetComponent<ICollider>();
////    if (collider != nullptr) {
////        static_cast<SkCollider*>(collider)->computeAttackBoxes();
////    }

}

void Wrap1::setAnim(const std::string & animId) {
    auto* a = dynamic_cast<AnimationRenderer*>(m_entity->GetComponent<Renderer>());
    a->setAnimation(animId);
}

void Wrap1::setModel(pybind11::object obj) {
    // TODO restore
    auto renderer = m_entity->GetComponent<Renderer>();
    auto factory = Engine::get().GetSceneFactory();
    PyTab tab(obj);
    auto model = factory->make2<Model>(tab);
    renderer->setModel(model);
    //AddComponent(model->makeRenderer(model));
    //renderer->setModel()
//    Renderer* r = m_entity->GetComponent<Renderer>();
//    IAnimator* a = m_entity->GetComponent<IAnimator>();
//    auto model = Engine::get().GetAssetManager().getModel(obj);
//    r->setModel(model);
//    a->setModel(model);
//    r->Start();
    auto collider = m_entity->GetComponent<ICollider>();
    if (collider != nullptr) collider->Start();
}

void Wrap1::setText(const std::string& text) {

    Renderer *r = m_entity->GetComponent<Renderer>();
    auto tm = dynamic_cast<TextModel *>(r->GetModel());
    glm::vec2 oldOffset = tm->getOffset();
    tm->setText(text);
    glm::vec2 offset = tm->getOffset();
    r->SetTransform(glm::translate(glm::vec3(offset, 0.0f)));
}

void Wrap1::appendText(pybind11::object text) {
    TextView* r = dynamic_cast<TextView*>(m_entity);
    r->AddItem(text);
}

int Wrap1::add(pybind11::object ref) {

    auto mf = Engine::get().GetSceneFactory();
    PyTab table(ref);
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

void Wrap1::setVisible(bool value) {
	auto renderer = m_entity->GetComponent<Renderer>();
	if (renderer != nullptr) {
		renderer->setActive(value);
	}
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

void Wrap1::runScript(Engine& engine, pybind11::object o) {

    //auto scheduler = m_engine->GetRunner<Scheduler>();
    auto scheduler = engine.GetRunner<Scheduler>();

    //PyTab t(o);
    auto script = std::make_shared<Script>(PyTab(o));
    scheduler->AddScript(script);
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

pybind11::list Wrap1::getCollisionBounds() {
//	auto* a = dynamic_cast<Animator*>(m_entity->GetComponent<IAnimator>());
//	auto* model = static_cast<BoxedModel*>(a->getModel());
//	auto bounds = model->getShape(a->GetAnimation(), a->GetFrame())->getBounds();
	pybind11::list l;
//	float scale = m_entity->GetScale();
//	auto pos = m_entity->GetPosition();
//	l.append(pos.x + scale * bounds.min.x);
//	l.append(pos.y + scale * bounds.min.y);
//	l.append(pos.x + scale * bounds.max.x);
//	l.append(pos.y + scale * bounds.max.y);
	return l;

}

pybind11::list Wrap1::getChildren(bool recursive) {
	std::list<Entity*> entities{m_entity};
	pybind11::list l;
	while (!entities.empty()) {
		auto entity = entities.front();
		entities.pop_front();
		if (entity != m_entity) {
			l.append(Wrap1::create(entity));
		}
		if (recursive || m_entity == m_entity) {
			for (const auto &c : entity->GetChildren()) {
				for (const auto &d : c.second) {
					entities.push_back(d.get());
				}
			}
		}
	}
	return l;


}

pybind11::list Wrap1::getAttackCollisionBounds() {
	auto* a = m_entity->GetComponent<IAnimator>();
	auto shape = a->getShapeCast();
//	auto* a = dynamic_cast<Animator*>(m_entity->GetComponent<IAnimator>());
//	auto* model = static_cast<BoxedModel*>(a->getModel());
//	auto bounds = model->getShapeCast(a->GetAnimation(), a->GetFrame())->getBounds();
	if (shape == nullptr) {
		return pybind11::none();
	}
	auto bounds = shape->getBounds();
	pybind11::list l;
	float f = m_entity->GetFlipX() ? -1.0f : 1.0f;
	float scale = m_entity->GetScale();
	auto pos = m_entity->GetPosition();
	l.append(pos.x + f * scale * bounds.min.x);
	l.append(pos.y + scale * bounds.min.y);
	l.append(pos.x + f *scale * bounds.max.x);
	l.append(pos.y + scale * bounds.max.y);
	return l;

}


pybind11::list Wrap1::getBoxSize(const std::string& animId) {
    auto* a = m_entity->GetComponent<IAnimator>();
    auto bounds = a->getShape(animId)->getBounds().GetSize();
    //auto* model = static_cast<SkModel*>(a->getModel());

    //auto bounds = model->getShape(animId)->getBounds().GetSize();
    pybind11::list l;
    l.append(bounds[0]);
    l.append(bounds[1]);
    return l;
}

//pybind11::object Wrap1::getKeyPoint(const std::string &joint, const std::string &point) {
//	auto* a = m_entity->GetComponent<IAnimator>();
//	auto* model = static_cast<SkModel*>(a->getModel());
//	auto p = model->getKeyPointRestWorld(joint, point);
//	if (p.first) {
//		pybind11::list l;
//		l.append(p.second[0]);
//		l.append(p.second[1]);
//		return l;
//	}
//	return pybind11::cast<pybind11::none>(Py_None);
//
//}

py::object Wrap1::getInfo() {
    auto hs = m_entity->GetComponent<LuaInfo>();
    return hs->getStuff();

}

std::string Wrap1::getState() {
    return m_entity->GetComponent<StateMachine>()->GetState();
}

void Wrap1::setState(const std::string & s, py::dict d) {
    m_entity->GetComponent<StateMachine>()->SetState(s, PyTab(d));
}

void Wrap1::rotx(float angle) {
	m_entity->Rotate(glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));

}

void Wrap1::play(pybind11::object o) {

    auto sp = m_entity->GetComponent<ScriptPlayer>();

    auto script = std::make_shared<Script>(PyTab(o));
    sp->play(script);
}

void Wrap1::killScripts() {
    m_entity->GetComponent<ScriptPlayer>()->killScripts();
}

void Wrap1::setControllerBounds(float width, float height, float depth, float x, float y, float z) {
    m_entity->GetComponent<IController>()->setBounds(glm::vec3(width, height, depth), glm::vec3(x, y, z));
}

int Wrap1::getCollisionFlag() const {
    auto collider = m_entity->GetComponent<ICollider>();
    return collider->GetCollisionFlag();
}
void Wrap1::setCollisionFlag(int flag) {
    auto collider = m_entity->GetComponent<ICollider>();
    collider->setCollisionFlag(flag);
}

