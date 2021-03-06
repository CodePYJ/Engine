#pragma once

#include "Engine/Core/Core.h"
#include "Engine/EEpch.h"

namespace EE {

	enum class FramebufferTextureFormat
	{
		None = 0,

		// Color
		RGBA8,
		RED_INTEGER,
		RGB16F,

		// Depth/stencil
		DEPTH24STENCIL8,

		// Defaults
		Depth = DEPTH24STENCIL8
	};

	enum class FramebufferTextureDataFormat
	{
		None = 0, UNSIGNED_BYTE, FLOAT
	};

	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format, FramebufferTextureDataFormat data_formate)
			: TextureFormat(format), TextureDataFormat(data_formate) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
		FramebufferTextureDataFormat TextureDataFormat = FramebufferTextureDataFormat::None;

		// TODO: filtering/wrap
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
			: Attachments(attachments) {}

		std::vector<FramebufferTextureSpecification> Attachments;
	};

	struct FramebufferSpecification
	{
		uint32_t Width = 0, Height = 0;
		FramebufferAttachmentSpecification Attachments;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		~Framebuffer();

		void Init();
		void Bind();
		void Unbind();
		void SetFramebufferSpec(FramebufferSpecification spec);
		void Resize(int w, int h);
		unsigned int GetColorAttachmentID(uint32_t index=0) { return m_ColorAttachments[index]; }
		int ReadPixel(uint32_t attachmentIndex, int x, int y);
		void ClearAttachment(uint32_t attachmentIndex, int value);
		
	private:
		FramebufferSpecification m_Spec;
		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = { FramebufferTextureFormat::None, FramebufferTextureDataFormat::None };
		std::vector<uint32_t> m_ColorAttachments;
		unsigned int m_RendererID = 0;
		unsigned int m_DepthAttachment = 0;
	};
}

