#include <monkey/meshfactory.h>
#include <monkey/quadmesh.h>
#include <monkey/math/earcut.h>

MeshFactoryTextured::MeshFactoryTextured(const std::string &texture, float x0, float y0, float repx, float repy, float slantx, float slanty,
                                         std::shared_ptr<Fill> fill)
        : m_texId(texture), m_x0(x0), m_y0(y0), m_rx(repx), m_ry(repy), m_a(slantx), m_b(slanty), m_fill(fill)
{

}

std::shared_ptr<IMesh> MeshFactoryTextured::CreateMesh(
        Shape &s,
        const std::string &texture,
        float x0,
        float y0,
        float repx,
        float repy,
        float slantx,
        float slanty,
        std::shared_ptr<Fill> fill)
{
    MeshFactoryTextured m(texture, x0, y0, repx, repy, slantx, slanty, fill);
    s.accept(m);
    return m.m_mesh;
}

void MeshFactoryTextured::visit(Poly & poly) {

    // The number type to use for tessellation
    using Coord = float;

    // The index type. Defaults to uint32_t, but you can also pass uint16_t if you know that your
    // data won't have more than 65536 vertices.
    using N = uint32_t;

    // Create array
    using Point = std::array<Coord, 2>;
    std::vector<std::vector<Point>> polygon;
    auto p = poly.getPoints();
    // Fill polygon structure with actual data. Any winding order works.
    // The first polyline defines the main polygon.
    std::vector<Vertex3D> vertices;

    std::vector<Point> outline;
    for (const auto& vec : p) {
        outline.push_back({vec.x, vec.y});
        glm::vec3 p(vec.x, vec.y, 1.0f);
        float tx = (vec.x - m_a * vec.y - m_x0) / m_rx;
        float ty = (vec.y - m_b * vec.x - m_y0) / m_ry;
        //float r = glm::dot(m_red, p);
        //float g = glm::dot(m_green, p);
        //float b = glm::dot(m_blue, p);
        //float a = glm::dot(m_alpha, p);
        auto color = m_fill->getColor(glm::vec2(vec.x, vec.y));
        //float c = -(1.0f/256.0f)*vec.y +1;
        //vertices.emplace_back( Vertex3D(vec.x, vec.y, 0.0f, tx, ty, c, c, c, 1.0f));
        vertices.emplace_back( Vertex3D(vec.x, vec.y, 0.0f, tx, ty, color.r, color.g, color.b, color.a));
    }
    polygon.push_back(outline);
    auto mesh  = std::make_shared<QuadMesh>(GL_TRIANGLES, m_texId);
    // Run tessellation
    // Returns array of indices that refer to the vertices of the input polygon.
    // e.g: the index 6 would refer to {25, 75} in this example.
    // Three subsequent indices form a triangle. Output triangles are clockwise.
    std::vector<N> indices = mapbox::earcut<N>(polygon);
    mesh->Init(vertices, indices);
    m_mesh = mesh;


}