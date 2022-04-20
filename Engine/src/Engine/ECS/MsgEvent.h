#pragma once

#include <map>

namespace EE {

	enum class MsgType
	{
		None = 0,
		CAMERA_MSG,
		LIGHT_MSG
	};

	class MsgEvent
	{
	public:

		void SetMat4Msg(MsgType type, glm::mat4 msg) { msgMat4Events[type] = msg; }
		glm::mat4 getMat4Msg(MsgType type) { return msgMat4Events[type]; }

		void SetIntMsg(MsgType type, int value) { msgIntEvents[type] = value; }
		int getIntMsg(MsgType type) { return msgIntEvents[type]; }

		std::map<MsgType, glm::mat4> msgMat4Events;
		std::map<MsgType, glm::vec3> msgVec3Events;
		std::map<MsgType, int> msgIntEvents;
	};

}
