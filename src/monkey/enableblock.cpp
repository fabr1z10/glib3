#include <monkey/enableblock.h>
#include <monkey/walkarea.h>
#include <gfx/engine.h>

void EnableBlock::Start() {
    auto walkarea = Engine::get().GetRef<WalkArea>("walkarea");
    walkarea->EnableBlockedLine(m_wall, m_active);
    SetComplete();

}