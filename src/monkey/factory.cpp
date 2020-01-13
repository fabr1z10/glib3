#include <monkey/factory.h>
#include <monkey/engine.h>

void AbstractFactoryMethod::setTarget (const LuaTable& table, TargetActivity* targetActivity ) {

    if (table.HasKey("tag")) {
        targetActivity->SetTag(table.Get<std::string>("tag"));
    } else {
        targetActivity->SetId(table.Get<int>("id"));
    }
}
