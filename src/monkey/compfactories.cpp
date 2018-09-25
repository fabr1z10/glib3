#include <monkey/compfactories.h>
#include <gfx/renderer.h>
#include <gfx/font.h>
#include <gfx/engine.h>
#include <gfx/textmesh.h>
#include <glm/gtx/transform.hpp>
#include <gfx/keyinput.h>
#include <gfx/switch.h>
#include <gfx/quadmesh.h>
#include <gfx/meshfactory.h>
#include <monkey/walkarea.h>
#include <monkey/scripthotspot.h>
#include <gfx/keyboardcontroller.h>
#include <monkey/luakeylistener.h>
#include <gfx/depth.h>
#include <gfx/follow.h>
#include <gfx/billboard.h>
#include <monkey/scaling.h>
#include <monkey/info.h>
#include <gfx/textview.h>
#include <gfx/statemachine.h>
#include <monkey/luacollision.h>
#include <gfx/walkstate.h>

// a text component is actually a renderer
void TextComponentFactory::operator() (luabridge::LuaRef& ref, Entity* e) {
    auto tc = ReadTextComponent(ref);
    e->AddComponent(tc);
}

void OutlineTextComponentFactory::operator() (luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);

    std::string font = table.Get<std::string>("font");
    float size = table.Get<float>("size");
    std::string text = table.Get<std::string>("id");
    TextAlignment align = table.Get<TextAlignment>("align", TOP_LEFT);
    glm::vec4 fontColor = table.Get<glm::vec4>("fontcolor", glm::vec4(255.0f));
    glm::vec4 outlineColor = table.Get<glm::vec4>("outlinecolor", glm::vec4(255.0f));
    fontColor /= 255.0f;
    outlineColor /= 255.0f;
    Font* f = Engine::get().GetAssetManager().GetFont(font);
    auto mesh = std::make_shared<TextMesh>(f, text, size, align);
    glm::vec2 offset = mesh->getOffset();
    glm::vec2 outlineOffsets[] = {{0, 0}, {-1, 0}, {-1,1}, {0, 1}, {1,1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    for (int i =0; i < 9; ++i) {
        auto entity = std::make_shared<Entity>();
        auto renderer = std::make_shared<Renderer>();
        renderer->SetMesh(mesh);
        entity->SetPosition(glm::vec3(outlineOffsets[i] * 0.5f, i == 0 ? 0 : -1));
        renderer->SetTint(i==0 ? fontColor : outlineColor);
        //renderer->SetRenderingTransform(glm::translate(glm::vec3(offset, 0.0f)));
        //entity->AddComponent(renderer);
        parent->AddChild(entity);
    }
}


std::shared_ptr<Renderer> ReadTextComponent (luabridge::LuaRef& ref) {
    LuaTable table(ref);
    auto renderer = std::make_shared<Renderer>();

    // read input
    std::string text = table.Get<std::string>("id");
    std::string font = table.Get<std::string>("font");
    float size = table.Get<float>("size", 8);
    TextAlignment align = table.Get<TextAlignment>("align", TOP_LEFT);
    float maxWidth = table.Get<float>("maxwidth", 0.0f);
    glm::vec4 color = table.Get<glm::vec4>("color", glm::vec4(255.0f));
    color /= 255.0f;

    Font* f = Engine::get().GetAssetManager().GetFont(font);
    auto mesh = std::make_shared<TextMesh>(f, text, size, align, maxWidth);
    glm::vec2 offset = mesh->getOffset();
    renderer->SetRenderingTransform(glm::translate(glm::vec3(offset, 0.0f)));
    renderer->SetTint(color);
    renderer->SetMesh(mesh);
    return renderer;
}

std::shared_ptr<Shape> ReadShape(luabridge::LuaRef& ref) {
    LuaTable at (ref);
    std::string type = at.Get<std::string>("type");
    glm::vec2 offset = at.Get<glm::vec2>("offset", glm::vec2(0.0f));
    if (type == "rect") {
        float w = at.Get<float>("width");
        float h = at.Get<float>("height");
        return std::make_shared<Rect>(w, h, offset);
    } else if (type=="line") {
        glm::vec2 A = at.Get<glm::vec2>("A");
        glm::vec2 B = at.Get<glm::vec2>("B");
        return std::make_shared<Line>(A, B);
    } else if (type == "poly") {
        std::vector<float> outline = at.GetVector<float>("outline");
        std::vector<glm::vec2> points;
        for (int i = 0; i < outline.size(); i = i + 2)
            points.push_back(glm::vec2(outline[i], outline[i + 1]));
        if (at.HasKey("holes")) {
            std::unique_ptr<Polygon> mainOutline(new Polygon(points));
            luabridge::LuaRef holes = at.Get<luabridge::LuaRef>("holes");
            LuaTable ha(holes);
            auto poly = std::make_shared<Poly>(std::move(mainOutline));
            for (int j = 0; j < holes.length(); ++j) {
                luabridge::LuaRef h = holes[j + 1];
                std::vector<float> holeOutline = ReadVector<float>(h);
                std::vector<glm::vec2> points;
                for (int i = 0; i < holeOutline.size(); i = i + 2)
                    points.push_back(glm::vec2(holeOutline[i], holeOutline[i + 1]));
                poly->AddHole(std::unique_ptr<Polygon>(new Polygon(points)));

            }
            return poly;

        } else {


            return std::make_shared<Polygon>(points);
        }
    } else if (type == "circle") {
        float radius = at.Get<float>("radius");
        return std::make_shared<Circle>(radius, offset);
    } else if (type == "graph") {
        // read the vertices
        luabridge::LuaRef rVert = at.Get<luabridge::LuaRef>("vertices");
        std::vector<glm::vec2> vertices;
        std::vector<std::pair<int, int>> edges;
        for (int i = 0; i< rVert.length(); ++i) {
            luabridge::LuaRef vertex = rVert[i+1];
            glm::vec2 p(vertex[1].cast<float>(), vertex[2].cast<float>());
            vertices.push_back(p);
        }
        luabridge::LuaRef rEdges = at.Get<luabridge::LuaRef>("edges");
        for (int i = 0; i< rEdges.length(); ++i) {
            luabridge::LuaRef edge = rEdges[i+1];
            std::pair<int, int> e(edge[1].cast<int>(), edge[2].cast<int>());
            edges.push_back(e);
        }
        return std::make_shared<PolyLine>(vertices,edges);
    } else if (type =="compound") {
        luabridge::LuaRef rshapes = at.Get<luabridge::LuaRef>("shapes");
        auto cs = std::make_shared<CompoundShape>();
        for (int i = 0; i<rshapes.length(); ++i) {
            luabridge::LuaRef rshape = rshapes[i+1];
            auto s = ReadShape(rshape);
            cs->AddShape(s);
        }
        return cs;
    }

    return nullptr;
}


std::unique_ptr<Function2D> GetFunc2D(luabridge::LuaRef& ref) {
    std::unique_ptr<PatchwiseLinear2D> p (new PatchwiseLinear2D);
    for (int i = 0; i < ref.length(); ++i) {
        luabridge::LuaRef f = ref[i+1];
        LuaTable funcTable(f);
        glm::vec4 domain = funcTable.Get<glm::vec4>("rect");
        bool isX = (funcTable.Get<char>("dir") == 'x');
        glm::vec2 bounds = funcTable.Get<glm::vec2>("bounds");
        p->AddFunction(domain, isX, bounds.x, bounds.y);
    }
    return std::move(p);
}

std::shared_ptr<HotSpot> GetHotSpot (luabridge::LuaRef& ref, std::shared_ptr<Shape> shape) {
    LuaTable table(ref);
    int priority = table.Get<int>("priority");
    auto hotspot = std::make_shared<ScriptHotSpot>(shape, priority);
    if (table.HasKey("onenter")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onenter");
        hotspot->SetOnEnter(r);
    }
    if (table.HasKey("onleave")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onleave");
        hotspot->SetOnLeave(r);
    }
    if (table.HasKey("onclick")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onclick");
        hotspot->SetOnClick(r);
    }
    if (table.HasKey("onmove")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onmove");
        hotspot->SetOnMove(r);
    }
    return hotspot;
}

void CameraFactory::operator()(luabridge::LuaRef & cam, Entity * entity) {
    LuaTable tcam(cam);
    std::string camType = tcam.Get<std::string>("type");
    std::string tag = tcam.Get<std::string>("tag", "");
    glm::vec3 pos = tcam.Get<glm::vec3>("pos", glm::vec3(0.0f));
    glm::vec3 direction = tcam.Get<glm::vec3> ("direction", glm::vec3(0, 0, -1));
    glm::vec3 up = tcam.Get<glm::vec3> ("up", glm::vec3(0, 1, 0));
    glm::vec4 viewport = tcam.Get<glm::vec4>("viewport", glm::vec4(0.0f, 0.0f, Engine::get().GetDeviceSize()));

    if (camType == "ortho") {
        // orhographic camera
        glm::vec2 size = tcam.Get<glm::vec2>("size");
        glm::vec4 bounds = tcam.Get<glm::vec4>("bounds", glm::vec4(0.0));
        auto camera = std::unique_ptr<OrthographicCamera>(new OrthographicCamera(size.x, size.y, viewport));
        if (bounds != glm::vec4(0.0f))
            camera->SetBounds(bounds[0], bounds[2], bounds[1], bounds[3]);
        camera->SetPosition(pos, direction, up);
        if (!tag.empty())
            camera->SetTag(tag);
        entity->SetCamera(std::move(camera));
    }

    // perspective camera...
    else if (camType == "perspective") {
        // get field of view
        float fov = tcam.Get<float>("fov", 45.0f);
        float near = tcam.Get<float>("near", 0.05f);
        float far = tcam.Get<float>("far", 1000.0f);
        auto camera = std::unique_ptr<PerspectiveCamera>(new PerspectiveCamera(viewport, fov, near, far));
        camera->SetPosition(pos, direction, up);
        if (!tag.empty())
            camera->SetTag(tag);
        entity->SetCamera(std::move(camera));
        
    }
}

void KeyInputFactory::operator()(luabridge::LuaRef & ref, Entity * entity) {
    LuaTable table(ref);

    // read input
    int maxLength = table.Get<int>("maxlength");

    // callback function when user hits enter
    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("func");
    entity->AddComponent(std::make_shared<KeyInput>(maxLength, shapeR));
}

void GfxComponentFactory::operator()(luabridge::LuaRef & ref, Entity * entity) {
    LuaTable table(ref);

    auto renderer = std::make_shared<Renderer>();
    if (table.HasKey("image")) {
        std::string image = table.Get<std::string>("image");
        float w = table.Get<float>("width", 0.0f);
        float h = table.Get<float>("height", 0.0f);
        auto mesh = std::make_shared<QuadMesh>(image, w, h);
        renderer->SetMesh(mesh);
    } else if (table.HasKey("model")) {
        std::string model = table.Get<std::string>("model");
        std::string anim = table.Get<std::string>("anim", "");
        bool flip = table.Get<bool>("flip", false);
        renderer->SetMesh(Engine::get().GetAssetManager().GetMesh(model));
        renderer->SetFlipX(flip);
        //renderer->SetRenderingTransform(glm::scale(glm::vec3(0.1f))*glm::rotate(90.0f, glm::vec3(1.0f,0.0f,0.0f)));
        //renderer->SetScale(0.1f);
        renderer->SetAnimation(anim);
    } else if (table.HasKey("shape")) {
        luabridge::LuaRef sref = table.Get<luabridge::LuaRef>("shape");
        std::string draw = table.Get<std::string>("draw","outline");
        glm::vec4 color = table.Get<glm::vec4>("color");
        color /= 255.0f;
        auto shape = ReadShape(sref);
        if (draw == "outline") {
            auto mesh = MeshFactory::CreateMesh(*(shape.get()), 0.0f);
            renderer->SetMesh(mesh);
        } else if (draw == "solid") {
            auto mesh = MeshFactorySolid::CreateMesh(*(shape.get()), 0.0f);
            renderer->SetMesh(mesh);

        }
        renderer->SetTint(color);

    }
    entity->AddComponent(renderer);
}

void ColliderComponentFactory::operator()(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);

    // input
    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    int tag = table.Get<int>("tag");
    int flag = table.Get<int>("flag");
    auto shape = ReadShape(shapeR);

    parent->AddComponent(std::make_shared<Collider>(shape, tag, flag));
}


