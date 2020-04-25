#include <monkey/components/basicrenderer.h>
#include <monkey/meshfactory.h>
#include <monkey/lua/luatable.h>
#include <monkey/quadmesh.h>
#include <monkey/math/geom.h>

BasicRenderer::BasicRenderer(std::shared_ptr<IModel> model) : Renderer() {
    m_model = std::dynamic_pointer_cast<BasicModel>(model);
    m_baseModel = model.get();
}

BasicRenderer::BasicRenderer(const ITable & t) : Renderer() {
    int cls = t.get<int>("cls");
    if (cls == 0) {
        auto image = t.get<std::string>("image");
        auto w = t.get<float>("width", 0.0f);
        auto h = t.get<float>("height", 0.0f);
        glm::vec2 offset = t.get<glm::vec2>("offset", glm::vec2(0.0f));
        std::shared_ptr<IMesh> mesh;
        if (t.hasKey("quad")) {
            glm::ivec4 quad = t.get<glm::ivec4>("quad");
            mesh = std::make_shared<QuadMesh>(image, w, h, offset, quad[0], quad[1], quad[2], quad[3]);
        } else {
            glm::vec2 repeat = t.get<glm::vec2>("rep", glm::vec2(1.0f, 1.0f));
            glm::vec2 skew = t.get<glm::vec2>("skew", glm::vec2(0.0f, 0.0f));
            mesh = std::make_shared<QuadMesh>(image, w, h, repeat.x, repeat.y, skew.x, skew.y, offset);
        }
        SetModel(std::make_shared<BasicModel>(mesh));
        //m_model = std::make_shared<BasicModel>(mesh);

    } else if (cls == 1) {
        auto image = t.get<std::string>("image");
        auto size = t.get<float>("size", 1.0f);
        int width = t.get<int>("width");
        int height = t.get<int>("height");
        int repx = t.get<int>("repx", 1);
        int repy = t.get<int>("repy", 1);
        float angle = deg2rad * t.get<float>("angle", 0.0f);
        glm::vec2 delta = t.get<glm::vec2>("delta", glm::vec2(0.0f, 0.0f));
        glm::ivec2 sheetSize = t.get<glm::ivec2>("sheetSize");
        std::vector<int> data = t.get<std::vector<int>>("tileData");
        auto mesh = std::make_shared<QuadMesh>(image, height, width, size, data, sheetSize.y, sheetSize.x, repx, repy, delta, angle);
        //m_model = std::make_shared<BasicModel>(mesh)//;
        SetModel( std::make_shared<BasicModel>(mesh));
    } else if (cls == 2) {
        // shape renderer
        auto factory = Engine::get().GetSceneFactory();
        auto shapeT = t.get<PyTable>("shape");
        auto shape = factory->make2<Shape>(shapeT);
        auto tex = t.get<std::string>("tex");
        float x0 = t.get<float>("x0", 0.0f);
        float y0 = t.get<float>("y0", 0.0f);
        float repx = t.get<float>("repx");
        float repy = t.get<float>("repy");
        float slantx = t.get<float>("slantx", 0.0f);
        float slanty = t.get<float>("slanty", 0.0f);
        std::shared_ptr<Fill> fill;
        if (t.hasKey("fill")) {
            auto fillT = t.get<PyTable>("fill");
            fill = factory->make2<Fill>(fillT);
        } else {
            fill = std::make_shared<SolidFill>(glm::vec4(255.0f));
        }
        auto mesh = MeshFactoryTextured::CreateMesh(*(shape.get()), tex, x0, y0, repx, repy, slantx, slanty, fill);
        SetModel (std::make_shared<BasicModel>(mesh));
    } else if (cls ==3) {
        auto factory = Engine::get().GetSceneFactory();
        auto shapeT = t.get<PyTable>("shape");
        auto shape = factory->make2<Shape>(shapeT);
        auto fillT = t.get<PyTable>("fill");
        auto fill = factory->make2<Fill>(fillT);
        float z = t.get<float>("z", 0.0f);
        auto mesh = MeshFactorySolid::CreateMesh(*(shape.get()), fill, z);
        SetModel (std::make_shared<BasicModel>(mesh));

    }
}


