//#include <phy/factories.h>
//#include <phy/road.h>
//#include <monkey/quadmesh.h>
//#include <monkey/components/renderer.h>
//
//
//
//
//std::unique_ptr<Component> RoadComponentFactory::Create(luabridge::LuaRef& ref) {
//    // REQUIRED
//    // texture, texture increment, number
//    // THE NUMBER OF POINTS PER ARC DEPEND ON THE ARC LENGTH!!!
//    // it doesnt make sense to have a fixed n of points per arc as some arc might be much longer than others!
//
//
//    LuaTable table(ref);
//    // number of samples per unit length
//    int n = table.Get<int>("n");
//    std::string tex = table.Get<std::string>("image");
//    luabridge::LuaRef points = table.Get<luabridge::LuaRef>("points");
//    std::unordered_map<int, glm::vec3> pts;
//    std::vector<Road::Edge> arcs;
//    for (int i = 0; i < points.length(); ++i) {
//        luabridge::LuaRef p = points[i+1];
//        LuaTable t2(p);
//        int id = t2.Get<int>("id");
//        glm::vec3 pos = t2.Get<glm::vec3>("pos");
//        pts[id] = pos;
//    }
//    luabridge::LuaRef edges = table.Get<luabridge::LuaRef>("edges");
//    for (int i = 0; i < edges.length(); ++i) {
//        luabridge::LuaRef e = edges[i+1];
//        LuaTable t2(e);
//        int p1 = t2.Get<int>("from");
//        int p2 = t2.Get<int>("to");
//        glm::vec2 angles = t2.Get<glm::vec2>("angles");
//        arcs.push_back(Road::Edge{p1,p2,angles[0],angles[1],1.0,1.0});
//    }
//    Road road(pts, arcs);
//    auto& roadArcs = road.GetArcs();
//
//    auto m = std::make_shared<QuadMesh>(GL_TRIANGLE_STRIP, tex);
//
//    std::vector<Vertex3D> vertices;
//    std::vector<unsigned> indices;
//    float roadWidth = 10.0f;
//    int j = 0; // index count
//    int narcs = 0;
//    for (auto& a : roadArcs) {
//        if (narcs > 0) {
//            indices.push_back(j-1);
//            indices.push_back(j);
//        }
//        double t = 0.0;
//        float texY = 0.0;
//        float length = a.second.GetArcLength();
//        int m = std::max(static_cast<int>(length  / n), 2);
//        float inc = 1.0 / (m-1);
//        for (int i = 0; i < m; ++i) {
//            glm::vec3 P = a.second(t);
//            glm::vec3 ta = a.second.tangent(t);
//            glm::vec3 n = glm::normalize(glm::vec3(-ta.y, ta.x, 0.0));
//            glm::vec3 P1 = P + n * roadWidth;
//            glm::vec3 P2 = P - n*roadWidth;
//            vertices.push_back(Vertex3D{P1.x, P1.y, P1.z, 0.0f, texY});
//            vertices.push_back(Vertex3D{P2.x, P2.y, P2.z, 1.0f, texY});
//            t += inc;
//            texY += 0.1;
//            indices.push_back(j++);
//            indices.push_back(j++);
//        }
//        narcs++;
//    }
//    m->Init(vertices, indices);
//    auto r = std::unique_ptr<Renderer>(new Renderer);
//    r->SetMesh(m);
//    return std::move(r);
//
//}