// Read the walk-area
void WalkAreaComponentFactory::operator() (luabridge::LuaRef& ref, Entity* parent) {
    LuaTable table(ref);

    // input
    int priority = table.Get<int>("priority");
    std::string targetId = table.Get<std::string>("target");
    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    auto shape = ReadShape(shapeR);
    auto hotspot = std::make_shared<WalkArea>(shape, priority, targetId);

    // see if it has a depthfunc
    if (table.HasKey("scaling")) {
        luabridge::LuaRef sref = table.Get<luabridge::LuaRef>("scaling");
        luabridge::LuaRef depthRef = sref["depth"];
        auto depthFunc = GetFunc2D(depthRef);
        hotspot->SetDepthFunction(std::move(depthFunc));
        luabridge::LuaRef scaleRef = sref["scale"];
        auto scaleFunc = GetFunc2D(scaleRef);
        hotspot->SetScalingFunction(std::move(scaleFunc));
    }

    if (table.HasKey("blockedlines")) {
        luabridge::LuaRef ref = table.Get<luabridge::LuaRef>("blockedlines");
        for (int i = 0; i < ref.length(); ++i) {
            luabridge::LuaRef bl = ref[i+1];
            LuaTable t(bl);
            glm::vec2 A = t.Get<glm::vec2>("A");
            glm::vec2 B = t.Get<glm::vec2>("B");
            bool active = t.Get<bool>("active");
            hotspot->AddBlockedLine(A, B, active);
        }
    }
    hotspot->SetTag("walkarea");
    parent->AddComponent(hotspot);
}

