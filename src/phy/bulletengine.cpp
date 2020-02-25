#include "bulletengine.h"
#include <monkey/lua/luatable.h>

BulletEngine::BulletEngine(const LuaTable & t) : Runner() {

    glm::vec3 g = t.Get<glm::vec3>("gravity");
    m_gravity = btVector3(g.x, g.y, g.z);
}

BulletEngine::~BulletEngine() {

    //delete dynamics world
    delete m_world;

    //delete solver
    delete m_solver;

    //delete broadphase
    delete m_bpInterface;

    //delete dispatcher
    delete m_collDisptacher;

    delete m_collConfig;

}

void BulletEngine::Init() {
    m_collConfig = new btDefaultCollisionConfiguration();
    m_collDisptacher = new btCollisionDispatcher(m_collConfig);
    m_bpInterface = new btDbvtBroadphase();
    m_solver = new btSequentialImpulseConstraintSolver;
    m_world = new btDiscreteDynamicsWorld (m_collDisptacher, m_bpInterface, m_solver, m_collConfig);

    m_world->setGravity(m_gravity);
}

void BulletEngine::Update(double dt) {
    m_world->stepSimulation(dt, 10);
}

void BulletEngine::addBody(btRigidBody* b) {
    m_world->addRigidBody(b);
}