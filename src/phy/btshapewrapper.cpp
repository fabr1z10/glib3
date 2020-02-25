#include "btshapewrapper.h"

btBoxWrapper::btBoxWrapper(const LuaTable & t) : btShapeWrapper() {
    glm::vec3 he = t.Get<glm::vec3>("half_extents");
    btVector3 hef (he.x, he.y, he.z);
    m_shape = std::make_shared<btBoxShape>(hef);
}

btSphereWrapper::btSphereWrapper(const LuaTable & t) : btShapeWrapper() {
    btScalar radius = t.Get<btScalar>("radius");
    m_shape = std::make_shared<btSphereShape>(radius);
}