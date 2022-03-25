#pragma once

#include <set>
#include "Entity.h"


namespace EE {

	class System
	{
	public:
		std::set<Entity> mEntities;
	};
}
