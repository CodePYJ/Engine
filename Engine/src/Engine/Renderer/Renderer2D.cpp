#include "Renderer2D.h"
#include  <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


namespace EE {

	Renderer2DData::Renderer2DData()
	{
		VAO = std::make_unique<EE::VertexArray>();
		VAO->Bind();

		VBO = std::make_unique<EE::VertexBuffer>(vertices, verSize);
		layout.PushFloat(3);		//position
		layout.PushFloat(3);		//color
		layout.PushFloat(3);		//normal

		EBO = std::make_unique<EE::IndexBuffer>(indices, indCount);
		VAO->AddBuffer(*VBO, layout);
		VAO->AddEBO(*EBO);

		shader = std::make_unique<EE::Shader>(shaderPath);
		shader->Bind();
		shader->SetUniformMat4("transform", glm::mat4(1.0f));
	}

	void Renderer2D::RendererInit(std::shared_ptr<Renderer2DData> renderdata)
	{
		renderdata->VAO = std::make_unique<EE::VertexArray>();
		renderdata->VAO->Bind();

		renderdata->VBO = std::make_unique<EE::VertexBuffer>(renderdata->vertices, renderdata->verSize);
		renderdata->layout.PushFloat(3);		//position
		renderdata->layout.PushFloat(3);		//color
		renderdata->layout.PushFloat(3);		//normal

		renderdata->EBO = std::make_unique<EE::IndexBuffer>(renderdata->indices, renderdata->indCount);
		renderdata->VAO->AddBuffer(*(renderdata->VBO), renderdata->layout);
		renderdata->VAO->AddEBO(*(renderdata->EBO));

		renderdata->shader = std::make_unique<EE::Shader>(renderdata->shaderPath);
		renderdata->shader->Bind();
		renderdata->shader->SetUniformMat4("transform", glm::mat4(1.0f));
	}

	void Renderer2D::Shutdown()
	{

	}

	void Renderer2D::BeginScene(Camera& camera)
	{

	/*	currentObj->shader->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		if(!currentObj->isLight())
			currentObj->shader->SetUniformMat4("viewMatrix", camera.GetViewMatrix());*/
	}

	void Renderer2D::EndScene()
	{

	}


	// Primitives

	void Renderer2D::DrawQuad(glm::vec3 lightPos)
	{
		//glm::mat4 transform;
		/*transform = glm::translate(glm::mat4(1.0f), currentObj->GetPosition());
		transform = glm::rotate(transform, glm::radians(currentObj->GetRotation()), glm::vec3(0.0, 0.0, 1.0))
			* glm::scale(glm::mat4(1.0f), currentObj->GetSize());
		currentObj->shader->SetUniformMat4("transform", transform);
		currentObj->shader->SetUniform4f("lightColor", glm::vec4(1.0, 1.0, 1.0, 1.0));
		if (!currentObj->isLight()) {
			currentObj->shader->SetUniform4f("objectColor", currentObj->GetColor());
			currentObj->shader->SetUniform3f("lightPos", lightPos);
		}*/
		//glDrawElements(GL_TRIANGLES, currentObj->EBO->GetCount(), GL_UNSIGNED_INT, nullptr);//为什么通过VAO获取EBO画不出来
	}
}