void HotSpotComponentFactory::operator() (luabridge::LuaRef& ref, Entity* parent) {
    LuaTable table(ref);
    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    auto shape = ReadShape(shapeR);
    auto hs = GetHotSpot(ref, shape);
    Shape* s = hs->GetShape();
    parent->AddComponent(hs);
    int layer = table.Get<int>("layer", 1);
    auto ce = std::make_shared<Entity>();
    ce->SetLayer(layer);
    auto cer = std::make_shared<Renderer>();
    auto debugMesh = MeshFactory::CreateMesh(*s, 1.0f);
    cer->SetMesh(debugMesh);
    ce->AddComponent(cer);
    parent->AddChild(ce);
}


std::shared_ptr<State> WalkStateFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);
    float speed = table.Get<float>("speed");
    auto ptr = std::make_shared<WalkState>(speed);
    return ptr;

}


StateMachineComponentFactory::StateMachineComponentFactory() {
    m_stateFactories["walk"] = std::make_shared<WalkStateFactory>();
}

void StateMachineComponentFactory::operator()(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);

    std::string initialState = table.Get<std::string>("initialstate");
    auto comp = std::make_shared<KeyboardControlledStateMachine>(initialState);
    // get the array of states

    luabridge::LuaRef ts = table.Get<luabridge::LuaRef>("states");
    for (int i = 0 ; i < ts.length(); ++i) {
        luabridge::LuaRef tss = ts[i+1];
        std::string id = tss["id"].cast<std::string>();
        std::string type = tss["type"].cast<std::string>();
        auto it = m_stateFactories.find(type);
        if (it == m_stateFactories.end())
            GLIB_FAIL("Unknown state " << type);
        auto state = it->second->Create(tss);
        comp->AddState(id, state);
    }

