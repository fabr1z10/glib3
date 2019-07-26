#include <platformer/factories/building.h>
#include <gfx/model/combomodel.h>
#include <gfx/math/geom.h>
#include <glm/gtx/vector_angle.hpp>
// create a box -- for platformers
//
std::shared_ptr<IModel> BuildingFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);

    float width = table.Get<float>("width");
    float depth = table.Get<float>("depth");
    float height = table.Get<float>("height");
    std::string wallTex = table.Get<std::string>("wall");
    glm::vec2 wallInc = table.Get<glm::vec2>("wall_inc");

    auto model = std::make_shared<ComboModel>();

    // create the 1st mesh for top and bottom


    auto topMesh = std::make_shared<TexturedMesh<Vertex3DN>>(TEXTURE_SHADER_LIGHT, GL_TRIANGLES, wallTex);
    std::vector<Vertex3DN> vertices;
    std::vector<unsigned> indices;
    // front face
    vertices.emplace_back(Vertex3DN{0.0f, 0.0f, 0.0f, 0.0f, height/wallInc.y, 0.0f, 0.0f, 1.0f});
    vertices.emplace_back(Vertex3DN{width, 0.0f, 0.0f,  width/wallInc.x, height/wallInc.y, 0.0f, 0.0f, 1.0f});
    vertices.emplace_back(Vertex3DN{width, height, 0.0f, width/wallInc.x, 0.0f, 0.0f, 0.0f, 1.0f});
    vertices.emplace_back(Vertex3DN{0.0f, height, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f});
    indices.emplace_back(0);
    indices.emplace_back(1);
    indices.emplace_back(2);
    indices.emplace_back(2);
    indices.emplace_back(3);
    indices.emplace_back(0);
    // right face
    vertices.emplace_back(Vertex3DN{width, 0.0f, 0.0f, 0.0f, height/wallInc.y, 1.0f, 0.0f, 0.0f});
    vertices.emplace_back(Vertex3DN{width, 0.0f, -depth,  width/wallInc.x, height/wallInc.y, 1.0f, 0.0f, 0.0f});
    vertices.emplace_back(Vertex3DN{width, height, -depth, width/wallInc.x, 0.0f, 1.0f, 0.0f, 0.0f});
    vertices.emplace_back(Vertex3DN{width, height, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f});
    indices.emplace_back(4);
    indices.emplace_back(5);
    indices.emplace_back(6);
    indices.emplace_back(6);
    indices.emplace_back(7);
    indices.emplace_back(4);
    topMesh->Init(vertices, indices);
    model->AddMesh(topMesh);
    return model;
}