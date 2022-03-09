#pragma once

#include "Engine.h"

class ExampleLayer : public EE::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{

	}

	void OnUpdate() override
	{

	}

	void OnEvent(EE::Event& event) override
	{
		EE_INFO("Example Event");
	}
};