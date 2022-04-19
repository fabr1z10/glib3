#include <monkey/activities/showmessage.h>
#include <monkey/engine.h>
#include <monkey/textmesh.h>
#include <monkey/components/renderer.h>
#include <glm/gtx/transform.hpp>
#include <monkey/model/textmodel.h>
#include <monkey/model/factory.h>

ShowMessage::ShowMessage(const ITab& t) {
    m_actor = -1;
    m_message = t.get<std::string>("text");
    m_font = t.get<std::string>("font");
    m_size = t.get<float>("size", 8.0f);
    m_color = t.get<glm::vec4>("color");
    m_outlineColor = t.get<glm::vec4>("outline_color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    //m_color /= 255.0f;
    //m_outlineColor /= 255.0f;

    m_align = static_cast<TextAlignment>(t.get<int>("align", TextAlignment::BOTTOM));
    m_offset = t.get<glm::vec2>("offset", glm::vec2(0.0f));
    m_time = t.get<float>("time", 1.0f);
    m_pos = t.get<glm::vec3>("pos");
	m_endOnClick = t.get<bool>("end_on_click", false);
	m_outline = t.get<bool>("outline", false);
	m_box = t.get<bool>("box", false);
	m_padding = t.get<glm::vec2>("padding", glm::vec2(0.0f));
	m_innerTexture = t.get<std::string>("inner_texture", "");
	m_borderTexture = t.get<std::string>("border_texture", "");
	m_maxWidth = t.get<float>("max_width", 1000.0f);
	m_outlineThickness = t.get<float>("thickness", 1.0f);
}

void ShowMessage::Start() {
    auto& m = Monkey::get();
    if (m_endOnClick) {
    	m_mouseListener = std::make_shared<LMBCallback>([&] () { SetComplete(); });
    	Engine::get().RegisterToMouseEvent(m_mouseListener.get());
    }
    m_mainCam = m.Get<OrthographicCamera>("maincam");
    auto scene = m.Get<Entity>("main");
    glm::vec2 currentPos;
    if (m_actor != -1) {
        auto actor = m.Get<Entity>(m_actor);
        currentPos = (actor->GetPosition());
    } else {
        currentPos = m_pos;
    }

    currentPos += m_offset;
	auto maxY = m_mainCam->GetPosition().y + (0.5f*m_mainCam->GetSize().y) - m_size;
	currentPos.y = std::min(currentPos.y, maxY);
    auto parent = std::make_shared<Entity>();
    Font* f = Engine::get().GetAssetManager().get<Font>(m_font).get();

    auto model = std::make_shared<TextModel>(f, m_size, m_align, m_color, m_maxWidth);
    model->setText(m_message);
    auto offset = model->getOffset();
    glm::mat4 transform = glm::translate(glm::vec3(offset, 0.0f));
    Bounds ex = model->getBounds();
    ex.Transform(transform);
	std::cout << "the bounds: " << ex.min.x << ", " << ex.min.y << " to " << ex.max.x << ", " << ex.max.y << "\n";
		glm::vec2 outlineOffsets[] = {{0,  0},
									  {-m_outlineThickness, 0},
									  {m_outlineThickness, 0},
									  {0,  m_outlineThickness},
                                      {0,  -m_outlineThickness},
									  {m_outlineThickness,  m_outlineThickness},
                                      {m_outlineThickness,  -m_outlineThickness},
                                      {-m_outlineThickness,  m_outlineThickness},
									  {-m_outlineThickness, -m_outlineThickness}};
		for (int i = 0; i < (m_outline ? 9: 1); ++i) {
			auto entity = std::make_shared<Entity>();

			//auto model = std::make_shared<TextModel>(mesh);
			auto renderer = std::make_shared<Renderer>(model);

			entity->SetPosition(glm::vec3(outlineOffsets[i][0], outlineOffsets[i][1], i == 0 ? 0 : -0.1));
			renderer->setMultColor(i == 0 ? m_color : m_outlineColor);
			renderer->SetTransform(transform);
			entity->AddComponent(renderer);
			parent->AddChild(entity);
		}

	if (m_box) {
		auto size = ex.GetSize();
		auto innerRect = std::make_shared<Entity>();
		float width = size.x + m_padding.x * 2.0f;
		float height = size.y + m_padding.y * 2.0f;
		glm::vec2 repeat(1.0f);
		if (!m_innerTexture.empty()) {
			auto tex = Engine::get().GetAssetManager().get<Tex>(m_innerTexture);
			repeat.x = width/tex->GetWidth();
			repeat.y = height/tex->GetHeight();
		}
		auto model = ModelFactory::rect(width, height, glm::vec2(ex.min.x - m_padding.x, ex.min.y - m_padding.y), RenderType::FILL,
								  glm::vec4(1.0f), m_innerTexture, repeat);
		auto renderer = model->makeRenderer(model);
		innerRect->AddComponent(renderer);
		innerRect->SetPosition(glm::vec3(0.0f, 0.0f, -0.1f));
		parent->AddChild(innerRect);
		if (!m_borderTexture.empty()) {
			glm::vec3 boxBottomLeft(ex.min.x - m_padding.x, ex.min.y - m_padding.y, 0.0f);
			float borderWidth = 4.0f;
			parent->AddChild(makeBorder(width, borderWidth, width/borderWidth, 1.0f, boxBottomLeft.x, boxBottomLeft.y + height));
			parent->AddChild(makeBorder(width, borderWidth, width/borderWidth, 1.0f, boxBottomLeft.x, boxBottomLeft.y - borderWidth));
			parent->AddChild(makeBorder(borderWidth, height, 1.0f, height/borderWidth, boxBottomLeft.x - borderWidth, boxBottomLeft.y));
			parent->AddChild(makeBorder(borderWidth, height, 1.0f, height/borderWidth, boxBottomLeft.x + width, boxBottomLeft.y));
			parent->AddChild(makeBorder(borderWidth, borderWidth, 1.0f, 1.0f, boxBottomLeft.x - borderWidth, boxBottomLeft.y + height));
			parent->AddChild(makeBorder(borderWidth, borderWidth, 1.0f, 1.0f, boxBottomLeft.x + width, boxBottomLeft.y + height));
			parent->AddChild(makeBorder(borderWidth, borderWidth, 1.0f, 1.0f, boxBottomLeft.x - borderWidth, boxBottomLeft.y - borderWidth));
			parent->AddChild(makeBorder(borderWidth, borderWidth, 1.0f, 1.0f, boxBottomLeft.x + width, boxBottomLeft.y - borderWidth));
			//			auto top = std::make_shared<Entity>();
//			auto btop = ModelFactory::rect(width, borderWidth, glm::vec2(0.0f), RenderType::FILL, glm::vec4(1.0f), m_borderTexture, glm::vec2(width/4.0f, 1.0f));
//			top->AddComponent(btop->makeRenderer(btop));
//			top->SetPosition(glm::vec3(boxBottomLeft.x, boxBottomLeft.y + height, 0.0f));
//			parent->AddChild(top);

		}


	}
    // adjust position so that the message is all visible
    glm::vec2 camPos(m_mainCam->GetPosition());
    glm::vec2 camSize = 0.5f * m_mainCam->GetSize();
    float shiftX = 0.0f;
    if (currentPos.x + ex.min.x < camPos.x - camSize.x) {
        // we need th shift the message RIGHT
        shiftX = (camPos.x - camSize.x) - currentPos.x - ex.min.x;
    } else if (currentPos.x + ex.max.x > camPos.x + camSize.x) {
        shiftX = (camPos.x + camSize.x) - currentPos.x - ex.max.x;
    }

    currentPos += glm::vec2(shiftX, 0.0f);
    glm::vec3 textpos(currentPos.x, currentPos.y, 5.0);
    parent->SetPosition(textpos);
    //parent->SetLayer(1);
    scene->AddChild(parent);
    m_generatedEntity = parent;
    m_elapsedTime=0.0f;
    //SetComplete();
}

std::shared_ptr<Entity> ShowMessage::makeBorder(float w, float h, float rx, float ry, float x, float y) {
	auto top = std::make_shared<Entity>();
	auto btop = ModelFactory::rect(w, h, glm::vec2(0.0f), RenderType::FILL, glm::vec4(1.0f), m_borderTexture, glm::vec2(rx, ry));
	top->AddComponent(btop->makeRenderer(btop));
	top->SetPosition(glm::vec3(x, y, 0.0f));
	return top;

}

void ShowMessage::Run(float dt) {
    m_elapsedTime+=dt;
    if (m_elapsedTime >= m_time) {

        SetComplete();
        if (m_generatedEntity != nullptr) {
            Engine::get().Remove(m_generatedEntity.get());
            m_generatedEntity = nullptr;
        }
    }

}
void ShowMessage::NotifySuspend(){
    SetComplete();
    if (m_generatedEntity != nullptr) {
        Engine::get().Remove(m_generatedEntity.get());
        m_generatedEntity = nullptr;
    }
}

ShowMessage::~ShowMessage() {
    if (m_generatedEntity != nullptr) {
        Engine::get().Remove(m_generatedEntity.get());
        m_generatedEntity = nullptr;
    }
}
