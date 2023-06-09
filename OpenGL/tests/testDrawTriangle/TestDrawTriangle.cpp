#include "TestDrawTriangle.h"
#include <iostream>

#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtx/string_cast.hpp"
namespace test {

	TestDrawTriangle::TestDrawTriangle()		
	{
		//unsigned int m_TriangleColor[] { 1.0f, 1.0f, 1.0f, 1.0f };
		float m_VertexPositions[6]{
		100.0f, 100.0f,
		200.0f, 100.0f,
		200.0f, 200.0f
		};
		unsigned int m_TriangleIndexieIndex[3] = { 
			0, 1, 2 
		};

		m_Position = new glm::vec3(0.0f);

		VertexBuffer vb(m_VertexPositions, 2 * 3 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);

		layout.Push<float>(2);

		m_VertexArray = new VertexArray();
		m_VertexArray->AddBuffer(vb, layout);

		m_IndexBuffer = new IndexBuffer(m_TriangleIndexieIndex, 3);

		
		m_Projection = new glm::mat4(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f));
		m_View = new glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));
		m_Model = new glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));

		glm::mat4 mvp = (*m_Projection) * (*m_View) * (*m_Model);

		m_Shader = new Shader("tests/testDrawTriangle/BasicShader.shader");
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		m_Shader->UnBind();
		m_VertexArray->UnBind();
		m_IndexBuffer->UnBind();
	} 

	TestDrawTriangle::~TestDrawTriangle() {
		delete m_IndexBuffer;
		delete m_VertexArray;
		delete m_Shader;
	}

	void TestDrawTriangle::OnRender() {
		Renderer renderer;

		auto newModel = new glm::mat4(glm::translate(*m_Model, *m_Position));


		glm::mat4 mvp = (*m_Projection) * (*m_View) * (*newModel);
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);

		delete newModel;
	}

	void TestDrawTriangle::OnImGuiRender() {
		ImGui::DragFloat("Vertex float x", &m_Position->x, 0.01);
		ImGui::DragFloat("Vertex float y", &m_Position->y, 0.01);
	}
}