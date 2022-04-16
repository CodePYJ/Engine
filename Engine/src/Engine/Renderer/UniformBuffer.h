#pragma once

namespace EE {

	class UniformBuffer
	{
	public:
		UniformBuffer(unsigned int size);
		~UniformBuffer();
		void Bind();
		void Unbind();
		void SetBindPoint(int bind_point);
		void SetBindPoint(int bind_point, int start_pos, int end_pos);
		void SetData(unsigned int size, void* data);

	private:
		unsigned int block_id;
	};
}
