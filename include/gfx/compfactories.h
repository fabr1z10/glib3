#pragma once

#include <gfx/lua/luatable.h>
#include <gfx/factories.h>
#include <memory>

class Entity;
class Shape;
class Renderer;
class Function2D;
class HotSpot;
class Runner;
class State;



// helper functions
std::shared_ptr<Renderer> ReadTextComponent (luabridge::LuaRef& ref);
std::shared_ptr<Shape> ReadShape(luabridge::LuaRef& ref);
std::unique_ptr<Function2D> GetFunc2D(luabridge::LuaRef& ref);
std::shared_ptr<HotSpot> GetHotSpot (luabridge::LuaRef& ref, std::shared_ptr<Shape> shape);

class TextComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class OutlineTextComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class CameraFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class KeyInputFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class GfxComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class ColliderComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class HotSpotComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class StateMachineComponentFactory : public ComponentFactory {
public:
    StateMachineComponentFactory();
    void operator()(luabridge::LuaRef&, Entity*) override;
private:
    // state factory

    SceneFactory* m_sceneFactory;
};

class LuaKeyboardComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class SwitchComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class DepthComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class InfoComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class FollowComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class BillboardComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};



class ButtonComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class TextViewComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class ShadowComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class Controller2DComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class Dynamics2DComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

// --- runners
class HotSpotManagerFactory : public RunnerFactory {
public:
    void Create(luabridge::LuaRef&) override;
};

class SchedulerFactory : public RunnerFactory {
public:
    void Create(luabridge::LuaRef&) override;
};

class CollisionEngineFactory : public RunnerFactory {
public:
    void Create(luabridge::LuaRef&) override;
};

// --- states
class BasicStateFactory : public StateFactory {
    std::shared_ptr<State> Create(luabridge::LuaRef&) override;
};

class WalkStateFactory : public StateFactory {
    std::shared_ptr<State> Create(luabridge::LuaRef&) override;
};

class WalkCollisionStateFactory : public StateFactory {
    std::shared_ptr<State> Create(luabridge::LuaRef&) override;
};

class HitStateFactory : public StateFactory {
    std::shared_ptr<State> Create(luabridge::LuaRef&) override;
};

class AIWalkStateFactory : public StateFactory {
    std::shared_ptr<State> Create(luabridge::LuaRef&) override;
};

