#pragma once

#include "Test.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

namespace test {
	class TestDrawLines : public Test {
	public:
		TestDrawLines();
		~TestDrawLines();

		void OnRender() override;
		void OnImGuiRender() override;
	private:
		VertexArray* m_VertexArray;
		IndexBuffer* m_IndexBuffer;
		Shader* m_Shader;

		glm::mat4* m_Projection;
		glm::mat4* m_View;
		glm::mat4* m_Model;

		glm::vec3* m_Position;
		glm::vec3* m_Scale;
		float* m_Rotation;
	};
}