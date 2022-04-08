#pragma once
#include "Engine/EEpch.h"
#include <filesystem>
#include "Engine/Renderer/Texture.h"


namespace EE {

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();
		void OnImGuiRenderer();

	private:
		std::filesystem::path currentDir;

		std::shared_ptr<Texture> m_DirectoryIcon;
		std::shared_ptr<Texture> m_FileIcon;
	};
}
