#include <monkey/bullet/rigidbody.h>
#include <monkey/bullet/bulletworld.h>
#include <monkey/engine.h>

BulletRigidBody::BulletRigidBody(const ITab& t) {
    auto pos = t.get<glm::vec3>("pos");
    auto mass = t.get<float>("mass");

    // let's create the shape
    auto world = Engine::get().GetRunner<BulletWorld>();

    m_shape = world->getShape(*t["shape"]);

    m_transform.setIdentity();
    m_transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
    bool isDynamic = (mass != 0.0f);
    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        m_shape->calculateLocalInertia(mass, localInertia);

    //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(m_transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, m_shape, localInertia);
    btRigidBody* body = new btRigidBody(rbInfo);

    //add the body to the dynamics world
    world->addBody(body);
    m_body = body;
}

void BulletRigidBody::Update(double) {
    btTransform trans;
    auto pa = m_body->getMotionState();
    if (m_body && m_body->getMotionState())
    {
        m_body->getMotionState()->getWorldTransform(trans);
    }
    else
    {
        trans = m_body->getWorldTransform();
    }
    std::cout << "pos = " << trans.getOrigin().getX() << ", " << trans.getOrigin().getY() << ", " << trans.getOrigin().getZ() << "\n";
    btVector3 min, max;
    m_body->getAabb(min ,max);
    std::cout << "min: " << min.x() << ", " << min.y() << ", " << min.z() << std::endl;
    std::cout << "max: " << max.x() << ", " << max.y() << ", " << max.z() << std::endl;
    auto mat = bulletToGlm(trans);
    m_entity->SetLocalTransform(mat);
}

glm::mat4 BulletRigidBody::bulletToGlm(const btTransform& t)
{
    glm::mat4 m;
    const btMatrix3x3& basis = t.getBasis();
    // rotation
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            m[c][r] = basis[r][c];
        }
    }
    // traslation
    btVector3 origin = t.getOrigin();
    m[3][0] = origin.getX();
    m[3][1] = origin.getY();
    m[3][2] = origin.getZ();
    // unit scale
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
    return m;
}