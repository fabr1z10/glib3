#include <gfx/compfactories.h>

#include <gfx/activities/noop.h>
#include <gfx/activities/changeroom.h>


std::shared_ptr<Activity> NoOpActFactory::Create(luabridge::LuaRef &ref) {
    return std::make_shared<NoOp>();
}

std::shared_ptr<Activity> ChangeRoomActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string roomId = table.Get<std::string>("room");
    return std::make_shared<ChangeRoom>(roomId);
};