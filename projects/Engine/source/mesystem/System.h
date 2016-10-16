#pragma once
#include "MessageBus.h"
#include "Message.h"

#include <atomic>
#include <thread>
#include <chrono>

class Message;

class System
{
	friend class MessageBus;

public:
	System()
	{
		MessageBus::_MessageBus().AttachSystem(*this);
	}
	
	//Threading
	static void Thread(System* _system, bool* _update)
	{
		Message* _read = Message::CreateMessage();

		while (true)
		{
			if (*_update && _system->m_Finished == false)
			{
				for (Message* _message : *MessageBus::_MessageBus().Queue())
				{
					Message::CopyMessage(_read, _message);

					if (_read->Recipient() == nullptr || _read->Recipient() == _system)
						_system->IncomingMessage(_read);
				}

				printf("MultiThread - System Finished\n");

				_system->m_Finished = true;
			}
		}
	}

	//Threading
	bool m_Finished = false;

protected:
	virtual void HandleMessage(Message* _message) = 0;

private:
	void IncomingMessage(Message* _message)
	{
		_message->m_Index = 0;

		HandleMessage(_message);
	};

};