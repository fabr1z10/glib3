#include <monkey/components/box2dlistener.h>
#include <monkey/components/box2dbody.h>

void Box2DListener::BeginContact(b2Contact *contact) {
    //b2ContactListener::BeginContact(contact);
    auto* a = reinterpret_cast<Box2DBody*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    auto* b = reinterpret_cast<Box2DBody*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
    a->startContact(b, contact, true);
    b->startContact(a, contact, false);

}

void Box2DListener::EndContact(b2Contact *contact) {
//    auto* a = reinterpret_cast<Box2DBody*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
//    a->endContact();
}

//void Box2DPlatfomerListener::startContact(Box2DBody *other, b2Contact * c, bool y) {
//    auto normal = c->GetManifold()->localNormal;
//    std::cerr << normal.x << ", " << normal.y << ", " << y << "\n";
//}