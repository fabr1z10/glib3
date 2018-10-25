#include <gfx/factories.h>
#include <gfx/engine.h>
#include <gfx/math/geom.h>

#include <gfx/activities/noop.h>
#include <gfx/activities/changeroom.h>
#include <gfx/activities/callfunc.h>
#include <gfx/activities/scroll.h>
#include <gfx/activities/collisioncheck.h>
#include <gfx/activities/move.h>
#include <gfx/activities/rotate.h>
#include <gfx/activities/delay.h>
#include <gfx/activities/animate.h>
#include <gfx/activities/changestate.h>
#include <gfx/activities/showmessage.h>
#include <gfx/activities/blink.h>

std::unique_ptr<Activity> NoOpActFactory::Create(luabridge::LuaRef &ref) {
    return std::unique_ptr<NoOp>(new NoOp);
}

std::unique_ptr<Activity> ChangeRoomActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string roomId = table.Get<std::string>("room");
    return std::unique_ptr<ChangeRoom>(new ChangeRoom(roomId));
};

std::unique_ptr<Activity> CallFuncActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    luabridge::LuaRef fref = table.Get<luabridge::LuaRef>("func");
    return std::unique_ptr<CallFunc>(new CallFunc(fref));
};

std::unique_ptr<Activity> ScrollActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string camId = table.Get<std::string>("cam");
    bool relative{false};
    glm::vec2 displacement(0.0f);
    if (table.HasKey("by")) {
        relative = true;
        displacement = table.Get<glm::vec2>("by");
    } else {
        displacement = table.Get<glm::vec2>("to");
    }
    float speed = table.Get<float>("speed");
    return std::unique_ptr<Scroll>(new Scroll(camId, displacement, relative, speed));
};

std::unique_ptr<Activity> CollisionCheckActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    auto factory = Engine::get().GetSceneFactory();
    std::string actor = table.Get<std::string>("actor");
    luabridge::LuaRef rshape = table.Get<luabridge::LuaRef>("shape");
    std::shared_ptr<Shape> shape = factory->Get<Shape>(rshape);
    glm::vec2 offset = table.Get<glm::vec2>("offset");
    int mask = table.Get<float>("mask");
    luabridge::LuaRef callback = table.Get<luabridge::LuaRef>("func");
    return std::unique_ptr<CollisionCheck>(new CollisionCheck(shape, actor, offset, mask, callback));
};

std::unique_ptr<Activity> MoveActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string actor = table.Get<std::string>("actor");
    bool relative = true;
    glm::vec2 dest;
    if (table.HasKey("to")) {
        relative = false;
        dest = table.Get<glm::vec2>("to");
    } else if (table.HasKey("by")) {
        relative = true;
        dest = table.Get<glm::vec2>("by");
    } else {
        GLIB_FAIL("move action requires to or by attribute.")
    }
    float speed = table.Get<float>("speed", 0.0f);
    bool immediate = table.Get<bool>("immediate", false);
    auto m = std::unique_ptr<MoveTo>(new MoveTo(actor, dest, speed, relative, immediate));
    if (table.HasKey("acceleration")) {
        float acceleration = table.Get<float>("acceleration");
        m->SetAcceleration(acceleration);
    }
    return std::move(m);
};

std::unique_ptr<Activity> MoveGravityActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string actor = table.Get<std::string>("actor");
    glm::vec2 initialVelocity = table.Get<glm::vec2>("velocity");
    float g = table.Get<float>("g");
    float yStop = table.Get<float>("ystop");
    float rotSpeed = table.Get<float>("rotationspeed", 0.0f);
    float finRotation = table.Get<float>("finalrotation", 0.0f) * deg2rad;
    return std::unique_ptr<MoveGravity>(new MoveGravity(actor, initialVelocity, g, yStop, rotSpeed, finRotation));
};


std::unique_ptr<Activity> RotateActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string actor = table.Get<std::string>("actor");
    float initialVelocity = table.Get<float>("speed");
    float acceleration = table.Get<float>("acceleration", 0.0f);
    float deg = table.Get<float>("deg");
    return std::unique_ptr<Rotate>(new Rotate(actor, deg, acceleration, initialVelocity));
};


std::unique_ptr<Activity> DelayActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    float sec = table.Get<float>("sec");
    return std::unique_ptr<DelayTime>(new DelayTime(sec));
};

std::unique_ptr<Activity> AnimateActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string actor = table.Get<std::string>("actor");
    std::string anim = table.Get<std::string>("anim");
    int flip{0};
    if (table.HasKey("flipx")) {
        flip = table.Get<bool>("flipx") ? 2 : 1;
    }
    int loopCount = table.Get<int>("loop", 0);
    auto act = std::unique_ptr<Animate>(new Animate(actor, anim, flip));
    act->SetLoop(loopCount);
    return std::move(act);
};


std::unique_ptr<Activity> ChangeStateActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string actor = table.Get<std::string>("actor");
    std::string state = table.Get<std::string>("state");
    return std::unique_ptr<ChangeState>(new ChangeState(actor, state));
};

std::unique_ptr<Activity> ShowMessageActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string msg = table.Get<std::string>("message");
    std::string font = table.Get<std::string>("font", "monkey");
    TextAlignment align = table.Get<TextAlignment>("align", BOTTOM);
    glm::vec4 color = table.Get<glm::vec4>("color");
    glm::vec2 offset = table.Get<glm::vec2>("offset", glm::vec2(0.0f));
    float time = table.Get<float>("time", 1.0f);
    glm::vec4 outlineColor = table.Get<glm::vec4>("outlinecolor", glm::vec4(0.0f, 0.0f, 0.0f, 255.0f));
    color/=255.0f;
    outlineColor /= 255.0f;
    float size = table.Get<float>("size", 8.0f);
    glm::vec3 pos = table.Get<glm::vec3>("pos");
    return std::unique_ptr<ShowMessage>(new ShowMessage(msg, font, pos, size, color, outlineColor, align, time, offset));
};

std::unique_ptr<Activity> BlinkActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string actor = table.Get<std::string>("actor");
    float duration = table.Get<float>("duration");
    float blinkDuration = table.Get<float>("blinkduration");
    return std::unique_ptr<Blink>(new Blink(actor, duration, blinkDuration));


}