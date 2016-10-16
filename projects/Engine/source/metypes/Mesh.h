#pragma once
#include "GLEW\glew.h"
#include "Attribute.h"

class Mesh
{
	Mesh()
	{
		for (size_t i = 0; i < AttributeType::ATTRIBUTE_COUNT; i++)
			m_Buffers[i] = 0;
	}

	void LoadToBufferObject(Attribute<unsigned int> _i, Attribute<float> _vx)
	{
		CreateBufferObject();
		BindIndicesBuffer(_i.Data(), _i.Count());

		AddAttribute(((unsigned int) _vx.Type()), _vx.Size(), _vx.Data(), _vx.Count());

		UnbindBuffer();

		m_Size = _i.Count();
	}

	void LoadToBufferObject(Attribute<unsigned int> _i, Attribute<float> _vx, Attribute<float> _uv)
	{
		CreateBufferObject();
		BindIndicesBuffer(_i.Data(), _i.Count());

		AddAttribute(((unsigned int) _vx.Type()), _vx.Size(), _vx.Data(), _vx.Count());
		AddAttribute(((unsigned int) _uv.Type()), _uv.Size(), _uv.Data(), _uv.Count());

		UnbindBuffer();

		m_Size = _i.Count();
	}

	unsigned int GetBufferObject()
	{
		return m_Buffer;
	}

	unsigned int GetSize()
	{
		return m_Size;
	}
	
private:
	unsigned int m_Buffers[AttributeType::ATTRIBUTE_COUNT];
	
	unsigned int m_Buffer;
	unsigned int m_Size;

	void CreateBufferObject()
	{
		glGenVertexArrays(1, &m_Buffer);
		glBindVertexArray(m_Buffer);
	}

	void AddAttribute(unsigned int _attribute, int _size, float* _data, unsigned int _count)
	{
		unsigned int _buffer;
		glGenBuffers(1, &_buffer);

		glBindBuffer(GL_ARRAY_BUFFER, _buffer);

		glBufferData(GL_ARRAY_BUFFER, _count * sizeof(float), _data, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(_attribute, _size, GL_FLOAT, false, 0, 0);

		m_Buffers[_attribute] = _buffer;

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BindIndicesBuffer(unsigned int* _data, unsigned int _count)
	{
		unsigned int _buffer;
		glGenBuffers(1, &_buffer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(unsigned int), _data, GL_STATIC_DRAW);
	}

	void UnbindBuffer()
	{
		glBindVertexArray(0);
	}

	void RenderBegin()
	{
		for (size_t i = 0; i < AttributeType::ATTRIBUTE_COUNT; i++)
			if(m_Buffers[i] > 0)
				glEnableVertexAttribArray(i);
	}

	void RenderEnd()
	{
		glBindVertexArray(0);

		for (size_t i = 0; i < AttributeType::ATTRIBUTE_COUNT; i++)
			glDisableVertexAttribArray(i);	
	}

};