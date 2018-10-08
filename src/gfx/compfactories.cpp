#include <gfx/compfactories.h>
#include <gfx/components/renderer.h>
#include <gfx/font.h>
#include <gfx/engine.h>
#include <gfx/textmesh.h>
#include <glm/gtx/transform.hpp>
#include <gfx/components/keyinput.h>
#include <gfx/components/switch.h>
#include <gfx/quadmesh.h>
#include <gfx/meshfactory.h>
//#include <monkey/walkarea.h>
#include <gfx/components/scripthotspot.h>
#include <gfx/components/luakeylistener.h>
#include <gfx/components/depth.h>
#include <gfx/components/follow.h>
#include <gfx/components/billboard.h>
//#include <monkey/scaling.h>
#include <gfx/components/info.h>
#include <gfx/components/textview.h>
#include <gfx/components/statemachine.h>
#include <gfx/luacollision.h>
#include <gfx/walkstate.h>
#include <gfx/hit.h>
#include <gfx/aiwalk.h>
#include <gfx/components/shadow.h>
#include <gfx/basicstate.h>

#include <gfx/components/controller2d.h>
#include <gfx/components/dynamics2d.h>

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
    } else if (type == "ellipse") {
        glm::vec2 axes = at.Get<glm::vec2>("semiaxes");
        return std::make_shared<Ellipse>(axes.x, axes.y, offset);
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
    LuaTable table(ref);
    std::string type = table.Get<std::string>("type");
    if (type == "linear_x") {
        glm::vec4 values = table.Get<glm::vec4>("values");
        std::unique_ptr<Function2D> f(new Linear2Dx(values[0], values[1], values[2], values[3]));
        return std::move(f);
    } else if (type == "linear_y") {
        glm::vec4 values = table.Get<glm::vec4>("values");
        std::unique_ptr<Function2D> f(new Linear2Dy(values[0], values[1], values[2], values[3]));
        return std::move(f);
    } else if (type == "patchwise") {

        std::unique_ptr<PatchwiseLinear2D> p(new PatchwiseLinear2D);
        for (int i = 0; i < ref.length(); ++i) {
            luabridge::LuaRef f = ref[i + 1];
            LuaTable funcTable(f);
            glm::vec4 domain = funcTable.Get<glm::vec4>("rect");
            bool isX = (funcTable.Get<char>("dir") == 'x');
            glm::vec2 bounds = funcTable.Get<glm::vec2>("bounds");
            p->AddFunction(domain, isX, bounds.x, bounds.y);
        }
        return std::move(p);
    }
    GLIB_FAIL("Unknown function " << type);
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
        glm::vec2 repeat = table.Get<glm::vec2>("rep", glm::vec2(1.0f, 1.0f));
        glm::vec2 skew = table.Get<glm::vec2>("skew", glm::vec2(0.0f, 0.0f));
        auto mesh = std::make_shared<QuadMesh>(image, w, h, repeat.x, repeat.y, skew.x, skew.y);
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
    if (table.HasKey("scale")) {
        float scale = table.Get<float>("scale");
        renderer->SetScale(scale);
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

    auto coll = std::make_shared<Collider>(shape, tag, flag);
    parent->AddComponent(coll);
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

std::shared_ptr<State> AIWalkStateFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);
    float speed = table.Get<float>("speed");
    std::string target = table.Get<std::string>("target");
    auto ptr = std::make_shared<AIWalk>(target, speed);
    return ptr;

}


std::shared_ptr<State> WalkCollisionStateFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);
    float speed = table.Get<float>("speed");
    float width = table.Get<float>("width");
    float height = table.Get<float>("height");
    int horRays = table.Get<int>("horizontal_rays");
    int vertRays = table.Get<int>("vertical_rays");

    auto ptr = std::make_shared<WalkStateCollision>(width, height, speed, horRays, vertRays);
    if (table.HasKey("anims")) {
        luabridge::LuaRef animsTable = table.Get<luabridge::LuaRef>("anims");
        for (int i = 0; i < animsTable.length(); ++i) {
            luabridge::LuaRef anim = animsTable[i+1];
            std::string id = anim["id"].cast<std::string>();
            std::string animName = anim["anim"].cast<std::string>();
            ptr->AddAnimation(id, animName);
        }
    }
    return ptr;

}


