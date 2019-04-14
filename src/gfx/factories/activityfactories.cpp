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
#include <gfx/activities/cambounds.h>
#include <gfx/activities/enablekey.h>
#include <gfx/activities/virtualkey.h>
#include <gfx/activities/flip.h>
#include <gfx/activities/scale.h>
#include <gfx/activities/scriptactions.h>
#include <gfx/activities/setstate.h>
#include <gfx/activities/waitclick.h>
#include <gfx/activities/treemove.h>
#include <gfx/activities/setactive.h>

std::shared_ptr<Activity> NoOpActFactory::Create(luabridge::LuaRef &ref) {
    return std::unique_ptr<NoOp>(new NoOp);
}

std::shared_ptr<Activity> ChangeRoomActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string roomId = table.Get<std::string>("room");
    return std::unique_ptr<ChangeRoom>(new ChangeRoom(roomId));
};

std::shared_ptr<Activity> CallFuncActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    luabridge::LuaRef fref = table.Get<luabridge::LuaRef>("func");
    return std::unique_ptr<CallFunc>(new CallFunc(fref));
};

std::shared_ptr<Activity> ScrollActFactory::Create(luabridge::LuaRef &ref) {
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

std::shared_ptr<Activity> CollisionCheckActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    auto factory = Engine::get().GetSceneFactory();
    std::string actor = table.Get<std::string>("actor");
    luabridge::LuaRef rshape = table.Get<luabridge::LuaRef>("shape");
    std::shared_ptr<Shape> shape = factory->makeShape(rshape);
    glm::vec2 offset = table.Get<glm::vec2>("offset");
    int mask = table.Get<float>("mask");
    luabridge::LuaRef callback = table.Get<luabridge::LuaRef>("func");
    return std::unique_ptr<CollisionCheck>(new CollisionCheck(shape, actor, offset, mask, callback));
};

std::shared_ptr<Activity> MoveActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
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
    std::shared_ptr<MoveTo> m;
    if (table.HasKey("angle")) {
        float angle = table.Get<float>("angle");
        bool relAngle = table.Get<bool>("angle_relative");
        //m = std::make_shared<MoveTo>((dest, speed, relative, immediate, angle, relAngle));
    } else {
        m = std::make_shared<MoveTo>(dest, speed, relative, immediate);
    }
    setTarget(table, m.get());
    if (table.HasKey("acceleration")) {
        float acceleration = table.Get<float>("acceleration");
        m->SetAcceleration(acceleration);
    }
    return (m);
};

std::shared_ptr<Activity> MoveAcceleratedActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);

    glm::vec2 initialVelocity = table.Get<glm::vec2>("velocity");
    glm::vec2 acceleration= table.Get<glm::vec2>("acceleration");
    float yStop = table.Get<float>("ystop");
    float rotSpeed = table.Get<float>("rotationspeed", 0.0f);
    float finRotation = table.Get<float>("finalrotation", 0.0f) * deg2rad;
    auto ptr = std::make_shared<MoveAccelerated>(initialVelocity, acceleration, yStop, rotSpeed, finRotation);
    setTarget(table, ptr.get());
    return ptr;
};


std::shared_ptr<Activity> RotateActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string actor = table.Get<std::string>("actor");
    float initialVelocity = table.Get<float>("speed");
    float acceleration = table.Get<float>("acceleration", 0.0f);
    float deg = table.Get<float>("deg");
    auto ptr = std::make_shared<Rotate>(deg, acceleration, initialVelocity);
    setTarget (table, ptr.get());
    return ptr;
}

std::shared_ptr<Activity> DelayActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    float sec = table.Get<float>("sec");
    return std::unique_ptr<DelayTime>(new DelayTime(sec));
};

std::shared_ptr<Activity> DelayDynamicActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    luabridge::LuaRef func = table.Get<luabridge::LuaRef>("func");
    return std::unique_ptr<DelayTimeDynamic>(new DelayTimeDynamic(func));
};


