#include <gfx/factory.h>

class ZenChanFactory : public FactoryMethod<State> {
public:
    std::shared_ptr<State> Create(luabridge::LuaRef& ref) override;

};