BasicRenderer::BasicRenderer(const LuaTable & t) : Renderer() {

//    if (t.HasKey("image")) {
//        auto image = t.Get<std::string>("image");
//        auto w = t.Get<float>("width", 0.0f);
//        auto h = t.Get<float>("height", 0.0f);
//        glm::vec2 offset = t.Get<glm::vec2>("offset", glm::vec2(0.0f));
//        std::shared_ptr<IMesh> mesh;
//        if (t.HasKey("quad")) {
//            glm::ivec4 quad = t.Get<glm::ivec4>("quad");
//            mesh = std::make_shared<QuadMesh>(image, w, h, offset, quad[0], quad[1], quad[2], quad[3]);
//        } else {
//            glm::vec2 repeat = t.Get<glm::vec2>("rep", glm::vec2(1.0f, 1.0f));
//            glm::vec2 skew = t.Get<glm::vec2>("skew", glm::vec2(0.0f, 0.0f));
//            mesh = std::make_shared<QuadMesh>(image, w, h, repeat.x, repeat.y, skew.x, skew.y, offset);
//        }
//        SetModel(std::make_shared<BasicModel>(mesh));
//        //m_model = std::make_shared<BasicModel>(mesh);
//    } else if (t.HasKey("shape")) {
//        luabridge::LuaRef sref = t.Get<luabridge::LuaRef>("shape");
//        std::string draw = t.Get<std::string>("draw","outline");
//        glm::vec4 color = t.Get<glm::vec4>("color");
//        color /= 255.0f;
//        auto factory = Engine::get().GetSceneFactory();
//        auto shape = factory->make<Shape>(sref);
//        std::shared_ptr<IMesh> mesh;
//        if (draw == "outline") {
//            mesh = MeshFactory::CreateMesh(*(shape.get()), 0.0f);
//        } else if (draw == "solid") {
//            mesh = MeshFactorySolid::CreateMesh(*(shape.get()), 0.0f);
//        }
//        m_model = std::make_shared<BasicModel>(mesh);
//        setMultColor(color);
//    } else if (t.HasKey("tiledata")) {
//        std::string image = t.Get<std::string>("img");
//        float size = t.Get<float>("size", 1.0f);
//        int width = t.Get<int>("width");
//        int height = t.Get<int>("height");
//        int repx = t.Get<int>("repx", 1);
//        int repy = t.Get<int>("repy", 1);
//        glm::vec2 delta = t.Get<glm::vec2>("delta", glm::vec2(0.0f, 0.0f));
//        glm::ivec2 sheetSize = t.Get<glm::ivec2>("sheetsize");
//        std::vector<int> data = t.GetVector<int>("tiledata");
//        auto mesh = std::make_shared<QuadMesh>(image, height, width, size, data, sheetSize.x, sheetSize.y, repx, repy, delta);
//        m_model = std::make_shared<BasicModel>(mesh);
//    } else if (t.HasKey("model")) {
//        std::string modelId = t.Get<std::string>("model");
//        m_model = std::dynamic_pointer_cast<BasicModel>(Engine::get().GetAssetManager().GetModel(modelId));
//        m_baseModel = m_model.get();
//    }
//    } else if (t.HasKey("prim3d")) {
//        auto factory = Engine::get().GetSceneFactory();
//        auto model = factory->make<IModel>(table.Get<luabridge::LuaRef>("prim3d"));
//        renderer = std::make_shared<BasicRenderer>(model);
//    }
}

BasicRenderer::BasicRenderer(const BasicRenderer & orig) : Renderer(orig), m_model(orig.m_model) {}

std::shared_ptr<Component> BasicRenderer::clone() const {
    return std::make_shared<BasicRenderer>(*this);
}

void BasicRenderer::Draw(Shader* shader) {
    Renderer::Draw(shader);
    m_model->Draw(shader);

}

void BasicRenderer::SetModel(std::shared_ptr<IModel> model) {
    m_model = std::dynamic_pointer_cast<BasicModel>(model);
    m_baseModel = model.get();
}

std::type_index BasicRenderer::GetType() {
    return std::type_index(typeid(Renderer));
}
