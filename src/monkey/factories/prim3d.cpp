#include <monkey/factories/prim3d.h>
#include <monkey/model/combomodel.h>

// create a box -- for platformers
//
std::shared_ptr<IModel> ModelBox3D::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);

    float width = table.Get<float>("width");
    float height = table.Get<float>("height");
    float depth = table.Get<float>("depth");

    // get the top texture info. We need the texture, and the period (x, z)
    // i.e. the length of the texture in the x and z directions
    luabridge::LuaRef texInfo = table.Get<luabridge::LuaRef>("texture");
    luabridge::LuaRef texTop = texInfo["top"];
    LuaTable t1(texTop);
    std::string texTopName = t1.Get<std::string>("name");
    glm::vec2 texTopPeriod = t1.Get<glm::vec2>("rep");
    luabridge::LuaRef texSide = texInfo["side"];
    LuaTable t2(texSide);
    std::string texSideName = t2.Get<std::string>("name");
    glm::vec2 texSidePeriod = t2.Get<glm::vec2>("rep");

    // ok, we need a combo model
    auto model = std::make_shared<ComboModel>();

    // create the 1st mesh for top and bottom
    model->AddMesh( CreateTopMesh(width, height, depth, texTopName, texTopPeriod.x, texTopPeriod.y));
    model->AddMesh( CreateSideMesh(width, height, depth, texSideName, texSidePeriod.x, texSidePeriod.y));
    return model;



}

std::shared_ptr<IMesh> ModelBox3D::CreateTopMesh(float width, float height, float depth, const std::string& tex, float rx, float rz) {
    auto topMesh = std::make_shared<TexturedMesh<Vertex3DN>>(TEXTURE_SHADER_LIGHT, GL_TRIANGLES, tex);
    std::vector<Vertex3DN> vertices = {
        // top
        { 0, height, depth, 0, depth/rz, 0, 1, 0 },
        { 0, height, 0, 0, 0, 0, 1, 0},
        { width, height, depth, width / rx, depth/rz, 0, 1, 0},
        { width, height, 0, width/rx, 0, 0, 1, 0},
        // bottom
        { 0, 0, depth, 0, depth/rz, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0},
        { width, 0, depth, width /rx, depth/rz, 0, 1, 0},
        { width, 0, 0, width/rx, 0, 0, 1, 0},
    };
    std::vector<unsigned> indices = { 0, 2, 1, 1, 2, 3, 4, 5, 6, 6, 5, 7 };
    topMesh->Init(vertices, indices);
    return topMesh;
}

std::shared_ptr<IMesh> ModelBox3D::CreateSideMesh(float w, float h, float d, const std::string & tex, float rx, float ry) {

    auto topMesh = std::make_shared<TexturedMesh<Vertex3DN>>(TEXTURE_SHADER_LIGHT, GL_TRIANGLES, tex);
    std::vector<Vertex3DN> vertices = {
            // front
            { 0, h, d, 0, 0, 0, 0, 1 },
            { 0, 0, d, 0, h/ry, 0, 0, 1},
            { w, 0, d, w/rx, h/ry, 0, 0, 1},
            { w, h, d, w/rx, 0, 0, 0, 1},
            // right
            { w, h, d, 0, 0, 1, 0, 0},
            { w, 0, d, 0, h/ry, 1, 0, 0},
            { w, 0, 0, d/rx, h/ry, 1, 0, 0},
            { w, h, 0, d/rx, 0, 1, 0, 0},
            // back
            { w, h, 0, 0, 0, 0, 0, -1},
            { w, 0, 0, 0, h/ry, 0, 0, -1},
            { 0, 0, 0, w/rx, h/ry, 0, 0, -1},
            { 0, h, 0, w/rx, 0, 0, 0, -1},
            // left
            { 0, h, 0, 0, 0, -1, 0, 0},
            { 0, 0, 0, 0, h/ry, -1, 0, 0},
            { 0, 0, d, d/rx, h/ry, -1, 0, 0},
            { 0, h, d, d/rx, 0, -1, 0, 0}
    };
    std::vector<unsigned> indices = {
            0,1,2,2,3,0,
            4,5,6,6,7,4,
            8,9,10,10,11,8,
            12,13,14,14,15,12
    };
    topMesh->Init(vertices, indices);
    return topMesh;
}