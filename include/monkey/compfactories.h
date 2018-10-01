#pragma once

#include <monkey/luatable.h>
#include <memory>

class Entity;
class Shape;
class Renderer;
class Function2D;
class HotSpot;
class Runner;
class State;

class ComponentFactory {
public:
    virtual void operator()(luabridge::LuaRef&, Entity*) = 0;
};
class StateFactory {
public:
    virtual std::shared_ptr<State> Create(luabridge::LuaRef&) = 0;
};
class RunnerFactory {
public:
    virtual void Create(luabridge::LuaRef&) = 0;
};

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

class WalkAreaComponentFactory : public ComponentFactory {
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
    std::unordered_map<std::string, std::shared_ptr<StateFactory> > m_stateFactories;

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

class ScalingComponentFactory : public ComponentFactory {
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
class EmptyStateFactory : public StateFactory {
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

