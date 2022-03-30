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
		void SetActiveScene(std::shared_ptr<Scene> scene_ptr);

	private:
		int selectedEntity = -1;		//Entity
		std::shared_ptr<Scene> activeScene_ptr;
	};
}

