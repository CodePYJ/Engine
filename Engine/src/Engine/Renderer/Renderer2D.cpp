#include  <glad/glad.h>
#include "Camera.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include <glm/gtc/type_ptr.hpp>


namespace EE {

	RenderObj* Renderer2D::currentObj;
	std::vector<RenderObj*> Renderer2D::RenderObjs;
	int Renderer2D::LatestObjID = -1;

	unsigned int Renderer2D::CreatObj(std::string path)
	{
		RenderObjs.emplace_back(new RenderObj(path));
		LatestObjID++;
		return LatestObjID;
	}

	void Renderer2D::Shutdown()
	{
		for (RenderObj* obj : RenderObjs)
			delete obj;
	}

	void Renderer2D::BeginScene(unsigned int objID, OrthographicCamera& camera)
	{
		currentObj = RenderObjs[objID];
		currentObj->VAO->Bind();
		currentObj->shader->Bind();
		currentObj->shader->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		currentObj->VAO->Unbind();
		currentObj->shader->Unbind();
	}

	// Primitives
	void Renderer2D::DrawQuad(const glm::vec2& position, const float& rotation, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position, 0.0f), rotation, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const float& rotation, const glm::vec2& size, const glm::vec4& color)
	{
		currentObj->shader->SetUniform4f("u_Color", color);
		glm::mat4 transform;
		transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
		transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0))
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		currentObj->shader->SetUniformMat4("transform", transform);
		glDrawElements(GL_TRIANGLES, currentObj->EBO->GetCount(), GL_UNSIGNED_INT, nullptr);//为什么通过VAO获取EBO画不出来
		//std::cout <<  << "\n";
	}
}