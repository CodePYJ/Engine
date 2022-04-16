#include "UniformBuffer.h"
#include <glad/glad.h>


namespace EE {

	UniformBuffer::UniformBuffer(unsigned int size)
	{
		glGenBuffers(1, &block_id);
		glBindBuffer(GL_UNIFORM_BUFFER, block_id);
		glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
	}

	UniformBuffer::~UniformBuffer()
	{
		glDeleteBuffers(1, &block_id);
	}

	void UniformBuffer::Bind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, block_id);
	}

	void UniformBuffer::Unbind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void UniformBuffer::SetBindPoint(int bind_point)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, bind_point, block_id);
	}

	void UniformBuffer::SetBindPoint(int bind_point, int start_pos, int end_pos)
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, bind_point, block_id, start_pos, end_pos);
	}

	void UniformBuffer::SetData(unsigned int size, void* data)
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
	}

}


