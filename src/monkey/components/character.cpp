#include "monkey/components/character.h"
#include <monkey/entity.h>
#include <monkey/components/animator.h>

std::pair<std::string, bool> ICharAnimator::getAnim(const std::string &anim, char dir) {
	switch (dir) {
		case 'e':
			return getAnim(anim, glm::vec2(1.0f, 0.0f));
		case 'w':
			return getAnim(anim, glm::vec2(-1.0f, 0.0f));
		case 'n':
			return getAnim(anim, glm::vec2(0.0f, 1.0f));
		case 's':
			return getAnim(anim, glm::vec2(0.0f, -1.0f));
	}

}

std::pair<std::string, bool> WalkAni4::getAnim(const std::string &anim, glm::vec2 move) {
	std::stringstream stream;
	bool flipH = false;
	stream << anim;
	if (fabs(move.x) > fabs(move.y)) {
		stream << "_e";
		flipH = move.x < 0;
	} else {
		stream << (move.y > 0 ? "_n" : "_s");
	}
	return std::make_pair(stream.str(), flipH);
}

std::pair<std::string, bool> WalkAni2::getAnim(const std::string &anim, glm::vec2 move) {
	return std::make_pair(anim, move.x < 0);
}

CharacterController::CharacterController(const ITab &t) : Component(t) {
    m_dir = t.get<std::string>("dir")[0];
    m_speed = t.get<float>("speed");
    m_textOffset = t.get<glm::vec2>("text_offset");
    m_textColor = t.get<glm::vec4>("text_color");
    m_textColor /= 255.0f;
	auto ways = t.get<int>("ways", 4);
	if (ways == 4) {
		m_charAnimator = std::make_unique<WalkAni4>();
	} else {
		m_charAnimator = std::make_unique<WalkAni2>();
	}
}

std::pair<std::string, bool> CharacterController::getAnim(const std::string &anim, glm::vec2 move) {
	return  m_charAnimator->getAnim(anim, move);
}

void CharacterController::Start() {
    m_animator = dynamic_cast<AnimationRenderer*>(m_entity->GetComponent<Renderer>());
    if (m_animator != nullptr) {
		//GLIB_FAIL("animator required");
		turn(m_dir);
    }

}

void CharacterController::turn(char dir) {
    m_dir = dir;
    auto canim = m_charAnimator->getAnim("idle", dir);
    std::string anim = "idle_" + std::string(1,dir == 'w' ? 'e' : dir);
    m_entity->SetFlipX(canim.second);//  dir == 'w');
    m_animator->setAnimation(canim.first);

}
