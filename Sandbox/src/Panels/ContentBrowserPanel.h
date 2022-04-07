#pragma once

#include <filesystem>

namespace EE {

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();
		void OnImGuiRenderer();

	private:
		std::filesystem::path currentDir;
	};
}
