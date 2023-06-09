#include "TestDrawTextureOnAQuad.h"
#include "../glm/gtc/type_ptr.hpp"

#include "../glm/gtx/string_cast.hpp"
#include <iostream>

namespace test {
	TestDrawTextureOnAQuad::TestDrawTextureOnAQuad() {
		m_Position = new glm::vec3(0.0f);
		m_Rotation = new float(0.0f);
		m_Scale = new glm::vec3(1.0f);

		//Static render of verticies
		float trianglePos[16] = {
			-50.0f, -50.0f, 0.0f, 0.0f,
			 50.0f, -50.0f, 1.0f, 0.0f,
			 50.0f,  50.0f, 1.0f, 1.0f,
			-50.0f,  50.0f, 0.0f, 1.0f
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
		// View Matrix: Rotation/Transformaton/Scale of the camera
		m_View = new glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));

		// Model matrix: Rotation/Transformaton/Scale of all the models in a scene
		m_Model = new glm::mat4(glm::translate(glm::mat4(1.0f), *m_Position));

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
		delete m_Position;
		delete m_Rotation;
		delete m_Scale;
	}

	void TestDrawTextureOnAQuad::OnRender() {
		Renderer renderer;

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, *m_Position);
		trans = glm::rotate(trans, *m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::scale(trans, *m_Scale);

		glm::mat4 mvp = (*m_Projection) * (*m_View) * (trans);
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
	}

	void TestDrawTextureOnAQuad::OnImGuiRender() {
		ImGui::DragFloat("Position x", &m_Position->x, 0.5);
		ImGui::DragFloat("Position y", &m_Position->y, 0.5);
		ImGui::DragFloat("Rotation", m_Rotation, 0.1);
		ImGui::DragFloat("Scale x", &m_Scale->x, 0.1);
		ImGui::DragFloat("Scale y", &m_Scale->y, 0.1);
	}
}