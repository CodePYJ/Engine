#pragma once

#include "Core.h"

namespace EE {

	class EE_API Timestep 
	{
	public:
		Timestep(float time = 0.0f) 
		:m_Time(time) {  }
		
		float GetSecond() { return m_Time; }
		
	private:
		float m_Time;
	};
}

