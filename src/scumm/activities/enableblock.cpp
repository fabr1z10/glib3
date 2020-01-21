#include "enableblock.h"
#include "../components/walkarea.h"
#include <monkey/engine.h>

void EnableBlock::Start() {
    auto walkarea = dynamic_cast<WalkArea*>(Monkey::get().Get<Entity>(m_id)->GetComponent<HotSpot>());
    walkarea->EnableBlockedLine(m_wall, m_active);
    SetComplete();

}