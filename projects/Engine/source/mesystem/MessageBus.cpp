#include "MessageBus.h"
#include "Message.h"
#include "System.h"

MessageBus MessageBus::m_MessageBus;

void MessageBus::AttachSystem(System& _system)
{
	m_Systems.push_back(&_system);
}

void MessageBus::PostMessage(Message* _message)
{
	m_WriteQueue->push_back(_message);
}

void MessageBus::ReadQueue()
{
	for (System* _system : m_Systems)
	{
		printf("NOMultiThread - System Finished\n");

		for (Message* _message : *m_ReadQueue)
			if (_message->m_Recipient == nullptr || _message->m_Recipient == _system)
				_system->IncomingMessage(_message);
	}	
}

std::vector<Message*>* MessageBus::Queue()
{
	return m_ReadQueue;
}

std::vector<Message*>* MessageBus::WriteQueue()
{
	return m_WriteQueue;
}

void MessageBus::SwapQueue()
{
	for (Message* _message : *m_ReadQueue)
		if(_message)
			if(_message->m_Free)
				delete _message;

	m_ReadQueue->clear();

	if (m_ReadQueue == &m_MessageQueue_01)
	{
		m_ReadQueue		= &m_MessageQueue_02;
		m_WriteQueue	= &m_MessageQueue_01;
	}
	else
	{
		m_ReadQueue		= &m_MessageQueue_01;
		m_WriteQueue	= &m_MessageQueue_02;
	}
}