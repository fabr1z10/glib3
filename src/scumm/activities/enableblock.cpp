#include "enableblock.h"
#include "../components/walkarea.h"
#include <monkey/engine.h>

EnableBlock::EnableBlock(const ITable & table) : Activity() {
    m_id = table.get<std::string>("walkarea");
    m_wall = table.get<int>("wall");
    m_active = table.get<bool>("active");
}

void EnableBlock::Start() {
    auto walkarea = dynamic_cast<WalkArea*>(Monkey::get().Get<Entity>(m_id)->GetComponent<HotSpot>());
    walkarea->EnableBlockedLine(m_wall, m_active);
    SetComplete();

}