//    float width = table.Get<float>("width");
//    float height = table.Get<float>("height");
//    float speed = table.Get<float>("speed");
//    int horRays = table.Get<int>("horizontal_rays");
//    int vertRays = table.Get<int>("vertical_rays");
//
//    auto c = std::make_shared<KeyboardControllerCollision>(width, height, speed, horRays, vertRays);
//    if (table.HasKey("anims")) {
//        auto anims = table.Get<luabridge::LuaRef>("anims");
//        for (int i = 0 ; i < anims.length(); ++i) {
//            luabridge::LuaRef an = anims[i+1];
//            std::string id = an["id"].cast<std::string>();
//            std::string anim = an["anim"].cast<std::string>();
//            c->AddAnimation(id, anim);
//        }
//    }
    parent->AddComponent(comp);
}

void LuaKeyboardComponentFactory::operator()(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);
    auto keyListener = std::make_shared<LuaKeyListener>();
    luabridge::LuaRef hotkeys = table.Get<luabridge::LuaRef>("keys");
    for (int i = 0; i < hotkeys.length(); ++i) {
        luabridge::LuaRef hotkey = hotkeys[i+1];
        int key = hotkey["key"].cast<int>();
        luabridge::LuaRef callback = hotkey["func"];
        keyListener->AddHotKey(key, callback);
    }
    parent->AddComponent(keyListener);

}

void SwitchComponentFactory::operator()(luabridge::LuaRef & ref, Entity * p) {
    LuaTable table(ref);
    std::vector<std::string> stateNames = table.GetVector<std::string>("states");
    std::string initialState = table.Get<std::string>("initial");
    auto sw = std::make_shared<Switch>(stateNames, initialState);
    p->AddComponent(sw);
}

void DepthComponentFactory::operator()(luabridge::LuaRef & ref, Entity * p) {
    LuaTable table(ref);
    auto comp = std::make_shared<DepthCalculator>();
    if (table.HasKey("depth")) {
        luabridge::LuaRef dref = table.Get<luabridge::LuaRef>("depth");
        auto depthFunc = GetFunc2D(dref);
        comp->SetDepthFunction(std::move(depthFunc));
    }
    if (table.HasKey("scale")) {
        luabridge::LuaRef dref = table.Get<luabridge::LuaRef>("scale");
        auto scaleFunc = GetFunc2D(dref);
        comp->SetScalingFunction(std::move(scaleFunc));
    }
    p->AddComponent(comp);

}

