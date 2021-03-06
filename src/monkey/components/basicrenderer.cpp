#include <monkey/components/basicrenderer.h>
#include <monkey/meshfactory.h>
#include <monkey/quadmesh.h>
#include <monkey/math/geom.h>
#include <monkey/texmeshfactory.h>

BasicRenderer::BasicRenderer(std::shared_ptr<IModel> model) : Renderer() {
    m_model = std::dynamic_pointer_cast<BasicModel>(model);
    m_baseModel = model.get();
}

BasicRenderer::BasicRenderer(const ITab & t) : Renderer(t) {
    int cls = t.get<int>("cls");
    if (cls == 0) {
        auto image = t.get<std::string>("image");
        auto w = t.get<float>("width", 0.0f);
        auto h = t.get<float>("height", 0.0f);
        glm::vec2 offset = t.get<glm::vec2>("offset", glm::vec2(0.0f));
        std::shared_ptr<IMesh> mesh;
        if (t.has("quad")) {
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
//        auto factory = Engine::get().GetSceneFactory();
//        auto shapeT = t.get<PyTable>("shape");
//        auto shape = factory->make2<IShape>(shapeT);
//        auto tex = t.get<std::string>("tex");
//        float x0 = t.get<float>("x0", 0.0f);
//        float y0 = t.get<float>("y0", 0.0f);
//        float repx = t.get<float>("repx", 1.0f);
//        float repy = t.get<float>("repy",1.0f);
//        float slantx = t.get<float>("slantx", 0.0f);
//        float slanty = t.get<float>("slanty", 0.0f);
//        std::shared_ptr<Fill> fill;
//        if (t.hasKey("fill")) {
//            auto fillT = t.get<PyTable>("fill");
//            fill = factory->make2<Fill>(fillT);
//        } else {
//            fill = std::make_shared<SolidFill>(glm::vec4(255.0f));
//        }
//        auto mesh = MeshFactoryTextured::CreateMesh(*(shape.get()), tex, x0, y0, repx, repy, slantx, slanty, fill);
      //  SetModel (std::make_shared<BasicModel>(mesh));
    } else if (cls == 3) {
        auto factory = Engine::get().GetSceneFactory();
        auto shapeT = t["shape"];
        auto color = t.get<glm::vec4>("color");
        auto shape = factory->make2<IShape>(*shapeT);
        MeshFactory mf;
        auto model = mf.createWireframe(shape.get(), color);
        SetModel(model);
        
    } else if (cls==4) {
        // create a colored shape outline texture
//        auto factory = Engine::get().GetSceneFactory();
//        auto color = t.get<glm::vec4>("color");
//        color /= 255.0f;
//        auto shapeT = t.get<PyTable>("shape");
//        auto shape = factory->make2<IShape>(shapeT);
//        auto z = t.get<float>("z", 0.0f);
//        auto mesh = MeshFactory::CreateMesh(*(shape.get()), z, color);
//        SetModel (std::make_shared<BasicModel>(mesh));
    } else if (cls == 5) {
		// textured mesh
//		auto factory = Engine::get().GetSceneFactory();
//		TexMeshFactory meshFactory;
//		t.foreach<PyDict>("texinfo", [&] (const PyDict& d) {
//			auto id = d.get<std::string>("id", "default");
//			auto tex = d.get<std::string>("tex");
//			auto repeat = d.get<glm::vec2>("repeat", glm::vec2(1.0f, 1.0f));
//			meshFactory.addTexInfo( TexInfo{id,tex,repeat});
//		});
//		auto shapeT = t.get<PyTable>("shape");
//		auto shape = factory->make2<IShape>(shapeT);
//		auto meshes = meshFactory.CreateMesh(*(shape.get()));
//		if (meshes.size() == 1) {
//			SetModel (std::make_shared<BasicModel>(meshes.front()));
//		}
		// you can provide a list of textures. Each texture has
		// id, tex, repeat (offset, skew)


    }
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
