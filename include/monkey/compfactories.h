#pragma once

#include <monkey/luatable.h>
#include <memory>

class Entity;
class Shape;
class Renderer;
class Function2D;
class HotSpot;
class Runner;

class ComponentFactory {
public:
    virtual void operator()(luabridge::LuaRef&, Entity*) = 0;
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

class KeyboardCollisionComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
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

// --- runners
class HotSpotManagerFactory : public RunnerFactory {
public:
    void Create(luabridge::LuaRef&) override;
};

class SchedulerFactory : public RunnerFactory {
public:
    void Create(luabridge::LuaRef&) override;
};