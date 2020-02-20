#include <regex>
#include <monkey/entitywrapper.h>
#include <monkey/components/renderer.h>
#include <monkey/components/hotspot.h>
#include <monkey/model/textmodel.h>
#include <glm/gtx/transform.hpp>
#include <monkey/engine.h>
#include <monkey/entities/textview.h>
#include <monkey/activities/animate.h>
#include <monkey/factories.h>
#include <monkey/components/info.h>
#include <monkey/components/depth.h>
#include <monkey/components/animator.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/statemachine.h>
#include <monkey/properties.h>
#include <monkey/components/extstatemachine.h>
#include <monkey/components/smartcollider.h>
#include <monkey/components/platform.h>
#include <monkey/components/depth25.h>
#include <monkey/components/follow.h>
#include <monkey/components/luahook.h>
#include <boost/filesystem/operations.hpp>

extern GLFWwindow* window;

float EntityWrapper::GetX() const {
    return m_underlying->GetPosition().x;
}
float EntityWrapper::GetY() const {
    return m_underlying->GetPosition().y;
}
float EntityWrapper::GetZ() const {
    return m_underlying->GetPosition().z;
}

int EntityWrapper::GetId() const {
    return m_underlying->GetId();
}
float EntityWrapper::GetVx() const {
    return m_underlying->GetComponent<Dynamics2D>()->m_velocity.x;
}
float EntityWrapper::GetVy() const {
    return m_underlying->GetComponent<Dynamics2D>()->m_velocity.y;
}
float EntityWrapper::GetVx25() const {
    return m_underlying->GetComponent<Depth25>()->getVelocity().x;
}


void EntityWrapper::SetVx(float value) {
    m_underlying->GetComponent<Dynamics2D>()->m_velocity.x = value;
}
void EntityWrapper::SetVx25(float value) {
    m_underlying->GetComponent<Depth25>()->getVelocity().x =  value;
}
void EntityWrapper::SetVy(float value) {
    m_underlying->GetComponent<Dynamics2D>()->m_velocity.y = value;
}

float EntityWrapper::GetScale() const {
    return m_underlying->GetScale();
}
void EntityWrapper::SetScale(float value) {
    m_underlying->SetScale(value);
}
std::string EntityWrapper::GetTag() const {
    return m_underlying->GetTag();
}
std::string EntityWrapper::GetState() const {
    auto sm = m_underlying->GetComponent<StateMachine>();
    return sm->GetState();
}

void EntityWrapper::SetState(const std::string& state) {
    auto sm = m_underlying->GetComponent<StateMachine>();
    return sm->SetState(state);
}

void EntityWrapper::EnableStateMachine(bool value) {
    auto sm = m_underlying->GetComponent<StateMachine>();
    sm->setActive(value);
}

void EntityWrapper::DropCharacters() {
    m_underlying->GetComponent<PlatformComponent>()->RemoveCharacters();

}

luabridge::LuaRef EntityWrapper::GetProperty(const std::string& key) const {
    auto sm = m_underlying->GetComponent<Properties>();
    if (sm == nullptr) {
        return luabridge::LuaRef(LuaWrapper::L);
    }
    return sm->get(key);
}

void EntityWrapper::SetProperty (const std::string& key, luabridge::LuaRef value) {
    auto sm = m_underlying->GetComponent<Properties>();
    return sm->set(key, value);
}

void EntityWrapper::SendMessage(luabridge::LuaRef ref) {
    //auto sm = dynamic_cast<ExtendedStateMachine*>(m_underlying->GetComponent<StateMachine>());
    //return sm->SendMessage(ref);

}

std::string EntityWrapper::GetText() const {
    Renderer* r = m_underlying->GetComponent<Renderer>();
    auto tm = dynamic_cast<TextMesh*>(r->GetModel());
    return tm->GetText();
}

int EntityWrapper::GetLines() const {
    Renderer* r = m_underlying->GetComponent<Renderer>();
    auto tm = dynamic_cast<TextMesh*>(r->GetModel());
    return tm->getNumberOfLines();
}


