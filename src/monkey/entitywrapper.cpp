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
#include <monkey/callfunc.h>
#include <monkey/monkeyfactory.h>

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
    return EntityWrapper(Engine::get().GetRef<Entity>(id));
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


void EntityWrapper::SetText(const std::string& text) {
    Renderer* r = m_underlying->GetComponent<Renderer>();
    auto tm = dynamic_cast<TextMesh*>(r->GetMesh());
    tm->UpdateText(text);
    glm::vec2 offset = tm->getOffset();
    r->SetRenderingTransform(glm::translate(glm::vec3(offset, 0.0f)));
}

namespace luaFunctions {
    
    void PlayScript (luabridge::LuaRef ref) {
        auto scheduler = Engine::get().GetRef<Scheduler>("_scheduler");
        int startId = ref["startid"].cast<int>();
        std::string scriptId = ref["id"].cast<std::string>();
        auto script = std::make_shared<Script>(startId);
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
                std::string walkareaId = table.Get<std::string>("walkarea");
                // at this point branch on the type of action
                auto walkarea = Engine::get().GetRef<WalkArea>(walkareaId);
                glm::vec2 pos = table.Get<glm::vec2>("pos");
                script->AddActivity(std::unique_ptr<Walk>(new Walk(id, actor, pos, walkarea->GetShape())));
            } else if (type == "gotoroom") {
                std::string roomId = table.Get<std::string>("room");
                script->AddActivity(std::unique_ptr<ChangeRoom>(new ChangeRoom(id, roomId)));
            } else if (type == "showmessage") {
                std::string actor = table.Get<std::string>("actor");
                std::string msg = table.Get<std::string>("message");
                std::string font = table.Get<std::string>("font");
                TextAlignment align = table.Get<TextAlignment>("align", BOTTOM);
                glm::vec4 color = table.Get<glm::vec4>("color");
                glm::vec4 outlineColor = table.Get<glm::vec4>("outlinecolor");
                color/=255.0f;
                outlineColor /= 255.0f;
                float size = table.Get<float>("size");
                script->AddActivity(std::unique_ptr<ShowMessage>(new ShowMessage(id, msg, font, actor, size, color, outlineColor, align,0.0f)));
            } else if (type == "say") {
                std::string actor = table.Get<std::string>("actor");
                std::vector<std::string> msg = table.GetVector<std::string>("message");
                glm::vec4 color = table.Get<glm::vec4>("color");
                color/=255.0f;
                script->AddActivity(std::unique_ptr<Say>(new Say(id, actor, msg, color)));
            } else if (type == "turn") {
                std::string actor = table.Get<std::string>("actor");
                std::string dir = table.Get<std::string>("face");
                std::string anim;
                bool flip {false};
                if (dir == "east") {
                    anim = "idle_right";
                } else if (dir == "west") {
                    anim = "idle_right";
                    flip = true;
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
                script->AddActivity(std::unique_ptr<Animate>(new Animate(id, actor, anim)));
            } else if (type == "delay") {
                float sec = table.Get<float>("sec");
                script->AddActivity(std::unique_ptr<DelayTime>(new DelayTime(id, sec)));
            } else if (type == "callfunc") {
                luabridge::LuaRef ref = table.Get<luabridge::LuaRef>("func");
                script->AddActivity(std::unique_ptr<CallFunc>(new CallFunc(id, ref)));
            }
        }
        luabridge::LuaRef edges = ref["edges"];
        for (int i= 0; i < edges.length(); ++i) {
            luabridge::LuaRef edge = edges[i+1];
            int edgeFrom = edge[1].cast<int>();
            int edgeTo = edge[2].cast<int>();
            script->AddEdge(edgeFrom, edgeTo);
        }
        scheduler->AddScript(scriptId, script);
    }
    
}

void EntityWrapper::SetActive (bool value) {
    m_underlying->SetActive(value);
}

void EntityWrapper::EnableGroup(int id) {
    auto hs = Engine::get().GetRef<HotSpotManager>("_hotspotmanager");
    hs->EnableGroup(id);
}

void EntityWrapper::DisableGroup(int id) {
    auto hs = Engine::get().GetRef<HotSpotManager>("_hotspotmanager");
    hs->DisableGroup(id);

}

void EntityWrapper::SetPosition(float x, float y, float z) {
    m_underlying->SetPosition(glm::vec3(x, y, z));
}