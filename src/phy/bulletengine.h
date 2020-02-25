#pragma once

#include <monkey/runner.h>
#include "bullet/btBulletDynamicsCommon.h"

class BulletEngine : public Runner {
public:
    BulletEngine (const LuaTable&);
    virtual ~BulletEngine();
    void Init () override;
    void Update(double) override ;
    void addBody (btRigidBody*);
private:
    btDefaultCollisionConfiguration* m_collConfig;
    btCollisionDispatcher * m_collDisptacher;
    btBroadphaseInterface * m_bpInterface;
    btSequentialImpulseConstraintSolver* m_solver;
    btDiscreteDynamicsWorld* m_world;

    btVector3 m_gravity;
};