#pragma once

#include "Engine/EEpch.h"
#include "Engine/Scene/Scene.h"


namespace EE{

	class SceneHierarchyPanel
	{
	public:
		void OnImGuiRender();
		void DrawEntityNode();
		void DrawComponents(Entity entity);
		//void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValues = 0.0f, float columnWidth = 100.0f);
		void DrawAddComponent();
		void SetActiveScene(std::shared_ptr<Scene> scene_ptr);

		template<typename T, typename UIFunction>
		void DrawComponent(const std::string& name, Entity entity, UIFunction uiFunction)
		{
			const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
			if (activeScene_ptr->GetCooptr()->HasComponent<T>(entity)) {
				auto& component = activeScene_ptr->GetComponent<T>(entity);

				ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
				float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
				ImGui::Separator();

				bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
				ImGui::PopStyleVar();
				ImGui::SameLine(contentRegionAvailable.x - lineHeight * 2.0f);

				bool removeComponent = false;
				if (ImGui::Button("Remove", ImVec2{ lineHeight*2.5f, lineHeight })) {
					removeComponent = true;
				}

				if (open) {
					uiFunction(component);
					ImGui::TreePop();
				}
				if (removeComponent) {
					activeScene_ptr->RemoveComponent<T>(entity);
				}
			}
		}

	private:
		Entity selectedEntity = -1;		//Entity
		std::shared_ptr<Scene> activeScene_ptr;
	};
}

