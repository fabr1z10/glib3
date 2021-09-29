#include <monkey/scenefactory.h>
#include "states/walkside.h"
#include "states/walkside3d.h"
#include "states/ishit.h"
#include "states/jump2d.h"
#include "states/jump3d.h"
#include "states/foewalk.h"
#include "states/foechase.h"
#include "states/foechase3d.h"
#include "states/foedead.h"
#include "walkanim.h"
#include "states/climb.h"
#include "states/fly.h"
#include "states/npcwalk3d.h"

extern "C" void applyExtension(SceneFactory* f) {

    std::cout << "--- loading platformer extension\n";

    f->add2<WalkSide> ("state.walkside");
    f->add2<WalkSide3D> ("state.walkside3d");
    f->add2<NPCWalk3D> ("state.npcwalk3d");
    f->add2<Jump2D> ("state.jump");
    f->add2<Jump3D> ("state.jump3D");
    f->add2<Climb> ("state.climb");
    f->add2<Fly> ("state.fly");

    f->add2<FoeWalk> ("state.foewalk");
    f->add2<FoeChase> ("state.foechase");
    f->add2<FoeChase3D> ("state.foechase3d");
    f->add2<IsHit> ("state.hit");
    f->add2<FoeDead> ("state.foedead");

    f->add2<BasicWalkAnim>("walkanim.basic")     ;
    f->add2<WalkYAnim>("walkanim.y")     ;

}