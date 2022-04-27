#pragma once

#include "Engine/EEpch.h"
#include "Engine/Core/Core.h"


namespace EE {

	class EE_API Texture
	{
	public:
		Texture(const std::string& path, int vertical = 1); 
		Texture(uint32_t width, uint32_t height);

		~Texture();

		void Bind(unsigned int slot = 0);
		void Unbind();

		inline int GetWidth() { return m_Width; }
		inline int GetHeight() { return m_Height; }
		inline unsigned int GetRendererID() { return m_RendererID; }
		void SetData(void* data, uint32_t size);

		bool operator==(const Texture& other) const
		{
			return m_RendererID == other.m_RendererID;
		}

		std::string type;

	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_Channels;
	};
}
