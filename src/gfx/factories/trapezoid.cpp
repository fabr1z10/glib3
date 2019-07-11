#include <gfx/factories/prim3d.h>
#include <gfx/model/combomodel.h>

// create a box -- for platformers
//
std::shared_ptr<IModel> ModelTrapezoid3D::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);

    float depth = table.Get<float>("depth");
    std::vector<float> points = table.GetVector<float>("points");
    // get the top texture info. We need the texture, and the period (x, z)
    // i.e. the length of the texture in the x and z directions
    luabridge::LuaRef texInfo = table.Get<luabridge::LuaRef>("texture");
    luabridge::LuaRef texTop = texInfo["top"];
    LuaTable t1(texTop);
    std::string texTopName = t1.Get<std::string>("name");
    glm::vec2 texTopPeriod = t1.Get<glm::vec2>("rep");

    luabridge::LuaRef texSide = texInfo["side"];

//    luabridge::LuaRef texSide = texInfo["side"];
//    LuaTable t2(texSide);
//    std::string texSideName = t2.Get<std::string>("name");
//    glm::vec2 texSidePeriod = t2.Get<glm::vec2>("rep");

    // ok, we need a combo model
    auto model = std::make_shared<ComboModel>();

    // create the 1st mesh for top and bottom
    model->AddMesh( CreateTopMesh(points, depth, texTopName, texTopPeriod.x, texTopPeriod.y));

    if (!texSide.isNil()) {
        // need to create side mesh too
        bool parallel = false;
        float h  = 0.0f;
        if (table.HasKey("y")) {
            h = table.Get<float>("y");

        } else {
            parallel = true;
            h = table.Get<float>("thickness");
        }
        LuaTable t2(texSide);
        std::string texSideName = t2.Get<std::string>("name");
        glm::vec2 texSidePeriod = t2.Get<glm::vec2>("rep");

        model->AddMesh( CreateSideMesh(points, depth, h, texSideName, texSidePeriod.x, texSidePeriod.y, parallel));

    }

    return model;



}

std::shared_ptr<IMesh> ModelTrapezoid3D::CreateTopMesh (const std::vector<float>& points, float d, const std::string& tex, float rx, float rz) {
    auto topMesh = std::make_shared<TexturedMesh<Vertex3DN>>(TEXTURE_SHADER_LIGHT, GL_TRIANGLES, tex);
    std::vector<Vertex3DN> vertices;
    std::vector<unsigned> indices;
    unsigned c = 0;
    for (size_t i = 0; i < points.size()-2; i+=2) {
        glm::vec3 P0(points[i], points[i + 1], d);
        glm::vec3 P1(points[i + 2], points[i + 3], d);
        glm::vec3 P2(points[i], points[i + 1], 0);
        glm::vec3 n = glm::normalize(glm::cross(P1 - P0, P2 - P1));

        vertices.emplace_back(Vertex3DN{points[i], points[i + 1], d, points[i] / rx, d / rz, n.x, n.y, n.z});
        vertices.emplace_back(Vertex3DN{points[i + 2], points[i + 3], d, points[i + 2] / rx, d / rz, n.x, n.y, n.z});
        vertices.emplace_back(Vertex3DN{points[i + 2], points[i + 3], 0, points[i + 2] / rx, 0.0f, n.x, n.y, n.z});
        vertices.emplace_back(Vertex3DN{points[i], points[i + 1], 0, points[i] / rx, 0.0f, n.x, n.y, n.z});
        indices.emplace_back(c);
        indices.emplace_back(c+1);
        indices.emplace_back(c+3);
        indices.emplace_back(c+1);
        indices.emplace_back(c+2);
        indices.emplace_back(c+3);
        c+=4;
    }
    topMesh->Init(vertices, indices);
    return topMesh;
}


std::shared_ptr<IMesh> ModelTrapezoid3D::CreateSideMesh(const std::vector<float> &points, float d, float h,
                                                        const std::string & tex, float rx, float ry, bool par)
{
    auto sideMesh = std::make_shared<TexturedMesh<Vertex3DN>>(TEXTURE_SHADER_LIGHT, GL_TRIANGLES, tex);
    std::vector<Vertex3DN> vertices;
    std::vector<unsigned> indices;
    unsigned c = 0;
    // front
    for (size_t i = 0; i < points.size()-2; i+=2) {
        glm::vec3 P0(points[i], points[i + 1], d);
        glm::vec3 P1(points[i + 2], points[i + 3], d);
        float y0 = (par ? points[i+1]-h : h);
        float y1 = (par ? points[i+3]-h : h);
        vertices.emplace_back(Vertex3DN{P0.x, P0.y, d, P0.x / rx, P0.y / ry, 0, 0, 1});
        vertices.emplace_back(Vertex3DN{P0.x, y0, d, P0.x/rx, y0/ry, 0, 0, 1});
        vertices.emplace_back(Vertex3DN{P1.x, y1, d, P1.x/rx, y1/ry, 0, 0, 1});
        vertices.emplace_back(Vertex3DN{P1.x, P1.y, d, P1.x/rx, P1.y/ry, 0, 0, 1});
        indices.emplace_back(c);
        indices.emplace_back(c+1);
        indices.emplace_back(c+2);
        indices.emplace_back(c+2);
        indices.emplace_back(c+3);
        indices.emplace_back(c);
        c+=4;
    }
    sideMesh->Init(vertices, indices);
    return sideMesh;


}