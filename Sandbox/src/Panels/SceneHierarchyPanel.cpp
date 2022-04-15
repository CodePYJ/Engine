#include "SceneHierarchyPanel.h"
#include "Engine/ECS/Component/Components.h"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "Engine/ECS/Entity.h"
#include "Engine.h"
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>
#include "Engine/Scene/SceneSerializer.h"


namespace EE {

	extern const std::filesystem::path assetsPath;

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		DrawPopupWindow();

		DrawEntityNode();

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			selectedEntity = -1;

		ImGui::End();

		ImGui::Begin("Properties");
		if (selectedEntity != -1) {
			DrawComponents(selectedEntity);

			if (ImGui::Button("Add Component"))
				ImGui::OpenPopup("AddComponent");
			if (ImGui::BeginPopup("AddComponent"))
			{
				DrawAddComponent();
				ImGui::EndPopup();
			}
		}
		ImGui::End();	//Properties
	}

	void SceneHierarchyPanel::DrawPopupWindow()
	{
		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity")) {
				Entity entity = activeScene_ptr->CreateEntity();
				std::string name = "entity ";
				activeScene_ptr->AddComponent<TagComponent>(entity, { name + std::to_string(entity) });
				activeScene_ptr->AddComponent<TransformComponent>(entity,
					{
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(1.0f, 1.0f, 1.0f)
					});
				SetSelectedEntity(entity);
			}
			if (ImGui::MenuItem("Create Camera")) {
				Entity entity = activeScene_ptr->CreateEntity();
				std::string name = "camera ";
				activeScene_ptr->AddComponent<TagComponent>(entity, { name + std::to_string(entity) });
				activeScene_ptr->AddComponent<TransformComponent>(entity,
					{
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(1.0f, 1.0f, 1.0f)
					});
				activeScene_ptr->AddComponent<CameraComponent>(entity,
					{
						std::make_shared<CameraController>(activeScene_ptr->GetAspectRatio()),
						glm::mat4(1.0f),
						glm::mat4(1.0f),
						true
					});
				activeScene_ptr->PushCamera(entity);
				activeScene_ptr->SetActiveCamera(entity);
				SetSelectedEntity(entity);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Create Square")) {
				Entity entity = activeScene_ptr->CreateEntity();
				std::string name = "square ";
				activeScene_ptr->AddComponent<TagComponent>(entity, { name + std::to_string(entity) });
				activeScene_ptr->AddComponent<TransformComponent>(entity,
					{
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(1.0f, 1.0f, 1.0f)
					});
				activeScene_ptr->AddComponent<Renderable2DComponent>(entity,
					{
						glm::vec3(0.5f, 0.5f, 0.3f),
						Render2DType::SQUARE
					});
				SetSelectedEntity(entity);
			}
			if (ImGui::MenuItem("Create Circle")) {
				Entity entity = activeScene_ptr->CreateEntity();
				std::string name = "circle ";
				activeScene_ptr->AddComponent<TagComponent>(entity, { name + std::to_string(entity) });
				activeScene_ptr->AddComponent<TransformComponent>(entity,
					{
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(1.0f, 1.0f, 1.0f)
					});
				activeScene_ptr->AddComponent<Renderable2DComponent>(entity,
					{
						glm::vec3(0.5f, 0.5f, 0.0f),
						Render2DType::CIRCLE
					});
				SetSelectedEntity(entity);
			}
			if (ImGui::MenuItem("Create Mesh")) {
				Entity entity = activeScene_ptr->CreateEntity();
				std::string name = "mesh ";
				activeScene_ptr->AddComponent<TagComponent>(entity, { name + std::to_string(entity) });
				activeScene_ptr->AddComponent<TransformComponent>(entity,
					{
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(1.0f, 1.0f, 1.0f)
					});
				activeScene_ptr->AddComponent<MeshComponent>(entity, 
					{ 
						
					});
				SetSelectedEntity(entity);
			}
			ImGui::EndPopup();
		}
	}

	void SceneHierarchyPanel::DrawEntityNode()
	{
		std::vector<Entity> livingEntities = activeScene_ptr->GetLivingEntities();

		for(Entity entity : livingEntities) {
			ImGuiTreeNodeFlags flags = ((selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
			flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
			TagComponent& tagComponent = activeScene_ptr->GetComponent<TagComponent>(entity);
			bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tagComponent.tag.c_str());
			if (ImGui::IsItemClicked())
			{
				SetSelectedEntity(entity);
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
					activeScene_ptr->SetActiveCamera(-1);

				if (selectedEntity == entity)
					SetSelectedEntity(-1);
			}
		}//for
	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (activeScene_ptr->HasComponent<TagComponent>(entity)) {
			std::string& tagName= activeScene_ptr->GetComponent<TagComponent>(entity).tag;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tagName.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
				tagName = std::string(buffer);
			}
		}

		DrawComponent<TransformComponent>("Transform", entity, [](auto& component)
			{
				DrawVec3Control("Translation", component.position);
				glm::vec3 rotation = glm::degrees(component.rotation);
				DrawVec3Control("Rotation", rotation);
				component.rotation = glm::radians(rotation);
				DrawVec3Control("Scale", component.scale, 1.0f);
			});

		DrawComponent<CameraComponent>("Camera", entity, [this, entity](auto& component)
			{
				std::shared_ptr<CameraController> cameraController = component.cameraController;
				ImGui::Checkbox("Primary", &component.primary);
				const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
				const char* currentProjectionTypeString = projectionTypeStrings[(int)cameraController->GetCameraType()];

				if (ImGui::BeginCombo("Projection", currentProjectionTypeString)) {
					for (int i = 0; i < 2; i++) {
						bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected)) {
							currentProjectionTypeString = projectionTypeStrings[i];
							cameraController->SetCameraType((Camera::ProjectionType)i);
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if (cameraController->GetCameraType() == Camera::ProjectionType::Orthographic) {
					float cameraSize = cameraController->GetOrthoSize();
					if (ImGui::DragFloat("Size", &cameraSize))
						cameraController->SetOrthoSize(cameraSize);

					float m_near = cameraController->GetOrthoNear();
					if (ImGui::DragFloat("Near", &m_near))
						cameraController->SetOrthoNear(m_near);

					float m_far = cameraController->GetOrthoFar();
					if (ImGui::DragFloat("Far", &m_far))
						cameraController->SetOrthoFar(m_far);
				}

				if (cameraController->GetCameraType() == Camera::ProjectionType::Perspective) {
					float fov = cameraController->GetPerspFov();
					if (ImGui::DragFloat("Fov", &fov))
						cameraController->SetPerspFov(fov);

					float m_near = cameraController->GetPerspNear();
					if (ImGui::DragFloat("Near", &m_near))
						cameraController->SetPerspNear(m_near);

					float m_far = cameraController->GetPerspFar();
					if (ImGui::DragFloat("Far", &m_far))
						cameraController->SetPerspFar(m_far);
				}
			});

		DrawComponent<Renderable2DComponent>("Renderer2D", entity, [this](auto& component)
			{
				ImGui::ColorEdit3("Color", glm::value_ptr(component.color));
				if (ImGui::TreeNode("Texture"))
				{
					ImGui::Image((ImTextureID)(component.texture ? component.texture->GetRendererID() : nullTex->GetRendererID()), { 80.0f, 80.0f }, { 0, 1 }, { 1, 0 });
					if (ImGui::BeginDragDropTarget()) {
						if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
						{
							const wchar_t* path = (const wchar_t*)payload->Data;
							std::filesystem::path texturePath = std::filesystem::path(assetsPath) / path;
							component.texture = std::make_shared<Texture>(texturePath.string());
						}
						ImGui::EndDragDropTarget();
					}	//DragDrop
					ImGui::TreePop();
				}	//TreeNode
			});

		DrawComponent<MeshComponent>("Mesh", entity, [](auto& component)
			{
				ImGui::ColorEdit3("Color", glm::value_ptr(component.color));
				ImGui::Columns(2);
				ImGui::Text("Model");
				ImGui::NextColumn();
				ImGui::Text(component.obj_name.c_str());
				if (ImGui::BeginDragDropTarget()) {
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
					{
						const wchar_t* path = (const wchar_t*)payload->Data;
						std::filesystem::path modelPath = std::filesystem::path(assetsPath) / path;
						component.obj_name = modelPath.filename().string();
						component.path = modelPath.string();
						component.model = std::make_shared<Model>(modelPath.string());
					}
					ImGui::EndDragDropTarget();
				}	//DragDrop
				ImGui::NextColumn();
				ImGui::Columns(1);
				ImGui::Spacing();
			});
	}

	void SceneHierarchyPanel::DrawAddComponent()
	{
		if (ImGui::MenuItem("Camera")) {
			activeScene_ptr->AddComponent<CameraComponent>(selectedEntity,
				{
					std::make_shared<CameraController>(activeScene_ptr->GetAspectRatio()),
					glm::mat4(1.0f),
					glm::mat4(1.0f),
					true
				});
			activeScene_ptr->PushCamera(selectedEntity);
			activeScene_ptr->SetActiveCamera(selectedEntity);
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("Renderable2D")) {
			activeScene_ptr->AddComponent<Renderable2DComponent>(selectedEntity,
				{
					glm::vec3(0.5f, 0.5f, 0.0f),
					Render2DType::SQUARE
				});

			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("Mesh")) {
			activeScene_ptr->AddComponent<MeshComponent>(selectedEntity,
				{ nullptr });

			ImGui::CloseCurrentPopup();
		}
	}

	void SceneHierarchyPanel::SetActiveScene(std::shared_ptr<Scene> scene_ptr)
	{
		activeScene_ptr = scene_ptr;
	}

}