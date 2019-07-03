#include <gfx/factory.h>
#include <gfx/spritemesh.h>

class IModel;

class SimpleModelFactory : public FactoryMethod<IModel> {
public:
    std::shared_ptr<IModel> Create(luabridge::LuaRef& ref) override;
protected:
    std::shared_ptr<SpriteMesh> ReadSpriteMesh(LuaTable&);
};

class BoxedModelFactory : public SimpleModelFactory {
public:
    std::shared_ptr<IModel> Create(luabridge::LuaRef& ref) override;

};

class GenericModel3DFactory : public FactoryMethod<IModel> {
public:
    std::shared_ptr<IModel> Create(luabridge::LuaRef& ref) override;

};