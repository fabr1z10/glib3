#include <monkey/bullet/shapefactory.h>

ShapeFactory::ShapeFactory() {
    m_factories["bullet.box"] = [&] (const ITab& t) { return makeBox(t); };
    m_factories["bullet.ramp"] = [&] (const ITab& t) { return makeConvexHull(t); };
}

ShapeFactory::~ShapeFactory() {
    //delete collision shapes
    for (int j = 0; j < m_collisionShapes.size(); j++)
    {
        btCollisionShape* shape = m_collisionShapes[j];
        m_collisionShapes[j] = 0;
        delete shape;
    }
}

btCollisionShape * ShapeFactory::getShape(const ITab & t) {

    auto ref = t.get<std::string>("ref", "");
    if (!ref.empty()) {
        return m_shapes.at(ref);
    }

    auto id = t.get<std::string>("id", "");
    auto type = t.get<std::string>("type");
    auto it = m_factories.find(type);
    if (it == m_factories.end()) {
        std::cerr << "don't know how to build shape: " << type << "\n";
        exit(1);
    }
    auto shape = it->second(t);
    if (!id.empty()) {
        m_shapes[id] = shape;
    }
    //btVector3 li;
    return shape;
}

btCollisionShape * ShapeFactory::makeBox(const ITab & t) {
    auto size = t.get<glm::vec3>("size");

    btCollisionShape* box = new btBoxShape(btVector3(btScalar(size.x), btScalar(size.y), btScalar(size.z)));
    btVector3 li;
    box->calculateLocalInertia(1.0f, li);

    return box;
}

btCollisionShape * ShapeFactory::makeConvexHull(const ITab & t) {
    auto shape = new btConvexHullShape();
    float width = t.get<float>("width");
    float length = t.get<float>("length");
    float height = t.get<float>("height");
    shape->addPoint(btVector3(0.0f, 0.0f, 0.0f));
    shape->addPoint(btVector3(width, 0.0f, 0.0f));
    shape->addPoint(btVector3(width, 0.0f, length));
    shape->addPoint(btVector3(0.0f, 0.0f, length));
    shape->addPoint(btVector3(width, height, length));
    shape->addPoint(btVector3(0.0f, height, length));
    return shape;
}