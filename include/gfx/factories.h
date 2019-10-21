#pragma once

#include <gfx/lua/luatable.h>
#include <gfx/factory.h>
#include <memory>
#include <gfx/imodel.h>
#include <gfx/spritefactory.h>

class Entity;
class Shape;
class Renderer;
class Function2D;
class HotSpot;
class Runner;
class State;
class Activity;
class IMesh;
class Model;
class SkeletalAnimation;
class IFrameChangeHandler;

#define FACTORY(name, type) \
    class name : public FactoryMethod<type> { \
    public: \
        std::shared_ptr<type> Create(luabridge::LuaRef& ref) override; \
    };

#define FACTORY_I(name, type) \
    class name : public FactoryMethod<type> { \
    public: \
        std::shared_ptr<type> Create(luabridge::LuaRef& ref) override; \
        void init (const LuaTable&, std::shared_ptr<type>) override; \
    };

#define FACTORY_S(name, sub, type) \
    class name : public sub { \
    public: \
        std::shared_ptr<type> Create(luabridge::LuaRef& ref) override; \
        void init (const LuaTable&, std::shared_ptr<type>) override; \
    };

// Entities
FACTORY(EntityFactory, Entity)
FACTORY(OutlineTextFactory, Entity)
FACTORY(ButtonFactory, Entity)
FACTORY(TextViewFactory, Entity)
FACTORY(BoxedMessageFactory, Entity)
FACTORY(ParallaxBackgroundFactory, Entity)
//FACTORY(SpriteFactory, Entity)
//FACTORY(HeightMapFactory, Entity)


// Components
FACTORY(TextComponentFactory, Component)
FACTORY(GfxComponentFactory, Component)
//FACTORY(Gfx3DComponentFactory, Component)
FACTORY(ColliderComponentFactory, Component)
//FACTORY(Collider3DComponentFactory, Component)

FACTORY(SmartColliderComponentFactory, Component)
FACTORY(SkeletalColliderComponentFactory, Component)
FACTORY(StateMachineComponentFactory, Component)
FACTORY(HotSpotComponentFactory, Component)
FACTORY(DepthComponentFactory, Component)
FACTORY(FollowComponentFactory, Component)
FACTORY(Follow3DComponentFactory, Component)
FACTORY(Controller2DComponentFactory, Component)
FACTORY(Controller3DComponentFactory, Component)

FACTORY(Dynamics2DComponentFactory, Component)
FACTORY(InfoComponentFactory, Component)
FACTORY(KeyInputComponentFactory, Component)
FACTORY(LuaKeyboardComponentFactory, Component)
FACTORY(ShadowComponentFactory, Component)
FACTORY(BillboardComponentFactory, Component)
FACTORY(PlatformComponentFactory, Component)
//FACTORY(ParallaxComponentFactory, Component)
FACTORY(Parallax3DComponentFactory, Component)
FACTORY(FPSComponentFactory, Component)
FACTORY(CursorComponentFactory, Component)
FACTORY(LightComponentFactory, Component)
FACTORY(KeyboardInputMethodCompFactory, Component)
FACTORY(PropertiesCompFactory, Component)
FACTORY(GarbageCollectCompFactory,Component)
//#include <gfx/factories/statemachinefactory.h>

FACTORY(StateMachineCompFactory, Component)
FACTORY(ExtStateMachineCompFactory, Component)

//FACTORY(RaycastControllerComponentFactory, Component)

// Frame handlers


// Runners
FACTORY(HotSpotManagerFactory, Runner)
FACTORY(SchedulerFactory, Runner)
FACTORY(CollisionEngineFactory, Runner)
FACTORY(CollisionEngine3DFactory, Runner)

FACTORY(DynamicWorldBuilderFactory, Runner)

// Shapes
FACTORY(RectFactory, Shape)
FACTORY(LineFactory, Shape)
FACTORY(PolyFactory, Shape)
FACTORY(CircleFactory, Shape)
FACTORY(EllipseFactory, Shape)
FACTORY(GraphFactory, Shape)
FACTORY(CompoundFactory, Shape)
FACTORY(Plane3DFactory,Shape)
FACTORY(BoxFactory,Shape)

// Cameras
FACTORY(OrthoCamFactory, Camera)
FACTORY(PerspectiveCamFactory, Camera)

// Activities
FACTORY(NoOpActFactory, Activity)
FACTORY(ChangeRoomActFactory, Activity)
FACTORY(CallFuncActFactory, Activity)
FACTORY(RepeatActFactory, Activity)
FACTORY(ScrollActFactory, Activity)
FACTORY(CollisionCheckActFactory, Activity)
FACTORY(MoveActFactory, Activity)
FACTORY(MoveAcceleratedActFactory, Activity)
FACTORY(RotateActFactory, Activity)
FACTORY(DelayActFactory, Activity)
FACTORY(DelayDynamicActFactory, Activity)
FACTORY(AnimateActFactory, Activity)
FACTORY(SetStateActFactory, Activity)
FACTORY(FlipActFactory, Activity)
FACTORY(ChangeStateActFactory, Activity)
FACTORY(ShowMessageActFactory, Activity)
FACTORY(BlinkActFactory, Activity)
FACTORY(CamBoundsActFactory, Activity)
FACTORY(EnableKeyActFactory, Activity)
FACTORY(VirtualKeyActFactory, Activity)
FACTORY(ScaleActFactory, Activity)
FACTORY(SuspendScriptActFactory, Activity)
FACTORY(SuspendAllScriptActFactory, Activity)
FACTORY(ResumeScriptActFactory, Activity)
FACTORY(KillScriptActFactory, Activity)
FACTORY(WaitClickActFactory, Activity)
FACTORY(TreeMoveActFactory, Activity);
FACTORY(SetActiveActFactory, Activity);

FACTORY(SkeletalAnimFactory, SkeletalAnimation)

// Asset
FACTORY_I(StateFactory, State)
FACTORY_S(Walk25StateFactory, StateFactory, State)
FACTORY_S(Hit25StateFactory, StateFactory, State)
FACTORY_S(SimpleStateFactory, StateFactory, State)

//FACTORY(SimpleModelFactory, IModel)
//FACTORY(BoxedModelFactory, IModel)
//FACTORY(CompositeModelFactory, IModel)

// States
//FACTORY(AnimInitializerFactory, StateInitializer)
//FACTORY(AnimColliderInitializerFactory, StateInitializer)
//FACTORY(LuaAnimColliderInitializerFactory, StateInitializer)
//FACTORY(LuaInitializerFactory, StateInitializer)

//class EntityFactory : public FactoryMethod<Entity> {
//public:
//    std::shared_ptr<Entity> Create(luabridge::LuaRef& ref) override;
//
//};

// helper functions
//std::shared_ptr<Renderer> ReadTextComponent (luabridge::LuaRef& ref);
//std::shared_ptr<Shape> ReadShape(luabridge::LuaRef& ref);
std::shared_ptr<Function2D> GetFunc2D(luabridge::LuaRef& ref);
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
