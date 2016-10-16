#pragma once

struct AttributeType
{
	enum Type
	{
		ATTRIBUTE_VERTEX,
		ATTRIBUTE_UV,
		ATTRIBUTE_COLOR,
		ATTRIBUTE_OTHER,
		ATTRIBUTE_NULL,
		ATTRIBUTE_COUNT
	};
};

template<typename T>
class Attribute
{
public:
	Attribute(T* _data, unsigned int _size, unsigned int _count, AttributeType::Type _type)
	{
		m_Data = _data;
		m_Size = _size;
		m_Count = _count;
		m_Type = _type;
	}

	T* Data()
	{
		return m_Data;
	}

	unsigned int Size()
	{
		return m_Size;
	}

	unsigned int Count()
	{
		return m_Count;
	}

	AttributeType::Type Type()
	{
		return m_Type;
	}

private:
	T*				m_Data = nullptr;
	unsigned int	m_Size = 0;
	unsigned int	m_Count = 0;

	AttributeType::Type	m_Type = ATTRIBUTE_NULL;

};