EntityWrapper EntityWrapper::GetParent() {
    return EntityWrapper(m_underlying->GetParent());
}

void EntityWrapper::SetColor(int r, int g, int b, int a) {
    m_underlying->GetComponent<Renderer>()->SetTint(glm::vec4(r/255.0f, g/255.0f, b/255.0f, a/255.0f));
}


EntityWrapper EntityWrapper::GetEntityFromTag(const std::string& id) {
    try {
        auto ref = Monkey::get().Get<Entity>(id);
        return EntityWrapper(ref);
    } catch (Error& err) {
        return EntityWrapper();
    }
}

EntityWrapper EntityWrapper::GetEntityFromId(int id) {
    try {
        auto ref = Monkey::get().Get<Entity>(id);
        return EntityWrapper(ref);
    } catch (Error& err) {
        return EntityWrapper();
    }
}


int EntityWrapper::AddEntity(luabridge::LuaRef ref, EntityWrapper* parent) {

    auto mf = Engine::get().GetSceneFactory();
    LuaTable table(ref);
    auto ptr = mf->make<Entity>(table);
    parent->m_underlying->AddChild(ptr);
    //ptr->start();
    //ptr->Begin();
    return ptr->GetId();


}

bool EntityWrapper::isKeyDown(int id) {
    int state = glfwGetKey(window, id);
    return (state == GLFW_PRESS);

}


void EntityWrapper::RemoveEntityFromTag(const std::string& tag) {
    std::cout << "*** lua request delete item with tag = " << tag << "\n";
    auto entity = Monkey::get().Get<Entity>(tag);
    Engine::get().Remove(entity->GetId());
}

void EntityWrapper::RemoveEntityFromId (int id) {
    std::cout << "*** lua request delete item with id = " << id << "\n";
    Engine::get().Remove(id);

}

void EntityWrapper::Clear() {
    m_underlying->ClearAllChildren();
}

void EntityWrapper::ClearText() {
    TextView* r = dynamic_cast<TextView*>(m_underlying);
    r->ClearText();
}

void EntityWrapper::Remove() {
    Engine::get().Remove(m_underlying->GetId());
}

void EntityWrapper::EnableDepth(bool value) {
    m_underlying->GetComponent<DepthCalculator>()->setActive(value);
}

void EntityWrapper::SetText(const std::string& text) {
    Renderer* r = m_underlying->GetComponent<Renderer>();
    auto tm = dynamic_cast<TextModel*>(r->GetModel());
    glm::vec2 oldOffset = tm->GetOffset();
    tm->SetText(text);
    glm::vec2 offset = tm->GetOffset();
    r->SetTransform(glm::translate(glm::vec3(offset, 0.0f)));
    //r->GetObject()->MoveLocal(-oldOffset+offset);
}

void EntityWrapper::EnableUpdate(bool value) {
    m_underlying->SetEnableUpdate(value);
}



namespace luaFunctions {

    void EnableScriptEngine (bool value) {

        auto schedule = Engine::get().GetRunner<Scheduler>();
        schedule->setActive(value);
    }

    void EndRoom() {
        Engine::get().EndScene();
    }



    void EnableMouse(bool value) {
        //Engine::get().GetMouseHandler()->Enable(value);
    }

    void EnableKeyboard(bool value) {
        //Engine::get().GetKeyboardListener()->Enable(value);
    }

    void EnableKey(int key, bool value) {
        //Engine::get().GetKeyboardListener()->EnableKey(key, value);
    }

