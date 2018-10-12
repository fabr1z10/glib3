#include <gfx/entitywrapper.h>
#include <gfx/components/renderer.h>
#include <gfx/textmesh.h>
#include <gfx/components/statemachine.h>
#include <glm/gtx/transform.hpp>
#include <gfx/engine.h>
#include <gfx/components/textview.h>
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

EntityWrapper EntityWrapper::RemoveEntity(const std::string& tag) {
    auto entity = Engine::get().GetRef<Entity>(tag);
    Engine::get().Remove(entity);
}

void EntityWrapper::Clear() {
    m_underlying->ClearAllChildren();
}

void EntityWrapper::ClearText() {
    TextView* r = m_underlying->GetComponent<TextView>();
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
        auto a = LuaTable::getIntValueMap(actions);
        auto factory = Engine::get().GetSceneFactory();
        for (auto& p : a) {
            auto activity= factory->Get<Activity>(p.second);
            script->AddActivity(p.first, std::move(activity));
        }

        for (auto& p : a) {
            luabridge::LuaRef after = p.second["after"];
            if (!after.isNil()) {
                int tail = p.first;
                for (int i = 0; i < after.length(); ++i) {
                    int b = after[i+1].cast<int>();
                    //int af = b < 0 ? p.first - b : b;
                    script->AddEdge(b, tail);
                }
            }
        }
//        luabridge::LuaRef edges = ref["edges"];
//        auto e = LuaTable::getIntValueMap(edges);
//        for (auto& p : e) {
//            int tail = p.first;
//            for (int i = 0; i< p.second.length(); ++i) {
//                int head = p.second[i+1].cast<int>();
//                script->AddEdge(tail, head);
//            }
//        }
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

std::string EntityWrapper::GetAnim() const {
    Renderer* r = m_underlying->GetComponent<Renderer>();
    return r->GetAnimation();
}

bool EntityWrapper::GetFlipX() const {
    Renderer* r = m_underlying->GetComponent<Renderer>();
    return r->GetFlipX();

}

void EntityWrapper::AppendText(const std::string& text) {
    TextView* r = m_underlying->GetComponent<TextView>();
    //auto hs = std::make_shared<ScriptHotSpot>(1);
    r->AppendText(text);
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
