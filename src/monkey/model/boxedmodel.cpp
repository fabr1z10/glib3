#include <monkey/model/boxedmodel.h>
#include <monkey/contour.h>

#include <iostream>

namespace py = pybind11;

BoxedModel::BoxedModel(std::shared_ptr<SpriteMesh> mesh) : SpriteModel(mesh) {}


std::vector<std::shared_ptr<IShape>> BoxedModel::getAttackShapes() const {

    std::vector<std::shared_ptr<IShape>> shapes;
    for (const auto& m : m_shapeCast) {
        shapes.push_back(m_shapes[m.second]);
    }
    return shapes;
}

BoxedModel::BoxedModel(const YAML::Node &t) : SpriteModel(t) {

	if (t["boxes"]) {
		const auto boxes = t["boxes"].as<std::vector<YAML::Node>>();
		for (const auto &box : boxes) {
			auto pp = box.as<std::vector<float>>();
			int nboxes = pp.size() / 4;
			nboxes = 1;
			std::shared_ptr<IShape> shape;
			for (int i = 0; i < nboxes; ++i) {
				float width = pp[2] - pp[0];
				float height = pp[3] - pp[1];
				shape = std::make_shared<Rect>(width, height, glm::vec3(pp[0], pp[1], 0.0f));
			}
			addShape(shape);
		}
	}


    auto anims = t["animations"].as<YAML::Node>();
    for (auto anim : anims) {
        // get the box
        auto animId = anim.first.as<std::string>();
        auto animData = anim.second;
        // each animation might have a box
        if (animData["box"]) {
            int boxId = animData["box"].as<int>();
            this->setAnimShape(animId, boxId);
        }

        if (animData["elements"]) {
            auto frames = animData["elements"].as<std::vector<YAML::Node>>();
            int frameId = 0;
            for (auto frame : frames) {
                int box = frame["box"].as<int>(-1);;
                int attack = frame["attack"].as<int>(-1);
                if (box != -1) {
                    this->setFrameShape(animId, frameId, box);
                }
                if (attack != -1) {
                    this->setShapeCast(animId, frameId, attack);
                }
                frameId++;
            }

        }
    }
}

void BoxedModel::addShape(std::shared_ptr<IShape> s) {
    m_shapes.push_back(s);
    m_maxBounds.ExpandWith(s->getBounds());
}

void BoxedModel::setAnimShape(const std::string &anim, int shapeId) {
    int fc = GetAnimInfo(anim)->frameCount;
    for (int i=0;i<fc; ++i) {
        m_boxInfo[std::make_pair(anim, i)] = shapeId;
    }
    m_maxBounds.ExpandWith(m_shapes[shapeId]->getBounds());
    m_animBounds[anim] = m_shapes[shapeId]->getBounds();
}


void BoxedModel::setFrameShape(const std::string &anim, int frame, int shapeId) {
    m_boxInfo[std::make_pair(anim, frame)] = shapeId;
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

int BoxedModel::getShapeId(const std::string & anim, int frame) {
    auto key = std::make_pair(anim, frame);
    auto box = m_boxInfo.find(key);
    if (box == m_boxInfo.end()) {
        return -1;
    }
    return box->second;
}

std::shared_ptr<IShape> BoxedModel::shape(int id) {
    return m_shapes[id];
}

int BoxedModel::getShapeCastId(const std::string & anim, int frame) {
    auto key = std::make_pair(anim, frame);
    auto box = m_shapeCast.find(key);
    if (box == m_shapeCast.end()) {
        return -1;
    }
    return box->second;

}

std::shared_ptr<IShape> BoxedModel::getShape(const std::string & anim, int frame) {
    auto key = std::make_pair(anim, frame);
    auto box = m_boxInfo.find(key);
    if (box == m_boxInfo.end()) {
        return nullptr;
    }
    return m_shapes[box->second];
}

std::shared_ptr<IShape> BoxedModel::getShapeCast(const std::string & anim, int frame) {
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