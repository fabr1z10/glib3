#include <monkey/entitywrapper.h>
#include <gfx/renderer.h>
#include <gfx/textmesh.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <gfx/engine.h>
#include <gfx/scheduler.h>
#include <monkey/luatable.h>
#include <monkey/walk.h>
#include <monkey/walkarea.h>
#include <monkey/changeroom.h>

float EntityWrapper::GetX() const {
    return m_underlying->GetPosition().x;
}

std::string EntityWrapper::GetText() const {
    Renderer* r = m_underlying->GetComponent<Renderer>();
    auto tm = dynamic_cast<TextMesh*>(r->GetMesh());
    return tm->GetText();
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
                script->AddActivity(std::make_shared<Walk>(id, actor, pos, walkarea->GetShape()));
            } else if (type == "gotoroom") {
                std::string roomId = table.Get<std::string>("room");
                script->AddActivity(std::make_shared<ChangeRoom>(id, roomId));
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