    void PlayScript (luabridge::LuaRef ref) {
        auto scheduler = Engine::get().GetRunner<Scheduler>();
        LuaTable table(ref);
        //int startId = table.Get<int>("startid");
        int loopId = table.Get<int>("loop", -1);
        std::string scriptId = table.Get<std::string>("name", "");
        auto script = std::make_shared<Script>();
        luabridge::LuaRef actions = ref["actions"];

        std::vector<std::pair<int, int>> edges;
        auto factory = Engine::get().GetSceneFactory();
        for (int i = 0; i < actions.length(); ++i) {
            luabridge::LuaRef action = actions[i+1];
            if (action["id"].isNil())
                GLIB_FAIL("When reading a script, found action with no required <id> field!");
            luabridge::LuaRef ac = action["action"];
            int id = action["id"].cast<int>();
            if (!action["after"].isNil()) {
                luabridge::LuaRef after = action["after"];
                for (int j = 0; j < after.length(); ++j) {
                    int a = after[j+1].cast<int>();
                    edges.push_back(std::make_pair(a, id));
                }
            } else {
                // If I don't specify an <after> field, then I assume it follows the previous one
                // unless of course it is the first
                if (id > 1) {
                    edges.push_back(std::make_pair(id-1, id));
                }
            }
            LuaTable tac(ac);
            auto activity= factory->make<Activity>(tac);
            script->AddActivity(id, std::move(activity));
        }

        for (auto& i : edges) {
            script->AddEdge(i.first, i.second);
        }
        if (loopId != -1) {
            script->SetLoop(loopId);
        }

        if (scriptId.empty())
            scheduler->AddScript(script);
        else
            scheduler->AddScript(scriptId, script);
    }
    
}

void EntityWrapper::SetActive (bool value) {
    m_underlying->setActive(value);
}

void EntityWrapper::SetEnableControls (bool value) {
    m_underlying->SetControlsEnabled(value);
}

void EntityWrapper::EnableCollisions(bool value) {
    auto collider = m_underlying->GetComponent<ICollider>();
    if (collider != nullptr)
        collider->setActive(value);
    auto& children = m_underlying->GetChildren();
    for (auto& child : children) {
        EntityWrapper e(child.second.get());
        e.EnableCollisions(value);
    }
}

void EntityWrapper::ForceClick(float x, float y) {
    auto hotspot = m_underlying->GetComponent<HotSpot>();
    hotspot->onClick(glm::vec2(x, y), GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);

}

//void EntityWrapper::EnableGroup(int id) {
//    auto hs = Engine::get().GetRef<HotSpotManager>("_hotspotmanager");
//    hs->EnableGroup(id);
//}
//
//void EntityWrapper::DisableGroup(int id) {
//    auto hs = Engine::get().GetRef<HotSpotManager>("_hotspotmanager");
//    hs->DisableGroup(id);
//
//}

void EntityWrapper::SetPosition(float x, float y, float z) {
    m_underlying->SetPosition(glm::vec3(x, y, z));
}

void EntityWrapper::Move(float x, float y, float z) {
    m_underlying->MoveOrigin(glm::vec3(x, y, z));
}

luabridge::LuaRef EntityWrapper::GetAnim() const {
    //Animator* r = m_underlying->GetComponent<Animator>();
    //const auto& m = r->GetAnimation();
    luabridge::LuaRef rr = luabridge::newTable(LuaWrapper::L);

    //for (auto& p : m) {
      //  rr[p.first] = p.second;
    //}

    return rr;
}

void EntityWrapper::SetAnim(const std::string& anim) {
    IAnimator* r = m_underlying->GetComponent<IAnimator>();
    r->SetAnimation(anim);
}

void EntityWrapper::SetModel(const std::string& modelId, const std::string& anim) {
    Renderer* r = m_underlying->GetComponent<Renderer>();
    IAnimator* a = m_underlying->GetComponent<IAnimator>();
    auto model = Engine::get().GetAssetManager().GetModel(modelId);
    r->SetModel(model);
    a->setModel(model);
    r->Start();
    auto collider = m_underlying->GetComponent<ICollider>();
    if (collider != nullptr) collider->Start();
//    auto mesh = Engine::get().GetAssetManager().GetModel(model);
//    r->SetModel(mesh);
//
//    r->SetAnimation(anim);
}

bool EntityWrapper::GetFlipX() const {
    return m_underlying->GetFlipX();

}

