#include <monkey/components/smartcollider.h>
#include <monkey/components/spriterenderer.h>
#include <monkey/model/boxedmodel.h>

#include <monkey/assets/model.h>
#include <monkey/components/statemachine.h>
#include <monkey/entity.h>
#include <monkey/meshfactory.h>
#include <monkey/mesh.h>
#include <monkey/components/animrenderer.h>
#include <monkey/collisionengine.h>

SmartColliderRenderer::SmartColliderRenderer(
        std::shared_ptr<Model> model,
        const std::vector<std::pair<unsigned int, unsigned int>> & info,
        BoxedModel * boxedModel,
        SpriteRenderer * renderer) : Renderer(model), m_boxedModel(boxedModel), m_renderer(renderer), m_shapeInfo(info) {

}

void SmartColliderRenderer::Draw(Shader * shader) {
    if (shader->getShaderType() == COLOR_SHADER) {

        auto anim = m_renderer->getAnimation();
        auto frame = m_renderer->getFrame();
        const auto &boxInfo = m_boxedModel->getBoxInfo(anim, frame);
        //m_model->getMesh(0)->draw(shader, 0, 0);
        if (boxInfo.collisionShape != -1) {
            const auto &pair = m_shapeInfo[boxInfo.collisionShape];
            m_model->getMesh(0)->draw(shader, pair.first, pair.second);
        }
        if (boxInfo.attackShape != -1) {
            const auto &pair = m_shapeInfo[boxInfo.attackShape];
            m_model->getMesh(0)->draw(shader, pair.first, pair.second);
        }
    }
}

void SmartColliderRenderer::Start() {

}

std::type_index SmartColliderRenderer::GetType() {
    return std::type_index(typeid(Renderer));
}

SmartCollider::~SmartCollider() = default;


SmartCollider::SmartCollider(const ITab& table) : ICollider(table), m_shapeEntity(nullptr), m_colliderRenderer(nullptr) {

    m_castTag = table.get<int>("cast_tag", 0);
    m_castMask = table.get<int>("cast_mask", 0);

}

void SmartCollider::AddAttackTag(const std::string& anim, int tag, int mask) {
    m_attackInfo.insert(std::make_pair(anim, std::make_pair(tag, mask)));
}


Bounds SmartCollider::getAttackBounds() const {
//    auto anim = m_animator->GetAnimation();
//    int fr = m_animator->GetFrame();
//
//
//    const auto& bi = m_model->getShapeCast(anim,fr);
//    if (bi == nullptr) {
//        return Bounds();
//    }
//    auto bounds = bi->getBounds();
//    bounds.Transform(m_entity->GetWorldTransform());
//    return bounds;

}


void SmartCollider::addStateCollisionDetails (const std::string& id, int flag, int mask, int tag) {
    m_collisionDetailsOverride[id] = SmartCollisionDetails {flag, mask, tag};
}


void SmartCollider::Update(double) {
    auto animId = m_animator->getAnimation();
    auto frame = m_animator->getFrame();
    auto box = m_model->getShapeCast(animId, frame);
    bool hit = false;
    if (box != nullptr) {
        //std::cerr << "qui\n";
        auto t = m_entity->GetWorldTransform();
        auto e = m_engine->ShapeCast(box.get(), t, m_castMask);
        if (e.report.collide) {
            hit = true;
            if (e.entity != m_lastHit) {
                m_lastHit = e.entity;
                auto rm = m_engine->GetResponseManager();
                if (rm == nullptr) {
                    std::cerr << "no handler!\n";
                } else {
                    auto object = e.entity->GetObject();
                    auto handler = rm->GetHandler(m_castTag, e.entity->GetCollisionTag());
                    if (handler.response != nullptr) {
                        std::cerr << "FOUND RESPONSE\n";
                        //m_stateMachine->getCurrentState()->onCollide();
                        if (handler.flip) {
                            handler.response->onStart(object, m_entity, e.report);
                        } else {
                            handler.response->onStart(m_entity, object, e.report);
                        }
                    }
                }
            }
        }
    }
    if (!hit) {
        m_lastHit = nullptr;
    }
////
////			if (e.report.collide) {
////				//std::cerr << "HIT!\n";
////				auto rm = m_engine->GetResponseManager();
////				if (rm == nullptr) {
////					std::cerr << "no handler!\n";
////				}
////				auto handler = rm->GetHandler(m_castTag, e.entity->GetCollisionTag());
////				if (handler.response != nullptr) {
////					auto object = e.entity->GetObject();
////					//std::cerr << "FOUND RESPONSE\n";
////					if (handler.flip) {
////						handler.response->onStart(object, m_entity, e.report);
////					} else {
////						handler.response->onStart(m_entity, object, e.report);
////					}
////				}
////			}



}

