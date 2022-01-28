#include <monkey/model/boxedmodel.h>
#include <monkey/engine.h>
#include <monkey/math/shapes/compound.h>

#include <iostream>
#include <monkey/math/shapes3d/aabb.h>

namespace py = pybind11;

//BoxedModel::BoxedModel(std::shared_ptr<SpriteMesh> mesh) : SpriteModel(mesh) {}

//
//std::vector<std::shared_ptr<IShape>> BoxedModel::getAttackShapes() const {
//
//    std::vector<std::shared_ptr<IShape>> shapes;
//    for (const auto& m : m_shapeCast) {
//        shapes.push_back(m_shapes[m.second]);
//    }
//    return shapes;
//}

BoxedModel::BoxedModel(const ITab& t) : SpriteModel(t) {

	auto thick= Engine::get().getVariable<float>("data.globals.thickness");
    auto thickness = t.get<float>("thickness", 0.0f);
    auto halfThickness = 0.5*thickness;
	if (t.has("boxes")) {
	    t.foreach("boxes", [&] (const ITab& box) {
            auto pp = box.as<std::vector<float>>();
            int nboxes = pp.size() / 4;
            std::shared_ptr<IShape> shape;
            if (nboxes == 1) {
                float width = pp[2] - pp[0];
                float height = pp[3] - pp[1];
                //shape = std::make_shared<Rect>(width, height, glm::vec3(pp[0], pp[1], 0.0f));
                shape = std::make_shared<AABB>(glm::vec3(width, height, thickness), glm::vec3(pp[0], pp[1], -halfThickness));
            } else {
                auto cs = std::make_shared<CompoundShape>();
                for (int i = 0; i < pp.size(); i+= 4) {
                    float width = pp[i+2] - pp[i];
                    float height = pp[i+3] - pp[i+1];
                    //auto rect = std::make_shared<Rect>(width, height, glm::vec3(pp[i], pp[i+1], 0.0f));
                    auto rect = std::make_shared<AABB>(glm::vec3(width, height, thickness), glm::vec3(pp[i], pp[i+1], -halfThickness));
                    cs->addShape(rect);
                }
                shape = cs;
            }
            addShape(shape);
	    });
	}

	//m_attackDistance = std::numeric_limits<float>::infinity();
    //auto anims = t["animations"].as<YAML::Node>();
    float attackMin = -std::numeric_limits<float>::infinity();
    float attackMax = std::numeric_limits<float>::infinity();
    t.foreach("animations", [&] (const std::string& animId, const ITab& anim) {
        // each animation might have a box
        auto animBoxId = anim.get<int>("box", -1);

        setAnimShape(animId, animBoxId);

        // find attack position for this animation, if any
        bool isAttackingAnim = false;

        int frameId = 0;
        // for each animation, find the xmin and xmax
        float xAttackMin = std::numeric_limits<float>::infinity();
        float xAttackMax = -std::numeric_limits<float>::infinity();
        anim.foreach("frames", [&] (const ITab& element) {
            int box = element.get<int>("box", -1);
            int attack = element.get<int>("attack", -1);
            if (box != -1) {
                this->setFrameShape(animId, frameId, box);
            }
            if (attack != -1) {
                isAttackingAnim = true;
                auto shape = m_shapes[attack]->getBounds();
                float currentFrameMin = shape.min.x;
				float currentFrameMax = shape.max.x;
                xAttackMin = std::min(xAttackMin, currentFrameMin);
                xAttackMax = std::max(xAttackMin, currentFrameMax);
                this->setShapeCast(animId, frameId, attack);
            }
            frameId++;

        });

        if (isAttackingAnim) {
            attackMin = std::min(attackMin, xAttackMin);
            attackMax = std::max(attackMax, xAttackMax);
        }
    });
    m_attackRange = glm::vec2(std::max(0.0f, attackMin), std::max(0.0f, attackMax));
}

void BoxedModel::addShape(std::shared_ptr<IShape> s) {
    m_shapes.push_back(s);
    //m_maxBounds.ExpandWith(s->getBounds());
}

void BoxedModel::setAnimShape(const std::string &anim, int shapeId) {
    int fc = m_animInfos.at(anim).frames.size();
    for (int i=0;i<fc; ++i) {
        m_boxInfos[std::make_pair(anim, i)] = BoxInfo{shapeId, -1};
    }
    if (shapeId != -1) {
        m_maxBounds.ExpandWith(m_shapes[shapeId]->getBounds());
        m_animBounds[anim] = m_shapes[shapeId]->getBounds();
    }
}


