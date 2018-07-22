#include <monkey/entitywrapper.h>
#include <gfx/renderer.h>
#include <gfx/textmesh.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <gfx/engine.h>
#include <gfx/scheduler.h>
#include <gfx/animate.h>
#include <monkey/luatable.h>
#include <monkey/walk.h>
#include <monkey/walkarea.h>
#include <monkey/changeroom.h>
#include <monkey/showmessage.h>
#include <monkey/say.h>
#include <gfx/delay.h>
#include <gfx/scriptactions.h>
#include <monkey/callfunc.h>
#include <monkey/monkeyfactory.h>
#include <monkey/enableblock.h>
#include <monkey/scripthotspot.h>
#include <gfx/textview.h>

float EntityWrapper::GetX() const {
    return m_underlying->GetPosition().x;
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

    auto mf = dynamic_cast<MonkeyFactory *>(Engine::get().GetSceneFactory());
    auto ptr = mf->ReadItem(ref);
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



void EntityWrapper::SetText(const std::string& text) {
    Renderer* r = m_underlying->GetComponent<Renderer>();
    auto tm = dynamic_cast<TextMesh*>(r->GetMesh());
    tm->UpdateText(text);
    glm::vec2 offset = tm->getOffset();
    r->SetRenderingTransform(glm::translate(glm::vec3(offset, 0.0f)));
}



namespace luaFunctions {

    void EnableScriptEngine (bool value) {
        auto schedule = Engine::get().GetScriptingEngine();
        schedule->SetActive(value);
    }

    void EndRoom() {
        Engine::get().EndScene();
    }

    void EnableUpdate(bool value) {
        Engine::get().SetEnableUpdate(value);
    }

    void EnableMouse(bool value) {
        Engine::get().GetMouseHandler()->Enable(value);
    }

    void EnableKeyboard(bool value) {
        Engine::get().GetKeyboardListener()->Enable(value);
    }

    void EnableKey(int key, bool value) {
        Engine::get().GetKeyboardListener()->EnableKey(key, value);
    }

    void PlayScript (luabridge::LuaRef ref) {
        auto scheduler = Engine::get().GetScriptingEngine();
        LuaTable table(ref);
        int startId = table.Get<int>("startid");
        int loopId = table.Get<int>("loop");
        std::string scriptId = table.Get<std::string>("id", "");
        auto script = std::make_shared<Script>(startId);
        script->SetLoop(loopId);
        luabridge::LuaRef actions = ref["actions"];
        for (int i= 0; i < actions.length(); ++i) {
            luabridge::LuaRef action = actions[i+1];
            LuaTable table(action);
            // get the unique id
            int id = table.Get<int>("id");
            // see what action is performing
            std::string type = table.Get<std::string>("type");
            if (type == "walkto") {
                // see who is performing the action
                std::string actor = table.Get<std::string>("actor");
                // see who is performing the action
                //std::string walkareaId = table.Get<std::string>("walkarea");
                // at this point branch on the type of action
                //auto walkarea = Engine::get().GetRef<WalkArea>(walkareaId);
                glm::vec2 pos = table.Get<glm::vec2>("pos");
                script->AddActivity(std::unique_ptr<Walk>(new Walk(id, actor, pos)));
            } else if (type == "gotoroom") {
                std::string roomId = table.Get<std::string>("room");
                script->AddActivity(std::unique_ptr<ChangeRoom>(new ChangeRoom(id, roomId)));
            } else if (type == "showmessage") {
                std::string actor = table.Get<std::string>("actor", "");
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
                if (!actor.empty()) {
                    script->AddActivity(std::unique_ptr<ShowMessage>(
                            new ShowMessage(id, msg, font, actor, size, color, outlineColor, align, time, offset)));
                } else {
                    glm::vec3 pos = table.Get<glm::vec3>("pos");
                    script->AddActivity(std::unique_ptr<ShowMessage>(
                            new ShowMessage(id, msg, font, pos, size, color, outlineColor, align, time, offset)));
                }
            } else if (type == "say") {
                std::string actor = table.Get<std::string>("actor");
                std::vector<std::string> msg = table.GetVector<std::string>("message");
                glm::vec4 color = table.Get<glm::vec4>("color");
                glm::vec2 offset = table.Get<glm::vec2>("offset", glm::vec2(0.0f));
                color/=255.0f;
                auto say = std::unique_ptr<Say>(new Say(id, actor, msg, color, offset));
                std::string animStart = table.Get<std::string>("animstart", "");
                std::string animEnd = table.Get<std::string>("animend","");
                bool noAnim = table.Get<bool>("noanim", false);
                say->SetAnimationEnd(animEnd);
                say->SetAnimationStart(animStart);
                say->SetNoAnim(noAnim);
                script->AddActivity(std::move(say));
            } else if (type == "turn") {
                std::string actor = table.Get<std::string>("actor");
                std::string dir = table.Get<std::string>("face");
                std::string anim;
                int flip =1;
                if (dir == "east") {
                    anim = "idle_right";
                } else if (dir == "west") {
                    anim = "idle_right";
                    flip = 2;
                } else if (dir == "north") {
                    anim = "idle_back";
                } else if (dir == "south") {
                    anim = "idle_front";
                } else {
                    GLIB_FAIL("Unknown direction " << dir)
                }
                script->AddActivity(std::unique_ptr<Animate>(new Animate(id, actor, anim, flip)));
            } else if (type == "animate") {
                std::string actor = table.Get<std::string>("actor");
                std::string anim = table.Get<std::string>("anim");
                int flip{0};
                if (table.HasKey("flipx")) {
                    flip = table.Get<bool>("flipx") ? 2 : 1;
                }
                int loopCount = table.Get<int>("loop", 0);
                auto act = std::unique_ptr<Animate>(new Animate(id, actor, anim, flip));
                act->SetLoop(loopCount);
                script->AddActivity(std::move(act));
            } else if (type == "delay") {
                float sec = table.Get<float>("sec");
                script->AddActivity(std::unique_ptr<DelayTime>(new DelayTime(id, sec)));
            } else if (type == "callfunc") {
                luabridge::LuaRef ref = table.Get<luabridge::LuaRef>("func");
                script->AddActivity(std::unique_ptr<CallFunc>(new CallFunc(id, ref)));
            } else if (type == "suspendscript") {
                std::string s = table.Get<std::string>("script");
                script->AddActivity(std::unique_ptr<SuspendScript>(new SuspendScript(id, s)));
            } else if (type == "resumescript") {
                std::string s = table.Get<std::string>("script");
                script->AddActivity(std::unique_ptr<ResumeScript>(new ResumeScript(id, s)));
            } else if (type == "activatewall") {
                int wallId = table.Get<int>("wall");
                bool active = table.Get<bool>("active");
                script->AddActivity(std::unique_ptr<EnableBlock>(new EnableBlock(id, wallId, active)));
            }
        }
        luabridge::LuaRef edges = ref["edges"];
        for (int i= 0; i < edges.length(); ++i) {
            luabridge::LuaRef edge = edges[i+1];
            int edgeFrom = edge[1].cast<int>();
            int edgeTo = edge[2].cast<int>();
            script->AddEdge(edgeFrom, edgeTo);
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
    TextView* r = m_underlying->GetComponent<TextView>();
    LuaTable table(ref);
    std::string text = table.Get<std::string>("text");
    auto mf = dynamic_cast<MonkeyFactory*>(Engine::get().GetSceneFactory());
    auto hs = mf->GetHotSpot(ref, nullptr);
    r->AppendText(text, hs);
}

