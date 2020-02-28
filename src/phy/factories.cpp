#include "factories.h"

#include "bulletengine.h"
#include "rigidbody.h"
#include <monkey/scenefactory.h>
#include "btshapewrapper.h"
#include "c3d.h"

void Extension::extendLua() {


}
void Extension::extend(SceneFactory* f) {

    f->add<BulletEngine> ("bulletengine");
    f->add<RigidBody> ("rigidbody");

    f->add<btBoxWrapper> ("btbox");
    f->add<btSphereWrapper> ("btsphere");
    f->add<Controller3Db> ("c3d");
}

