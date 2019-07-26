#include <gfx/factory.h>
#include <gfx/spritemesh.h>


class BuildingFactory : public FactoryMethod<IModel> {
public:
    std::shared_ptr<IModel> Create(luabridge::LuaRef& ref) override;
};