#include <monkey/monkeyfactory.h>

std::shared_ptr<Entity> MonkeyFactory::Create() {

    auto entity = std::make_shared<Entity>();
    return entity;

}