void EntityWrapper::SetFlipX(bool value) {
    m_underlying->SetFlipX(value);
}
void EntityWrapper::AppendText(luabridge::LuaRef ref) {
    TextView* r = dynamic_cast<TextView*>(m_underlying);
    r->AddItem(ref);
}

void EntityWrapper::AppendButton(luabridge::LuaRef ref) {
//    TextView* r = m_underlying->GetComponent<TextView>();
//    LuaTable table(ref);
//    std::string text = table.Get<std::string>("text");
//    auto mf = dynamic_cast<SceneFactory*>(Engine::get().GetSceneFactory());
//    auto hs = GetHotSpot(ref, nullptr);
//    r->AppendText(text, hs);
}

luabridge::LuaRef EntityWrapper::GetTextInfo() {
    Renderer* r = m_underlying->GetComponent<Renderer>();
    TextModel* tm = dynamic_cast<TextModel*>(r->GetModel());
    luabridge::LuaRef rr = luabridge::newTable(LuaWrapper::L);
    glm::vec3 f = tm->GetBounds().GetSize();
    rr["width"] = f.x;
    rr["height"] = f.y;
    return rr;
}

luabridge::LuaRef EntityWrapper::GetAttackRect() {
    ICollider* collider = m_underlying->GetComponent<ICollider>();
    luabridge::LuaRef rr = luabridge::newTable(LuaWrapper::L);
    auto bounds = collider->getAttackBounds();
    auto size = bounds.GetSize();
    rr["width"] = size.x;
    rr["height"] = size.y;
    rr["x"] = bounds.min.x;
    rr["y"] = bounds.min.y;
    //glm::vec3 f = tm->GetBounds().GetSize();
    //rr["width"] = f.x;
    //rr["height"] = f.y;
    return rr;
}


void EntityWrapper::ChangeState(const std::string& name)
{
    m_underlying->GetComponent<StateMachine>()->SetState(name);
}

void EntityWrapper::ChangeStateParam(const std::string& name, luabridge::LuaRef param)
{
    //m_underlying->GetComponent<StateMachine>()->ChangeState(name, param);
}

void EntityWrapper::ResetState() {
    //auto sm = m_underlying->GetComponent<StateMachine>();
    //sm->GetCurrentState()->Start();
}



luabridge::LuaRef EntityWrapper::GetInfo() {
    return m_underlying->GetComponent<LuaInfo>()->get();
}

void EntityWrapper::KillScript(const std::string& scriptName) {

    Engine::get().GetRunner<Scheduler>()->GetScript(scriptName)->Kill();

}

void EntityWrapper::SetFollow(bool value) {

    m_underlying->GetComponent<Follow>()->setActive(value);
}


void EntityWrapper::Call(const std::string& id, luabridge::LuaRef args) {
    LuaHook* luaHook = m_underlying->GetComponent<LuaHook>();
    luaHook->call(id, args);

}


luabridge::LuaRef EntityWrapper::getFiles(const std::string &dir, bool recursive, const std::string& pattern) {
    std::string gameDir = Engine::get().GetGameDirectory();
    size_t l = gameDir.length();
    std::string folder = gameDir + dir;
    luabridge::LuaRef rr = luabridge::newTable(LuaWrapper::L);
    int i = 1;
    std::regex reg(pattern);
    auto lambda = [&] (const boost::filesystem::path& path) {
        std::string full_path = path.string();
        if (std::regex_match(path.filename().string(), reg)) {
            rr[i++] = full_path.substr(l, full_path.length()-l-4);
        }
    };

    if (recursive) {
        for (boost::filesystem::recursive_directory_iterator itr(folder); itr != boost::filesystem::recursive_directory_iterator(); ++itr) {
            lambda (itr->path());
        }
    } else {
        for (boost::filesystem::directory_iterator itr(folder); itr != boost::filesystem::directory_iterator(); ++itr) {
            lambda (itr->path());
        }
    }

    return rr;

}