void BoxedModel::setFrameShape(const std::string &anim, int frame, int shapeId) {
    m_boxInfos[std::make_pair(anim, frame)].collisionShape = shapeId;
    m_maxBounds.ExpandWith(m_shapes[shapeId]->getBounds());
    m_animBounds[anim] = m_shapes[shapeId]->getBounds();

}


void BoxedModel::setShape(const std::string &anim, int frame, int shapeId) {
    m_boxInfos[std::make_pair(anim, frame)].collisionShape = shapeId;
}

void BoxedModel::setShapeCast(const std::string &anim, int frame, int shapeId) {
    m_boxInfos[std::make_pair(anim, frame)].attackShape = shapeId;
}

//void BoxedModel::AddAnimationData(const std::string &anim, Bounds b) {
//    m_animBounds.insert(std::make_pair(anim, b));
//}
Bounds BoxedModel::GetAnimBounds(const std::string & name) const {
    auto it = m_animBounds.find(name);
    if (it == m_animBounds.end()) {
        return Bounds();
    }

    return it->second;
}
//
//void BoxedModel::AddCollisionData(const std::string &anim
//                             , int frame
//                             , std::shared_ptr<Shape> collision) {
//                             //, std::shared_ptr<Shape> attack) {
//    auto key = std::make_pair(anim, frame);
//    if (collision != nullptr) {
//        if (m_boxInfo.empty()) {
//            m_maxBounds = collision->getBounds();
//        } else {
//            m_maxBounds.ExpandWith(collision->getBounds());
//        }
//    }
//    m_boxInfo.insert(std::make_pair(key, BoxInfo(collision))); //, attack})));
//}
//
//void BoxedModel::AddAttackData(const std::string &anim, int frame, std::shared_ptr<Shape> attack) {
//    m_boxInfo.at(std::make_pair(anim, frame)).m_attackShape = attack;
//}

//int BoxedModel::getShapeId(const std::string & anim, int frame) {
//    auto key = std::make_pair(anim, frame);
//    auto box = m_boxInfo.find(key);
//    if (box == m_boxInfo.end()) {
//        return -1;
//    }
//    return box->second;
//}

std::shared_ptr<IShape> BoxedModel::shape(int id) {
    return m_shapes[id];
}

BoxInfo & BoxedModel::getBoxInfo(const std::string& anim, int frame) {
    auto key = std::make_pair(anim, frame);
    return m_boxInfos.at(key);
}

//int BoxedModel::getShapeCastId(const std::string & anim, int frame) {
//    auto key = std::make_pair(anim, frame);
//    auto box = m_shapeCast.find(key);
//    if (box == m_shapeCast.end()) {
//        return -1;
//    }
//    return box->second;
//
//}
//
std::shared_ptr<IShape> BoxedModel::getShape(const std::string & anim, int frame) {
    auto key = std::make_pair(anim, frame);
    auto box = m_boxInfos.at(key).collisionShape;
    if (box == -1) {
        return nullptr;
    }
    return m_shapes[box];
}

std::shared_ptr<IShape> BoxedModel::getShapeCast(const std::string & anim, int frame) {
    auto key = std::make_pair(anim, frame);
    auto box = m_boxInfos.at(key).attackShape;
    if (box == -1) {
        return nullptr;
    }
    return m_shapes[box];
}

//int BoxedModel::addShapeMesh(const std::shared_ptr<Shape>& shape, int& pc, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices) {
//    int count = 0;
//    if (shape != nullptr) {
//        auto contour = Contour::CreateContour(shape.get());
//        vertices.emplace_back(VertexColor(contour[0].x, contour[0].y, contour[0].z, 1.0f, 0.0f, 0.0f, 1.0f));
//        for (int i = 1; i< contour.size(); ++i) {
//            vertices.emplace_back(VertexColor(contour[i].x, contour[i].y, contour[i].z, 1.0f, 0.0f, 0.0f, 1.0f));
//            indices.emplace_back(pc++);
//            indices.emplace_back(pc);
//            count += 2;
//        }
//        pc++;
//    }
//
//    return count;
//}
//
//void BoxedModel::generateDebugMesh() {
//    std::vector<VertexColor> vertices ;
//    std::vector<unsigned int> indices;
//    int pc = 0;
//    int offset = 0;
//    for (auto& m : m_boxInfo) {
//        m.second.offset = offset;
//        m.second.count = 0;
//        m.second.count += addShapeMesh(m.second.m_shape, pc, vertices, indices);
//        m.second.count += addShapeMesh(m.second.m_attackShape, pc, vertices, indices);
//        offset += m.second.count;
//    }
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->m_primitive = GL_LINES;
//    mesh->Init(vertices, indices);
//    m_collisionMesh = mesh;
//
//
//
//
//}