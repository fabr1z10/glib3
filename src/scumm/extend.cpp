#include <monkey/scenefactory.h>
#include "components/walkarea.h"
#include "components/character.h"
#include "activities/walk.h"
#include "activities/say.h"
#include "activities/enableblock.h"
#include "activities/turn.h"

extern "C" void applyExtension(SceneFactory* f) {

    std::cout << "--- loading scumm extension\n";

    f->add2<WalkArea>("scumm.components.walkarea");
    f->add2<CharacterController>("scumm.components.character_controller");

    f->add2<Walk>("scumm.action.walk");
    f->add2<Turn>("scumm.action.turn");
    f->add2<Say> ("scumm.action.say");
    f->add2<EnableBlock> ("scumm.action.enable_block");
//    f->add2<CharacterController>("scumm.components.character_controller");
//    f->add2<StateCharacter>("components.character");
//    f->add2<Walk>("scumm.action.walk");
//    f->add2<Turn>("scumm.action.turn");
//    f->add2<Say>("scumm.action.say");
//    f->add2<EnableBlock>("scumm.action.enable_block");
}