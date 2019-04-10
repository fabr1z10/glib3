#include <monkey/activities/enableblock.h>
#include <monkey/components/walkarea.h>
#include <gfx/engine.h>

void EnableBlock::Start() {
    auto walkarea = Ref::Get<WalkArea>("walkarea").get();
    walkarea->EnableBlockedLine(m_wall, m_active);
    SetComplete();

}