#include "ContentBrowserPanel.h"
#include <imgui/imgui.h>


namespace EE {

	static const char* assetsPath = "assets";

	ContentBrowserPanel::ContentBrowserPanel()
		:currentDir(assetsPath)
	{
		
	}

	void ContentBrowserPanel::OnImGuiRenderer()
	{
		ImGui::Begin("Browser");
		if (currentDir != std::filesystem::path(assetsPath))
		{
			if (ImGui::Button("<-"))
				currentDir = currentDir.parent_path();
		}
		for (auto& it : std::filesystem::directory_iterator(currentDir)) {
			const auto path = it.path();
			auto relativePath = std::filesystem::relative(path, assetsPath);
			std::string filename = relativePath.filename().string();
			if (it.is_directory())
			{
				if (ImGui::Button(filename.c_str())) {
					currentDir /= it.path().filename();
				}
			}
		}

		ImGui::End();
	}

}