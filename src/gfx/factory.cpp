#include <gfx/factory.h>
#include <gfx/engine.h>

int AbstractFactoryMethod::getId(const LuaTable &table) {
    if (table.HasKey("tag")) {

        return Engine::get().getIdFromTag(table.Get<std::string>("tag"));
    }
    int id = table.Get<int>("id");
    return id;
}