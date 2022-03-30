#include "SceneHierarchyPanel.h"
#include "Engine/ECS/Component/Components.h"
#include <imgui/imgui.h>
#include "Engine/ECS/Entity.h"
#include "Engine.h"
#include <glm/gtc/type_ptr.hpp>


namespace EE {

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");
		DrawEntityNode();
		if (ImGui::Button("Create")) {
			Entity entity = activeScene_ptr->CreateEntity();
			std::string name = "entity ";
			activeScene_ptr->AddComponent<TagComponent>(entity, { name + std::to_string(entity)});
			activeScene_ptr->AddComponent<TransformComponent>(entity,
				{
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
				});
			activeScene_ptr->AddComponent<Renderable2DComponent>(entity,
				{
					std::make_shared<Renderer2DData>(),
					glm::vec3(0.5f, 0.5f, 0.0f),
					glm::mat4(1.0f)
				});
		}
		ImGui::End();

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			selectedEntity = -1;

		ImGui::Begin("Properties");
		if (selectedEntity != -1) {
			DrawComponents(selectedEntity);
		}
		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode()
	{
		//uint32_t livingEntityCount = activeScene_ptr->GetCooptr()->GetLivingEntityCount();
		std::vector<Entity> livingEntities = activeScene_ptr->GetCooptr()->GetLivingEntities();

		for(Entity entity : livingEntities) {
			ImGuiTreeNodeFlags flags = ((selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
			TagComponent& tagComponent = activeScene_ptr->GetCooptr()->GetComponent<TagComponent>(entity);
			bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tagComponent.tag.c_str());
			if (ImGui::IsItemClicked())
			{
				selectedEntity = entity;
			}

			bool entityDeleted = false;
			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::MenuItem("Delete Entity"))
					entityDeleted = true;
				ImGui::EndPopup();
			}

			if (opened)
			{
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
				bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tagComponent.tag.c_str());
				if (opened)
					ImGui::TreePop();
				ImGui::TreePop();
			}

			if (entityDeleted)
			{
				activeScene_ptr->DestroyEntity(entity);
				if (selectedEntity == activeScene_ptr->GetActiveCamera())
					activeScene_ptr->SetActiveCamera(513);

				if (selectedEntity == entity)
					selectedEntity = {};
			}
		}//for
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (activeScene_ptr->GetCooptr()->HasComponent<TagComponent>(entity)) {
			std::string& tagName= activeScene_ptr->GetComponent<TagComponent>(entity).tag;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tagName.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
				tagName = std::string(buffer);
			}
		}

		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;

		if (activeScene_ptr->GetCooptr()->HasComponent<TransformComponent>(entity)) {
			bool open = ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), treeNodeFlags, "Transform");
			if (open) {
				auto& transCom = activeScene_ptr->GetComponent<TransformComponent>(entity);
				float pos[3] = { transCom.position.x, transCom.position.y , transCom.position.z };
				ImGui::DragFloat3("Position", pos, 0.1f);
				transCom.position.x = pos[0], transCom.position.y = pos[1], transCom.position.z = pos[2];
				ImGui::TreePop();
			}
		}

		if (activeScene_ptr->GetCooptr()->HasComponent<CameraComponent>(entity)) {
			bool open = ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), treeNodeFlags, "Camera");
			if (open) {
				auto& cameraCom = activeScene_ptr->GetComponent<CameraComponent>(entity);
				std::shared_ptr<OrthCameraController> cameraController = cameraCom.cameraController;
				float cameraSize = cameraController->GetSize();
				if (ImGui::DragFloat("Size", &cameraSize))
					cameraController->SetSize(cameraSize);

				float m_near = cameraController->GetNear();
				if (ImGui::DragFloat("Near", &m_near))
					cameraController->SetNear(m_near);

				float m_far = cameraController->GetFar();
				if (ImGui::DragFloat("Far", &m_far))
					cameraController->SetFar(m_far);
				ImGui::TreePop();
			}
		}

		if (activeScene_ptr->GetCooptr()->HasComponent<Renderable2DComponent>(entity)) {
			bool open = ImGui::TreeNodeEx((void*)typeid(Renderable2DComponent).hash_code(), treeNodeFlags, "2D Renderer");
			if (open) {
				auto& renderer = activeScene_ptr->GetComponent<Renderable2DComponent>(entity);
				float color[3] = { renderer.color.x, renderer.color.y , renderer.color.z };
				ImGui::ColorEdit3("Color", color);
				renderer.color.x = color[0], renderer.color.y = color[1], renderer.color.z = color[2];
				ImGui::TreePop();
			}
		}
	}

	void SceneHierarchyPanel::SetActiveScene(std::shared_ptr<Scene> scene_ptr)
	{
		activeScene_ptr = scene_ptr;
	}

}