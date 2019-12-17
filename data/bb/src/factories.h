#include <gfx/factory.h>

#include <gfx/scenefactory.h>

//extern "C" void hello(SceneFactory* f);

class ZenChanFactory : public FactoryMethod<State> {
public:
    std::shared_ptr<State> Create(luabridge::LuaRef& ref) override;

};

