#include <monkey/scenefactory.h>
#include "components/road.h"

extern "C" void applyExtension(SceneFactory* f) {

    std::cout << "--- loading scumm extension\n";

    f->add2<Road>("racer.components.road");
}