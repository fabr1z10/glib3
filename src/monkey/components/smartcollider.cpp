#include <monkey/components/smartcollider.h>
#include <monkey/components/animator.h>
#include <monkey/model/boxedmodel.h>

#include <monkey/model/basicmodel.h>
#include <monkey/components/statemachine.h>
#include <monkey/entity.h>
#include <monkey/components/multirenderer.h>
#include <monkey/meshfactory.h>


SmartCollider::~SmartCollider() {


}


SmartCollider::SmartCollider(const ITable & table) : ICollider(table), m_shapeEntity(nullptr), m_colliderRenderer(nullptr) {
    m_tag = table.get<int>("tag");
    m_flag = table.get<int>("flag");
    m_mask = table.get<int>("mask");
    m_castTag = table.get<int>("cast_tag", 0);
    m_castMask = table.get<int>("cast_mask", 0);

}

void SmartCollider::AddAttackTag(const std::string& anim, int tag, int mask) {
    m_attackInfo.insert(std::make_pair(anim, std::make_pair(tag, mask)));
}


Bounds SmartCollider::getAttackBounds() const {
    auto anim = m_animator->GetAnimation();
    int fr = m_animator->GetFrame();


    const auto& bi = m_model->getShapeCast(anim,fr);
    if (bi == nullptr) {
        return Bounds();
    }
    auto bounds = bi->getBounds();
    bounds.Transform(m_entity->GetWorldTransform());
    return bounds;

}


void SmartCollider::addStateCollisionDetails (const std::string& id, int flag, int mask, int tag) {
    m_collisionDetailsOverride[id] = SmartCollisionDetails {flag, mask, tag};
}



void SmartCollider::onFrameUpdate(Animator *a) {
    auto anim = a->GetAnimation();
    int fr = a->GetFrame();

    if (m_colliderRenderer != nullptr) {
		m_colliderRenderer->clearVisible();
		int shapeId = m_model->getShapeId(anim, fr);
		m_colliderRenderer->setVisible(shapeId);
		auto castShapeId = m_model->getShapeCastId(anim, fr);

		// now, check if I have an attack box
		if (castShapeId != -1) {
			auto castShape = m_model->shape(castShapeId);
			m_colliderRenderer->setVisible(castShapeId);

			auto t = m_entity->GetWorldTransform();
			//std::cout <<" **** hit ****\n";
			//std::cout << "character at position = " << t[3][0] << ", " << t[3][1] << " scale " << t[0][0] << "\n";
			auto e = m_engine->ShapeCast(castShape.get(), t, m_castMask);

			if (e.report.collide) {
				//std::cerr << "HIT!\n";
				auto rm = m_engine->GetResponseManager();
				if (rm == nullptr) {
					std::cerr << "no handler!\n";
				}
				auto handler = rm->GetHandler(m_castTag, e.entity->GetCollisionTag());
				if (handler.response != nullptr) {
					auto object = e.entity->GetObject();
					//std::cerr << "FOUND RESPONSE\n";
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
void SmartCollider::Start() {
    // a smart collider requires an animator
    m_animator = dynamic_cast<Animator*>(m_entity->GetComponent<IAnimator>());
    m_model = dynamic_cast<BoxedModel*>(m_animator->GetModel().get());
    //m_controllerBounds = m_model->getControllerBounds();
    m_animator->onFrameUpdate.Register(this, [&] (Animator* a) { this->onFrameUpdate(a); });
    ICollider::Start();


    // if debug is active, show currently active collision shapes
    if (m_debug) {
        auto shapeEntity = std::make_shared<Entity>();
        if (m_shapeEntity != nullptr) {
            m_entity->Remove(m_shapeEntity);
            m_shapeEntity = nullptr;
        }
        m_entity->AddChild(shapeEntity);
        m_shapeEntity = shapeEntity.get();
        auto renderer = std::make_shared<MultiRenderer>();
        MeshFactory mf;
        for (const auto &shape : m_model->getShapes()) {
            auto model = mf.createWireframe(shape.get(), glm::vec4(1.0f));
            renderer->addModel(model);
        }
        m_shapeEntity->AddComponent(renderer);
        m_colliderRenderer = renderer.get();
    }
//
//    //renderer->SetMeshInfo(0, 8);
    //m_entity->AddChild(c);
//    m_stateMachine = m_entity->GetComponent<StateMachine>();
}

IShape* SmartCollider::GetShape() {
    int frame = m_animator->GetFrame();
    std::string anim = m_animator->GetAnimation();
    // now with these info, I ask the model to give me the current shape
    return m_model->getShape(anim, frame).get();
}


int SmartCollider::setCollisionMask(int tag) {
    m_tag = tag;
	return tag;
}
int SmartCollider::GetCollisionTag() const {
    return m_tag;
}

int SmartCollider::GetCollisionFlag() const {

    return m_flag;
}

int SmartCollider::GetCollisionMask() const {
    return m_mask;
//    if (m_stateMachine == nullptr) {
//        return m_mask;
//    }
//    std::string currentState = m_stateMachine->GetState();
//    auto it = m_collisionDetailsOverride.find(currentState);
//    if (it == m_collisionDetailsOverride.end()) {
//        return m_mask;
//    }
//    return it->second.mask;
}

// this returns the max bounds and is used by the collision engine
// to locate the item in teh collision grid. However, this should not be used in the collider 2d!!!
Bounds SmartCollider::GetStaticBoundsI() const {
    return m_model->GetMaxBounds();
}

Bounds SmartCollider::GetDynamicBoundsI() const {
    std::string anim = m_animator->GetAnimation();
    auto bounds = m_model->GetAnimBounds(anim);
//    bounds.min.z = bounds.min.x;
//    bounds.max.z = bounds.max.x;
    return bounds;
}
std::type_index SmartCollider::GetType() {
    return std::type_index(typeid(ICollider));
}
