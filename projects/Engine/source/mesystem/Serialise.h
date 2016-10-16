#pragma once
#include <memory>
#include <math.h>
#include <atomic>

class ISerialise
{
public:
	~ISerialise()
	{
		Free();
	}

	const unsigned int _MaxSize = 32;

	/*
		Write Position
	*/
	unsigned int m_Size		= 0;

	/*
		Read Position
	*/
	unsigned int m_Index	= 0;

	template<typename T> void Validate(unsigned int _count)
	{
		if (m_Bytes)
		{
			if (m_Size + sizeof(T) * _count > m_Memory)
			{
				if (sizeof(T) > _MaxSize)
					m_Memory += (unsigned int) ceil(((sizeof(T) * _count) / _MaxSize)) * _MaxSize;
				else
					m_Memory += _MaxSize;

				byte* _new = new byte[m_Memory];

				memcpy(_new, m_Bytes, m_Size);

				delete[] m_Bytes;

				m_Bytes = _new;
			}

			return;
		}

		m_Bytes = new byte[_MaxSize];

		Validate<T>(_count);
	}

	template<typename T> void Write(T _object)
	{
		Validate<T>(0);

		memcpy(m_Bytes + m_Size, &_object, sizeof(T));

		m_Size += sizeof(T);

		//byte* _new = new byte[m_Size + sizeof(T)];
		//
		//if (m_Bytes)
		//{
		//	memcpy(_new, m_Bytes, m_Size + sizeof(T));
		//	delete m_Bytes;
		//}
		//
		//m_Bytes = _new;
		//
		//memcpy(m_Bytes + m_Size, &_object, sizeof(T));
		//
		//m_Size += sizeof(T);
	}

	template<typename T> void WriteArray(T* _object, unsigned int _count)
	{
		Validate<T>(0);

		memcpy(m_Bytes + m_Size, _object, sizeof(T) * _count);

		m_Size += sizeof(T) * _count;

		//byte* _new = new byte[m_Size + (sizeof(T) * _count)];
		//
		//if (m_Bytes)
		//{
		//	memcpy(_new, m_Bytes, m_Size + (sizeof(T) * _count));
		//	delete m_Bytes;
		//}
		//
		//m_Bytes = _new;
		//
		//memcpy(m_Bytes + m_Size, _object, sizeof(T) * _count);
		//
		//m_Size += sizeof(T) * _count;
	}

	template<typename T> T Read()
	{
		if (m_Bytes)
		{
			T _object = T();

			memcpy((byte*)&_object, m_Bytes + m_Index, sizeof(T));

			m_Index += sizeof(T);

			return _object;
		}

		return T();
	}

	template<typename T> T* ReadArray(unsigned int _count)
	{
		if (m_Bytes)
		{
			T* _object = new T[_count];

			memcpy(_object, m_Bytes + m_Index, sizeof(T) * _count);

			m_Index += sizeof(T) * _count;

			return _object;
		}

		return nullptr;
	}

	unsigned int Size()
	{
		return m_Size;
	}
	
	void Free()
	{
		if (m_Bytes)
			delete[] m_Bytes;
	}
	
	static void CopySerialise(ISerialise* _destination, ISerialise* _source)
	{
		_destination->m_Index	= _source->m_Index;
		_destination->m_Size	= _source->m_Size;
		_destination->m_Bytes	= _source->m_Bytes;
		_destination->m_Memory	= _source->m_Memory;
	}

protected:
	typedef unsigned char byte;

private:
	byte* m_Bytes			= nullptr;
	
	/*
		Memory allocated
	*/
	unsigned int m_Memory	= _MaxSize;

};