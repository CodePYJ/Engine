#include "LayerStack.h"


namespace EE {

	LayerStack::LayerStack()
	{
		//m_layerIndex = m_layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_layers.emplace(m_layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_layers.begin() + m_LayerInsertIndex) {
			m_layers.erase(it);
			layer->OnDetach();
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		m_layers.emplace_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_layers.begin() + m_LayerInsertIndex, m_layers.end(), overlay);
		if (it != m_layers.end())
		{
			overlay->OnDetach();
			m_layers.erase(it);
		}
	}

}

