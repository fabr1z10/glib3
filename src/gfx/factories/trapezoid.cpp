#include <gfx/factories/prim3d.h>
#include <gfx/model/combomodel.h>
#include <gfx/math/geom.h>
#include <glm/gtx/vector_angle.hpp>
// create a box -- for platformers
//
std::shared_ptr<IModel> ModelTrapezoid3D::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    m_topPoints.clear();
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
    // the path will lie on xz plane, y is the elevation
    glm::vec3 nOld;

    std::vector <glm::vec3> pts;

    // store points
    for (size_t i = 0; i < points.size(); i += 3) {
        pts.push_back(glm::vec3(points[i], points[i+1], points[i+2]));
    }



    std::vector <glm::vec3> tangents;
    std::vector <float> length;
    float cumulatedLength = 0.0f;
    length.push_back(0.0f);
    for (size_t i = 0; i < pts.size()-1; ++i) {
        glm::vec3 displacement = pts[i+1]-pts[i];
        float l = glm::length(displacement);
        length[i+1] = length[i] + l;
        tangents.push_back(glm::normalize(displacement));
    }
    std::vector <glm::vec3> normals_xz(pts.size());

    // first point
    glm::vec3 a = pts[1] - pts[0];
    normals_xz[0] = glm::normalize(glm::cross(monkey::up, glm::vec3(a.x, 0, a.z)));

    // let's compute normals on xz plane
    for (size_t i = 1; i < pts.size()-1; ++i) {
        glm::vec3 t1 = pts[i] - pts[i-1];
        glm::vec3 t2 = pts[i+1] - pts[i];
        length[1] = length[0] + glm::length(t1);
        t1.y = 0;
        t2.y = 0;
        glm::vec3 n1 = glm::normalize(glm::cross(monkey::up, t1));
        glm::vec3 n2 = glm::normalize(glm::cross(monkey::up, t2));
        normals_xz[i] = glm::normalize(0.5f*(n1+n2));
    }

    // last points
    glm::vec3 b = pts[pts.size()-1] - pts[pts.size()-2];
    normals_xz[normals_xz.size()-1] = glm::normalize(glm::cross(monkey::up, glm::vec3(b.x, 0, b.z)));

    glm::vec3 P00 = pts[0] + normals_xz[0] * d;
    glm::vec3 P01 = pts[0] - normals_xz[0] * d;
    m_topPoints.push_back(P00);
    m_topPoints.push_back(P01);
    float l0 = 0.0f;
    float l1 = 0.0f;
    // compute normals for extremal points
    for (size_t i = 0; i < pts.size()-1; ++i) {
        // for each point I put a quad

        glm::vec3 Pnext = pts[i+1];
        float t0 = monkey::rayint(
                glm::vec2(P00.z, P00.x),
                glm::vec2(tangents[i].z, tangents[i].x),
                glm::vec2(Pnext.z, Pnext.x),
                glm::vec2(normals_xz[i+1].z, normals_xz[i+1].x));
        float t1 = monkey::rayint(
                glm::vec2(P01.z, P01.x),
                glm::vec2(tangents[i].z, tangents[i].x),
                glm::vec2(Pnext.z, Pnext.x),
                glm::vec2(-normals_xz[i+1].z, -normals_xz[i+1].x));

        glm::vec3 P0_next = P00 + t0 * tangents[i];
        glm::vec3 P1_next = P01 + t1 * tangents[i];
        m_topPoints.push_back(P0_next);
        m_topPoints.push_back(P1_next);
//        glm::vec3 P00 = pts[i] + normals_xz[i]*d;
//        glm::vec3 P01 = pts[i] - normals_xz[i]*d;
//        glm::vec3 P10 = pts[i+1] + normals_xz[i+1]*d;
//        glm::vec3 P11 = pts[i+1] -  normals_xz[i+1]*d;
        glm::vec3 n = glm::cross(tangents[i], normals_xz[i]);
        // compute angle between tangent and normal
        float angle = glm::angle(glm::vec2(tangents[i].z, tangents[i].x), glm::vec2(normals_xz[i].z, normals_xz[i].x));
        float vantaggio = 2.0*d * tan(angle-1.57079632679489661923);

        vertices.emplace_back(Vertex3DN{P00.x, P00.y, P00.z, l0/rx,0, n.x, n.y, n.z});
        vertices.emplace_back(Vertex3DN{P01.x, P01.y, P01.z, (l1+vantaggio)/rx,d/rz, n.x, n.y, n.z});
        vertices.emplace_back(Vertex3DN{P0_next.x, P0_next.y, P0_next.z, (l0+t0) / rx, 0, n.x, n.y, n.z});
        vertices.emplace_back(Vertex3DN{P1_next.x, P1_next.y, P1_next.z, (l1+vantaggio+t1) / rx, d/rz, n.x, n.y, n.z});
        l0 +=t0;
        l1 +=t1;
        l0=0.0f;
        l1=0.0f;
        indices.emplace_back(c);
        indices.emplace_back(c+1);
        indices.emplace_back(c+3);
        indices.emplace_back(c);
        indices.emplace_back(c+3);
        indices.emplace_back(c+2);
        c+=4;

        P00 = P0_next;
        P01 = P1_next;
        //if (i == 0) break;
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
    // front. loop through odd points
    float length = 0;
    for (size_t i = 1; i < m_topPoints.size()-2; i+=2) {
        glm::vec3 P0 = m_topPoints[i];
        glm::vec3 P1 = m_topPoints[i+2];
        glm::vec3 P0l = P0;
        glm::vec3 P1l = P1;
        glm::vec3 n = glm::normalize(glm::cross(P1-P0, monkey::up));
        float inc = glm::length(glm::vec3(P1.x,0,P1.z) - glm::vec3(P0.x, 0, P0.z));
        P0l.y = (par ? P0.y-h : h);
        P1l.y = (par ? P1.y-h : h);
        vertices.emplace_back(Vertex3DN{P0.x,  P0.y,  P0.z,  length/rx, P0.y / ry, n.x, n.y, n.z});
        vertices.emplace_back(Vertex3DN{P0l.x, P0l.y, P0l.z, length/rx, P0l.y /ry, n.x, n.y, n.z});
        vertices.emplace_back(Vertex3DN{P1.x,  P1.y,  P1.z,  (length+inc)/rx, P1.y /ry, n.x, n.y, n.z});
        vertices.emplace_back(Vertex3DN{P1l.x, P1l.y, P1l.z, (length+inc)/rx, P1l.y /ry, n.x, n.y, n.z});
        length +=inc;
        indices.emplace_back(c);
        indices.emplace_back(c+1);
        indices.emplace_back(c+3);
        indices.emplace_back(c);
        indices.emplace_back(c+3);
        indices.emplace_back(c+2);
        c+=4;
    }
    // back face; loop through even points.
    for (size_t i = 0; i < m_topPoints.size()-2; i+=2) {
        glm::vec3 P0 = m_topPoints[i];
        glm::vec3 P1 = m_topPoints[i+2];
        glm::vec3 P0l = P0;
        glm::vec3 P1l = P1;
        glm::vec3 n = glm::normalize(glm::cross(monkey::up, P1-P0));
        float inc = glm::length(glm::vec3(P1.x,0,P1.z) - glm::vec3(P0.x, 0, P0.z));
        P0l.y = (par ? P0.y-h : h);
        P1l.y = (par ? P1.y-h : h);
        vertices.emplace_back(Vertex3DN{P0.x,  P0.y,  P0.z,  length/rx, P0.y / ry, n.x, n.y, n.z});
        vertices.emplace_back(Vertex3DN{P0l.x, P0l.y, P0l.z, length/rx, P0l.y /ry, n.x, n.y, n.z});
        vertices.emplace_back(Vertex3DN{P1.x,  P1.y,  P1.z,  (length+inc)/rx, P1.y /ry, n.x, n.y, n.z});
        vertices.emplace_back(Vertex3DN{P1l.x, P1l.y, P1l.z, (length+inc)/rx, P1l.y /ry, n.x, n.y, n.z});
        length +=inc;
        indices.emplace_back(c);
        indices.emplace_back(c+2);
        indices.emplace_back(c+3);
        indices.emplace_back(c+1);
        indices.emplace_back(c);
        indices.emplace_back(c+3);
        c+=4;
    }
    // left
    {
        glm::vec3 P0 = m_topPoints[0];
        glm::vec3 P1 = m_topPoints[1];
        glm::vec3 P0l = P0;
        glm::vec3 P1l = P1;
        P0l.y = (par ? P0.y - h : h);
        P1l.y = (par ? P1.y - h : h);
        glm::vec3 n1 = glm::normalize(glm::cross(P1 - P0, monkey::up));
        vertices.emplace_back(Vertex3DN{P0.x, P0.y, P0.z, 0.0f, P0.y / ry, n1.x, n1.y, n1.z});
        vertices.emplace_back(Vertex3DN{P0l.x, P0l.y, P0l.z, 0.0f, P0l.y / ry, n1.x, n1.y, n1.z});
        vertices.emplace_back(Vertex3DN{P1.x, P1.y, P1.z, d / rx, P1.y / ry, n1.x, n1.y, n1.z});
        vertices.emplace_back(Vertex3DN{P1l.x, P1l.y, P1l.z, d / rx, P1l.y / ry, n1.x, n1.y, n1.z});
        indices.emplace_back(c);
        indices.emplace_back(c+1);
        indices.emplace_back(c+3);
        indices.emplace_back(c);
        indices.emplace_back(c+3);
        indices.emplace_back(c+2);
        c+=4;
    }
    // right
    {
        glm::vec3 P0 = m_topPoints[m_topPoints.size()-2];
        glm::vec3 P1 = m_topPoints[m_topPoints.size()-1];
        glm::vec3 P0l = P0;
        glm::vec3 P1l = P1;
        P0l.y = (par ? P0.y - h : h);
        P1l.y = (par ? P1.y - h : h);
        glm::vec3 n1 = glm::normalize(glm::cross(monkey::up, P1 - P0));
        vertices.emplace_back(Vertex3DN{P0.x, P0.y, P0.z, 0.0f, P0.y / ry, n1.x, n1.y, n1.z});
        vertices.emplace_back(Vertex3DN{P0l.x, P0l.y, P0l.z, 0.0f, P0l.y / ry, n1.x, n1.y, n1.z});
        vertices.emplace_back(Vertex3DN{P1.x, P1.y, P1.z, d / rx, P1.y / ry, n1.x, n1.y, n1.z});
        vertices.emplace_back(Vertex3DN{P1l.x, P1l.y, P1l.z, d / rx, P1l.y / ry, n1.x, n1.y, n1.z});
        indices.emplace_back(c);
        indices.emplace_back(c+2);
        indices.emplace_back(c+3);
        indices.emplace_back(c+1);
        indices.emplace_back(c);
        indices.emplace_back(c+3);
        c+=4;
    }


    sideMesh->Init(vertices, indices);
    return sideMesh;


}