//#include <monkey/math/geom.h>
#include <monkey/meshfactory.h>
//#include <monkey/vertices.h>
#include <cmath>
//#include <monkey/math/earcut.h>
#include <monkey/quadmesh.h>
#include <monkey/assets/model.h>
#include <monkey/math/shapes3d/aabb.h>
#include <monkey/math/shapes3d/plane.h>
#include <monkey/math/shapes3d/prism.h>
#include <monkey/model/combomodel.h>
#include <monkey/math/earcut.h>
#include <monkey/texturedmesh.h>
#include <monkey/math/shapes3d/pseudo3d.h>
//
//

MeshFactory::MeshFactory(float z) : m_z(z) {
    m_plotters.insert(std::make_pair(ShapeType::RECT, [&] (IShape* s, glm::vec4 color, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices)
        { return drawConvexPoly(s, color, vertices, indices, true); }));
    m_plotters.insert(std::make_pair(ShapeType::SEGMENT, [&] (IShape* s, glm::vec4 color, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices)
        { return drawConvexPoly(s, color, vertices, indices, false); }));
    m_plotters.insert(std::make_pair(ShapeType::CONVEXPOLY, [&] (IShape* s, glm::vec4 color, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices)
        { return drawConvexPoly(s, color, vertices, indices, true); }));
	m_plotters.insert(std::make_pair(ShapeType::CIRCLE, [&] (IShape* s, glm::vec4 color, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices)
	    { return drawCircle(s, color, vertices, indices); }));
	m_plotters.insert(std::make_pair(ShapeType::COMPOUND, [&] (IShape* s, glm::vec4 color, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices)
		{ return drawCompound(s, color, vertices, indices); }));
    m_plotters.insert(std::make_pair(ShapeType::POLY, [&] (IShape* s, glm::vec4 color, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices)
        { return drawPoly(s, color, vertices, indices); }));
    m_plotters.insert(std::make_pair(ShapeType::POLYLINE, [&] (IShape* s, glm::vec4 color, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices)
        { return drawPolyLine(s, color, vertices, indices); }));
	m_plotters.insert(std::make_pair(ShapeType::AABB, [&] (IShape* s, glm::vec4 color, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices)
		{ return drawAABB(s, color, vertices, indices); }));
	m_plotters.insert(std::make_pair(ShapeType::PLANE, [&] (IShape* s, glm::vec4 color, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices)
		{ return drawPlane(s, color, vertices, indices); }));
	m_plotters.insert(std::make_pair(ShapeType::PRISM, [&] (IShape* s, glm::vec4 color, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices)
		{ return drawPrism(s, color, vertices, indices); }));
    m_plotters.insert(std::make_pair(ShapeType::PSEUDO3D, [&] (IShape* s, glm::vec4 color, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices)
        { return drawPseudo3D(s, color, vertices, indices); }));


	//m_plottersTex.insert(std::make_pair(ShapeType::POLY, [&] (IShape* s, const std::vector<TexInfo>& texInfos) { return drawPolyTex(s, texInfos); }));
    m_plottersTex.insert(std::make_pair(ShapeType::PRISM, [&] (IShape* s, const std::vector<TexInfo>& texInfos) { return drawPrismTex(s, texInfos); }));
    m_plottersTex.insert(std::make_pair(ShapeType::AABB, [&] (IShape* s, const std::vector<TexInfo>& texInfos) { return drawAABBTex(s, texInfos); }));

}

void MeshFactory::drawPlane(IShape* s, glm::vec4 color, std::vector<VertexColor> &vertices, std::vector<unsigned int> &indices) {
	auto* a = static_cast<Plane*>(s);
	auto n = a->getNormal();
	auto t1 = (n == glm::vec3(0.0f, 1.0f, 0.0f) ? glm::vec3(0.0f, 0.0f, 1.0f) : glm::normalize(glm::cross(n, glm::vec3(0.0f, 1.0f, 0.0f))));
	auto t2 = glm::cross(n, t1);
	auto origin = a->getNormal() * a->getDistance();
	// make a grid
	float size = 10.0f;
	float hsize = size* 0.5f;
	int np = 10;
	float delta = size / (np - 1);
	glm::vec3 b = origin - t1 * hsize - t2 * hsize;
	glm::vec3 c = origin - t1 * hsize + t2 * hsize;
	for (int i = 0; i < np; ++i) {
		glm::vec3 b1 = b + t1 * (i*delta);
		glm::vec3 c1 = c + t1 * (i*delta);
		vertices.emplace_back(b1.x, b1.y, b1.z, color.r, color.g, color.b, color.a);
		vertices.emplace_back(c1.x, c1.y, c1.z, color.r, color.g, color.b, color.a);
	}
	b = origin - t2 * hsize - t1 * hsize;
	c = origin - t2 * hsize + t1 * hsize;
	for (int i = 0; i < np; ++i) {
		glm::vec3 b1 = b + t2 * (i*delta);
		glm::vec3 c1 = c + t2 * (i*delta);
		vertices.emplace_back(b1.x, b1.y, b1.z, color.r, color.g, color.b, color.a);
		vertices.emplace_back(c1.x, c1.y, c1.z, color.r, color.g, color.b, color.a);
	}
	for (int i = 0; i < 4*np; ++i) {
		indices.emplace_back(i);
	}

}

