#include "TestDrawTextureOnAQuad.h"

namespace test {
	TestDrawTextureOnAQuad::TestDrawTextureOnAQuad() {
		//Static render of verticies
		float trianglePos[16] = {
			100.0f, 100.0f, 0.0f, 0.0f,
			200.0f, 100.0f, 1.0f, 0.0f,
			200.0f, 200.0f, 1.0f, 1.0f,
			100.0f, 200.0f, 0.0f, 1.0f
		};

		//Instead of repeting each vertex's position multiple times, we store how they are connected.
		unsigned int indicies[6] = {
			0, 1, 2,
			2, 3, 0
		};

		VertexBuffer vb(trianglePos, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		m_VertexArray = new VertexArray();
		m_VertexArray->AddBuffer(vb, layout);

		m_IndexBuffer = new IndexBuffer(indicies, 6);

		// Projection Matrix: Converting any space cordinates, to 1-1 space mapping: mapping the screen from 0 left to 1 right for example, projective/ortrocraphic view
		m_Projection = new glm::mat4(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f));
		// View Matrix: Rotation/Transformaton/Scale of the camera: moves the camera to the left 100 units
		m_View = new glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0)));

		// Model matrix: Rotation/Transformaton/Scale of all the models in a scene
		m_Model = new glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(300, 150, 0)));

		glm::mat4 mvp = (*m_Projection) * (*m_View) * (*m_Model);

		m_Shader = new Shader("resources/shaders/basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		m_Texture = new Texture("resources/textures/pic.png");
		m_Texture->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

		m_VertexArray->UnBind();
		vb.UnBind();
		m_IndexBuffer->UnBind();
		m_Shader->UnBind();
	}

	TestDrawTextureOnAQuad::~TestDrawTextureOnAQuad() {
		delete m_VertexArray;
		delete m_IndexBuffer;
		delete m_Shader;
		delete m_Texture;
		delete m_Projection;
		delete m_View;
		delete m_Model;
	}

	void TestDrawTextureOnAQuad::OnRender() {
		Renderer renderer;

		glm::mat4 mvp = (*m_Projection) * (*m_View) * (*m_Model);
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
	}

	void TestDrawTextureOnAQuad::OnImGuiRender() {
		ImGui::DragFloat("Vertex #1 X:", &m_Model[0][0].a, 0.0001);
		ImGui::DragFloat("Vertex #1 X:", &m_Model[0][1].a, 0.0001);
		ImGui::DragFloat("Vertex #1 X:", &m_Model[0][2].a, 0.0001);
		ImGui::DragFloat("Vertex #1 X:", &m_Model[0][3].a, 0.0001);
	}
}