#pragma once

#include "Engine/EEpch.h"
#include "Core.h"
#include "Engine/Events/Event.h"
#include "Timestep.h"

namespace EE {

	class EE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {  }
		virtual void OnDetach() {  }
		virtual void OnUpdate(Timestep timestep) {  }
		virtual void OnImGuiRender() {  }
		virtual void OnEvent(Event& event) {  }
		virtual std::string GetName() { return layerName; }
	protected:
		std::string layerName;
	};
}
