#pragma once

#include <monkey/runner.h>
#include "btBulletDynamicsCommon.h"
#include <monkey/bullet/shapefactory.h>

class BulletWorld : public Runner {
public:
    BulletWorld(const ITab& t);
    virtual ~BulletWorld();
    void Update(double) override;
    //float getScalingFactor() const;
    btCollisionShape* getShape(const ITab&);
    void addBody(btRigidBody*);
    btDiscreteDynamicsWorld* getDynamicsWorld();
    btRigidBody* addBody(btScalar mass, const btTransform& startTransform, btCollisionShape* shape);
private:
    ShapeFactory* m_shapeFactory;
    btDefaultCollisionConfiguration* m_collisionCnfiguration;
    btCollisionDispatcher* m_dispatcher;
    btBroadphaseInterface* m_overlappingPairCache;
    btSequentialImpulseConstraintSolver* m_solver;
    btDiscreteDynamicsWorld* m_dynamicsWorld;
    //keep track of the shapes, we release memory at exit.
    //make sure to re-use collision shapes among rigid bodies whenever possible!
};

inline btDiscreteDynamicsWorld* BulletWorld::getDynamicsWorld() {
    return m_dynamicsWorld;
}

