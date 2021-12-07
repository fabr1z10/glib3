//#include <monkey/components/controllerflat.h>
//#include <monkey/engine.h>
//#include <monkey/monkey.h>
//
//using namespace glm;
//
//ControllerFlat::ControllerFlat(const ITab&t) {
//	m_horizontalRayCount = t.get<int>("hor_rays", 4);
//	m_verticalRayCount = t.get<int>("vert_rays", 4);
//	m_skinWidth = t.get<float>("skinWidth", .015f);
//	m_mask = t.get<int>("mask");
//	m_size = t.get<glm::vec2>("size");
//	m_horizontalRaySpacing = (2.0f * m_size[1]) / (m_horizontalRayCount - 1);
//	m_verticalRaySpacing = (2.0f * m_size[0]) / (m_verticalRayCount - 1);
//}
//
//void ControllerFlat::drawShape() {
//
//}
//void ControllerFlat::Start() {
//	m_collision = Engine::get().GetRunner<ICollisionEngine>();
//	if (m_collision == nullptr)
//	GLIB_FAIL("Controller2D requires a collision engine running!");
//}
//
//void ControllerFlat::Begin() {
//
//}
//
//void ControllerFlat::HorizontalCollisions(glm::vec2 &velocity) {
//	std::cerr << "hor coll s: " << velocity.x << "\n";
//	bool flipx = m_entity->GetFlipX();
//	bool facingLeft = (flipx && velocity.x > 0) || (!flipx && velocity.x < 0);
//	float directionX = facingLeft ? -1.0 : 1.0;
//	float rayLength = fabs(velocity.x) + m_skinWidth;
//
//	glm::vec2 pos = m_entity->GetPosition();
//	vec2 r0 = pos + glm::vec2(facingLeft ? -m_size[0] : m_size[0], -m_size[1]);
//
//	for (int i = 0; i < m_horizontalRayCount; i++) {
//		vec2 rayOrigin = r0 + vec2(0.0f, i * m_horizontalRaySpacing);
//		RayCastHit hit = m_collision->Raycast(glm::vec3(rayOrigin, 0.0f), monkey::right * directionX, rayLength, m_mask);
//		if (hit.collide) {
//			velocity.x = (hit.length - m_skinWidth) * sign(velocity.x);
//			rayLength = hit.length;
//		}
//	}
//	std::cerr << "hor coll e: " << velocity.x << "\n";
//}
//
//void ControllerFlat::Move(glm::vec3& delta) {
//	glm::vec2 dx(delta);
//	float scale = m_entity->GetScale();
//	if (dx != vec2(0.0f)) {
//		// try first going horizontal
//		if (!isEqual(dx.x, 0.0f))
//			HorizontalCollisions(dx);
//		if (!isEqual(dx.y, 0.0f))
//			VerticalCollisions(dx);
//		glm::vec2 actualMove = dx / scale;
//		m_entity->MoveLocal(glm::vec3(actualMove.x, actualMove.y, 0));
//	}
//}
//
//
//void ControllerFlat::VerticalCollisions(glm::vec2& velocity) {
//	float directionY = sign(velocity.y);
//	float rayLength = std::abs(velocity.y) + m_skinWidth;
//	Entity* m_obstacle = nullptr;
//	float velx = velocity.x * (m_entity->GetFlipX() ? -1.0f : 1.0f);
//	glm::vec2 pos = m_entity->GetPosition();
//	vec2 r0 = pos + vec2(-m_size[0], directionY > 0 ? m_size[1] : -m_size[1]);
//	for (int i = 0; i < m_verticalRayCount; i++) {
//		vec2 rayOrigin = r0 + vec2(1,0) * (velx + i * m_verticalRaySpacing);
//		//rayOrigin += vec2(i * m_verticalRaySpacing + velx, 0) ;
//		RayCastHit hit = m_collision->Raycast(vec3(rayOrigin, 0.0f), monkey::up * directionY, rayLength, m_mask);
//		if (hit.collide) {
//			velocity.y = (hit.length - m_skinWidth) * directionY;
//			rayLength = hit.length;
//		}
//	}
//}
//
