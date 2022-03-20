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

	unsigned int Renderer2D::CreatObj(float vers[36],std::string path)
	{
		RenderObjs.emplace_back(new RenderObj(vers, path));
		LatestObjID++;
		EE_TRACE(LatestObjID);
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

	RenderObj* Renderer2D::GetObj(unsigned int objID)
	{
		return RenderObjs[objID];
	}


	// Primitives

	void Renderer2D::DrawQuad(glm::vec3 lightPos)
	{
		glm::mat4 transform;
		transform = glm::translate(glm::mat4(1.0f), currentObj->GetPosition());
		transform = glm::rotate(transform, glm::radians(currentObj->GetRotation()), glm::vec3(0.0, 0.0, 1.0))
			* glm::scale(glm::mat4(1.0f), currentObj->GetSize());
		currentObj->shader->SetUniformMat4("transform", transform);
		currentObj->shader->SetUniform4f("lightColor", glm::vec4(1.0, 1.0, 1.0, 1.0));
		if (!currentObj->isLight()) {
			currentObj->shader->SetUniform4f("objectColor", currentObj->GetColor());
			currentObj->shader->SetUniform3f("lightPos", lightPos);
		}
		glDrawElements(GL_TRIANGLES, currentObj->EBO->GetCount(), GL_UNSIGNED_INT, nullptr);//为什么通过VAO获取EBO画不出来
	}
}