std::shared_ptr<Activity> AnimateActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    // get id
    //int id = getId(table);
    std::string anim = table.Get<std::string>("anim");
    bool fwd = table.Get<bool>("fwd", true);
    int flip{0};
    if (table.HasKey("flipx")) {
        flip = table.Get<bool>("flipx") ? 2 : 1;
    }
    auto act = std::make_shared<Animate>(anim, fwd, flip);
    bool sync = table.Get<bool>("sync", false);
    act->SetSync(sync);
    setTarget(table, act.get());

    return act;
};

std::shared_ptr<Activity> SetStateActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);

    std::string state = table.Get<std::string>("state");
    auto act = std::make_shared<SetState>(state);
    setTarget(table, act.get());

    return std::move(act);
};



//std::unique_ptr<Activity> ChangeStateActFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    std::string actor = table.Get<std::string>("actor");
//    std::string state = table.Get<std::string>("state");
//    return std::unique_ptr<ChangeState>(new ChangeState(actor, state));
//};

std::shared_ptr<Activity> ShowMessageActFactory::Create(luabridge::LuaRef &ref) {
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
    return std::make_shared<ShowMessage>(msg, font, pos, size, color, outlineColor, align, time, offset);
};

std::shared_ptr<Activity> BlinkActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string actor = table.Get<std::string>("actor");
    float duration = table.Get<float>("duration");
    float blinkDuration = table.Get<float>("blinkduration");
    return std::make_shared<Blink>(actor, duration, blinkDuration);


}
std::shared_ptr<Activity> CamBoundsActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string cam = table.Get<std::string>("cam");

    float xMin = table.Get<float>("xmin");
    float xMax = table.Get<float>("xmax");
    float yMin = table.Get<float>("ymin");
    float yMax = table.Get<float>("ymax");
    return std::make_shared<ChangeCamBounds>(cam, xMin, xMax, yMin, yMax);


}

std::shared_ptr<Activity> EnableKeyActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    int key = table.Get<int>("key");
    bool enable = table.Get<bool>("enabled");
    return std::make_shared<EnableKey>(key, enable);
}

std::shared_ptr<Activity> VirtualKeyActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    int key = table.Get<int>("key");
    int action = table.Get<int>("action");
    return std::make_shared<VirtualKey>(key, action);
}

std::shared_ptr<Activity> FlipActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);

    int mode = table.Get<bool>("mode", 0);
    auto ptr = std::make_shared<Flip>(mode);
    setTarget(table, ptr.get());
    return ptr;
}

std::shared_ptr<Activity> ScaleActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string actor = table.Get<std::string>("actor");
    float duration = table.Get<float>("duration");
    float scale = table.Get<float>("scale");
    auto ptr = std::make_shared<ScaleTo>(duration, scale);
    setTarget(table, ptr.get());
    return ptr;
}

std::shared_ptr<Activity> SuspendScriptActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string script = table.Get<std::string>("script");
    return std::make_shared<SuspendScript>(script);
}

std::shared_ptr<Activity> SuspendAllScriptActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    bool value = table.Get<bool>("value");
    return std::make_shared<SuspendActiveScripts>(value);
}

std::shared_ptr<Activity> WaitClickActFactory::Create(luabridge::LuaRef &ref) {
    return std::make_shared<WaitClick>();
}


std::shared_ptr<Activity> ResumeScriptActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string script = table.Get<std::string>("script");
    return std::make_shared<ResumeScript>(script);
}

std::shared_ptr<Activity> KillScriptActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string script = table.Get<std::string>("script");
    return std::make_shared<KillScript>(script);
}


std::shared_ptr<Activity> TreeMoveActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string tag = table.Get<std::string>("tag");
    std::string parent = table.Get<std::string>("to");
    auto ptr= std::make_shared<TreeMove>(parent);
    ptr->SetTag(tag);
    return ptr;
}

std::shared_ptr<Activity> SetActiveActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string tag = table.Get<std::string>("tag");
    bool active = table.Get<bool>("active");
    auto ptr = std::make_shared<SetActive>(tag, active);
    return ptr;
}

