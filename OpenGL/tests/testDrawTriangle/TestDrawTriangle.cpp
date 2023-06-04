#include "TestDrawTriangle.h"


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

		glm::mat4 mvp = (*m_Projection) * (*m_View) * (*m_Model);
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
	}

	void TestDrawTriangle::OnImGuiRender() {
		//MyTODO: figure out how the matrix4 class from GLM works, in order to access all of the matricies, and to make them easily editable via imGUI
		/*ImGui::DragFloat("Vertex #1 X:", &m_Model[0], 0.1);
		ImGui::DragFloat("Vertex #1 Y:", &m_Model[1], 0.1);
		ImGui::DragFloat("Vertex #2 X:", &m_Model[2], 0.1);
		ImGui::DragFloat("Vertex #2 Y:", &m_Model[3], 0.1);
		ImGui::DragFloat("Vertex #3 X:", &m_Model[4], 0.1);
		ImGui::DragFloat("Vertex #3 Y:", &m_Model[5], 0.1);*/
	}
}