std::shared_ptr<State> HitStateFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);
    std::string anim = table.Get<std::string>("anim");

    int frame = table.Get<int>("frame", -1);
    if (frame != -1) {
        int mask =table.Get<int>("mask");
        glm::vec2 offset = table.Get<glm::vec2>("offset");
        luabridge::LuaRef ts = table.Get<luabridge::LuaRef>("shape");
        auto shape = ReadShape(ts);
        luabridge::LuaRef callback = table.Get<luabridge::LuaRef>("func");
        auto ptr = std::make_shared<HitCollision>(anim, frame, shape, offset, mask, callback);
        return ptr;


    } else {
        auto ptr = std::make_shared<Hit>(anim);
        return ptr;
    }

}

StateMachineComponentFactory::StateMachineComponentFactory() {


}

void StateMachineComponentFactory::operator()(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);

    std::string initialState = table.Get<std::string>("initialstate");
    std::shared_ptr<StateMachine> comp;
    if (table.HasKey("keys")) {
        auto c  = std::make_shared<KeyboardControlledStateMachine>(initialState);
        // read the transition keys
        auto keys = table.GetVector<luabridge::LuaRef>("keys");
        for (auto& key : keys) {
            int k =  key["key"].cast<int>();
            std::string current =  key["current"].cast<std::string>();
            std::string next =  key["next"].cast<std::string>();
            c->AddKey(current, k, next);
        }
        comp = c;
    } else {
        auto c = std::make_shared<RandomTransitionStateMachine>(initialState);
        // read the transition keys
        auto keys = table.GetVector<luabridge::LuaRef>("transitionmatrix");
        for (auto& key : keys) {
            float prob =  key["prob"].cast<float>();
            std::string current =  key["current"].cast<std::string>();
            std::string next =  key["next"].cast<std::string>();
            c->Add(current, next, prob);
        }
        comp = c;
    }

    // get the array of states
    auto sceneFactory = Engine::get().GetSceneFactory();
    luabridge::LuaRef ts = table.Get<luabridge::LuaRef>("states");
    for (int i = 0 ; i < ts.length(); ++i) {
        luabridge::LuaRef tss = ts[i+1];
        std::string id = tss["id"].cast<std::string>();
        std::string type = tss["type"].cast<std::string>();
        auto factory = sceneFactory->GetStateFactory(type);
        if (factory == nullptr)
            GLIB_FAIL("Unknown state " << type);
        auto state = factory->Create(tss);
        state->SetId(id);
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

void ShadowComponentFactory::operator()(luabridge::LuaRef &, Entity * parent) {
    parent->AddComponent(std::make_shared<Shadow>());
}
void Controller2DComponentFactory::operator()(luabridge::LuaRef & ref, Entity * parent) {
    LuaTable table(ref);
    float maxClimbAngle = table.Get<float>("maxclimbangle");
    float maxDescendAngle = table.Get<float>("maxdescendangle");
    int horCount = table.Get<int>("horizontalrays", 4);
    int vertCount = table.Get<int>("veticalrays", 4);
    float skinWidth = table.Get<float>("skinwidth", .015f);
    parent->AddComponent(std::make_shared<Controller2D>(maxClimbAngle, maxDescendAngle, skinWidth, horCount, vertCount));
}

void Dynamics2DComponentFactory::operator()(luabridge::LuaRef & ref, Entity * parent) {
    LuaTable table(ref);
    float jumpHeight = table.Get<float>("jumpheight");
    float timeApex = table.Get<float>("timetojumpapex");
    parent->AddComponent(std::make_shared<Dynamics2D>(jumpHeight, timeApex));
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
    bool coll25 = table.Get<bool>("coll25", false);
    if (coll25) {
        float eps = table.Get<float>("eps");
        ce->Enable25DCollision(eps);
    }
    if (table.HasKey("response")) {
        // set the collision responsesfg
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

std::shared_ptr<State> BasicStateFactory::Create(luabridge::LuaRef & r) {
    LuaTable table(r);
    std::string anim = table.Get<std::string>("anim");
    std::vector<std::string> colliders = table.GetVector<std::string>("colliders");
    return std::make_shared<BasicState>(anim, colliders);
}

