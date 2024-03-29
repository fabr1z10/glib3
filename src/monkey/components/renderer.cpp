//
//  renderer.cpp
//  glib
//
//  Created by Fabrizio Venturini on 05/05/2018.
//
//

#include <monkey/components/renderer.h>
#include <monkey/shader.h>
#include <monkey/error.h>
#include <monkey/entity.h>
#include <iostream>


Renderer::Renderer(std::shared_ptr<Model> model) : m_model(model), m_renderingTransform(1.0f), m_multColor(glm::vec4(1.0f)), m_addColor(glm::vec4(0.0f)) {}
//Renderer::Renderer() : Component(), m_baseModel(nullptr),
//    m_multColor(1.0f), m_addColor(0.0f), m_renderingTransform(1.0f), m_forceZ(false), m_forcedZ(0.0f),
//    m_texOffset(0.0f), m_blend(Blend::DEFAULT), m_depth(GL_LESS) {
//
//}
//
//Renderer::Renderer(const Renderer& orig) : Component(orig),
//    m_multColor(orig.m_multColor), m_addColor(orig.m_addColor), m_renderingTransform(orig.m_renderingTransform),
//    m_baseModel(orig.m_baseModel), m_texOffset(0.0f), m_depth(GL_LESS)
//{
//
//}

Renderer::Renderer(const ITab& t) : m_multColor(1.0f),
	m_addColor(0.0f), m_renderingTransform(1.0f), m_forceZ(false), m_forcedZ(0.0f), m_texOffset(0.0f), m_blend(Blend::DEFAULT) {
	m_multColor = t.get<glm::vec4>("multcolor", glm::vec4(1.0f));
	m_addColor = t.get<glm::vec4>("addcolor", glm::vec4(0.0f));
	m_blend = static_cast<Blend>(t.get<int>("blend", 0));
	m_depth = static_cast<GLenum>(t.get<int>("depth", GL_LESS));
}


void Renderer::init(Shader* shader) {
	shader->setVec4("mult_color", m_multColor);
	shader->setVec4("add_color", m_addColor);

}

void Renderer::post() {
//	if (m_blend != Blend::DEFAULT) {
//		// reset to default
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//		glBlendEquation(GL_FUNC_ADD);
//
//	}
//	if (m_depth != GL_LESS) {
//		glDepthFunc(GL_LESS);
//	}

}

void Renderer::Draw(Shader* shader) {

    for (const auto& mesh : *m_model) {
//        auto mult_color_loc = glGetUniformLocation(shader->getProgId(), "mult_color");
//        if (mult_color_loc != GL_INVALID_VALUE) {
//            glUniform4fv(mult_color_loc, 1, &m_multColor[0]);
//        }
        if (shader->getShaderType() == mesh->getShaderType()) {
            mesh->draw(shader, 0, 0);
        }
    }
    //m_model->Draw(shader, m_offset, m_count);
}

const glm::mat4& Renderer::GetTransform() const {
    return m_renderingTransform;
}

void Renderer::SetTransform(const glm::mat4& t) {
    m_renderingTransform = t;
}

//ShaderType Renderer::GetShaderType() const {
//    return (m_model == nullptr ? ShaderType::NONE : m_model->GetShaderType());
//}

Bounds Renderer::GetBounds2D() const {
    Bounds b = GetBounds();

    b.Transform(m_renderingTransform);
    return b;
}


void Renderer::setBlendMode(Blend b) {
	m_blend = b;
}

void Renderer::setDepthFunc(GLenum f) {
	m_depth = f;
}

//void Renderer::AdvanceFrame(int m) {
//    m_frame += m;
//    int n = m_currentAnim->getFrameCount();
//    if (m_frame >= n) {
//        m_frame = 0;
//    } else if (m_frame < 0) {
//
//        m_frame = n-1;
//    }
//    std::cout << "new frame; " << m_frame << "\n";
//
//}







//void Renderer::SetScale(float scale) {
//    if (m_renderingTransform[0][0]<0)
//        scale = -scale;
//    m_renderingTransform[0][0] = scale;
//    m_renderingTransform[1][1] = fabs(scale);
//    m_renderingTransform[2][2] = fabs(scale);
//}

void Renderer::SetParent(Entity *parent) {
    Component::SetParent(parent);

}

