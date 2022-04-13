#pragma once

#include "Engine/EEpch.h"
#include "Engine/Core/Core.h"


namespace EE {

	class EE_API Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();

		void Bind(unsigned int slot = 0);
		void Unbind();

		inline int GetWidth() { return m_Width; }
		inline int GetHeight() { return m_Height; }
		inline unsigned int GetRendererID() { return m_RendererID; }

		std::string type;

	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_Channels;
	};
}
