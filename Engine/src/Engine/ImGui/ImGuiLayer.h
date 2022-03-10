#pragma once

#include "Engine/Core/Layer.h"


namespace EE {

	class EE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_time = 0.0f;
	};

}