void MeshFactory::drawAABB(IShape* s, glm::vec4 color, std::vector<VertexColor> &vertices,
						   std::vector<unsigned int> &indices)
{
	auto* a = static_cast<AABB*>(s);
	auto O = a->getOffset();
	auto size = a->getSize();
	auto n = vertices.size();
    if (size.z == 0.0f) {
        vertices.emplace_back(O.x, O.y, O.z, color.r, color.g, color.b, color.a);
        vertices.emplace_back(O.x + size.x, O.y, O.z, color.r, color.g, color.b, color.a);
        vertices.emplace_back(O.x + size.x, O.y + size.y, O.z, color.r, color.g, color.b, color.a);
        vertices.emplace_back(O.x, O.y + size.y, O.z, color.r, color.g, color.b, color.a);
        for (auto a : {0, 1, 1, 2, 2, 3, 3, 0}) {
            indices.push_back(n + a);
        }
    } else {
        vertices.emplace_back(O.x, O.y, O.z, color.r, color.g, color.b, color.a);
        vertices.emplace_back(O.x, O.y, O.z + size.z, color.r, color.g, color.b, color.a);
        vertices.emplace_back(O.x + size.x, O.y, O.z + size.z, color.r, color.g, color.b, color.a);
        vertices.emplace_back(O.x + size.x, O.y, O.z, color.r, color.g, color.b, color.a);
        vertices.emplace_back(O.x, O.y + size.y, O.z, color.r, color.g, color.b, color.a);
        vertices.emplace_back(O.x, O.y + size.y, O.z + size.z, color.r, color.g, color.b, color.a);
        vertices.emplace_back(O.x + size.x, O.y + size.y, O.z + size.z, color.r, color.g, color.b, color.a);
        vertices.emplace_back(O.x + size.x, O.y + size.y, O.z, color.r, color.g, color.b, color.a);
        for (auto a : {0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7}) {
            indices.push_back(n + a);
        }
    }
	//indices.insert(indices.end(), {0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7});


}

