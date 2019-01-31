#include <monkey/components/charactercomponent.h>
#include <gfx/entity.h>

void StateCharacter::SetDirection(Direction dir) {
    if (m_dir == dir) {
        return;
    }
    m_entity->SetFlipX(dir == Direction::WEST);
    m_dir = dir;
    ResetState();
}