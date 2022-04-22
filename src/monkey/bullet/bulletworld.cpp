#include <monkey/bullet/bulletworld.h>

BulletWorld::BulletWorld(const ITab& t) {
    float gravity = t.get<float>("gravity", -10.0f);
    ///-----initialization_start-----

    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    m_collisionCnfiguration = new btDefaultCollisionConfiguration();

    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    m_dispatcher = new btCollisionDispatcher(m_collisionCnfiguration);

    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    m_overlappingPairCache = new btDbvtBroadphase();

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    m_solver = new btSequentialImpulseConstraintSolver;

    m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_solver, m_collisionCnfiguration);

    m_dynamicsWorld->setGravity(btVector3(0, gravity, 0));

    m_shapeFactory = new ShapeFactory();
}



BulletWorld::~BulletWorld() {
    //remove the rigidbodies from the dynamics world and delete them
    for (auto i = m_dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
    {
        btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if (body && body->getMotionState())
        {
            delete body->getMotionState();
        }
        m_dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }
    //delete collision shapes
    delete m_shapeFactory;

    //delete dynamics world
    delete m_dynamicsWorld;

    //delete solver
    delete m_solver;

    //delete broadphase
    delete m_overlappingPairCache;

    //delete dispatcher
    delete m_dispatcher;

    delete m_collisionCnfiguration;

}

btCollisionShape * BulletWorld::getShape(const ITab & t) {
    return m_shapeFactory->getShape(t);
}

void BulletWorld::addBody(btRigidBody * body) {
    m_dynamicsWorld->addRigidBody(body);
}

void BulletWorld::Update(double) {
    m_dynamicsWorld->stepSimulation(1.f / 60.f, 10);

    // update pos of all objects
    //print positions of all objects
    for (int j = m_dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
    {
        btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[j];
        btRigidBody* body = btRigidBody::upcast(obj);
        btTransform trans;
        if (body && body->getMotionState())
        {
            body->getMotionState()->getWorldTransform(trans);
        }
        else
        {
            trans = obj->getWorldTransform();
        }
        printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
    }

}