std::shared_ptr<Model> MeshFactory::drawAABBTex(IShape * s, const std::vector<TexInfo> & texInfos) {
    std::vector<Vertex3DN> aaa;
    std::vector<unsigned> indices;
    auto* box = static_cast<AABB*>(s);
    auto size = box->getSize();
    const auto& texInfo = texInfos[0];
    float w = size.x;
    float h = size.y;
    float d = size.z;
    // face down
    aaa.emplace_back(0.0f, 0.0f, 0.0f, 0.0f, d/texInfo.rep1, 0.0f, -1.0f, 0.0f);
    aaa.emplace_back(w, 0.0f, 0.0f, w/texInfo.rep0, d/texInfo.rep1, 0.0f, -1.0f, 0.0f);
    aaa.emplace_back(w, 0.0f, d, w/texInfo.rep0, 0.0f, 0.0f, -1.0f, 0.0f);
    aaa.emplace_back(0.0f, 0.0f, d, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f);
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);
    // face up
    aaa.emplace_back(0.0f, h, 0.0f, 0.0f, d/texInfo.rep1, 0.0f, 1.0f, 0.0f);
    aaa.emplace_back(w, h, 0.0f, w/texInfo.rep0, d/texInfo.rep1, 0.0f, 1.0f, 0.0f);
    aaa.emplace_back(w, h, d, w/texInfo.rep0, 0.0f, 0.0f, 1.0f, 0.0f);
    aaa.emplace_back(0.0f, h, d, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    indices.push_back(5);
    indices.push_back(4);
    indices.push_back(7);
    indices.push_back(7);
    indices.push_back(6);
    indices.push_back(5);
    // face front
    aaa.emplace_back(0.0f, h, d, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    aaa.emplace_back(w, h, d, w/texInfo.rep0, 0.0f, 0.0f, 0.0f, 1.0f);
    aaa.emplace_back(w, 0.0f, d, w/texInfo.rep0, h/texInfo.rep1, 0.0f, 0.0f, 1.0f);
    aaa.emplace_back(0.0f, 0.0f, d, 0.0f, h/texInfo.rep1, 0.0f, 0.0f, 1.0f);
    indices.push_back(8);
    indices.push_back(9);
    indices.push_back(11);
    indices.push_back(11);
    indices.push_back(10);
    indices.push_back(9);
    // face left
    aaa.emplace_back(0.0f, h, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
    aaa.emplace_back(0.0f, h, d, d/texInfo.rep0, 0.0f, -1.0f, 0.0f, 0.0f);
    aaa.emplace_back(0.0f, 0.0f, d, d/texInfo.rep0, h/texInfo.rep1, -1.0f, 0.0f, 0.0f);
    aaa.emplace_back(0.0f, 0.0f, 0.0f, 0.0f, h/texInfo.rep1, -1.0f, 0.0f, 1.0f);
    indices.push_back(12);
    indices.push_back(15);
    indices.push_back(14);
    indices.push_back(14);
    indices.push_back(13);
    indices.push_back(12);
    // face right
    aaa.emplace_back(w, h, d, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    aaa.emplace_back(w, h, 0.0f, d/texInfo.rep0, 0.0f, 1.0f, 0.0f, 0.0f);
    aaa.emplace_back(w, 0.0f, 0.0f, d/texInfo.rep0, h/texInfo.rep1, 1.0f, 0.0f, 0.0f);
    aaa.emplace_back(w, 0.0f, d, 0.0f, h/texInfo.rep1, 1.0f, 0.0f, 1.0f);
    indices.push_back(16);
    indices.push_back(19);
    indices.push_back(18);
    indices.push_back(18);
    indices.push_back(17);
    indices.push_back(16);


    auto mesh = std::make_shared<Mesh<Vertex3DN>>(TEXTURE_SHADER_LIGHT, GL_TRIANGLES);
    mesh->addTexture(texInfo.tex, TexType::DIFFUSE);
    mesh->Init(aaa, indices);
    auto cm = std::make_shared<Model>(mesh);
    return cm;
}

std::shared_ptr<Model> MeshFactory::drawPrismTex(IShape * s, const std::vector<TexInfo>& texInfos) {
    auto comboModel = std::make_shared<Model>();

    // create top mesh
    auto* prism = static_cast<Prism*>(s);
    auto* baseShape = static_cast<Polygon*>(prism->getBaseShape());
    auto it = m_plottersTex.find(baseShape->getShapeType());
    //auto cm = std::make_shared<Model>();
    auto h = prism->getHeight();

    auto m1 = drawPolyTex(baseShape, texInfos, h);
    comboModel->addMesh(m1);

    // plot border
    auto v = baseShape->getOutlineVertices();
    std::vector<Vertex3DN> aaa;
    std::vector<unsigned> indices;
    const auto& borderTexInfo = texInfos[1];
    float x0 = v[0].x;
    float z0 = -v[0].y;
    // place one quad for each side
    float tx = 0.0f;
    float tyh = h/borderTexInfo.rep1;
    for (size_t i = 0; i < v.size(); ++i) {
        auto j = (i+1) % v.size();
        auto tmp = glm::normalize(v[j] - v[i]);
        glm::vec3 normal = glm::cross(glm::vec3(tmp.x, 0.0f, -tmp.y), glm::vec3(0.0f, 1.0f, 0.0f));
        aaa.emplace_back(v[i].x, h, -v[i].y, tx/borderTexInfo.rep0, 0.0f, normal.x, normal.y, normal.z);
        aaa.emplace_back(v[i].x, 0.0f, -v[i].y, tx/borderTexInfo.rep0, tyh, normal.x, normal.y, normal.z);
        tx += glm::length(v[j] - v[i]);
        aaa.emplace_back(v[j].x, h, -v[j].y, tx/borderTexInfo.rep0, 0.0f, normal.x, normal.y, normal.z);
        aaa.emplace_back(v[j].x, 0.0f, -v[j].y, tx/borderTexInfo.rep0, tyh, normal.x, normal.y, normal.z);
        indices.push_back(i*4);
        indices.push_back(i*4+1);
        indices.push_back(i*4+2);
        indices.push_back(i*4+1);
        indices.push_back(i*4+3);
        indices.push_back(i*4+2);
    }
    auto mesh = std::make_shared<TexturedMesh<Vertex3DN>>(TEXTURE_SHADER_LIGHT, GL_TRIANGLES, borderTexInfo.tex);
    mesh->Init(aaa, indices);
    comboModel->addMesh(mesh);
    return comboModel;

}

void MeshFactory::drawPseudo3D(IShape * s, glm::vec4 t, std::vector<VertexColor> &vertices,
                               std::vector<unsigned int> &indices)
{
    auto ps =dynamic_cast<Pseudo3DShape*>(s);
    auto is = ps->getInternalShape();
    auto plotter = m_plotters.find(is->getShapeType());
    if (plotter != m_plotters.end()) {
        plotter->second(is, t, vertices, indices);
    }
}

void MeshFactory::drawPrism(IShape * s, glm::vec4 color, std::vector<VertexColor> &vertices,
							std::vector<unsigned int> &indices)
{
	auto* prism = static_cast<Prism*>(s);
	auto* baseShape = prism->getBaseShape();
	auto h = prism->getHeight();
	auto it = m_plotters.find(baseShape->getShapeType());
	if (it != m_plotters.end()) {
		it->second(baseShape, color, vertices, indices);
		for (auto& v : vertices) {
			v.z = -v.y;
			v.y = 0;
		}
		unsigned n = vertices.size();
		unsigned m = indices.size();
		for (size_t i = 0; i < n; ++i) {
			vertices.push_back(vertices[i]);
			vertices.back().y = h;
		}
		for (size_t i = 0; i < m; ++i) {
			indices.push_back(indices[i] + n);
		}
		for (size_t i = 0; i < n; ++i) {
			indices.push_back(i);
			indices.push_back(i + n);
		}


	}

}

void MeshFactory::drawCompound(IShape * s, glm::vec4 color, std::vector<VertexColor> &vertices, std::vector<unsigned int> &indices)
{
	auto* cs = static_cast<CompoundShape*>(s);
	for (const auto& shape : cs->getShapes()) {
		auto shapeType = shape->getShapeType();
		auto it = m_plotters.find(shapeType);
		if (it != m_plotters.end()) {
			it->second(shape.get(), color, vertices, indices);
		}
	}



}

void MeshFactory::drawPolyLine(IShape * s, glm::vec4 color, std::vector<VertexColor> &vertices, std::vector<unsigned int> &indices)
{
    auto* polyline = static_cast<PolyLine*>(s);
    const auto& v = polyline->getVertices();
    for (const auto& vertex : v) {
        vertices.emplace_back(vertex.x, vertex.y, 0.0f, color.r, color.g, color.b, color.a);
    }
    for (const auto& e : polyline->getEdges()) {
        indices.emplace_back(e[0]);
        indices.emplace_back(e[1]);
    }
}

std::shared_ptr<IMesh> MeshFactory::drawPolyTex(IShape * shape, const std::vector<TexInfo>& texInfos, float h) {
    using Coord = float;
    using Point = std::array<Coord, 2>;
    using N = uint32_t;
    std::vector<Vertex3DN> vertices;
    std::vector<unsigned> indices;
    auto* poly = static_cast<Polygon*>(shape);
    std::vector<Point> polygon;
    auto v = poly->getOutlineVertices();
    float x0 = v[0].x;
    float z0 = -v[0].y;
    const auto& texInfo = texInfos[0];
    for (const auto& vertex : v) {
        float z = -vertex.y;
        vertices.emplace_back(vertex.x, h, z, (vertex.x - x0) / texInfo.rep0, (z - z0) / texInfo.rep1, 0.0f, 1.0f, 0.0f);
        polygon.push_back({vertex.x, z});
    }

    // triangualate polygon
    std::vector<std::vector<Point>> p;
    p.push_back(polygon);
    auto tri = mapbox::earcut<N>(p);
    // now add indices
    for (const auto& i : tri) {
        indices.push_back(i);
    }
    auto mesh = std::make_shared<TexturedMesh<Vertex3DN>>(TEXTURE_SHADER_LIGHT, GL_TRIANGLES, texInfo.tex);
    mesh->Init(vertices, indices);
    return mesh;
}

void MeshFactory::drawPoly (IShape* s, glm::vec4 color, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices) {
    auto* poly = static_cast<Polygon*>(s);
    unsigned first = vertices.size();
    unsigned c = first;
    for (const auto& vertex : poly->getOutlineVertices()) {
        vertices.emplace_back(vertex.x, vertex.y, 0.0f, color.r, color.g, color.b, color.a);
        indices.emplace_back(c++);
        indices.emplace_back(c);
    }
    indices.back() = first;
    for (int i = 0; i < poly->getHoleCount(); ++i) {
        first = vertices.size();
        c = first;
        for (const auto& vertex : poly->getHoleVertices(i)) {
            vertices.emplace_back(vertex.x, vertex.y, 0.0f, color.r, color.g, color.b, color.a);
            indices.emplace_back(c++);
            indices.emplace_back(c);
        }
        indices.back() = first;
    }

}


void MeshFactory::drawConvexPoly (IShape* s, glm::vec4 color, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices, bool closeLoop) {
    auto* seg = static_cast<IConvexPolygon*>(s);
    unsigned offset = vertices.size();
    unsigned c = offset;
    unsigned count = 0;
    // offset is already taken into account in getVertices
    unsigned nVertices = seg->getVertices().size();
    for (const auto& vertex : seg->getVertices()) {
        vertices.emplace_back( vertex.x, vertex.y, m_z, color.r, color.g, color.b, color.a);
        if (count < nVertices - 1) {
            indices.emplace_back(c++);
            indices.emplace_back(c);
        } else {
        	if (closeLoop) {
        		// last
        		indices.emplace_back(c);
        		indices.emplace_back(offset);
        	}
        }
        count++;
    }
}

void MeshFactory::drawCircle(IShape * s, glm::vec4 color, std::vector<VertexColor> &vertices, std::vector<unsigned int> &indices) {
    auto* c = static_cast<Circle*>(s);
    float radius = c->getRadius();
    glm::vec2 center = c->getOffset();
    int n = 100;
    float angleStep = (2.0 * M_PI) / n;
    unsigned offset = indices.size();
    unsigned current = offset;
    for (int i = 0; i < n; ++i) {
        float alpha = i * angleStep;
        vertices.emplace_back(center.x + radius * cos(alpha), center.x + radius * sin(alpha), 0.0f, color.r, color.g, color.b, color.a);
        if (i < n-1) {
            indices.emplace_back(current++);
            indices.emplace_back(current);
        } else {
            indices.emplace_back(current);
            indices.emplace_back(offset);
        }
    }
}


//std::shared_ptr<BasicModel> MeshFactory::drawCircle(IShape * s, glm::vec4 color) {
//	auto* c = static_cast<Circle*>(s);
//	float radius = c->getRadius();
//	glm::vec2 center = c->getOffset();
//	std::vector<VertexColor> vertices;
//	int n = 100;
//	float angleStep = (2.0 * M_PI) / n;
//	unsigned count {};
//	std::vector<unsigned> indices = {0, 1};
//	for (int i = 0; i < n; ++i) {
//		float alpha = i * angleStep;
//		vertices.emplace_back(center.x + radius * cos(alpha), center.x + radius * sin(alpha), 0.0f, color.r, color.g, color.b, color.a);
//		indices.emplace_back(count++);
//	}
//	auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//	mesh->Init(vertices, indices);
//	mesh->m_primitive = GL_LINE_LOOP;
//	return std::make_shared<BasicModel>(mesh);
//
//}
//
//std::shared_ptr<BasicModel> MeshFactory::drawConvexPoly(IShape * s, glm::vec4 color) {
//    auto* seg = static_cast<IConvexPolygon*>(s);
//    std::vector<VertexColor> vertices;
//    std::vector<unsigned> indices = {0, 1};
//    unsigned c = 0;
//    for (const auto& vertex : seg->getVertices()) {
//        vertices.emplace_back(vertex.x, vertex.y, 0.0f, color.r, color.g, color.b, color.a);
//        indices.emplace_back(c++);
//    }
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->Init(vertices, indices);
//    mesh->m_primitive = GL_LINE_LOOP;
//    return std::make_shared<BasicModel>(mesh);
//}

std::shared_ptr<Model> MeshFactory::createSolid(IShape* shape, glm::vec4 color) {
	//auto st
}

void MeshFactory::j2(IShape * shape, std::vector<VertexColor> & vertices, std::vector<unsigned int> & indices, glm::vec4 color) {
    auto st = shape->getShapeType();
    auto it = m_plotters.find(st);
    if (it != m_plotters.end()) {
        it->second(shape, color, vertices, indices);
    }

}
std::shared_ptr<Model> MeshFactory::createTextured(IShape * shape, const std::vector<TexInfo>& texInfos) {
    auto st = shape->getShapeType();
    std::vector<Vertex3D> vertices;
    std::vector<unsigned> indices;
    auto it = m_plottersTex.find(st);
    if (it != m_plottersTex.end()) {
        return it->second(shape, texInfos);
    } else {
        return nullptr;
        //GLIB_FAIL("don't know how to build shape " << shape->getShapeType());
    }

}

std::shared_ptr<Model> MeshFactory::createWireframe(IShape * shape, glm::vec4 color) {
    auto st = shape->getShapeType();
    std::vector<VertexColor> vertices;
    std::vector<unsigned> indices;
    auto it = m_plotters.find(st);
    if (it != m_plotters.end()) {
        it->second(shape, color, vertices, indices);
    } else {
        return nullptr;
        //GLIB_FAIL("don't know how to build shape " << shape->getShapeType());
    }

    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINES;
    return std::make_shared<Model>(mesh);

////    return mesh;
////            {0.0f, 0.0f, 0.0f, color.r, color.g, color.b, color.a},
////            {width, 0.0f, 0.0f, color.r, color.g, color.b, color.a},
////            {width, height, 0.0f, color.r, color.g, color.b, color.a},
////            {0.0f, height, 0.0f, color.r, color.g, color.b, color.a}};
////

}
////std::shared_ptr<IMesh> MeshFactory::CreateBoxMesh (float width, float height, glm::vec4 color) {
////    std::vector<VertexColor> vertices = {
////            {0.0f, 0.0f, 0.0f, color.r, color.g, color.b, color.a},
////            {width, 0.0f, 0.0f, color.r, color.g, color.b, color.a},
////            {width, height, 0.0f, color.r, color.g, color.b, color.a},
////            {0.0f, height, 0.0f, color.r, color.g, color.b, color.a}};
////
////    std::vector<unsigned> indices {0, 1, 2, 3};
////    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
////    mesh->Init(vertices, indices);
////    mesh->m_primitive = GL_LINE_LOOP;
////    return mesh;
////}
//
//
//
//
//
//
//std::shared_ptr<IMesh> MeshFactory::CreateMesh (const Polygon& p, float z) {
//    std::vector<VertexColor> vertices ;
//    std::vector<unsigned int> indices;
//    int n = p.GetVertexCount();
//    for (int i = 0; i <n; ++i) {
//        glm::vec2 v = p.GetVertex(i);
//        vertices.push_back({v.x, v.y, z, 1.0, 1.0, 1.0, 1.0});
//        indices.push_back(i);
//    }
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->Init(vertices, indices);
//    mesh->m_primitive = GL_LINE_LOOP;
//    return mesh;
//}
//
//std::shared_ptr<IMesh> MeshFactory::CreateMesh (Shape& s, float z, glm::vec4 color) {
//    MeshFactory m (z, color);
//    s.accept(m);
//    return m.m_mesh;
//}
//
//
//
//void MeshFactory::visit(Rect& rect) {
//    float w = rect.GetWidth();
//    float h = rect.GetHeight();
//    glm::vec2 offset = rect.GetOffset();
//    std::vector<VertexColor> vertices = {
//            {offset.x, offset.y, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
//            {offset.x + w, offset.y, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
//            {offset.x + w, offset.y + h, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
//            {offset.x, offset.y + h, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
//    };
//    std::vector<unsigned int> indices = {0, 1, 2, 3};
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->Init(vertices, indices);
//    mesh->m_primitive = GL_LINE_LOOP;
//    m_mesh = mesh;
//}
//
//void MeshFactory::visit(Plane3D& rect) {
//
//	float hw = rect.width() * 0.5f;
//	float hh = rect.height() * 0.5f;
//
////	auto tex = t.get<std::string>("tex", "");
////
////	glm::vec2 repeat = t.get<glm::vec2>("repeat", glm::vec2(1.0f, 1.0f));
////
////	auto m = std::make_shared<TexturedMesh<Vertex3DN>>(TEXTURE_SHADER_LIGHT, GL_TRIANGLES, tex);
////	std::vector<Vertex3DN> vertices;
////	std::vector<unsigned int> indices;
////
////	vertices.push_back( Vertex3DN (-hw, 0, hh, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f));
////	vertices.push_back( Vertex3DN (-hw, 0, -hh, 0.0f, repeat.y, 0.0f, -1.0f, 0.0f));
////	vertices.push_back( Vertex3DN (hw, 0, -hh, repeat.x, repeat.y, 0.0f, -1.0f, 0.0f));
////	vertices.push_back( Vertex3DN (hw, 0, hh, repeat.x, 0.0f, 0.0f, -1.0f, 0.0f));
////	indices.push_back(0);
////	indices.push_back(1);
////	indices.push_back(2);
////	indices.push_back(2);
////	indices.push_back(3);
////	indices.push_back(0);
////	m->Init(vertices, indices);
////	m_meshes.push_back(m);
//}
//
//
//void MeshFactory::visit(Box3D& rect) {
//    float w = rect.width();
//    float d = rect.depth();
//    float h = rect.height();
//    glm::vec3 o = rect.GetOffset();
//    std::vector<VertexColor> vertices = {
//            {o.x, o.y, o.z+d, m_color.r, m_color.g, m_color.b, m_color.a},
//            {o.x+w, o.y, o.z+d, m_color.r, m_color.g, m_color.b, m_color.a},
//            {o.x+w, o.y+h, o.z+d, m_color.r, m_color.g, m_color.b, m_color.a},
//            {o.x, o.y+h, o.z+d, m_color.r, m_color.g, m_color.b, m_color.a},
//            {o.x, o.y, o.z, m_color.r, m_color.g, m_color.b, m_color.a},
//            {o.x+w, o.y, o.z, m_color.r, m_color.g, m_color.b, m_color.a},
//            {o.x+w, o.y+h, o.z, m_color.r, m_color.g, m_color.b, m_color.a},
//            {o.x, o.y+h, o.z, m_color.r, m_color.g, m_color.b, m_color.a},
//    };
//    std::vector<unsigned int> indices = {0, 1, 1,2,2,3,3,0,1,5,5,6,6,2,2,1,4,5,5,6,6,7,7,4,4,0,0,3,3,7,7,4};
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->Init(vertices, indices);
//    mesh->m_primitive = GL_LINES;
//    m_mesh = mesh;
//}
//
//void MeshFactory::visit(CompoundShape& shape) {
//
//    auto shapes = shape.GetShapes();
//    std::vector<VertexColor> vertices;
//    std::vector<unsigned int> indices;
//    unsigned int i{0};
//    unsigned int first = 0;
//    for (auto& shape : shapes) {
//        auto points = shape->getPoints();
//        glm::vec2 offset = shape->GetOffset();
//        size_t j = 0;
//        for (auto& p : points) {
//            vertices.emplace_back(VertexColor(p.x, p.y, m_z, m_color.g, m_color.r, m_color.b, m_color.a));
//            indices.push_back(i);
//            indices.push_back((j+1 >= points.size()) ? first : i+1);
//            i++;
//            j++;
//        }
//        first = i;
//    }
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->Init(vertices, indices);
//    mesh->m_primitive = GL_LINES;
//    m_mesh = mesh;
//}
//
//void MeshFactory::visit(Line& p) {
//    std::vector<VertexColor> vertices ;
//    std::vector<unsigned int> indices;
//    auto A = p.getA();
//    auto B = p.getB();
//    vertices.push_back({A.x, A.y, m_z, 1.0, 1.0, 1.0, 1.0});
//    vertices.push_back({B.x, B.y, m_z, 1.0, 1.0, 1.0, 1.0});
//    indices.push_back(0);
//    indices.push_back(1);
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->Init(vertices, indices);
//    mesh->m_primitive = GL_LINES;
//    m_mesh = mesh;
//}
//
//void MeshFactory::visit(Polygon& p) {
//    std::vector<VertexColor> vertices ;
//    std::vector<unsigned int> indices;
//    int n = p.GetVertexCount();
//    for (int i = 0; i < n; ++i) {
//        glm::vec2 v = p.GetVertex(i);
//        vertices.push_back({v.x, v.y, m_z, 1.0, 1.0, 1.0, 1.0});
//        indices.push_back(i);
//    }
//
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->Init(vertices, indices);
//    mesh->m_primitive = GL_LINE_LOOP;
//    m_mesh = mesh;
//}
//
//void MeshFactory::visit(PolyTri& p) {
//    std::vector<VertexColor> vertices ;
//    std::vector<unsigned int> indices;
//    const auto& points = p.getPoints();
//    int i = 0;
//    for (const auto& point : points) {
//        vertices.push_back({point.x, point.y, m_z, 1.0, 1.0, 1.0, 1.0});
//        indices.push_back(i++);
//    }
//    indices.push_back(0);
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->Init(vertices, indices);
//    mesh->m_primitive = GL_LINE_LOOP;
//    m_mesh = mesh;
//
//}
//
//void MeshFactory::visit(Circle& c) {
//    // number of points
//    int n = 20;
//    float dAngle = 2.0f * M_PI / n;
//    std::vector<VertexColor> vertices ;
//    std::vector<unsigned int> indices;
//    float radius = c.GetRadius();
//    glm::vec2 C= c.GetOffset();
//    for (int i = 0; i < n; ++i) {
//        float angle = dAngle * i;
//        vertices.push_back( { static_cast<GLfloat>(C.x + radius*cos(angle)), static_cast<GLfloat>(C.y + radius * sin(angle)), 0.0f, 1.0f, 1.0f, 1.0f, 1.0f });
//        indices.push_back(i);
//    }
//    indices.push_back(0);
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->Init(vertices, indices);
//    mesh->m_primitive = GL_LINE_STRIP;
//    m_mesh = mesh;
//}
//
//void MeshFactory::visit(Ellipse& e) {
//    // number of points
//    int n = 50;
//    float dAngle = 2.0f * M_PI / n;
//    std::vector<VertexColor> vertices ;
//    std::vector<unsigned int> indices;
//    glm::vec2 axes = e.GetSemiAxes();
//    glm::vec2 C= e.GetOffset();
//    float rx2 = axes.x * axes.x;
//    float ry2 = axes.y * axes.y;
//    float rxy = axes.x * axes.y;
//
//    for (int i = 0; i < n; ++i) {
//        float angle = dAngle * i;
//        float ca = cos(angle);
//        float sa = sin(angle);
//        float s = (rxy) / sqrt(ry2*ca*ca + rx2*sa*sa);
//        vertices.push_back( { static_cast<GLfloat>(C.x + s*cos(angle)), static_cast<GLfloat>(C.y + s * sin(angle)), 0.0f, 1.0f, 1.0f, 1.0f, 1.0f });
//        indices.push_back(i);
//    }
//    indices.push_back(0);
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->Init(vertices, indices);
//    mesh->m_primitive = GL_LINE_STRIP;
//    m_mesh = mesh;
//}
//
//void MeshFactory::visit(Poly& p) {
//    std::vector<VertexColor> vertices ;
//    std::vector<unsigned int> indices;
//
//    int n = p.getVertexCount();
//    for (int i = 0; i < n; ++i) {
//        glm::vec2 v = p.GetVertex(i);
//        vertices.push_back({v.x, v.y, m_z, 1.0, 1.0, 1.0, 1.0});
//        indices.push_back(i);
//        indices.push_back(i+1);
//    }
//    indices.back() = 0;
//    int offset = n;
//    const auto& holes = p.getHoles();
//    for (const auto& hole : holes) {
//        auto holePoly = hole.getPolygon();
//        n = holePoly->GetVertexCount();
//        for (int i = 0; i < n; ++i) {
//            glm::vec2 v = holePoly->GetVertex(i);
//            vertices.push_back({v.x, v.y, m_z, 1.0, 1.0, 1.0, 1.0});
//            indices.push_back(offset+i);
//            indices.push_back(offset+i+1);
//        }
//        indices.back() = offset;
//        offset += n;
//    }
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->Init(vertices, indices);
//    mesh->m_primitive = GL_LINES;
//    m_mesh = mesh;
//
////    int nPoly = p.GetPolygonCount();
////    std::vector<VertexColor> vertices ;
////    std::vector<unsigned int> indices;
////    int count = 0;
////    for (int i = 0; i < nPoly; ++i) {
////        auto poly = p.GetPolygon(i);
////        int nv = poly->GetVertexCount();
////        int first = count;
////        for (int j = 0; j < nv; ++j) {
////            glm::vec2 v = poly->GetVertex(j);
////            vertices.push_back({v.x, v.y, m_z, 1.0, 1.0, 1.0, 1.0});
////            indices.push_back(count++);
////            indices.push_back((j < nv-1) ? count : first);
////        }
////    }
////
////
////
////    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
////    mesh->Init(vertices, indices);
////    mesh->m_primitive = GL_LINES;
////    m_mesh = mesh;
//}
//
//void MeshFactory::visit(PolyLine& p) {
//
////    std::vector<VertexColor> vertices = {
////            {0.0f, 0.0f, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
////            {50, 0.0f, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
////            {50, 50, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
////            {0.0f, 50, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
////    };
////    std::vector<unsigned int> indices = {0, 1, 2, 3};
////    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
////    mesh->Init(vertices, indices);
////    mesh->m_primitive = GL_LINE_LOOP;
////    m_mesh = mesh;
//
//    std::vector<VertexColor> vertices ;
//    std::vector<unsigned int> indices;
//    auto& v = p.GetVertices();
//    auto& e = p.GetEdgeIndices();
//    for(auto& vertex : v){
//        vertices.push_back({vertex.x, vertex.y, m_z, 1.0, 1.0, 1.0, 1.0});
//    }
//    for(auto& edge : e){
//        indices.push_back(edge.first);
//        indices.push_back(edge.second);
//    }
//
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->Init(vertices, indices);
//    mesh->m_primitive = GL_LINES;
//    m_mesh = mesh;
//
//}
//
//
//