//void SmartCollider::onFrameUpdate(Animator *a) {
////    auto anim = a->GetAnimation();
////    int fr = a->GetFrame();
//
////    if (m_colliderRenderer != nullptr) {
////		m_colliderRenderer->clearVisible();
////		int shapeId = m_model->getShapeId(anim, fr);
////		m_colliderRenderer->setVisible(shapeId);
////		auto castShapeId = m_model->getShapeCastId(anim, fr);
////
////		// now, check if I have an attack box
////		if (castShapeId != -1) {
////			auto castShape = m_model->shape(castShapeId);
////			m_colliderRenderer->setVisible(castShapeId);
////
////			auto t = m_entity->GetWorldTransform();
////			//std::cout <<" **** hit ****\n";
////			//std::cout << "character at position = " << t[3][0] << ", " << t[3][1] << " scale " << t[0][0] << "\n";
////			auto e = m_engine->ShapeCast(castShape.get(), t, m_castMask);
////
////			if (e.report.collide) {
////				//std::cerr << "HIT!\n";
////				auto rm = m_engine->GetResponseManager();
////				if (rm == nullptr) {
////					std::cerr << "no handler!\n";
////				}
////				auto handler = rm->GetHandler(m_castTag, e.entity->GetCollisionTag());
////				if (handler.response != nullptr) {
////					auto object = e.entity->GetObject();
////					//std::cerr << "FOUND RESPONSE\n";
////					if (handler.flip) {
////						handler.response->onStart(object, m_entity, e.report);
////					} else {
////						handler.response->onStart(m_entity, object, e.report);
////					}
////				}
////			}
////		}
////	}
//
//
//}
void SmartCollider::Start() {
    // a smart collider requires an animator
    m_animator = dynamic_cast<SpriteRenderer*>(m_entity->GetComponent<Renderer>());
    m_model = dynamic_cast<BoxedModel*>(m_animator->GetModel());
    //m_controllerBounds = m_model->getControllerBounds();
    //m_animator->onFrameUpdate.Register(this, [&] (Animator* a) { this->onFrameUpdate(a); });
    ICollider::Start();


    // if debug is active, show currently active collision shapes
    if (m_debug) {
        MeshFactory mf;
        std::vector<VertexColor> vertices;
        std::vector<unsigned> indices;
        std::vector<std::pair<unsigned, unsigned>> shapeInfo;
        for (const auto &shape : m_model->getShapes()) {
            unsigned offset = indices.size();
            mf.j2(shape.get(), vertices, indices, glm::vec4(1.0f,0,0,1));
            unsigned count = indices.size() - offset;
            shapeInfo.push_back(std::make_pair(offset, count));
        }
        auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
        mesh->Init(vertices, indices);
        mesh->m_primitive = GL_LINES;
        auto model = std::make_shared<Model>();
        model->addMesh(mesh);
        auto shapeEntity = std::make_shared<Entity>();
        if (m_shapeEntity != nullptr) {
            m_entity->Remove(m_shapeEntity);
            m_shapeEntity = nullptr;
        }
        auto renderer = std::make_shared<SmartColliderRenderer>(model, shapeInfo, m_model, m_animator);
        renderer->setModel(model);

        shapeEntity->AddComponent(renderer);
        //shapeEntity->AddComponent(model->makeRenderer(model));

        m_entity->AddChild(shapeEntity);

//
//        m_entity->AddChild(shapeEntity);
//        m_shapeEntity = shapeEntity.get();
//        auto renderer = std::make_shared<Renderer>();
//        MeshFactory mf;
//        for (const auto &shape : m_model->getShapes()) {
//            auto model = mf.createWireframe(shape.get(), glm::vec4(1.0f));
//            renderer->addModel(model);
//        }
//        m_shapeEntity->AddComponent(renderer);
//        m_colliderRenderer = renderer.get();
    }
//
//    //renderer->SetMeshInfo(0, 8);
    //m_entity->AddChild(c);
//    m_stateMachine = m_entity->GetComponent<StateMachine>();
}

IShape* SmartCollider::GetShape() {
    int frame = m_animator->getFrame();
    std::string anim = m_animator->getAnimation();
    // now with these info, I ask the model to give me the current shape
    return m_model->getShape(anim, frame).get();
}


int SmartCollider::setCollisionMask(int tag) {
    m_tag = tag;
	return tag;
}


// this returns the max bounds and is used by the collision engine
// to locate the item in teh collision grid. However, this should not be used in the collider 2d!!!
Bounds SmartCollider::GetStaticBoundsI() const {
    return m_model->GetMaxBounds();
}

Bounds SmartCollider::GetDynamicBoundsI() const {
    std::string anim = m_animator->getAnimation();
    auto bounds = m_model->GetAnimBounds(anim);
//    bounds.min.z = bounds.min.x;
//    bounds.max.z = bounds.max.x;
    return bounds;
}
std::type_index SmartCollider::GetType() {
    return std::type_index(typeid(ICollider));
}

glm::vec2 SmartCollider::getAttackDistance() const {
    return m_model->getAttackDistance();
}