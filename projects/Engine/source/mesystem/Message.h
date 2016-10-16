#pragma once
#include "Serialise.h"

template<typename T>
class Allocator
{
public:
	Allocator(unsigned int _size)
	{
		m_Pointer	= new T[_size];
		m_Size		= _size;
	}

	T* Allocate()
	{
		if (m_StackCounter < m_Size)
		{
			T* _object = &m_Pointer[m_StackCounter];
			m_StackCounter++;

			return _object;
		}

		return nullptr;
	}
	
	void Free()
	{
		m_StackCounter = 0;
	}

private:
	unsigned int	m_Size			= 0;
	unsigned int	m_StackCounter	= 0;
	T*				m_Pointer		= nullptr;
};

class Message : public ISerialise
{
	friend class MessageBus;

public:
	bool m_Free = true;

	static Message* CreateMessage(void* _sender = nullptr, void* _recipient = nullptr)
	{
		Message* _message = new Message();

		_message->m_Sender		= _sender;
		_message->m_Recipient	= _recipient;

		return _message;
	}

	static void CopyMessage(Message* _destination, Message* _source)
	{
		CopySerialise(_destination, _source);

		_destination->m_Free		= _source->m_Free;
		_destination->m_Recipient	= _source->m_Recipient;
		_destination->m_Sender		= _source->m_Sender;
	}

	void* Sender()
	{
		return m_Sender;
	}

	void* Recipient()
	{
		return m_Recipient;
	}

private:
	void* m_Sender;
	void* m_Recipient;
};