#include "monkey/components/character.h"
#include <monkey/entity.h>
#include <monkey/components/animator.h>
#include <GLFW/glfw3.h>
#include <monkey/math/raycast2d.h>

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
	m_useKeyboard = t.get<bool>("use_keyboard", false);
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

	//m_animator = m_entity->GetComponent<Animator>();
	if (m_useKeyboard) {
		m_input = m_entity->GetComponent<InputMethod>();
		if (m_input == nullptr) {
			GLIB_FAIL("player jump state requires a input method component!");
		}
		m_walkArea = m_entity->GetParent()->GetComponent<WalkArea>();
	}
	m_inputLastFrame = 0;
}

void CharacterController::turn(char dir) {
    m_dir = dir;
    auto canim = m_charAnimator->getAnim("idle", dir);
    std::string anim = "idle_" + std::string(1,dir == 'w' ? 'e' : dir);
    m_entity->SetFlipX(canim.second);//  dir == 'w');
    m_animator->setAnimation(canim.first);

}


void CharacterController::Update(double dt) {
	if (m_useKeyboard) {
		bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
		bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
		bool up = m_input->isKeyDown(GLFW_KEY_UP);
		bool down = m_input->isKeyDown(GLFW_KEY_DOWN);

		glm::vec3 move(0.0f);
		std::string anim;
		bool flipx = left;
		bool isMoving = false;
		if (left || right) {
			anim = "walk_e";
			move += glm::vec3(left ? -1.0f : 1.0f, 0.0f, 0.0f);
			isMoving = true;
			m_dir = 'e';
		}
		if (up || down) {
			if (!left && !right) {
				anim = up ? "walk_n" : "walk_s";
				m_dir = up ? 'n' : 's';
			}
			move += glm::vec3(0.0f, up ? 1.0f : -1.0f, 0.0f);
			isMoving = true;
		}
		if (isMoving) {
			m_inputLastFrame = 1;
			m_animator->setAnimation(anim);
			m_entity->SetFlipX(flipx);
			move = glm::normalize(move);
			float length = m_speed * dt;
			auto startPosition = m_entity->GetPosition();
			auto le = m_walkArea->checkMove(startPosition, move, length);
			move.x = abs(move.x);
			m_entity->MoveLocal(move * le);
		} else {
			if (m_inputLastFrame == 1) {
				m_inputLastFrame = 0;
				auto dir = m_dir == 'w' ? 'e' : m_dir;
				m_animator->setAnimation("idle_" + std::string(1, dir));
			}
		}




/*		bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
		bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
		bool up = m_input->isKeyDown(GLFW_KEY_UP);*/
	}

}