void InfoComponentFactory::operator()(luabridge::LuaRef & ref, Entity * p) {
    auto comp = std::make_shared<LuaInfo>(ref);
    p->AddComponent(comp);

}

void FollowComponentFactory::operator()(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);
    std::string cam = table.Get<std::string>("cam");
    glm::vec3 relPos = table.Get<glm::vec3>("relativepos");
    glm::vec3 up = table.Get<glm::vec3>("up");
    auto f = std::make_shared<Follow>(cam, relPos, up);
    if (table.HasKey("z")) {
        float z = table.Get<float>("z");
        f->fixZ(z);
    }
    parent->AddComponent(f);
}

void BillboardComponentFactory::operator()(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);
    std::string cam = table.Get<std::string>("cam");
    parent->AddComponent(std::make_shared<Billboard>(cam));
}

void ScalingComponentFactory::operator() (luabridge::LuaRef& ref, Entity* parent) {
    parent->AddComponent(std::make_shared<ScalingDepthComponent>());
    
}

void ButtonComponentFactory::operator() (luabridge::LuaRef& ref, Entity* parent) {
    LuaTable table(ref);
    auto renderer = ReadTextComponent(ref);
    // for a button the shape is determined by the text size
    auto bounds = renderer->GetBounds();
    float w = bounds.max.x - bounds.min.x;
    float h = bounds.max.y - bounds.min.y;
    auto shape = std::make_shared<Rect>(w, h);
    //auto debugMesh = MeshFactory::CreateMesh(*(shape.get()), 1.0f);
    auto hs = GetHotSpot(ref, shape);
    parent->AddComponent(renderer);
    parent->AddComponent(hs);
}



void TextViewComponentFactory::operator() (luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);
    glm::vec4 viewport = table.Get<glm::vec4>("viewport");
    float w = table.Get<float>("width");
    float h = table.Get<float>("height");
    float size = table.Get<float>("size");
    float deltax = table.Get<float>("deltax", 0.0f);
    glm::vec4 color = table.Get<glm::vec4>("color", glm::vec4(255.0f));
    color /= 255.0f;
    std::string font = table.Get<std::string>("font");
    auto r = std::make_shared<TextView>(w, h, size, font, color, viewport, deltax);
    parent->AddComponent(r);
    
}


void HotSpotManagerFactory::Create(luabridge::LuaRef&) {
    auto hsm = std::make_shared<HotSpotManager>();
    Engine::get().AddRunner(hsm);
    //g.RegisterToMouseEvent(hsm.get());
}

void SchedulerFactory::Create(luabridge::LuaRef&) {
    // set-up the scripting engine
    auto scheduler = std::make_shared<Scheduler>();
    Engine::get().AddRunner(scheduler);
}

void CollisionEngineFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);
    glm::vec2 collisionSize = table.Get<glm::vec2>("size");
    auto ce = std::make_shared<CollisionEngine>(collisionSize.x, collisionSize.y);

    if (table.HasKey("response")) {
        // set the collision responses
        luabridge::LuaRef resp = table.Get<luabridge::LuaRef>("response");
        std::unique_ptr<CollisionResponseManager> crm (new CollisionResponseManager);
        for (int i = 0; i < resp.length();++i) {
            luabridge::LuaRef a = resp[i+1];
            LuaTable at(a);
            std::vector<int> tags = at.GetVector<int>("tag");
            std::unique_ptr<LuaCollisionResponse> l(new LuaCollisionResponse);
            if (at.HasKey("onenter")) {
                luabridge::LuaRef onEnter = at.Get<luabridge::LuaRef>("onenter");
                l->SetOnEnter(onEnter);
            }
            if (at.HasKey("onleave")) {
                luabridge::LuaRef onLeave = at.Get<luabridge::LuaRef>("onleave");
                l->SetOnLeave(onLeave);
            }
            if (at.HasKey("onstay")) {
                luabridge::LuaRef onStay = at.Get<luabridge::LuaRef>("onstay");
                l->SetOnStay(onStay);
            }
            crm->AddCollisionResponse(tags[0], tags[1], std::move(l));

        }
        ce->SetResponseManager(std::move(crm));
    }

    Engine::get().AddRunner(ce);

}
