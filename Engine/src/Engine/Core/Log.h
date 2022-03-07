#pragma once

#include "Core.h"
#include <iostream>

namespace EE {

	class EE_API Log
	{
	public:
		
	};
}

#define EE_TRACE(x)	std::cout << x << std::endl;
#define EE_INFO(x)		std::cout << (std::string)(x) << std::endl;
#define EE_WARN(x)	std::cout << x << std::endl;
#define EE_ERROR(x)	std::cout << x << std::endl;
#define EE_FATAL(x)	std::cout << x << std::endl;
