#include <monkey/activities/turn.h>
#include <gfx/engine.h>
#include <monkey/components/charactercomponent.h>

void Turn::Start() {

    auto actor = Engine::get().GetRef<Entity>(m_actorId);
    auto state = actor->GetComponent<StateCharacter>();
    Direction dir;
    switch (m_dir[0]) {
        case 'w':
            dir = Direction::WEST;
            break;
        case 'e':
            dir = Direction::EAST;
            break;
        case 'n':
            dir = Direction::NORTH;
            break;
        case 's':
            dir = Direction::SOUTH;
            break;
    }
    state->SetDirection(dir);
    SetComplete();

}