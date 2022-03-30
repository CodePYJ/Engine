#pragma once

#include <map>

namespace EE {

	enum class MsgType
	{
		None = 0,
		CAMERA_MSG
	};

	class MsgEvent
	{
	public:

		void SetMat4Msg(MsgType type, glm::mat4 msg) { msgMat4Events[type] = msg; }
		glm::mat4 getMat4Msg(MsgType type) { return msgMat4Events[type]; }

		std::map<MsgType, glm::mat4> msgMat4Events;
		std::map<MsgType, glm::vec3> msgVec3Events;
	};

}
