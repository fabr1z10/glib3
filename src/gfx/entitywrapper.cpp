#include <gfx/entitywrapper.h>
#include <gfx/components/renderer.h>
#include <gfx/textmesh.h>
#include <gfx/components/statemachine.h>
#include <glm/gtx/transform.hpp>
#include <gfx/engine.h>
#include <gfx/entities/textview.h>
#include <gfx/activities/animate.h>
#include <gfx/factories.h>
#include <gfx/components/info.h>
#include <gfx/components/depth.h>
#include <gfx/components/dynamics2d.h>

float EntityWrapper::GetX() const {
    return m_underlying->GetPosition().x;
}
float EntityWrapper::GetY() const {
    return m_underlying->GetPosition().y;
}
float EntityWrapper::GetZ() const {
    return m_underlying->GetPosition().z;
}

float EntityWrapper::GetVy() const {
    return m_underlying->GetComponent<Dynamics2D>()->m_velocity.y;
}

void EntityWrapper::SetVy(float value) {
    m_underlying->GetComponent<Dynamics2D>()->m_velocity.y = value;
}
std::string EntityWrapper::GetTag() const {
    return m_underlying->GetTag();
}
std::string EntityWrapper::GetState() const {
    auto sm = m_underlying->GetComponent<StateMachine>();
    return sm->GetCurrentState()->GetId();
}

std::string EntityWrapper::GetText() const {
    Renderer* r = m_underlying->GetComponent<Renderer>();
    auto tm = dynamic_cast<TextMesh*>(r->GetMesh());
    return tm->GetText();
}

int EntityWrapper::GetLines() const {
    Renderer* r = m_underlying->GetComponent<Renderer>();
    auto tm = dynamic_cast<TextMesh*>(r->GetMesh());
    return tm->getNumberOfLines();
}


EntityWrapper EntityWrapper::GetParent() {
    return EntityWrapper(m_underlying->GetParent());
}

void EntityWrapper::SetColor(int r, int g, int b, int a) {
    m_underlying->GetComponent<Renderer>()->SetTint(glm::vec4(r/255.0f, g/255.0f, b/255.0f, a/255.0f));
}


EntityWrapper EntityWrapper::GetEntity(const std::string& id) {
    try {
        auto ref = Engine::get().GetRef<Entity>(id);
        return EntityWrapper(ref);
    } catch (Error& err) {
        return EntityWrapper();
    }
}

EntityWrapper EntityWrapper::AddEntity(luabridge::LuaRef ref, EntityWrapper* parent) {

    auto mf = Engine::get().GetSceneFactory();
    auto ptr = mf->GetShared<Entity>(ref);
    parent->m_underlying->AddChild(ptr);

    EntityWrapper ew(ptr.get());
    return ew;


}

void EntityWrapper::RemoveEntity(const std::string& tag) {
    auto entity = Engine::get().GetRef<Entity>(tag);
    Engine::get().Remove(entity);
}

void EntityWrapper::Clear() {
    m_underlying->ClearAllChildren();
}

void EntityWrapper::ClearText() {
    TextView* r = dynamic_cast<TextView*>(m_underlying);
    r->ClearText();
}

void EntityWrapper::Remove() {
    Engine::get().Remove(m_underlying);
}

void EntityWrapper::EnableDepth(bool value) {
    m_underlying->GetComponent<DepthCalculator>()->SetActive(value);
}

void EntityWrapper::SetText(const std::string& text) {
    Renderer* r = m_underlying->GetComponent<Renderer>();
    auto tm = dynamic_cast<TextMesh*>(r->GetMesh());
    tm->UpdateText(text);
    glm::vec2 offset = tm->getOffset();
    r->SetRenderingTransform(glm::translate(glm::vec3(offset, 0.0f)));
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
        if (loopId != -1) {
            script->SetLoop(loopId);
        }
        luabridge::LuaRef actions = ref["actions"];

        std::vector<std::pair<int, int>> edges;
        auto factory = Engine::get().GetSceneFactory();
        for (int i = 0; i < actions.length(); ++i) {
            luabridge::LuaRef action = actions[i+1];
            if (action["id"].isNil())
                GLIB_FAIL("When reading a script, found action with no required <id> field!");
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
            auto activity= factory->Get<Activity>(action);
            script->AddActivity(id, std::move(activity));
        }

        for (auto& i : edges) {
            script->AddEdge(i.first, i.second);
        }

        if (scriptId.empty())
            scheduler->AddScript(script);
        else
            scheduler->AddScript(scriptId, script);
    }
    
}

void EntityWrapper::SetActive (bool value) {
    m_underlying->SetActive(value);
}

void EntityWrapper::SetEnableControls (bool value) {
    m_underlying->SetControlsEnabled(value);
}

void EntityWrapper::EnableCollisions(bool value) {
    auto collider = m_underlying->GetComponent<Collider>();
    if (collider != nullptr)
        collider->SetActive(value);
    auto& children = m_underlying->GetChildren();
    for (auto& child : children) {
        EntityWrapper e(child.get());
        e.EnableCollisions(value);
    }
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

std::string EntityWrapper::GetAnim() const {
    Renderer* r = m_underlying->GetComponent<Renderer>();
    return r->GetAnimation();
}

void EntityWrapper::SetAnim(const std::string& anim) {
    Renderer* r = m_underlying->GetComponent<Renderer>();
    r->SetAnimation(anim);
}


bool EntityWrapper::GetFlipX() const {
    return m_underlying->GetFlipX();

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
    TextMesh* tm = dynamic_cast<TextMesh*>(r->GetMesh());
    luabridge::LuaRef rr = luabridge::newTable(LuaWrapper::L);
    glm::vec2 f = tm->getBounds().GetSize();
    rr["width"] = f.x;
    rr["height"] = f.y;
    return rr;
}


void EntityWrapper::ChangeState(const std::string& name)
{
    m_underlying->GetComponent<StateMachine>()->ChangeState(name);
}

void EntityWrapper::ChangeStateParam(const std::string& name, luabridge::LuaRef param)
{
    m_underlying->GetComponent<StateMachine>()->ChangeState(name, param);
}

void EntityWrapper::ResetState() {
    auto sm = m_underlying->GetComponent<StateMachine>();
    sm->GetCurrentState()->Start();
}

void EntityWrapper::EnableStateMachine(bool value) {
    auto sm = m_underlying->GetComponent<StateMachine>();
    sm->SetActive(value);
}

luabridge::LuaRef EntityWrapper::GetInfo() {
    return m_underlying->GetComponent<LuaInfo>()->get();
}

void EntityWrapper::KillScript(const std::string& scriptName) {

    Engine::get().GetRunner<Scheduler>()->GetScript(scriptName)->Kill();

}