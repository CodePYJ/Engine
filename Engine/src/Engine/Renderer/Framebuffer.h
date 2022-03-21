#pragma once

#include "Engine/Core/Core.h"

namespace EE {

	class Framebuffer
	{
	public:
		Framebuffer(int w, int h);
		~Framebuffer();

		void Init();
		void Bind();
		void Unbind();

		void Resize(int w, int h);
		unsigned int GetColorAttachmentID() { return m_ColorAttachment; }

	private:
		unsigned int m_RendererID = 0;
		unsigned int m_ColorAttachment = 0;
		unsigned int m_DepthAttachment = 0;
		int width;
		int height;
	};
}

