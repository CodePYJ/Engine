#include "SceneHierarchyPanel.h"
#include <imgui/imgui.h>

namespace EE {

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");
		DrawEntityNode();
		if (ImGui::Button("Create")) {
			activeScene_ptr->CreateEntity();
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
				if (selectedEntity == entity)
					selectedEntity = {};
			}
		}//for
	}


	void SceneHierarchyPanel::SetActiveScene(std::shared_ptr<Scene> scene_ptr)
	{
		activeScene_ptr = scene_ptr;
	}

}