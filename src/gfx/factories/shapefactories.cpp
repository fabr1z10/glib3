#include <gfx/factories.h>
#include <gfx/engine.h>

#include <gfx/math/rect.h>
#include <gfx/math/line.h>
#include <gfx/math/poly.h>
#include <gfx/math/polyline.h>
#include <gfx/math/compound.h>
#include <gfx/math/circle.h>
#include <gfx/math/ellipse.h>

std::unique_ptr<Shape> RectFactory::Create(luabridge::LuaRef &ref) {
    LuaTable at (ref);
    glm::vec2 offset = at.Get<glm::vec2>("offset", glm::vec2(0.0f));
    float w = at.Get<float>("width");
    float h = at.Get<float>("height");
    return std::unique_ptr<Rect>(new Rect(w, h, offset));
}

std::unique_ptr<Shape> LineFactory::Create(luabridge::LuaRef &ref) {
    LuaTable at (ref);
    glm::vec2 A = at.Get<glm::vec2>("A");
    glm::vec2 B = at.Get<glm::vec2>("B");
    return std::unique_ptr<Line>(new Line(A, B));
}

std::unique_ptr<Shape> PolyFactory::Create(luabridge::LuaRef& ref) {
    LuaTable at (ref);
    //glm::vec2 offset = at.Get<glm::vec2>("offset", glm::vec2(0.0f));
    std::vector<float> outline = at.GetVector<float>("outline");
    std::vector<glm::vec2> points;
    for (size_t i = 0; i < outline.size(); i = i + 2)
        points.push_back(glm::vec2(outline[i], outline[i + 1]));
    if (at.HasKey("holes")) {
        std::unique_ptr<Polygon> mainOutline(new Polygon(points));
        luabridge::LuaRef holes = at.Get<luabridge::LuaRef>("holes");
        LuaTable ha(holes);
        auto poly = std::unique_ptr<Poly>(new Poly(std::move(mainOutline)));
        for (int j = 0; j < holes.length(); ++j) {
            luabridge::LuaRef h = holes[j + 1];
            std::vector<float> holeOutline = ReadVector<float>(h);
            std::vector<glm::vec2> points;
            for (int i = 0; i < holeOutline.size(); i = i + 2)
                points.push_back(glm::vec2(holeOutline[i], holeOutline[i + 1]));
            poly->AddHole(std::unique_ptr<Polygon>(new Polygon(points)));
        }
        return std::move(poly);
    } else {
        return std::unique_ptr<Polygon>(new Polygon(points));
    }
}

std::unique_ptr<Shape> CircleFactory::Create(luabridge::LuaRef& ref) {
    LuaTable at (ref);
    glm::vec2 offset = at.Get<glm::vec2>("offset", glm::vec2(0.0f));
    float radius = at.Get<float>("radius");
    return std::unique_ptr<Circle>(new Circle(radius, offset));
}

std::unique_ptr<Shape> EllipseFactory::Create(luabridge::LuaRef& ref) {
    LuaTable at (ref);
    glm::vec2 offset = at.Get<glm::vec2>("offset", glm::vec2(0.0f));
    glm::vec2 axes = at.Get<glm::vec2>("semiaxes");
    return std::unique_ptr<Ellipse>(new Ellipse(axes.x, axes.y, offset));
}

std::unique_ptr<Shape> GraphFactory::Create(luabridge::LuaRef& ref) {
    LuaTable at (ref);
    //glm::vec2 offset = at.Get<glm::vec2>("offset", glm::vec2(0.0f));
    // read the vertices
    luabridge::LuaRef rVert = at.Get<luabridge::LuaRef>("vertices");
    std::vector<glm::vec2> vertices;
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i< rVert.length(); ++i) {
        luabridge::LuaRef vertex = rVert[i+1];
        glm::vec2 p(vertex[1].cast<float>(), vertex[2].cast<float>());
        vertices.push_back(p);
    }
    luabridge::LuaRef rEdges = at.Get<luabridge::LuaRef>("edges");
    for (int i = 0; i< rEdges.length(); ++i) {
        luabridge::LuaRef edge = rEdges[i+1];
        std::pair<int, int> e(edge[1].cast<int>(), edge[2].cast<int>());
        edges.push_back(e);
    }
    return std::unique_ptr<PolyLine>(new PolyLine(vertices,edges));
}

std::unique_ptr<Shape> CompoundFactory::Create(luabridge::LuaRef& ref) {
    LuaTable at (ref);
    auto factory = Engine::get().GetSceneFactory();
    luabridge::LuaRef rshapes = at.Get<luabridge::LuaRef>("shapes");
    auto cs = std::unique_ptr<CompoundShape>(new CompoundShape);
    for (int i = 0; i<rshapes.length(); ++i) {
        luabridge::LuaRef rshape = rshapes[i+1];
        auto s = factory->GetShared<Shape>(rshape);
        cs->AddShape(s);
    }
    return std::move(cs);
}

