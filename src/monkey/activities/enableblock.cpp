#include <monkey/activities/enableblock.h>
#include <monkey/components/walkarea.h>
#include <gfx/engine.h>

void EnableBlock::Start() {
    auto walkarea = dynamic_cast<WalkArea*>(Ref::Get<Entity>(m_id)->GetComponent<HotSpot>());
    walkarea->EnableBlockedLine(m_wall, m_active);
    SetComplete();

}