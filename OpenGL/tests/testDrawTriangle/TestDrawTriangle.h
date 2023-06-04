#pragma once

#include "Test.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"

namespace test {
	class TestDrawTriangle : public Test
	{
	public:
		TestDrawTriangle();
		~TestDrawTriangle();

		void OnRender() override;
		void OnImGuiRender() override;
	private:
		IndexBuffer* m_IndexBuffer;
		VertexArray* m_VertexArray;
		Shader* m_Shader;

		glm::mat4* m_Projection;
		glm::mat4* m_View;
		glm::mat4* m_Model;
	};
}
