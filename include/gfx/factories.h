#pragma once

#include <gfx/lua/luatable.h>
#include <gfx/factory.h>
#include <memory>

class Entity;
class Shape;
class Renderer;
class Function2D;
class HotSpot;
class Runner;
class State;
class Activity;
class IMesh;

#define FACTORY(name, type) \
    class name : public FactoryMethod<type> { \
    public: \
        std::unique_ptr<type> Create(luabridge::LuaRef& ref) override; \
    };

// Entities
FACTORY(EntityFactory, Entity)
FACTORY(OutlineTextFactory, Entity)

// Components
FACTORY(TextComponentFactory, Component)
FACTORY(GfxComponentFactory, Component)
FACTORY(ColliderComponentFactory, Component)
FACTORY(StateMachineComponentFactory, Component)
FACTORY(HotSpotComponentFactory, Component)
FACTORY(DepthComponentFactory, Component)
FACTORY(FollowComponentFactory, Component)
FACTORY(Controller2DComponentFactory, Component)
FACTORY(Dynamics2DComponentFactory, Component)
FACTORY(InfoComponentFactory, Component)
FACTORY(KeyInputComponentFactory, Component)
FACTORY(LuaKeyboardComponentFactory, Component)
FACTORY(TextViewComponentFactory, Component)
FACTORY(ShadowComponentFactory, Component)
FACTORY(BillboardComponentFactory, Component)

// Runners
FACTORY(HotSpotManagerFactory, Runner)
FACTORY(SchedulerFactory, Runner)
FACTORY(CollisionEngineFactory, Runner)

// Shapes
FACTORY(RectFactory, Shape)
FACTORY(LineFactory, Shape)
FACTORY(PolyFactory, Shape)
FACTORY(CircleFactory, Shape)
FACTORY(EllipseFactory, Shape)
FACTORY(GraphFactory, Shape)
FACTORY(CompoundFactory, Shape)

// Cameras
FACTORY(OrthoCamFactory, Camera)
FACTORY(PerspectiveCamFactory, Camera)

// Activities
FACTORY(NoOpActFactory, Activity)
FACTORY(ChangeRoomActFactory, Activity)
FACTORY(CallFuncActFactory, Activity)
FACTORY(ScrollActFactory, Activity)
FACTORY(CollisionCheckActFactory, Activity)
FACTORY(MoveActFactory, Activity)
FACTORY(MoveGravityActFactory, Activity)
FACTORY(RotateActFactory, Activity)
FACTORY(DelayActFactory, Activity)
FACTORY(AnimateActFactory, Activity)
FACTORY(ChangeStateActFactory, Activity)
FACTORY(ShowMessageActFactory, Activity)

// Asset
FACTORY(SpriteFactory, IMesh)

// States
FACTORY(AnimInitializerFactory, StateInitializer)
FACTORY(AnimColliderInitializerFactory, StateInitializer)
FACTORY(LuaAnimColliderInitializerFactory, StateInitializer)
FACTORY(LuaInitializerFactory, StateInitializer)

//class EntityFactory : public FactoryMethod<Entity> {
//public:
//    std::shared_ptr<Entity> Create(luabridge::LuaRef& ref) override;
//
//};

// helper functions
//std::shared_ptr<Renderer> ReadTextComponent (luabridge::LuaRef& ref);
//std::shared_ptr<Shape> ReadShape(luabridge::LuaRef& ref);
std::unique_ptr<Function2D> GetFunc2D(luabridge::LuaRef& ref);
//std::shared_ptr<HotSpot> GetHotSpot (luabridge::LuaRef& ref, std::shared_ptr<Shape> shape);

//class TextComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};
//
//class OutlineTextComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};

//class CameraFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};

//class KeyInputFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};

//class GfxComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};

//class ColliderComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};

//class HotSpotComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};

//class StateMachineComponentFactory : public ComponentFactory {
//public:
//    StateMachineComponentFactory();
//    void operator()(luabridge::LuaRef&, Entity*) override;
//private:
//    // state factory
//
//    SceneFactory* m_sceneFactory;
//};
//
//class LuaKeyboardComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};

//class SwitchComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};

//class DepthComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};



//class FollowComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};
//
//class BillboardComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};

//
//
//class ButtonComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};

//class TextViewComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};
//
//class ShadowComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};
//
//

// --- runners


// --- states
//class BasicStateFactory : public Factory {
//    std::shared_ptr<State> Create(luabridge::LuaRef&) override;
//};
//
//class WalkStateFactory : public StateFactory {
//    std::shared_ptr<State> Create(luabridge::LuaRef&) override;
//};
//
//class WalkCollisionStateFactory : public StateFactory {
//    std::shared_ptr<State> Create(luabridge::LuaRef&) override;
//};
//
//class HitStateFactory : public StateFactory {
//    std::shared_ptr<State> Create(luabridge::LuaRef&) override;
//};
//
//class AIWalkStateFactory : public StateFactory {
//    std::shared_ptr<State> Create(luabridge::LuaRef&) override;
//};
//
