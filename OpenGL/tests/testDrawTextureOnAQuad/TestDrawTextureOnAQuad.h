#pragma once

#include "Test.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

namespace test {
	class TestDrawTextureOnAQuad : public Test {
	public:
		TestDrawTextureOnAQuad();
		~TestDrawTextureOnAQuad();

		void OnRender() override;
		void OnImGuiRender() override;
	private:
		VertexArray* m_VertexArray;
		IndexBuffer* m_IndexBuffer;
		Shader* m_Shader;
		Texture* m_Texture;

		glm::mat4* m_Projection;
		glm::mat4* m_View;
		glm::mat4* m_Model;
	};
}