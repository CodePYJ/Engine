#include "ContentBrowserPanel.h"
#include <imgui/imgui.h>


namespace EE {

	extern const std::filesystem::path assetsPath = "assets";

	ContentBrowserPanel::ContentBrowserPanel()
		:currentDir(assetsPath)
	{
		m_DirectoryIcon = std::make_shared<Texture>("Resources/Icons/ContentBrowser/DirectoryIcon.png");
		m_FileIcon = std::make_shared<Texture>("Resources/Icons/ContentBrowser/FileIcon.png");
	}

	void ContentBrowserPanel::OnImGuiRenderer()
	{
		ImGui::Begin("Browser");
		if (currentDir != std::filesystem::path(assetsPath))
		{
			if (ImGui::Button("<-"))
				currentDir = currentDir.parent_path();
		}

		static float padding = 16.0f;
		static float thumbnailSize = 128.0f;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		for (auto& it : std::filesystem::directory_iterator(currentDir)) {
			const auto path = it.path();
			auto relativePath = std::filesystem::relative(path, assetsPath);
			std::string filename = relativePath.filename().string();

			ImGui::PushID(filename.c_str());
			std::shared_ptr<Texture> icon = it.is_directory() ? m_DirectoryIcon : m_FileIcon;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });

			if (ImGui::BeginDragDropSource())
			{
				const wchar_t* itemPath = relativePath.c_str();
				ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
				ImGui::EndDragDropSource();
			}

			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (it.is_directory())
					currentDir /= it.path().filename();
			}
			ImGui::TextWrapped(filename.c_str());
			ImGui::NextColumn();
			ImGui::PopID();
		}

		ImGui::Columns(1);

		ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);

		ImGui::End();
	}

}