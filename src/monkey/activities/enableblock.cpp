#include <monkey/activities/enableblock.h>
#include <monkey/components/walkarea.h>
#include <monkey/engine.h>

EnableBlock::EnableBlock(const ITab& table) : Activity() {
    m_id = table.get<std::string>("walkarea");
    m_wall = table.get<int>("wall");
    m_active = table.get<bool>("active");
}

void EnableBlock::Start() {
    auto walkarea = Monkey::get().Get<Entity>(m_id)->GetComponent<WalkArea>();
    walkarea->EnableBlockedLine(m_wall, m_active);
    walkarea->recalc();
    SetComplete();

}