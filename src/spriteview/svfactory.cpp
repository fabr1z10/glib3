#include <spriteview/svfactory.h>
#include <gfx/camera.h>
#include <gfx/entity.h>
#include <gfx/components/renderer.h>
#include <gfx/math/line.h>
#include <gfx/textmesh.h>
#include <gfx/meshfactory.h>
#include <gfx/engine.h>
#include <spriteview/mousecontrol.h>
#include <gfx/lua/luatable.h>
#include <gfx/components/hotspot.h>
#include <gfx/entities/listview.h>

SpriteViewFactory::SpriteViewFactory() {


    // read assets
    luabridge::LuaRef refSprites = luabridge::getGlobal(LuaWrapper::L, "sprites");
    auto smap = LuaTable::getKeyValueMap(refSprites);
    for (auto& k : smap) {
        luabridge::LuaRef a = k.second;
        auto asset = GetShared<IMesh>(a);
        Engine::get().GetAssetManager().AddMesh(k.first, asset);

    }


}



std::shared_ptr<Entity> SpriteViewFactory::GenerateGrid(int xFrom, int xTo, int yFrom, int yTo) {

    std::vector<VertexColor> vertices;
    int nHor = yTo - yFrom + 1;
    int nVer = xTo - xFrom + 1;
    for (int x = xFrom; x <= xTo; ++x) {
        vertices.push_back({x, yFrom, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f});
        vertices.push_back({x, yTo, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f});
    }
    for (int y = yFrom; y <= yTo; ++y) {
        vertices.push_back({xFrom, y, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f});
        vertices.push_back({xTo, y, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f});
    }
    std::vector<unsigned int> indices;
    int n = 0;
    for (int i = 0; i < nHor*nVer; ++i) {
        indices.push_back(n++);
        indices.push_back(n++);
    }

    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINES;

    auto node = std::make_shared<Entity>();
    auto rend = std::make_shared<Renderer>();
    rend->SetMesh(mesh);
    node->AddComponent(rend);
    node->SetTag("grid");
    return node;

}

void SpriteViewFactory::LoadModel (const std::string& model) {
    auto m = Engine::get().GetRef<Entity>("model");
    m->ClearAllChildren();

    auto mesh = Engine::get().GetAssetManager().GetMesh(model);
    const auto& k = mesh->GetAnimInfo();
    std::string anim = k.begin()->first;
    auto node = std::make_shared<Entity>();
    auto rend = std::make_shared<Renderer>();

    rend->SetMesh(mesh);
    rend->SetAnimation(anim);
    node->AddComponent(rend);

    m->AddChild(node);
}

std::shared_ptr<Entity> SpriteViewFactory::Create() {
    Engine::get().AddRunner(std::make_shared<HotSpotManager>());
    auto node = std::make_shared<Entity>();

    float camWidth = 600;
    float camHeight = 600;

    auto panelNode = std::make_shared<Entity>();
    auto panelCam = std::make_shared<OrthographicCamera>(camWidth, camHeight, glm::vec4(200,0,600,600));
    panelCam->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    panelNode->SetCamera(panelCam);
    auto vc = std::make_shared<ViewerController>(camWidth, camHeight);
    vc->SetShape(std::make_shared<Rect>(600,600, glm::vec2(-300,-300)));
    panelNode->AddComponent(vc);



    auto mainNode = std::make_shared<Entity>();
    auto mainCam = std::make_shared<OrthographicCamera>(camWidth, camHeight, glm::vec4(200,0,600,600));
    mainCam->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    mainNode->SetCamera(mainCam);
    m_mainNode = mainNode.get();
    vc->SetTargetCam(mainCam.get());
    auto uiNode = std::make_shared<Entity>();





    auto uiCam = std::make_shared<OrthographicCamera>(800, 600);
    uiCam->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    uiNode->SetCamera(uiCam);

    // x-axis
    auto node_xAxis = std::make_shared<Entity>();
    Line l(glm::vec2(-10,0), glm::vec2(10, 0));
    auto mesh = MeshFactory::CreateMesh(l, 0.0f, glm::vec4(128.0f, 0.0f, 0.0f, 255.0f));
    auto renderer = std::make_shared<Renderer>();
    renderer->SetMesh(mesh);
    node_xAxis->AddComponent(renderer);
    mainNode->AddChild(node_xAxis);
    mainNode->AddChild(GenerateGrid(-400,400,-300,300));
    //auto p = std::make_shared<Entity>();
    //auto pr = std::make_shared<Renderer>();

    luabridge::LuaRef s = luabridge::getGlobal(LuaWrapper::L, "sprites");
    auto lt = LuaTable::getKeyValueMap(s);
    auto it = lt.begin();



    auto font = Engine::get().GetAssetManager().GetFont("main");
    // auto tm = std::make_shared<TextMesh>(font, it->first, 8.0f, TextAlignment::BOTTOM_LEFT);
    //pr->SetMesh(tm);
    //p->AddComponent(pr);

    //uiNode->AddChild(p);
    auto lv = std::make_shared<ListView>(200.0f, 300.0f, "main", 8.0f, glm::vec4(1.0f), glm::vec4(0.2f, 0.0f, 0.0f, 1.0f));
    lv->SetOnClick([&] (const std::string& c) {
        std::cout << "Selected: " << c << std::endl;
        LoadModel(c);
        auto mesh = Engine::get().GetAssetManager().GetMesh(c);
        const auto& m = mesh->GetAnimInfo();
        for (const auto& a : m) {
            std::cout << a.first << "\n";
        }

    });
    lv->SetPosition(glm::vec3(-400.0f, 0.0f, 1.0f));
    for (auto& a : lt) {
        lv->AddItem(a.second["id"].cast<std::string>());
    }

    uiNode->AddChild(lv);

    node->AddChild(panelNode);
    node->AddChild(mainNode);
    node->AddChild(uiNode);

    auto mnode = std::make_shared<Entity>();
    mnode->SetTag("model");
    mainNode->AddChild(mnode);

    //LoadModel("potostew");

    return node;
}
