#pragma once

#include <monkey/assets/model.h>
#include <string>

#include <box2d/box2d.h>

enum RenderType {
    FILL, WIREFRAME
};

class ModelFactory {

public:
    // create a rectangular image, having given width and height. If width or height are both zero, the image size
    // matches that of the image in pixel. If only one has a value, and the other is 0, the other is computed in order
    // to maintain the aspect ratio of the image. Repx and repy give how many texture repetition you want along x and y axis. 1 is default.
    static std::shared_ptr<Model> quad(const std::string& imagePath, float width = 0.0f, float height = 0.0f,
                                 float repx = 1.0f, float repy = 1.0f);
    static std::shared_ptr<Model> polygon(const ITab&);
	static std::shared_ptr<Model> prism(const ITab&);
	static std::shared_ptr<Model> shape(const ITab&);

	static std::shared_ptr<Model> _rect(const ITab&);
	static std::shared_ptr<Model> _quad(const ITab&);
    static std::shared_ptr<Model> rect(float width, float height, glm::vec2 offset,
                                       RenderType rtype, glm::vec4 color, const std::string& tex = "", glm::vec2 repeat = glm::vec2(1.0f, 1.0f),
                                       glm::vec2 scale = glm::vec2(1.0f, 1.0f));
    // create a shape from a polygon
    static std::shared_ptr<Model> _tiled(const ITab&);
    //static std::shared_ptr<IMesh> b2Poly(b2PolygonShape& shape, glm::vec4 color);
	static std::shared_ptr<IMesh> _mesh(const ITab&);

    static std::shared_ptr<Model> _box3DColor(const ITab&);

	static std::shared_ptr<Model> _cube3D(const ITab&);
private:
    static VertexColor get1(float* raw) {
        return VertexColor(raw[0], raw[1], 0.0f, raw[2], raw[3], raw[4], raw[5]);
    }

    static Vertex3D get2(float* raw) {
        return Vertex3D(raw[0], raw[1], 0.0f, raw[2], raw[3], raw[4], raw[5], raw[6], raw[7]);
    }

    template<typename Vertex>
    static void getPolyVerts(const ITab& t, std::vector<float>& in, std::vector<Vertex>& out, std::vector<std::vector<glm::vec2>>& points,
        int vertSize, std::function<Vertex(float*)> f) {
        std::vector<glm::vec2> outline;
        for (size_t i = 0; i < in.size(); i += vertSize) {
            outline.emplace_back(in[i], in[i + 1]);
            out.emplace_back(f(&in[i]));
        }
        points.push_back(outline);
        if (t.has("holes")) {
            t.foreach("holes", [&](const ITab &t) {
                auto ch = t.as<std::vector<float>>();
                std::vector<glm::vec2> h;
                for (size_t i = 0; i < ch.size(); i += vertSize) {
                    h.emplace_back(ch[i], ch[i + 1]);
                    out.emplace_back(f(&ch[i]));
                }
                points.push_back(h);
            });
        }
    }
};