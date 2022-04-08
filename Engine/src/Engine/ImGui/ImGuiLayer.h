#pragma once
#include "Engine/EEpch.h"
#include "Engine/Core/Layer.h"


namespace EE {

	class EE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& event);
		virtual void OnImGuiRender() override;
		void BlockEvents(bool block) { m_BlockEvents = block; }
		void  SetThemeColors();
		void SetDarkThemeColors();
		void Begin();
		void End();
	private:
		float m_time = 0.0f;
		bool m_BlockEvents = true;
	};

}


