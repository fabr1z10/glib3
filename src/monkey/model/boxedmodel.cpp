#include <monkey/model/boxedmodel.h>
#include <monkey/contour.h>

#include <iostream>

namespace py = pybind11;

BoxedModel::BoxedModel(std::shared_ptr<SpriteMesh> mesh) : SpriteModel(mesh) {}

BoxedModel::BoxedModel(const ITable &t) : SpriteModel(t) {

    float thickness = t.get<float>("thickness", 0.0f);
    float dz = 0.5f * thickness;
    bool model3d = (thickness > 0.0f);

    t.foreach<py::list>("boxes", [&] (py::list p) {
        float x0 = p[0].cast<float>();
        float y0 = p[1].cast<float>();
        float x1 = p[2].cast<float>();
        float y1 = p[3].cast<float>();
        float width = x1 - x0;
        float height = y1 - y0;
        auto rect = std::make_shared<Rect>(width, height, glm::vec3(x0, y0, 0.0f));
        this->addShape(rect);
    });

    auto anims = t.get<py::dict>("animations");
    for (auto anim : anims) {
        // get the box
        auto animId = anim.first.cast<std::string>();
        PyDict animData(anim.second.cast<py::dict>());
        // each animation might have a box
        if (animData.hasKey("box")) {
            int boxId = animData.get<int>("box");
            this->setAnimShape(animId, boxId);
        }
    }

    // read shape-casts



//        luabridge::LuaRef an = t.Get<luabridge::LuaRef>("animations");
//        // loop through animations
//        for (int i = 0; i < an.length(); ++i) {
//            luabridge::LuaRef at = an[i+1];
//            std::string anim = at["name"].cast<std::string>();
//            glm::vec4 box = LuaTable::Read<glm::vec4>(at["box"], glm::vec4(0.0f));
//            if (box != glm::vec4(0.0f)) {
//                pp->AddAnimationData(anim, Bounds{glm::vec3(box[0], box[1], box[0]), glm::vec3(box[2], box[3], box[2])});
//            }
//            luabridge::LuaRef fr = at["frames"];
//            for (int j = 0; j < fr.length(); ++j) {
//                luabridge::LuaRef a2 = fr[j + 1];
//                // get the shape associated to this frame
//                LuaTable table(a2);
//                if (box != glm::vec4(0.0f)) {
//                    if (table.HasKey("boxes")) {
//                        auto boxes = table.Get<luabridge::LuaRef>("boxes");
//                        if (boxes.length() == 1) {
//                            glm::vec4 box = LuaTable::Read<glm::vec4>(boxes[1]);
//                            std::shared_ptr<Shape> collisionShape;
//                            float width = box[2] - box[0];
//                            float height = box[3] - box[1];
//                            if (model3d) {
//                                collisionShape = std::make_shared<Box>(width, height, thickness,
//                                                                       glm::vec3(box[0], box[1], -dz));
//                            } else {
//                                collisionShape = std::make_shared<Rect>(width, height, glm::vec3(box[0], box[1], 0.0f));
//                            }
//                            pp->AddCollisionData(anim, j, collisionShape);
//                        }
//                    } else {
//                        // if no boxes field is specified for this frame, use the box at animation level
//                        std::shared_ptr<Shape> collisionShape;
//                        float width = box[2] - box[0];
//                        float height = box[3] - box[1];
//                        if (model3d) {
//                            collisionShape = std::make_shared<Box>(width, height, thickness,
//                                                                   glm::vec3(box[0], box[1], -dz));
//                        } else {
//                            collisionShape = std::make_shared<Rect>(width, height, glm::vec3(box[0], box[1], 0.0f));
//                        }
//                        pp->AddCollisionData(anim, j, collisionShape);
//                    }
//                } else {
//                    pp->AddCollisionData(anim, j, nullptr);
//                }
//
//                if (table.HasKey("attack")) {
//                    glm::vec4 attackBox = table.Get<glm::vec4>("attack");
//                    // attack box is a 4d vec {x, y, w, h} where x, y are the coords relative to the top left
//                    float w = attackBox[2];
//                    float h = attackBox[3];
//                    std::shared_ptr<Shape> attackShape;
//                    if (model3d) {
//                        attackShape = std::make_shared<Box>(w, h, thickness, glm::vec3(attackBox[0], attackBox[1], -dz));
//                    } else {
//                        attackShape = std::make_shared<Rect>(w, h, glm::vec3(attackBox[0], attackBox[1], 0.0f));
//                    }
//                    pp->AddAttackData(anim, j, attackShape);
//                    //attackTag = table.Get<int>("attack_tag");
//                }
//            }
//
//        }
//        pp->generateDebugMesh();
//        return pp;
//
//
//    }


}

void BoxedModel::addShape(std::shared_ptr<Shape> s) {
    m_shapes.push_back(s);
}

void BoxedModel::setAnimShape(const std::string &anim, int shapeId) {
    int fc = GetAnimInfo(anim)->frameCount;
    for (int i=0;i<fc; ++i) {
        m_boxInfo[std::make_pair(anim, i)] = shapeId;
    }
    m_maxBounds.ExpandWith(m_shapes[shapeId]->getBounds());
    m_animBounds[anim] = m_shapes[shapeId]->getBounds();
}

void BoxedModel::setShape(const std::string &anim, int frame, int shapeId) {
    m_boxInfo[std::make_pair(anim, frame)] = shapeId;
}

void BoxedModel::setShapeCast(const std::string &anim, int frame, int shapeId) {
    m_shapeCast[std::make_pair(anim, frame)] = shapeId;
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

std::shared_ptr<Shape> BoxedModel::getShape(const std::string & anim, int frame) {
    auto key = std::make_pair(anim, frame);
    auto box = m_boxInfo.find(key);
    if (box == m_boxInfo.end()) {
        return nullptr;
    }
    return m_shapes[box->second];
}

std::shared_ptr<Shape> BoxedModel::getShapeCast(const std::string & anim, int frame) {
    auto key = std::make_pair(anim, frame);
    auto box = m_shapeCast.find(key);
    if (box == m_shapeCast.end()) {
        return nullptr;
    }
    return m_shapes[box->second];
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